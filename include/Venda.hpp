/**
 * @file Venda.hpp
 * @brief Estruturas e gerenciamento do ciclo de vida de uma venda no sistema.
 */
#ifndef VENDA_HPP
#define VENDA_HPP

#include <string>
#include <vector>
#include "Endereco.hpp"
#include "ItemPedido.hpp"
#include "Desconto.hpp"

/**
 * @enum StatusVenda
 * @brief Define os estados possíveis do envio e processamento do pedido.
 */
enum class StatusVenda {
    PROCESSAMENTO,
    ENVIADO,
    ENTREGUE,
    CANCELADO
};

/**
 * @enum StatusPagamento
 * @brief Define a situação financeira da venda.
 */
enum class StatusPagamento {
    AGUARDANDO_PAGAMENTO,
    PAGO
};

/**
 * @class Venda
 * @brief Representa um pedido realizado, contendo itens, dados de entrega e pagamento.
 */
class Venda {
private:
    int _idVenda;
    std::string _nomeDestina;
    std::string _cpfCliente;
    double _valorTotal;
    std::vector<ItemPedido> _itens;
    Endereco _enderecoEntrega;
    StatusVenda _statusVenda;
    StatusPagamento _statusPagamento;
    Desconto _descontoAplicado;
    std::string _dataEntrega;
    std::string _horarioEntregaPrevisao;

    /** @brief Recalcula o valor total da venda considerando os itens e descontos. */
    void calcularValorTotal();

public:
    // Construtores e Destrutor
    Venda();

    /** @brief Inicializa uma venda com ID, CPF do cliente, endereço e destinatário. */
    Venda(int idVenda, const std::string& cpfCliente, const Endereco& enderecoEntrega, const std::string& nomeDestina);

    ~Venda();

    // Operações de Itens e Descontos
    /** @brief Adiciona um item ao carrinho/pedido da venda. */
    void adicionarItem(const ItemPedido& item);

    /** @brief Remove um item do pedido pelo seu identificador. */
    bool removerItem(int idItem);

    /** @brief Aplica um cupom de desconto sobre o valor do pedido. */
    void aplicarCupom(const Desconto& desconto);

    // Gestão de Estados
    void atualizarSvenda(StatusVenda novoStatus);
    void atualizarSpagamento(StatusPagamento novoStatus);

    // Getters
    int getIdVenda() const;
    const std::string& getCpfCliente() const;
    const std::string& getNomeDestina() const;
    double getValorTotal() const;

    /** @brief Retorna a lista de itens inclusos no pedido. */
    const std::vector<ItemPedido>& getItens() const;

    const std::string& getDataEntrega() const;
    const std::string& getHorarioEntregaPrevisao() const;
    const Endereco& getEnderecoEntrega() const;

    StatusVenda getStatusVenda() const;
    StatusPagamento getStatusPagamento() const;

    // Setters
    void setDataEntrega(const std::string& dataEntrega);
    void setHorarioEntregaPrevisao(const std::string& horarioPrevisao);
    void setEnderecoEntrega(const Endereco& endereco);
};

#endif