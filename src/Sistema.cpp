#include "Sistema.hpp"
#include <stdexcept> 
#include <algorithm>
#include <ctime>

Sistema::Sistema() {}

Sistema::~Sistema() {

    for (std::size_t i = 0; i < _usuarios.size(); i++){
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


const std::vector<Pessoa*>& Sistema::getUsuarios() const {
    return _usuarios;
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

const Desconto* Sistema::buscarCupom(const std::string& codigo) const {
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

const std::vector<Desconto>& Sistema::getCupons() const {
    return _cupons;
} 

const std::vector<Venda>& Sistema::getVendas() const {
    return _vendas;
}


Venda* Sistema::buscarVenda(int idVenda) {

    for (std::size_t i = 0; i < _vendas.size(); i++){

        if (idVenda == _vendas[i].getIdVenda()){
            return &_vendas[i];
        }

    }
        
    return nullptr;

}

void Sistema::adicionarVenda(const Venda& venda) {
    if(buscarVenda(venda.getIdVenda()) != nullptr){
        throw std::invalid_argument("Ja existe uma Venda com esse id.");
    }
    _vendas.push_back(venda);
}





void Sistema::devolverEstoque(const Venda& venda) {
    if (venda.getStatusVenda() != StatusVenda::CANCELADO)
        throw std::logic_error("So eh possivel devolver o estoque de pedidos cancelados");
    
    for (const ItemPedido& it : venda.getItens()){
        Produto* produto = buscarProduto(it.getProduto().getIdProduto());
        if(produto != nullptr){
            produto->adicionarEstoque(it.getQuantidade()); 
        }
    }
}

int Sistema::proximoIdUsusario() const {

    int maior = 0;
    for (const Pessoa* p : _usuarios){
        maior = std::max(maior, p->getIdPessoa());
    }

    return maior + 1;

}

int Sistema::proximoIdProduto() const {

    int maior = 0;
    for (const Produto& p : _produtos){
        maior = std::max(maior, p.getIdProduto());
    }

    return maior + 1;

}

int Sistema::proximoIdVenda() const {

    int maior = 0;

    for (const Venda& p : _vendas){
        maior = std::max(maior, p.getIdVenda());
    }

    return maior + 1;

}


static std::string dataDaquiA(int dias) {

    std::time_t t = std::time(nullptr) + static_cast<std::time_t>(dias) * 24 * 60 * 60;
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&t));

    return std::string(buffer);

}

Venda Sistema::finalizarPedido(Comprador& comprador, const Endereco& endereco, 
                               const Desconto& cupom, MetodoPagamento metodo){

    const std::vector<ItemPedido>& carrinho = comprador.consultarCarrinho();

    //aqui ta conferindo tudo antes de alterar alguma coisa
    if(carrinho.empty()){
        throw std::invalid_argument("O carrinho esta vazio.");
    }

    if(endereco.getNomeDest().empty()){
        throw std::invalid_argument("Informe o endereco de entrega.");
    }

    //conferindo item por item
    for(const ItemPedido& item : carrinho){

        Produto* produto = buscarProduto(item.getProduto().getIdProduto());

        if(produto == nullptr){
            throw std::runtime_error("Produto nao encontrado: " + item.getProduto().getNome());
        }

        if(item.getQuantidade() > produto->getQuantidadeEstoque()){
            throw std::runtime_error("Estoque insuficiente para " + produto->getNome());
        }

    }

    //dar baixa nos produtos
    for(const ItemPedido& item : carrinho){
        buscarProduto(item.getProduto().getIdProduto())->removerEstoque(item.getQuantidade());
    }


    //monta a venda, reaproveitando a funcao do Comprador
    Venda venda = comprador.fazerPedido(proximoIdVenda(), endereco, metodo);
    if(cupom.ehValido()){
        venda.setDataEntrega(dataDaquiA(2));
        venda.setHorarioEntregaPrevisao("Entre 08:00 e 18:00");

    }

    //guarda a venda no vector de _vendas
    _vendas.push_back(venda);
    return venda;


}