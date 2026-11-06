#include "Gerente.hpp"
#include <stdexcept>

Gerente::Gerente() : Pessoa() {}

Gerente::Gerente(int idPessoa, const std::string& nome, const std::string& cpf,
                 const std::string& email, const std::string& telefone,
                 const std::string& senha)
    : Pessoa(idPessoa, nome, cpf, email, telefone, senha) {}

Gerente::~Gerente() {}

void Gerente::cadastrarProduto(Produto& produto) {
    if (produto.getPreco() < 0.0) {
        throw std::invalid_argument("Produto com preco invalido.");
    }
}

void Gerente::editarProduto(Produto& produto, const std::string& nome, const std::string& descricao,
                            double preco, const std::string& categoria) {
    if (preco < 0.0) {
        throw std::invalid_argument("O preco nao pode ser negativo.");
    }
    produto.setNome(nome);
    produto.setDescricao(descricao);
    produto.setPreco(preco);
    produto.setCategoria(categoria);
}

void Gerente::adicionarEstoqueProduto(Produto& produto, int quantidade) {
    if (quantidade <= 0) {
        throw std::invalid_argument("Quantidade a adicionar deve ser maior que zero.");
    }
    produto.adicionarEstoque(quantidade);
}

bool Gerente::removerEstoqueProduto(Produto& produto, int quantidade) {
    if (quantidade <= 0) {
        return false;
    }
    return produto.removerEstoque(quantidade);
}

void Gerente::definirEstoqueMinimoProduto(Produto& produto, int quantidadeMinima) {
    if (quantidadeMinima < 0) {
        throw std::invalid_argument("Estoque minimo nao pode ser negativo.");
    }
    produto.setQuantidadeMinima(quantidadeMinima);
}

void Gerente::atualizarStatusVenda(Venda& venda, StatusVenda novoStatus) {
    venda.atualizarSvenda(novoStatus);
}

void Gerente::atualizarStatusPagamento(Venda& venda, StatusPagamento novoStatus) {
    venda.atualizarSpagamento(novoStatus);
}

Desconto Gerente::cadastrarCupom(const std::string& codigo, double porcentagem, const std::string& dataValidade) {
    if (porcentagem < 0.0 || porcentagem > 100.0) {
        return Desconto(codigo, 0.0, dataValidade);
    }
    return Desconto(codigo, porcentagem, dataValidade);
}

void Gerente::aplicarCupomVenda(Venda& venda, const Desconto& cupom) {
    venda.aplicarCupom(cupom);
}