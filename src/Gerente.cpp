#include "Gerente.hpp"

Gerente::Gerente() : Pessoa() {}

Gerente::Gerente(int idPessoa, const std::string& nome, const std::string& cpf,
                 const std::string& email, const std::string& telefone,
                 const std::string& senha)
    : Pessoa(idPessoa, nome, cpf, email, telefone, senha) {}

Gerente::~Gerente() {}

void Gerente::cadastrarProduto(Produto&) {}

void Gerente::editarProduto(Produto&, const std::string&, const std::string&,
                            double, const std::string&) {}

void Gerente::adicionarEstoqueProduto(Produto&, int) {}

bool Gerente::removerEstoqueProduto(Produto&, int) { return false; }

void Gerente::definirEstoqueMinimoProduto(Produto&, int) {}

void Gerente::atualizarStatusVenda(Venda&, StatusVenda) {}

void Gerente::atualizarStatusPagamento(Venda&, StatusPagamento) {}

Desconto Gerente::cadastrarCupom(const std::string&, double, const std::string&) {
    return Desconto();
}

void Gerente::aplicarCupomVenda(Venda&, const Desconto&) {}