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

std::vector<Venda>& Sistema::getVendas() {
    return _vendas;
}

const std::vector<Venda>& Sistema::getVendas() const {
    return _vendas;
}

Venda* Sistema::buscarVenda(int idVenda) {
    for (Venda& v : _vendas)
        if (v.getIdVenda() == idVenda) return &v;
    return nullptr;
}

void Sistema::adicionarVenda(const Venda& v) {
    _vendas.push_back(v);
}

int Sistema::proximoIdVenda() const{
    int maior = 0;
    for (const Venda& v : _vendas)
        if(v.getIdVenda() > maior){
            maior = v.getIdVenda();
        }
    return maior + 1;
}

Venda Sistema::finalizarPedido(Comprador& c, const Endereco& end,
                               MetodoPagamento metodo, const Desconto* cupom) {
    
    for (const ItemPedido& it : c.consultarCarrinho()) {
        Produto* p = buscarProduto(it.getProduto().getIdProduto());
        if (!p || p->getQuantidadeEstoque() < it.getQuantidade())
            throw std::runtime_error("Estoque insuficiente: " + it.getProduto().getNome());
    }
    Venda v = c.fazerPedido(proximoIdVenda(), end, metodo);
   
    for (const ItemPedido& it : c.consultarCarrinho())
        buscarProduto(it.getProduto().getIdProduto())->removerEstoque(it.getQuantidade());
    if (cupom && cupom->ehValido()) v.aplicarCupom(*cupom);
    _vendas.push_back(v);
    c.limparCarrinho();
    return v;
}

void Sistema::devolverEstoque(const Venda& venda) {
    if (venda.getStatusVenda() != StatusVenda::CANCELADO)
        throw std::logic_error("So eh posivel devolver o estoque de pedidos cancelados");
    
    for(const ItemPedido& it : venda.getItens()){
        Produto* p = buscarProduto(it.getProduto().getIdProduto());
        if(p) p->adicionarEstoque(it.getQuantidade());
    }
}