#ifndef mensagem_hpp
#define mensagem_hpp
#include "usuario.hpp"
#include <iostream>
#include <string>
#include <time.h>


class Mensagem{
    private:
    unsigned int id_mensagem;
    string data_hora, conteudo;
    Usuario* enviada_por;

    public:
    Mensagem(unsigned int id_mensagem, string data_hora, string conteudo, Usuario* enviada_por);
    unsigned int get_id();
    string get_data_hora();
    string get_conteudo();
    Usuario* get_enviada_por();
};
#endif