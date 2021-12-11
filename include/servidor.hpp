#ifndef servidor_hpp
#define servidor_hpp
#include"canaltexto.hpp"
#include"usuario.hpp" 
#include<string>
using namespace std;

class Servidor
{
    private:
    unsigned int id_servidor;
    string nome, descricao, convite;
    vector<Canaltexto> canaistexto;
    vector<Usuario*> participantes;

    public:
    Usuario* dono;
    Servidor(unsigned int id_servidor, string nome, Usuario &dono);
    string get_nome();
    string get_codigo();
    unsigned int get_id();
    void set_descricao(string descricao);
    void set_convite(string convite);
};
#endif