#include "mensagem.hpp"

Mensagem::Mensagem(unsigned int id_mensagem, string data_hora, string conteudo, Usuario* enviada_por){
    
}

unsigned int Mensagem::get_id(){
    return this->id_mensagem;
}

string Mensagem::get_data_hora(){
    return this->data_hora;
}

string Mensagem::get_conteudo(){
    return this->conteudo;
}

Usuario* Mensagem::get_enviada_por(){
    return this->enviada_por;
}