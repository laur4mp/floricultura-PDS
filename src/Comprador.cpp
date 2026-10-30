#include "Comprador.hpp"

using namespace std;

Comprador::~Comprador() {}


std::vector<Produto> Comprador::pesquisarProdutos(
    const std::vector<Produto>& produtos,
    const std::string& nome
) const {}

std::vector<Produto> Comprador::filtrarProdutos(
    const std::vector<Produto>& produtos,
    const std::string& categoria
) const {}

void Comprador::verDetalhesProduto(const Produto& produto) const {}

void Comprador::favoritarProduto(const Produto& produto) {}

void Comprador::desfavoritarProduto(const Produto& produto) {}

const std::vector<Produto>& Comprador::consultarProdutosFavoritos() const {}

Endereco Comprador::selecionarEndereco() const {}

Venda Comprador::fazerPedido(const std::vector<ItemPedido>& itens) {}

void Comprador::escolherMetodoPagamento(Venda& venda) {}

StatusVenda Comprador::acompanharPedido(const Venda& venda) const {}

void Comprador::cancelarPedido(Venda& venda) {}

const std::vector<Venda>& Comprador::consultarHistoricoCompras() const {}