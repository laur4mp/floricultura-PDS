#include "Pessoa.hpp"

Pessoa::Pessoa() : _idPessoa(0) {}

Pessoa::Pessoa(int, const std::string&, const std::string&, const std::string&,
               const std::string&, const std::string&) : _idPessoa(0) {}

Pessoa::~Pessoa() {}

int Pessoa::getIdPessoa() const { return 0; }

std::string Pessoa::getNome() const { return ""; }
void Pessoa::setNome(const std::string&) {}

std::string Pessoa::getCpf() const { return ""; }
void Pessoa::setCpf(const std::string&) {}

std::string Pessoa::getEmail() const { return ""; }
void Pessoa::setEmail(const std::string&) {}

std::string Pessoa::getTelefone() const { return ""; }
void Pessoa::setTelefone(const std::string&) {}

std::string Pessoa::getSenha() const { return ""; }
void Pessoa::setSenha(const std::string&) {}

const std::vector<Endereco>& Pessoa::getEnderecos() const { return _enderecos; }
void Pessoa::adicionarEndereco(const Endereco&) {}
void Pessoa::removerEndereco(std::size_t) {}