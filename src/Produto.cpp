#include "Produto.hpp"
#include <stdexcept>

Produto::Produto()
    : _idProduto(0), _preco(0.0), _quantidadeEstoque(0), _quantidadeMinima(0) {}

Produto::Produto(int id, const std::string& nome, const std::string& descricao,
                 const std::string& categoria, double preco,
                 const std::string& enderecoImagem, int estoqueInicial, int estoqueMinimo)
    : _idProduto(id), _nome(nome), _descricao(descricao), _categoria(categoria),
      _preco(preco), enderecoImagem(enderecoImagem),
      _quantidadeEstoque(estoqueInicial), _quantidadeMinima(estoqueMinimo) {
    if (id <= 0)                throw std::invalid_argument("Produto: id deve ser positivo.");
    if (nome.empty())           throw std::invalid_argument("Produto: nome nao pode ser vazio.");
    if (categoria.empty())      throw std::invalid_argument("Produto: categoria nao pode ser vazia.");
    if (preco < 0.0)            throw std::invalid_argument("Produto: preco nao pode ser negativo.");
    if (estoqueInicial < 0)     throw std::invalid_argument("Produto: estoque inicial nao pode ser negativo.");
    if (estoqueMinimo < 0)      throw std::invalid_argument("Produto: estoque minimo nao pode ser negativo.");
}

Produto::~Produto() {}

int Produto::getIdProduto() const { return _idProduto; }

const std::string& Produto::getNome() const { return _nome; }

void Produto::setNome(const std::string& nome) {
    if (nome.empty()) throw std::invalid_argument("Produto: nome nao pode ser vazio.");
    _nome = nome;
}

const std::string& Produto::getDescricao() const { return _descricao; }

void Produto::setDescricao(const std::string& descricao) { _descricao = descricao; }

const std::string& Produto::getCategoria() const { return _categoria; }

void Produto::setCategoria(const std::string& categoria) {
    if (categoria.empty()) throw std::invalid_argument("Produto: categoria nao pode ser vazia.");
    _categoria = categoria;
}

double Produto::getPreco() const { return _preco; }

void Produto::setPreco(double preco) {
    if (preco < 0.0) throw std::invalid_argument("Produto: preco nao pode ser negativo.");
    _preco = preco;
}

const std::string& Produto::getEnderecoImagem() const { return enderecoImagem; }

void Produto::setEnderecoImagem(const std::string& enderecoImagem) {
    this->enderecoImagem = enderecoImagem;
}

int Produto::getQuantidadeEstoque() const { return _quantidadeEstoque; }

int Produto::getQuantidadeMinima() const { return _quantidadeMinima; }

void Produto::setQuantidadeMinima(int quantidade) {
    if (quantidade < 0) throw std::invalid_argument("Produto: estoque minimo nao pode ser negativo.");
    _quantidadeMinima = quantidade;
}

void Produto::adicionarEstoque(int quantidade) {
    if (quantidade <= 0) {
        throw std::invalid_argument("Produto: quantidade a adicionar deve ser positiva.");
    }
    _quantidadeEstoque += quantidade;
}

bool Produto::removerEstoque(int quantidade) {
    if (quantidade <= 0) {
        throw std::invalid_argument("Produto: quantidade a remover deve ser positiva.");
    }
    if (_quantidadeEstoque < quantidade) {
        return false;  
    }
    _quantidadeEstoque -= quantidade;
    return true;
}

bool Produto::verificarEstoqueMinimo() const {
    return _quantidadeEstoque <= _quantidadeMinima;
}