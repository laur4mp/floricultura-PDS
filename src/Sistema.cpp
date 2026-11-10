#include "Sistema.hpp"
#include <stdexcept>

Sistema::Sistema() {}

Sistema::~Sistema() {
    for(std::size_t i = 0; i < _usuarios.size(); i++){
        delete _usuarios[i];
    }
}

Pessoa* Sistema::autenticar(const std::string& email, const std::string& senha) const {
    for (std::size_t i = 0; i < _usuarios.size(); i++){
        if(email == _usuarios[i]->getEmail() && senha == _usuarios[i]->getSenha()){
            return _usuarios[i];
        }
    }
    return nullptr;
}


void Sistema::adicionarUsuario(Pessoa* usuario){
    if(usuario == nullptr){
        throw std::invalid_argument("Usuario nulo.");
    }
    for(std::size_t i = 0; i < _usuarios.size(); i++){
        if(usuario->getEmail() == _usuarios[i]->getEmail()){
            delete usuario;
            throw std::invalid_argument("Ja existe um usuario com esse e-mail.");
        }
    }
    _usuarios.push_back(usuario);
}


Produto* Sistema::buscarProduto(int idProduto){
    for(std::size_t i = 0; i < _produtos.size(); i++){
        if(idProduto == _produtos[i].getIdProduto()){
            return &_produtos[i];
        }
    }
    return nullptr;
}

void Sistema::adicionarProduto(const Produto& produto){
    if(nullptr != buscarProduto(produto.getIdProduto())){
        throw std::invalid_argument("Ja existe um produto com esse id.");
    }
    _produtos.push_back(produto);
}

const Desconto* Sistema::buscarCupom(const std::string& codigo) const{
    for(std::size_t i = 0; i < _cupons.size(); i++){
        if(codigo == _cupons[i].getCupom()){
            return &_cupons[i];
        }
    }
    return nullptr;
}

void Sistema::adicionarCupom(const Desconto& cupom){
    if(cupom.getCupom().empty()){
        throw std::invalid_argument("Cupom sem codigo.");
    }
    if(nullptr != buscarCupom(cupom.getCupom())){
        throw std::invalid_argument("Ja existe um cupom com esse codigo"); 
    }
    _cupons.push_back(cupom);
}


const std::vector<Produto>& Sistema::getProdutos() const {
    return _produtos;
} 

const std::vector<Desconto>& Sistema::getCupons() const{
    return _cupons;
} 