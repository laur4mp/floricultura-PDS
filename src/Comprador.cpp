#include "Comprador.hpp"

using namespace std;


std::vector<Produto> Comprador::pesquisarProdutos(
    const std::vector<Produto>& produtos,
    const std::string& nome
) const {
    vector<Produto> resultado;

    for (const Produto& produto : produtos){
        if(produto.getNome().find(nome) != string::npos){
            resultado.push_back(produto);
        }
    }
    return resultado;
}

std::vector<Produto> Comprador::filtrarProdutos(
    const std::vector<Produto>& produtos,
    const std::string& categoria
) const {
    vector<Produto> resultado;

    for (const Produto& produto : produtos) {
        if (produto.getCategoria() == categoria) {
            resultado.push_back(produto);
        }
    }

    return resultado;
}

void Comprador::favoritarProduto(const Produto& produto) {
     for (const Produto& favorito : _produtosFavoritos) {
        if (favorito.getIdProduto() == produto.getIdProduto()) {
            return;
        }
    }

    _produtosFavoritos.push_back(produto);
}

void Comprador::desfavoritarProduto(const Produto& produto) {
    for (auto it = _produtosFavoritos.begin();
         it != _produtosFavoritos.end(); ++it) {

        if (it->getIdProduto() == produto.getIdProduto()) {
            _produtosFavoritos.erase(it);
            return;
        }
    }
}

const std::vector<Produto>& Comprador::consultarProdutosFavoritos() const {
    return _produtosFavoritos;
}


Venda Comprador::fazerPedido(
    int idVenda,
    const std::vector<ItemPedido>& itens,
    const Endereco& enderecoEntrega) {
        Venda venda(
        idVenda,
        getIdPessoa(),
        enderecoEntrega,
        enderecoEntrega.getNomeDest()
        );

        for (const ItemPedido& item : itens) {
            venda.adicionarItem(item);
        }

        _historicoPedidos.push_back(venda);

        return venda;
    }

StatusVenda Comprador::acompanharPedido(const Venda& venda) const {
        return venda.getStatusVenda();
    }

void Comprador::cancelarPedido(Venda& venda) {
    if (venda.getStatusVenda() == StatusVenda::PROCESSAMENTO){
        venda.atualizarSvenda(StatusVenda::CANCELADO);
    }
}

const std::vector<Venda>& Comprador::consultarHistoricoCompras() const {
     return _historicoPedidos;
}

void Comprador::aplicarCupomVenda(Venda& venda, const Desconto& cupom) {
    venda.aplicarCupom(cupom);
}

void Comprador::adicionarAoCarrinho(const ItemPedido& item) {
    _carrinho.push_back(item);
}

const std::vector<ItemPedido>& Comprador::consultarCarrinho() const {
    return _carrinho;
}

void Comprador::limparCarrinho() {
    _carrinho.clear();
}