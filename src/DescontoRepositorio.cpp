#include "DescontoRepositorio.hpp"
#include <algorithm> //para remover o | caso alguem digite
#include <fstream>
#include <sstream>
#include <stdexcept>

DescontoRepositorio::DescontoRepositorio(const std::string& caminho) : _caminho(caminho) {}

std::string DescontoRepositorio::limpar(std::string s) const { //tarabalha na parte de corrigir formatações add diferentes
    std::replace(s.begin(), s.end(), '|', '/');
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

void DescontoRepositorio::gravar(const std::vector<Desconto>& descontos) const {
    std::ofstream out(_caminho, std::ios::trunc);//mesma logica de apgar oq ta no arquivo antes de escrever
    if (!out.is_open()) {
        throw std::runtime_error("Não foi possível gravar o arquivo " + _caminho);
    }

    for (const auto& d : descontos) {
        out << limpar(d.getCupom()) << '|'
            << std::to_string(d.getPercentual()) << '|'
            << limpar(d.getDataValidade()) << '\n';
    }
}

std::vector<Desconto> DescontoRepositorio::carregar() const {
    std::vector<Desconto> descontos;
    std::ifstream in(_caminho);
    if (!in.is_open()) return descontos;
    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;

        std::vector<std::string> c;
        std::stringstream ss(linha);
        std::string campo;
        while (std::getline(ss, campo, '|')) c.push_back(campo);
        if (linha.back() == '|') c.push_back(""); // o getline descarta o último campo se ele for vazio (ex.: validade)

        if (c.size() != 3) {
            throw std::runtime_error("DescontoRepositorio: linha corrompida: " + linha);
        }
        descontos.push_back(Desconto(c[0], std::stod(c[1]), c[2]));
    }
    return descontos;
}