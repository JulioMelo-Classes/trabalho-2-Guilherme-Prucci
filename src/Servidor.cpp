#include"servidor.hpp"
#include<vector>



Servidor::Servidor(unsigned int id_servidor, string nome, Usuario &dono){
    this->id_servidor=id_servidor;
    this->nome=nome;
    this->dono=&dono;
}

vector<Canaltexto> Servidor::get_canaistexto(){
    return this->canaistexto;
}

string Servidor::get_nome(){
    return this->nome;
}

string Servidor::get_codigo(){
    return this->convite;
}

unsigned int Servidor::get_id(){
    return this->id_servidor;
}

void Servidor::set_descricao(string descricao){
    this->descricao=descricao;
}

void Servidor::set_convite(string convite){
    this->convite=convite;
}

void Servidor::adicionar_canaltexto(Canaltexto cadastrando){
    this->canaistexto.push_back(cadastrando);
} 