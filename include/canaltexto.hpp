#ifndef canaltexto_hpp
#define canaltexto_hpp
#include "mensagem.hpp"
#include <string>
#include <vector>

class Canaltexto
{
    private:
    unsigned int id_canal;
    string nome;
    Usuario* dono;
    vector <Mensagem> mensagens;

    public:
    Usuario* get_dono();
    vector<Mensagem> get_mensagens();
    int get_id();
    string get_nome();
    Canaltexto(string nome, Usuario* dono, unsigned int id_canal);
};

#endif