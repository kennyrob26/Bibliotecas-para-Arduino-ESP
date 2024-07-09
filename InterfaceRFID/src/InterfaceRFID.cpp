/*========================--- CLASSE INTERFACE RFID ========================
*
*   Uma classe simples que visa facilitar o uso de TAG RFID
*   Basicamente cria uma interface amigável para a classe <MFRC522.h>
*
============================================================================*/



/*========================--- BIBLIOTECAS ---========================*/

#include "InterfaceRFID.h"
#include <string.h>
#include <SPI.h>
#include "MFRC522.h"

/*=========================--- CONSTANTES ---=========================*/

#define DEBUG_MODE      0    //mensagens de DEBUG: 1 habilita / 0 desabilita

#define PINO_SS         21
#define PINO_RST        22

#define SIZE_BUFFER     18   //Com verificador de 2 bytes
#define SIZE_BLOCK      16   //Sem o verificador de 2 bytes

const uint8_t sectorTrailer[17] = {0, 3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63};

/*==========================--- FUNÇÕES ---===========================*/

boolean BlockIsSectorTrailer(uint8_t bloco);
void cortarString(String Texto, uint8_t qtdCortes, String cortes[] );


/*==========================--- OBJETOS ---===========================*/

MFRC522::MIFARE_Key key;            //Objeto de autenticação

MFRC522::StatusCode status;         //Código de retorno da autenticação

MFRC522 mfrc522(PINO_SS, PINO_RST); //Definicao dos pinos utilizados



/*===============--- CLASSE INTERNA NOMECAMPO ---=====================*/

/*___PRIVATES___*/

//Valida se os Blocos iniciais e finais contém valor
boolean InterfaceRFID::NomeCampo::validarBlocos()
{
    boolean blocosSetado = (this->blocoInicial > 0) && (this->blocoFinal > 0); 
    if(! blocosSetado)
    {
        Serial.println("GRAVACAO CANCELADA! Os blocos para o campo não foram setados!");
        return false;
    }
    else
        return true;
}

//Valida se a quantidade de caracteres é compátivel com os blocos setados
boolean InterfaceRFID::NomeCampo::validarQuantidadeCaracteres(String Texto)
{
    uint8_t qtdCaracteres = Texto.length();
    if(qtdCaracteres > this->maxCaracteres)
    {
        Serial.printf("GRAVACAO CANCELADA! O texto é maior que '%d' caracteres", maxCaracteres);
        return false;
    }
    else    
        return true;
    
}

/*____PUBLICS____*/

InterfaceRFID::NomeCampo::NomeCampo(InterfaceRFID* rfid)
{
    this->rfid = rfid;
}

void InterfaceRFID::NomeCampo::setBlocos(uint8_t inicio, uint8_t fim)
{
    this->blocoInicial = inicio;
    this->blocoFinal = fim;

    this->qtdBloco = (blocoFinal - blocoInicial) + 1;
    this->maxCaracteres = qtdBloco * 16;
}

void InterfaceRFID::NomeCampo::setSetor(uint8_t setor)
{
    //Pega o bloco anterior ao sector trailer
    uint8_t blocoFinal = (sectorTrailer[setor] - 1);
    uint8_t blocoInicial = 0;

    if(blocoFinal == 2)
        blocoInicial = 1;
    else   
        blocoInicial = blocoFinal - 2;

    this->setBlocos(blocoInicial, blocoFinal);
}

void InterfaceRFID::NomeCampo::gravar(String Texto)
{
    //Validações antes da gravação
    if (! (this->validarBlocos() && this->validarQuantidadeCaracteres(Texto)))
    {
        return;
    }
    
    //Recortar a String em pedacos do tamanho dos blocos
    String pedacos[qtdBloco] = {""};
    cortarString(Texto, qtdBloco, pedacos);

    //Realiza a gravação
    uint8_t indice = 0;
    for(uint8_t bloco = blocoInicial; bloco <= blocoFinal; bloco++)
    {
        rfid->gravarBloco(bloco, pedacos[indice]);
        indice++;
    }

}


String InterfaceRFID::NomeCampo::ler()
{
    this->leitura = ""; 
    for(uint8_t i = blocoInicial; i <= blocoFinal; i++)
    {
        if(BlockIsSectorTrailer(i))
            continue;

        this->leitura += rfid->lerBloco(i);
    } 
    this->leitura.trim();
    return this->leitura;
}

/*===============--- CLASSE EXTERNA INTERFACERFID ---=================*/

void InterfaceRFID::iniciarRFID()
{
    mfrc522.PCD_Init();
}

boolean InterfaceRFID::existirTag()
{
    //Verifica se esxiste um cartão
    if (! mfrc522.PICC_IsNewCardPresent())
        return false;

    //Seleciona um dos cartões
    if(! mfrc522.PICC_ReadCardSerial())
        return false;

    Serial.print("\n\n====--- Tag Detectada ---====\n");
    mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
    Serial.println("");

    return true;
}

void InterfaceRFID::encerrarComunicacaoTag()
{
    mfrc522.PICC_CMD_HLTA;
    mfrc522.PCD_StopCrypto1();
}

void InterfaceRFID::gravarBloco(uint8_t bloco, String texto)
{
    //Verificando se o bloco é um sector trailer
    if(BlockIsSectorTrailer(bloco))
    {
        Serial.printf("Bloco[%d] - GRAVACAO NAO AUTORIZADA: O bloco e um 'sector trailer'", bloco);
        return;
    }

    for (byte i=0; i < 6; i++)
        key.keyByte[i] = 0xFF;
    
    //Armazenando os dados no buffer
    uint8_t buffer[SIZE_BLOCK] = {0};
    uint8_t tamanho;

    // # é o delimitador do que será inserido
    tamanho = texto.length();

    uint8_t conta = 0;
    for(uint8_t i; i < tamanho; i++)
    {
        buffer[i] = (int)texto[i];
    }

    for(uint8_t i = tamanho; i < SIZE_BLOCK; i++)
        buffer[i] = ' ';

    //Autenticação
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(mfrc522.uid));
    if(status != MFRC522::STATUS_OK)
    {
        Serial.printf("Bloco[%d] - Falha na Autenticação: ", bloco);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }

    //Gravacao no bloco
    status = mfrc522.MIFARE_Write(bloco, buffer, SIZE_BLOCK);
    if(status != MFRC522::STATUS_OK)
    {
        Serial.printf("Bloco[%d] - A gravação falhou: ", bloco);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    else
        Serial.printf("Bloco[%d] - Gravacao bem sucedida\n", bloco);
        Serial.printf("Bloco[%d] - Gravou: %s\n", bloco, texto.c_str());
}


String InterfaceRFID::lerBloco(uint8_t bloco)
{

    for (uint8_t i = 0; i < 6; i++ )
        key.keyByte[i] = 0xFF;

    //Armazena os dados da leitura
    uint8_t buffer[SIZE_BUFFER] = {0};
    uint8_t tamanho = SIZE_BUFFER;

    //Autenticação
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, bloco, &key, &(mfrc522.uid));
    if(status != MFRC522::STATUS_OK)
    {
        Serial.printf("Bloco[%d] - Falha na Autenticação: ", bloco);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return "0";
    }

    //Realizando a leitura
    status = mfrc522.MIFARE_Read(bloco, buffer, &tamanho);
    if(status != MFRC522::STATUS_OK)
    {
        Serial.printf("Bloco[%d] - Falha na leitura: ", bloco);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return "0";
    }
    
    if(DEBUG_MODE)
    {
        Serial.print(F("\nDados do bloco ["));
        Serial.print(bloco);
        Serial.print(F("]:"));
    }

    //Coleta os dados do bloco
    String conteudo;
    for (uint8_t i = 0; i < SIZE_BLOCK; i++)
    {
        if (DEBUG_MODE) (Serial.write(buffer[i]));
        conteudo += (char)buffer[i];
    }
    conteudo.trim();
    //Serial.println(" ");

    return conteudo;
}




/*========================--- FUNÇÕES ---=========================*/

/*Verifica se um bloco passado é um 'setor trailer'*/
boolean BlockIsSectorTrailer(uint8_t bloco)
{
    for (uint8_t i = 0; i < 17; i++)
    {
        if(sectorTrailer[i] == bloco)
            return true;
    }

    return false;

}

//Corta o Texto em pedaços que cabem no bloco e adiciona em cortes[]
void cortarString(String Texto, uint8_t qtdCortes, String cortes[] )
{
    //Corta a string em pedaços de tamanho 16
    uint8_t tamanhoPedaco = 0;
    for(int i=0; i < qtdCortes; i++)
    {
        String pedaco = Texto.substring(tamanhoPedaco, tamanhoPedaco += SIZE_BLOCK);
        cortes[i] = pedaco;
    }

    if(DEBUG_MODE)
    {
        Serial.printf("\n\nIniciando o Recorte da String: %s\n\n", Texto.c_str());
        for(int i=0; i < qtdCortes; i++)
        {
            Serial.printf ("Recorte[%d] : %s \n", i, cortes[i].c_str());
        }
        Serial.printf("\n\n");
    }
}

/*========================--- END CLASSE ---=========================*/