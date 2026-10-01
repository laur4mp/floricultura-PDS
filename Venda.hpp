/**
 * @file Venda.hpp
 * @brief Estruturas e gerenciamento do ciclo de vida de uma venda no sistema.
 */
#ifndef VENDA_HPP
#define VENDA_HPP

#include <string>
#include <vector>
#include "ItemPedido.hpp"
#include "Endereco.hpp"
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
    std::_nomeDestina;
    std::string _cpfCliente;
    std::vector<ItemPedido> _itens;
    double _valorTotal;
    
    //entrega
    std::string _dataEntrega;
    std::string _horarioEntregaPrevisao;
    Endereco _enderecoEntrega;

    StatusVenda _statusVenda;
    StatusPagamento _statusPagamento;
    Desconto _descontoAplicado;

    public:
    // constutores
    Venda();
    /** @brief Inicializa uma venda com ID, CPF do cliente, endereço e destinatário. */
    Venda(int idVenda, const std::string& cpfCliente, const Endereco& enderecoEntrega, const std::string& _nomeDestina);
    ~Venda();

    /** @brief Adiciona um item ao carrinho/pedido da venda. */
    void adicionarItem(const ItemPedido& item);
    /** @brief Remove um item do pedido pelo seu identificador. */
    bool removerItem(int idItem);
    /** @brief Recalcula o valor total da venda considerando os itens e descontos. */
    void calcularValorTotal();
    /** @brief Aplica um cupom de desconto sobre o valor do pedido. */
    void aplicarCupom(const Desconto& desconto);
    //status
    void atualizarSvenda(StatusVenda novoStatus);
    void atualizarSpagamento(StatusPagamento novoStatus);

    //recuperar e modificar
    std::string getNomeDestina();
    int getIdVenda();
    std::string getCpfCliente();
    double getValorTotal();

    /** @brief Retorna a lista de itens inclusos no pedido. */
    const std::vector<ItemPedido>& getItens(); //vetor com produtos
    
    std::string getDataEntrega();
    void setDataEntrega(const std::string& dataEntrega);

    std::string getHorarioEntregaPrevisao();
    void setHorarioEntregaPrevisao(const std::string& horarioPrevisao);

    Endereco getEnderecoEntrega();
    void setEnderecoEntrega(const Endereco& endereco);

    StatusVenda getStatusVenda();
    StatusPagamento getStatusPagamento();
};

#endif



