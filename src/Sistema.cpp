#include"Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

	string Sistema::set_data_hora(){
    struct tm* horario;
    time_t tempo;
    time(&tempo);
    horario=localtime(&tempo);
    return "<"+to_string(horario->tm_yday)+"/"+to_string(horario->tm_mon+1)+"/"+to_string(horario->tm_year+1900)+" - "+to_string(horario->tm_hour)+":"+to_string(horario->tm_min);
	}

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
	int count_user=usuarios.size(), count_server=servidores.size();

	for (int i = 0; i < count_user; i++)
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
			return"";
		}
	}
}else return "usuario nao logado";
	return "erro em list_participants";
}

string Sistema::list_channels(int id) {
if (verificar_logado(id)){
	vector<Canaltexto> lista = servidores[usuariosLogados[id].first].get_canaistexto();
	int count_canaltexto=lista.size();

	for (int i = 0; i < count_canaltexto; i++)
	{
		cout<<lista[i].get_nome()<<endl;
	}
} else "usuario nao logado";
	return "erro em list_channels";
}

string Sistema::create_channel(int id, const string nome) {
if (verificar_logado(id)){
	Usuario* dono;
	int id_server=usuariosLogados[dono->get_id()].first;
	int count_user=usuarios.size();
		for (int i = 0; i < count_user; i++)
	{
		if (id==usuarios[i].get_id())
		{
			dono=&usuarios[i];
		}	
	}
	Canaltexto cadastrando(nome ,dono ,id_canaltexto);
	servidores[id_server].adicionar_canaltexto(cadastrando);
	id_canaltexto++;
	return "canal de texto criado";

} else return "usuario nao logado";
	return "erro emcreate_channel";
}

string Sistema::remove_channel(int id, const string nome) {
if (verificar_logado(id)){
	Usuario* sol;
	bool sair;
	int  count_user=usuarios.size(), count_server=servidores.size(), id_server, count_canal, local;
	for (int i = 0; i < count_user; i++){
		if (id==usuarios[i].get_id()){
			sol=&usuarios[i];
		}
		
	}

	for (int i = 0; i < count_server; i++){
		count_canal=servidores[i].get_canaistexto().size();
		for (int a = 0; a < count_canal; a++){
			if(servidores[i].get_canaistexto()[a].get_nome()==nome){
				id_server=servidores[i].get_id();
				local=i;
				sair=true;
				break;
			}
		}
		if (sair==true) break;
	}
	
	count_canal= servidores[local].get_canaistexto().size();


	for (int i = 0; i < count_canal; i++){
		if (servidores[local].get_canaistexto()[i].get_nome()==nome){
			if (servidores[local].get_canaistexto()[i].get_dono()==sol){
				servidores[local].get_canaistexto().erase(servidores[local].get_canaistexto().begin()+i);
				return "canal de texto removido";
			}else return "voce nao é o dono do canal";
		}
	}return "canal nao encontrado";

} else return "usuario nao logado";
	return "erro em remove_channel";
}

string Sistema::enter_channel(int id, const string nome) {
if (verificar_logado(id)){
	int count_user=usuarios.size() , count_server=servidores.size();
	int id_server;
		for (int i = 0; i < count_user; i++){
			if (id==usuarios[i].get_id()){
				if (usuariosLogados[usuarios[i].get_id()].first==0){
					return "entre primeiro em um server";
				}else{
				 	id_server=usuariosLogados[usuarios[i].get_id()].first;
				 	break;
				}
			}
		}
	int count_canaistexto = servidores[id_server].get_canaistexto().size();
		for (int i = 0; i < count_canaistexto; i++){
			if (nome==servidores[id_server].get_canaistexto()[i].get_nome()){
				usuariosLogados[id].second=servidores[id_server].get_canaistexto()[i].get_id();
			}
		}return "nenhum canal com esse nome";
		
} else return "usuario nao logado";
	return "erro em enter_channel";
}

string Sistema::leave_channel(int id) {
if (verificar_logado(id)){
	int count_user=usuarios.size();

	for (int i = 0; i < count_user; i++){
		if (usuarios[i].get_id()==id){
			usuariosLogados[id].second=0;
			return "saiu do canal";
		}
	}
} else "usuario nao logado";
	return "erro em leave_channel";
}

string Sistema::send_message(int id, const string mensagem) {
if (verificar_logado(id)){

	string corpo_mensagem;
	Usuario* remetente;
	int count_user, count_server, count_canal, count_mensagem;
	int id_server, id_canal;
	for (int i = 0; i < count_user; i++){
		if (id==usuarios[i].get_id()){
			remetente=&usuarios[i];
		}	
	}
	id_canal=usuariosLogados[id].second;
	string data_hora = set_data_hora();
	Mensagem enviando(id_mensagem, data_hora, mensagem, remetente);
	id_mensagem++;
	for (int i = 0; i < count_server; i++){
		count_canal=servidores[i].get_canaistexto().size();
		for (int a = 0; a < count_canal; a++){
			if (servidores[i].get_canaistexto()[a].get_id()==id_canal){
				servidores[i].get_canaistexto()[a].get_mensagens().push_back(enviando);
			}
		}
	}
	

	
} else "usuario nao logado";
	return "erro em send_message";
}

string Sistema::list_messages(int id) {
if (verificar_logado(id)){

	Usuario* remetente;
	int count_user, count_server=servidores.size(), count_canal, count_mensagem;
	int id_server, id_canal;
	for (int i = 0; i < count_user; i++){
		if (id==usuarios[i].get_id()){
			remetente=&usuarios[i];
		}	
	}

	for (int i = 0; i < count_server; i++){
		count_canal=servidores[i].get_canaistexto().size();
		for (int a = 0; a < count_canal; a++){
			count_mensagem=servidores[i].get_canaistexto()[a].get_mensagens().size();
			if(count_mensagem!=0){
				for (int b = 0; b < count_mensagem; b++)
				{
					cout<<servidores[i].get_canaistexto()[a].get_mensagens()[b].get_enviada_por()->get_nome();
					cout<<servidores[i].get_canaistexto()[a].get_mensagens()[b].get_data_hora()<<": ";
					cout<<servidores[i].get_canaistexto()[a].get_mensagens()[b].get_conteudo()<<endl;
				}
			}else return "Sem mensagens para exebir";
		}
	}
} else "usuario nao logado";
	return "list_messages NÃO IMPLEMENTADO";
}

