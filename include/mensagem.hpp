#ifndef mensagem_hpp
#define mensagem_hpp
#include "usuario.hpp"
#include <iostream>
#include <string>


class Mensagem{
    private:
    unsigned int id_mensagem;
    string data_hora, conteudo;
    Usuario* enviada_por;

    public:
    void enviar_mensagem();
};
#endif