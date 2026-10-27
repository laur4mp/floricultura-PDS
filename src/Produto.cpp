#include "Produto.hpp"

Produto::Produto() 
    : _idProduto(0), _preco(0.0), _quantidadeEstoque(0), _quantidadeMinima(0) {}

Produto::Produto(int id, const std::string& nome, const std::string& descricao, 
                 const std::string& categoria, double preco, 
                 const std::string& enderecoImagem, int estoqueInicial, int estoqueMinimo)
    : _idProduto(id), _nome(nome), _descricao(descricao), _categoria(categoria), 
      _preco(preco), enderecoImagem(enderecoImagem), 
      _quantidadeEstoque(estoqueInicial), _quantidadeMinima(estoqueMinimo) {}

Produto::~Produto() {}

int Produto::getIdProduto() const{
    return _idProduto;
}

std::string Produto::getNome(){
    return _nome;
}

void Produto::setNome(const std::string& nome) {
    _nome = nome;
}

std::string Produto::getDescricao() {
    return _descricao;
}

void Produto::setDescricao(const std::string& descricao) {
    _descricao = descricao;
}

std::string Produto::getCategoria() {
    return _categoria;
}

void Produto::setCategoria(const std::string& categoria) {
    _categoria = categoria;
}

double Produto::getPreco() {
    return _preco;
}

void Produto::setPreco(double preco) {
    _preco = preco;
}

std::string Produto::getEnderecoImagem() {
    return enderecoImagem;
}

void Produto::setEnderecoImagem(const std::string& enderecoImagem) {
    this->enderecoImagem = enderecoImagem;
}

int Produto::getQuantidadeEstoque() {
    return _quantidadeEstoque;
}

int Produto::getQuantidadeMinima() {
    return _quantidadeMinima;
}

void Produto::setQuantidadeMinima(int quantidade) {
    _quantidadeMinima = quantidade;
}

void Produto::adicionarEstoque(int quantidade) {
    if (quantidade > 0) {
        _quantidadeEstoque += quantidade;
    }
}

bool Produto::removerEstoque(int quantidade) {
    if (quantidade > 0 && _quantidadeEstoque >= quantidade) {
        _quantidadeEstoque -= quantidade;
        return true;
    }
    return false;
}

bool Produto::verificarEstoqueMinimo() {
    return _quantidadeEstoque <= _quantidadeMinima;
}