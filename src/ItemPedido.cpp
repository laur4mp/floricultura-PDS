#include "ItemPedido.hpp"

using namespace std;

ItemPedido::~ItemPedido() {}

const Produto& ItemPedido::getProduto() const {}

int ItemPedido::getQuantidade() const {}

double ItemPedido::calcularPrecoTotal() const {}

void ItemPedido::informarDados() const {}

double ItemPedido::calcularFrete(const Endereco& endereco) const {}