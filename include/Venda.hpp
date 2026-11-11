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

enum class MetodoPagamento { DINHEIRO, CARTAO, PIX };

/**
 * @class Venda
 * @brief Representa um pedido realizado, contendo itens, dados de entrega e pagamento.
 */
class Venda {
private:
    int _idVenda;
    int _avaliacao;
    std::string _nomeDestina;
    int _idPessoa;
    double _valorTotal;
    std::vector<ItemPedido> _itens;
    Endereco _enderecoEntrega;
    StatusVenda _statusVenda;
    StatusPagamento _statusPagamento;
    Desconto _descontoAplicado;
    std::string _dataEntrega;
    std::string _horarioEntregaPrevisao;
    MetodoPagamento _metodoPagamento;

    /** @brief Recalcula o valor total da venda considerando os itens e descontos. */
    void calcularValorTotal();

public:
    // Construtores e Destrutor
    Venda();

    /** @brief Inicializa uma venda com ID, ID do cliente, endereço e destinatário. */
    Venda(int idVenda, int idPessoa, int avaliacao, const Endereco& enderecoEntrega, const std::string& nomeDestina);

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
    void avaliar(int nota);
    

    // Getters
    int getIdVenda() const;
    int getIdPessoa() const;
    const std::string& getNomeDestina() const;
    double getValorTotal() const;
    /** @brief Retorna o desconto (cupom) aplicado ao pedido. */
    const Desconto& getDescontoAplicado() const;

    /** @brief Retorna a lista de itens inclusos no pedido. */
    const std::vector<ItemPedido>& getItens() const;

    int getAvaliacao() const;
    const std::string& getDataEntrega() const;
    const std::string& getHorarioEntregaPrevisao() const;
    const Endereco& getEnderecoEntrega() const;

    StatusVenda getStatusVenda() const;
    StatusPagamento getStatusPagamento() const;
    MetodoPagamento getMetodoPagamento() const;

    // Setters
    void setDataEntrega(const std::string& dataEntrega);
    void setHorarioEntregaPrevisao(const std::string& horarioPrevisao);
    void setEnderecoEntrega(const Endereco& endereco);
    void setMetodoPagamento(MetodoPagamento m);
};


#endif