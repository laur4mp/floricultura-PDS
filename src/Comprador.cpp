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