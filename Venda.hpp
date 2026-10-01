#ifndef VENDA_HPP
#define VENDA_HPP

#include <string>
#include <vector>
#include "ItemPedido.hpp"
#include "Endereco.hpp"
#include "Desconto.hpp"

enum class StatusVenda {
    PROCESSAMENTO,
    ENVIADO,
    ENTREGUE,
    CANCELADO
};

enum class StatusPagamento {
    AGUARDANDO_PAGAMENTO,
    PAGO
};

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
    Venda(int idVenda, const std::string& cpfCliente, const Endereco& enderecoEntrega, const std::string& _nomeDestina);
    ~Venda();

   
    void adicionarItem(const ItemPedido& item);
    bool removerItem(int idItem);
    void calcularValorTotal();
    void aplicarCupom(const Desconto& desconto);
    //status
    void atualizarSvenda(StatusVenda novoStatus);
    void atualizarSpagamento(StatusPagamento novoStatus);
    //recuperar e modificar
    std::string getNomeDest();
    int getIdVenda();
    std::string getCpfCliente();
    double getValorTotal();
    
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



