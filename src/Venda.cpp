#include "Venda.hpp"

Venda::Venda() : _idVenda(0), _valorTotal(0.0),  _statusVenda(StatusVenda::PROCESSAMENTO), _statusPagamento(StatusPagamento::AGUARDANDO_PAGAMENTO) {}

Venda::Venda(int idVenda, const std::string& cpfCliente, const Endereco& enderecoEntrega, const std::string& _nomeDestina)
    : _idVenda(idVenda), _cpfCliente(cpfCliente), _enderecoEntrega(enderecoEntrega), _nomeDestina(_nomeDestina), _valorTotal(0.0), _statusVenda(StatusVenda::PROCESSAMENTO), _statusPagamento(StatusPagamento::AGUARDANDO_PAGAMENTO) {}

Venda::~Venda() {}

void Venda::adicionarItem(const ItemPedido& item) {
    _itens.push_back(item);
    calcularValorTotal();
}

bool Venda::removerItem(int idItem) {

    for (auto it = _itens.begin(); it != _itens.end(); ++it) {
        if (it->getProduto().getIdProduto() == idItem) { 
            _itens.erase(it);
            calcularValorTotal();
            return true;
        }
    }
    return false;
}

void Venda::calcularValorTotal() {
    double totalBruto = 0.0;
    for (const auto& item : _itens) {
        totalBruto += item.calcularPrecoTotal();
    }
    
    _valorTotal = _descontoAplicado.aplicar(totalBruto);
}

void Venda::aplicarCupom(const Desconto& desconto) {
    _descontoAplicado = desconto;
    calcularValorTotal();
}

void Venda::atualizarSvenda(StatusVenda novoStatus) {
    _statusVenda = novoStatus;
}

void Venda::atualizarSpagamento(StatusPagamento novoStatus) {
    _statusPagamento = novoStatus;
}

std::string Venda::getNomeDestina() {
    return _nomeDestina;
}

int Venda::getIdVenda() const {
    return _idVenda;
}

std::string Venda::getCpfCliente() {
    return _cpfCliente;
}

double Venda::getValorTotal() {
    return _valorTotal;
}

const std::vector<ItemPedido>& Venda::getItens() {
    return _itens;
}

std::string Venda::getDataEntrega() {
    return _dataEntrega;
}

void Venda::setDataEntrega(const std::string& dataEntrega) {
    _dataEntrega = dataEntrega;
}

std::string Venda::getHorarioEntregaPrevisao() {
    return _horarioEntregaPrevisao;
}

void Venda::setHorarioEntregaPrevisao(const std::string& horarioPrevisao) {
    _horarioEntregaPrevisao = horarioPrevisao;
}

Endereco Venda::getEnderecoEntrega() {
    return _enderecoEntrega;
}

void Venda::setEnderecoEntrega(const Endereco& endereco) {
    _enderecoEntrega = endereco;
}

StatusVenda Venda::getStatusVenda() {
    return _statusVenda;
}

StatusPagamento Venda::getStatusPagamento() {
    return _statusPagamento;
}