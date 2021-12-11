#ifndef usuario_hpp
#define usuario_hpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Usuario{
    private:
        unsigned int id_usuario;   
        string nome, email, senha;

    public:
        Usuario(string nome, string id, string senha, unsigned int id_usuario);
        void cadastrar_conta(unsigned int id);
        string get_nome();
        string get_email();
        string get_senha();
        unsigned int get_id();
};
#endif