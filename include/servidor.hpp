#ifndef servidor_hpp
#define servidor_hpp
#include"canaltexto.hpp" 
#include<string>
#include<vector>
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
    vector<Canaltexto> get_canaistexto();
    string get_nome();
    string get_codigo();
    unsigned int get_id();
    void set_descricao(string descricao);
    void set_convite(string convite);
    void adicionar_canaltexto(Canaltexto cadastrando);
};
#endif