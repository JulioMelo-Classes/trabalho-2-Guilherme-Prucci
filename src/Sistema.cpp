#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

	int id_usuario=1, id_servidor=1, id_canaltexto=1, id_mensagem=1;


	bool Sistema::verificar_logado(int id){
		int count_user=usuarios.size();
		map<int ,pair<unsigned int, unsigned int> >::iterator it;
			for (it = usuariosLogados.begin() ; it !=usuariosLogados.end() ; it++){
        		if (it->first==id){
					return true;
				}
    		}
			return false;
	}

	vector<Usuario> Sistema::get_usuarios(){
		return usuarios;
	}

    bool usuario_novo(Usuario teste, vector<Usuario>lista){
        unsigned int tamanho=lista.size();
        string email_teste=teste.get_email();

        if (tamanho==0){
            return true;
        }

        for (int i = 0; i < tamanho; i++){
            if (email_teste== lista[i].get_email()){
                return false;
            }
        }
        return true;
    }

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
	Usuario cadastrando=Usuario(nome, email, senha, id_usuario);
	id_usuario++;
	if (usuario_novo(cadastrando, this->usuarios)){
		this->usuarios.push_back(cadastrando);
		return "usuario cadastrado";
	}
	else return "usuario ja existente";
	return "erro em create_user";

}

std::string Sistema::delete_user (const std::string email, const std::string senha){
	unsigned int count=usuarios.size();
	for (int i = 0; i < count; i++){
		if (usuarios[i].get_email()==email){
			if (usuarios[i].get_senha()==senha){
				usuarios.erase(usuarios.begin()+i);
				return "Usuario deletado";
			}else return "senha incorreta";
			
		}else return "Usuario nao existe";
	}
	return "erro em delete_user";
}

string Sistema::login(const string email, const string senha) {
	unsigned int count=usuarios.size();
	for (int i = 0; i < count; i++){
		if (usuarios[i].get_email()==email&&usuarios[i].get_senha()==senha){
			if(!verificar_logado(usuarios[i].get_id())){
			pair<unsigned int, unsigned int> loc;
			loc.first=0;
			loc.second=0;
			usuariosLogados[usuarios[i].get_id()]=loc;
			return "login feito";
			}else return "usuario ja esta logado";
		}
	}
	return "usuario ou senha incorretos";
	return "erro em login";
}


string Sistema::disconnect(int id) {
	if(verificar_logado(id)){
		usuariosLogados.erase(id);
		return "usuario disconectado";
	}
	else return "usuario nao esta logado";

}

string Sistema::create_server(int id, const string nome) {
	if (verificar_logado(id)){
	vector<Usuario> usuarios=get_usuarios();
	Usuario* dono;
	int count=usuarios.size(), count_server=servidores.size();

	for (int i = 0; i < count; i++)
	{
		if (id==usuarios[i].get_id())
		{
			dono=&usuarios[i];
		}	
	}
	Servidor cadastrando=Servidor(id_servidor, nome, *dono);
	id_servidor++;
	for (int i = 0; i < count_server; i++)
	{
		if (cadastrando.get_nome()==servidores[i].get_nome())
		{
			return "Servidor com esse nome ja existe";
		}
	}
	servidores.push_back(cadastrando);
	return "Servidor criado";
	}else return "usuario nao logado";
	return "erro em create_server";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
if(verificar_logado(id)){
	int count=servidores.size(), count_user=usuarios.size();
	Usuario* sol;

		for (int i = 0; i < count_user; i++){
		if (id==usuarios[i].get_id()){
			sol=&usuarios[i];
			}	
		}

	for (int i = 0; i < count; i++){
		if (nome==servidores[i].get_nome()){
			if (sol==servidores[i].dono){
				servidores[i].set_descricao(descricao);
				return "Descrição do servidor modificada!";
			} else return "Voce nao pode alterar a descricao de um servidor que nao foi criado por você";
		}else return "Servidor não existe";
	}	
} else return "usuario nao logado";
return "erro em set_server_desc";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
if(verificar_logado(id)){
	int count=servidores.size(), count_user=usuarios.size();
	Usuario* sol;

		for (int i = 0; i < count_user; i++){
		if (id==usuarios[i].get_id()){
			sol=&usuarios[i];
			}	
		}

	for ( int i = 0; i < count; i++){
		if (nome==servidores[i].get_nome()){
			if (sol==servidores[i].dono){
				servidores[i].set_convite(codigo);
				if (codigo=="") return "codigo de convite do servidor removido!";
				else return "codigo de convite do servidor modificada!";
			} else return "Voce nao pode alterar a descricao de um servidor que nao foi criado por você";
		}else return "Servidor não existe";
	}
}else return "usuario nao esta logado";
	return "erro em set_server_invite_code";
}

string Sistema::list_servers(int id) {
if(verificar_logado(id)){
	int count=servidores.size();
	for (int i = 0; i < count; i++)
	{
		cout<<servidores[i].get_nome()<<endl;
	}
	return"";
}else return "usuario nao logado";
}

string Sistema::remove_server(int id, const string nome) {
if(verificar_logado(id)){
	int count_user=usuarios.size(), count_server=servidores.size();
	Usuario* sol;
	pair<unsigned int, unsigned int> n_loc;
	n_loc.first=0;
	n_loc.second=0;
	for (int i = 0; i < count_user; i++){
		if (id==usuarios[i].get_id()){
			sol=&usuarios[i];
		}
	}

	for (int i = 0; i < count_server; i++){
		if (nome==servidores[i].get_nome()){
			if (sol==servidores[i].dono){
				servidores.erase(servidores.begin()+i);
				for (int a = 0; a < count_user; a++)
				{
					if (usuariosLogados[a].first==i+1)
					{
						usuariosLogados[a].first=0;
						usuariosLogados[a].second=0;
					}
				}
				return "servidor excluido";
			}else "voce nao e o dono do servidor";
		}else "esse servidor nao existe";
	}
}else return "usuario nao logado";
	return "erro em remove_server";
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
if(verificar_logado(id)){
	int count_server=servidores.size();
	pair <unsigned int, unsigned int> n_loc;
	for (int i = 0; i < count_server; i++){
		if (nome==servidores[i].get_nome()){
			if (codigo==servidores[i].get_codigo()){
				n_loc.first=i+1;
				n_loc.second=0;
				return"Entrou no servidor com sucesso";
			}else if (servidores[i].get_codigo()!="")
			{
				return "Servidor requer código de convite";
			}else return "codigo de convite errado";
		}
	}return "nome de servidor nao encontrado";
}else return "usuario nao logado";
	return "erro em enter_server";
}

string Sistema::leave_server(int id, const string nome) {
if (verificar_logado(id)){
	int count_server=servidores.size();
	pair<unsigned int, unsigned int> n_log;
		n_log.first=0;
		n_log.second=0;
		for (int i = 0; i < count_server; i++){
			if (nome==servidores[i].get_nome()){
				usuariosLogados[id]=n_log;
				return "deixou o servidor";
			}
		}return "servidor nao existe";
}else return "usuario nao logado";
	
	return "erro em leave_server";
}

string Sistema::list_participants(int id) {
if(verificar_logado(id)){
	map<int, pair<unsigned int, unsigned int>>::iterator it;
	for ( it =usuariosLogados.begin(); it != usuariosLogados.end(); it++)
	{
		if (usuariosLogados[id].first==it->second.first)
		{
			cout<<usuarios[it->first].get_nome()<<endl;
			return "";
		}
	}
}else return "usuario nao logado";
	return "erro em list_participants";
}

string Sistema::list_channels(int id) {
if (verificar_logado(id)){
	


} else "usuario nao logado";
	return "erro em list_channels";
}

string Sistema::create_channel(int id, const string nome) {
if (verificar_logado(id)){
	

	
} else "usuario nao logado";
	return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::remove_channel(int id, const string nome) {
if (verificar_logado(id)){
	

	
} else "usuario nao logado";
	return "remove_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
if (verificar_logado(id)){
	

	
} else "usuario nao logado";
	return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
if (verificar_logado(id)){
	

	
} else "usuario nao logado";
	return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
if (verificar_logado(id)){
	

	
} else "usuario nao logado";
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
if (verificar_logado(id)){
	

	
} else "usuario nao logado";
	return "list_messages NÃO IMPLEMENTADO";
}

