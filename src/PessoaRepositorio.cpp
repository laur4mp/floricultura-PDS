#include "PessoaRepositorio.hpp"
#include <algorithm> //para remover o | caso alguem digite
#include <fstream>
#include <sstream>
#include <stdexcept>

PessoaRepositorio::PessoaRepositorio(const std::string& caminho) : _caminho(caminho) {}

std::string PessoaRepositorio::limpar(std::string s) const {
    std::replace(s.begin(), s.end(), '|', '/');
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

void PessoaRepositorio::gravar(const std::vector<Pessoa>& pessoas) const {
    std::ofstream out(_caminho, std::ios::trunc); //logica de apagar arquivo e escrever de novo
    if (!out.is_open()) {
        throw std::runtime_error("Não foi possível gravar o arquivo " + _caminho);
    }

    for (const auto& p : pessoas) {
        // endereços primeiro associados a pessoa, cada um ocupa uma linha "E" e depois a linha "P" da própria pessoa

        for (const auto& e : p.getEnderecos()) {
            out << "E|" << limpar(e.getNomeDest()) << '|' << limpar(e.getCep()) << '|'
                << limpar(e.getRua()) << '|' << limpar(e.getNumero()) << '|'
                << limpar(e.getBairro()) << '|' << limpar(e.getComplemento()) << '|'
                << limpar(e.getCidade()) << '|' << limpar(e.getEstado()) << '\n';
        }

        out << "P|" << p.getIdPessoa() << '|' << limpar(p.getNome()) << '|'
            << limpar(p.getCpf()) << '|' << limpar(p.getEmail()) << '|'
            << limpar(p.getTelefone()) << '|' << limpar(p.getSenha()) << '\n';
    }
}

std::vector<Pessoa> PessoaRepositorio::carregar() const {
    std::vector<Pessoa> pessoas;
    std::vector<Endereco> enderecos; // endereços já lidos, esperando a linha da sua pessoa

    std::ifstream in(_caminho);
    if (!in.is_open()) return pessoas;

    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;

        std::vector<std::string> c;
        std::stringstream ss(linha);
        std::string campo;

        while (std::getline(ss, campo, '|')) c.push_back(campo);
        if (linha.back() == '|') c.push_back(""); //o getline descarta o último campo vazio

        if (c[0] == "E" && c.size() == 9) {
            enderecos.push_back(Endereco(c[1], c[2], c[3], c[4], c[5], c[6], c[7], c[8]));

        } else if (c[0] == "P" && c.size() == 7) {
            Pessoa p(std::stoi(c[1]), c[2], c[3], c[4], c[5], c[6]);
            for (const auto& e : enderecos) p.adicionarEndereco(e);
            enderecos.clear();
            pessoas.push_back(p);

        } else {
            throw std::runtime_error("PessoaRepositorio: linha corrompida: " + linha);
        }
    }
    return pessoas;
}