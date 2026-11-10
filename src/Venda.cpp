#include "Venda.hpp"
#include <stdexcept>

Venda::Venda()
    : _idVenda(0), _valorTotal(0.0),
      _statusVenda(StatusVenda::PROCESSAMENTO),
      _statusPagamento(StatusPagamento::AGUARDANDO_PAGAMENTO) {}

Venda::Venda(int idVenda, int idPessoa, const Endereco& enderecoEntrega,
             const std::string& nomeDestina)
    : _idVenda(idVenda), _idPessoa(idPessoa), _nomeDestina(nomeDestina), _valorTotal(0.0),
      _enderecoEntrega(enderecoEntrega),
      _statusVenda(StatusVenda::PROCESSAMENTO),
      _statusPagamento(StatusPagamento::AGUARDANDO_PAGAMENTO) {
    if (idVenda <= 0)          throw std::invalid_argument("Venda: id deve ser positivo.");
    if (idPessoa <= 0)         throw std::invalid_argument("Venda: id do cliente deve ser positivo.");
    if (nomeDestina.empty())    throw std::invalid_argument("Venda: nome do destinatario nao pode ser vazio.");
}

Venda::~Venda() {}

void Venda::adicionarItem(const ItemPedido& item) {
    if (item.getQuantidade() <= 0) {  
        throw std::invalid_argument("Venda: quantidade do item deve ser positiva.");
    }
    _itens.push_back(item);
    calcularValorTotal();
}

bool Venda::removerItem(int idItem) {
    if (idItem <= 0) {
        throw std::invalid_argument("Venda: id do item deve ser positivo.");
    }
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

    double total = _descontoAplicado.aplicar(totalBruto);
    _valorTotal = (total < 0.0) ? 0.0 : total;
}

void Venda::aplicarCupom(const Desconto& desconto) {
    _descontoAplicado = desconto;
    calcularValorTotal();
}

void Venda::atualizarSvenda(StatusVenda novoStatus) {
    if (novoStatus == _statusVenda) return;

    if (_statusVenda == StatusVenda::ENTREGUE || _statusVenda == StatusVenda::CANCELADO) {
        throw std::logic_error("Venda: pedido finalizado, status nao pode mais mudar.");
    }
    if (novoStatus == StatusVenda::PROCESSAMENTO) {
        throw std::logic_error("Venda: nao e possivel voltar para PROCESSAMENTO.");
    }
    if (novoStatus == StatusVenda::ENTREGUE && _statusVenda != StatusVenda::ENVIADO) {
        throw std::logic_error("Venda: so e possivel entregar um pedido que foi enviado.");
    }
    if (novoStatus == StatusVenda::ENVIADO && _itens.empty()) {
        throw std::logic_error("Venda: nao e possivel enviar pedido sem itens.");
    }
    if (novoStatus == StatusVenda::ENTREGUE) {
    _statusPagamento = StatusPagamento::PAGO;   // pagamento na entrega
}
}

void Venda::atualizarSpagamento(StatusPagamento novoStatus) {
    if (novoStatus == _statusPagamento) return;

    if (_statusPagamento == StatusPagamento::PAGO) {
        throw std::logic_error("Venda: pagamento ja confirmado, nao pode ser revertido.");
    }
    if (_statusVenda == StatusVenda::CANCELADO) {
        throw std::logic_error("Venda: nao e possivel pagar um pedido cancelado.");
    }
    if (_itens.empty()) {
        throw std::logic_error("Venda: nao e possivel pagar um pedido sem itens.");
    }
    _statusPagamento = novoStatus;
}

const std::string& Venda::getNomeDestina() const { return _nomeDestina; }
int Venda::getIdVenda() const { return _idVenda; }
int Venda::getIdPessoa() const { return _idPessoa; }
double Venda::getValorTotal() const { return _valorTotal; }
const std::vector<ItemPedido>& Venda::getItens() const { return _itens; }

const std::string& Venda::getDataEntrega() const { return _dataEntrega; }

void Venda::setDataEntrega(const std::string& dataEntrega) {
    if (dataEntrega.empty()) throw std::invalid_argument("Venda: data de entrega nao pode ser vazia.");
    _dataEntrega = dataEntrega;
}

const std::string& Venda::getHorarioEntregaPrevisao() const { return _horarioEntregaPrevisao; }

void Venda::setHorarioEntregaPrevisao(const std::string& horarioPrevisao) {
    if (horarioPrevisao.empty()) throw std::invalid_argument("Venda: horario de entrega nao pode ser vazio.");
    _horarioEntregaPrevisao = horarioPrevisao;
}

const Endereco& Venda::getEnderecoEntrega() const { return _enderecoEntrega; }

void Venda::setEnderecoEntrega(const Endereco& endereco) {
    _enderecoEntrega = endereco;
}
const Desconto& Venda::getDescontoAplicado() const { return _descontoAplicado; }
StatusVenda Venda::getStatusVenda() const { return _statusVenda; }
StatusPagamento Venda::getStatusPagamento() const { return _statusPagamento; }
