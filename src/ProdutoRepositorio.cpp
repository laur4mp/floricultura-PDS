#include "../include/ProdutoRepositorio.hpp"
#include <algorithm> // para remover o | caso alguém digite
#include <fstream>
#include <sstream>
#include <stdexcept>

ProdutoRepositorio::ProdutoRepositorio(const std::string& caminho) : _caminho(caminho) {}


std::string ProdutoRepositorio::limpar(std::string s) const {
    // n quebrar formato do arquivo
    std::replace(s.begin(), s.end(), '|', '/');
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

std::vector<Produto> ProdutoRepositorio::carregar() const {
    std::vector<Produto> produtos;
    std::ifstream in(_caminho);
    if (!in.is_open()) return produtos; // Retorna lista vazia se o arquivo ainda não existir

    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;

        std::vector<std::string> c;
        std::stringstream ss(linha);
        std::string campo;
        
        while (std::getline(ss, campo, '|')) {
            c.push_back(campo);
        }
        
        if (c.size() != 8) continue;   // linha vazia ou invalida

        produtos.push_back(Produto(
            std::stoi(c[0]), c[1], c[2], c[3], 
            std::stod(c[4]), c[5], std::stoi(c[6]), std::stoi(c[7])
        ));
    }
    return produtos;
}

void ProdutoRepositorio::gravar(const std::vector<Produto>& produtos) const {
    std::ofstream out(_caminho, std::ios::trunc); //basicamente apaga o arquivo e escreve de novo
    if (!out.is_open()) {
        throw std::runtime_error("Nao foi possivel gravar o arquivo " + _caminho);
    }

    for (const auto& p : produtos) {
        out << p.getIdProduto() << '|' 
            << limpar(p.getNome()) << '|' 
            << limpar(p.getDescricao()) << '|'
            << limpar(p.getCategoria()) << '|' 
             << std::to_string(p.getPreco()) << '|'
            << limpar(p.getEnderecoImagem()) << '|' 
            << p.getQuantidadeEstoque() << '|'
            << p.getQuantidadeMinima() << '\n';
    }
}