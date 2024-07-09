#ifndef RFID_H_INCLUDED
    #define RFID_H_INCLUDED

    #include <Arduino.h>

    class InterfaceRFID
    {
        private: 
            uint8_t bloco = 0;
            String texto = "";

        public:
            String lerBloco(uint8_t bloco);
            void gravarBloco(uint8_t bloco, String Texto);
            void iniciarRFID();
            boolean existirTag();
            void encerrarComunicacaoTag();

            class NomeCampo
            {
            private:
                InterfaceRFID* rfid;
                uint8_t blocoInicial;
                uint8_t blocoFinal;
                uint8_t qtdBloco;
                uint8_t maxCaracteres;

                String leitura;

                boolean validarQuantidadeCaracteres(String Texto);
                boolean validarBlocos();
            public:
                NomeCampo(InterfaceRFID* rfid);
                void setBlocos(uint8_t inicio, uint8_t fim);
                void setSetor(uint8_t setor);
                void gravar(String Texto);
                String ler();

            };
            

    };


#endif