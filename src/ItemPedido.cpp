#include "ItemPedido.hpp"
#include <stdexcept>
#include <cstdio>
#include <string>

using namespace std;

ItemPedido::ItemPedido(const Produto& produto, int quantidade)
    : _produtoPedido(produto), _quantidadePedida(quantidade){
        if (quantidade <= 0){
            throw std::invalid_argument("Quantidade deve ser positiva.");
        }
    }

ItemPedido::~ItemPedido() {}

const Produto& ItemPedido::getProduto() const {
    return _produtoPedido;
}

int ItemPedido::getQuantidade() const {
    return _quantidadePedida;
}

double ItemPedido::calcularPrecoTotal() const {
    return _produtoPedido.getPreco() * _quantidadePedida;
}

void ItemPedido::setQuantidade(int q){
    if(q <= 0){
        throw std::invalid_argument("Quantidade deve ser positiva.");
    }
    _quantidadePedida = q;
}

std::string ItemPedido::informarDados() const {

    char total[32];
    std::snprintf(total, sizeof total, "%.2f", calcularPrecoTotal());
    return std::to_string(_quantidadePedida) + " x " + _produtoPedido.getNome() + " (R$ " + total + ")";

}

double ItemPedido::calcularFrete(const Endereco& endereco) const {

    const std::string r = endereco.regiao();

    if( r == "Sudeste")
        return 13.0;

    if( r == "Sul")
        return 22.0;

    if( r == "Centro-Oeste")
        return 25.0;

    if( r == "Nordeste")
        return 30.0;

    if( r == "Norte")
        return 40.0;

    return 0.0;
}