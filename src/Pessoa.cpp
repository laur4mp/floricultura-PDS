#include "Pessoa.hpp"
#include <stdexcept>

Pessoa::Pessoa() 
    : _idPessoa(0), _nome(""), _cpf(""), _email(""), _telefone(""), _senha("") {}

Pessoa::Pessoa(int idPessoa, const std::string& nome, const std::string& cpf, 
               const std::string& email, const std::string& telefone, const std::string& senha)
    : _idPessoa(idPessoa), _nome(nome), _cpf(cpf), _email(email), _telefone(telefone), _senha(senha) {}

Pessoa::~Pessoa() {}

int Pessoa::getIdPessoa() const { 
    return _idPessoa; 
}

std::string Pessoa::getNome() const { 
    return _nome; 
}

void Pessoa::setNome(const std::string& nome) {
    _nome = nome;
}

std::string Pessoa::getCpf() const { 
    return _cpf; 
}

void Pessoa::setCpf(const std::string& cpf) {
    _cpf = cpf;
}

std::string Pessoa::getEmail() const { 
    return _email; 
}

void Pessoa::setEmail(const std::string& email) {
    _email = email;
}

std::string Pessoa::getTelefone() const { 
    return _telefone; 
}

void Pessoa::setTelefone(const std::string& telefone) {
    _telefone = telefone;
}

std::string Pessoa::getSenha() const { 
    return _senha; 
}

void Pessoa::setSenha(const std::string& senha) {
    _senha = senha;
}

const std::vector<Endereco>& Pessoa::getEnderecos() const { 
    return _enderecos; 
}

void Pessoa::adicionarEndereco(const Endereco& endereco) {
    _enderecos.push_back(endereco);
}

void Pessoa::removerEndereco(std::size_t indice) {
    if (indice >= _enderecos.size()) {
        throw std::out_of_range("Indice de endereco invalido.");
    }
    _enderecos.erase(_enderecos.begin() + indice);
}