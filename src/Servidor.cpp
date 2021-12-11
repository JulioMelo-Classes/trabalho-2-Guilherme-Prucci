#include"servidor.hpp"



Servidor::Servidor(unsigned int id_servidor, string nome, Usuario &dono){
    this->id_servidor=id_servidor;
    this->nome=nome;
    this->dono=&dono;
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
 