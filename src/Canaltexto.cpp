#include "canaltexto.hpp"

string Canaltexto::get_nome(){
    return this->nome;
}

int Canaltexto::get_id(){
    return this->id_canal;
}

Usuario* Canaltexto::get_dono(){
    return this->dono;
}

vector<Mensagem> Canaltexto::get_mensagens(){
    return this->mensagens;
}

Canaltexto::Canaltexto(string nome,Usuario* dono,unsigned int id_canal){

}