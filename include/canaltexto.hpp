#ifndef canaltexto_hpp
#define canaltexto_hpp
#include "mensagem.hpp"
#include "usuario.hpp"
#include <string>
#include <vector>

class Canaltexto
{
    private:
    unsigned int id_canal;
    string nome;
    Usuario* dono;
    vector <Mensagem> mensagens;
};

#endif