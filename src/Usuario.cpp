   #include "usuario.hpp"
   #include <vector>

    string Usuario::get_nome(){
        return this->nome;
    }
    
    string Usuario::get_email(){
        return this->email;
    }

    string Usuario::get_senha(){
        return this->senha;
    }

    unsigned int Usuario::get_id(){
        return this->id_usuario;
    }

    Usuario::Usuario(string nome, string email, string senha, unsigned int id_usuario){
        this->nome=nome;
        this->email=email;
        this->senha=senha;
        this->id_usuario=id_usuario;
    }


