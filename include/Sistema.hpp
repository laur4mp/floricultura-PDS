/**
 * @file Sistema.hpp
 * @brief Guarda os dados do sistema (usuarios, produtos e cupons) e faz o login.
 */
#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <string>
#include <vector>
#include "Pessoa.hpp"
#include "Produto.hpp"
#include "Desconto.hpp"
#include "Venda.hpp"
#include "Endereco.hpp"
#include "Comprador.hpp"



/**
 * @class Sistema
 * @brief Central de dados da floricultura.
 *
 * Os usuarios sao guardados como ponteiros (Pessoa*) para preservar o tipo
 * real de cada um (Gerente ou Comprador). O Sistema eh o dono desses objetos
 * e os apaga no destrutor.
 */
class Sistema {
private:
    std::vector<Pessoa*> _usuarios; 
    std::vector<Produto> _produtos;
    std::vector<Desconto> _cupons;
    std::vector<Venda> _vendas;

public:
    Sistema();
    ~Sistema();

    /** Um sistema nao pode ser copiado - shallow copy. */
    Sistema(const Sistema&) = delete;
    Sistema& operator=(const Sistema&) = delete;

    // --- usuarios e login ---

    /** @brief Cadastra um usuario; o Sistema passa a ser o dono do objeto.
     *  @throw std::invalid_argument se for nulo ou se o e-mail ja existir. */
    void adicionarUsuario(Pessoa* usuario);

    /** @brief Confere e-mail e senha. @return o usuario, ou nullptr se nao conferir. */
    Pessoa* autenticar(const std::string& email, const std::string& senha) const;

    /** 
     * @brief Retorna a lista de usuários cadastrados no sistema.
     * @return Referência constante ao vetor de ponteiros para Pessoa.
     */
    const std::vector<Pessoa*>& getUsuarios() const;

    /**
     * @brief acha um usuario pelo id.
     * @return o usuario com esse id ou nullptr
     */
    Pessoa* buscarUsuario(int idPessoa) const;

    // --- produtos ---

    /** @throw std::invalid_argument se ja existir produto com o mesmo id. */
    void adicionarProduto(const Produto& produto);

    /** @return o produto com esse id, ou nullptr. (Use na hora; nao guarde o ponteiro.) */
    Produto* buscarProduto(int idProduto);

    const std::vector<Produto>& getProdutos() const;

    // --- cupons ---

    /** @throw std::invalid_argument se o codigo for vazio ou ja existir. */
    void adicionarCupom(const Desconto& cupom);

    /** @return o cupom com esse codigo, ou nullptr. */
    const Desconto* buscarCupom(const std::string& codigo) const;

    const std::vector<Desconto>& getCupons() const;

    //vendas

    /**
     * @brief Adiciona uma nova venda ao histórico do sistema.
     * @param venda Objeto Venda a ser inserido.
     * @throw std::invalid_argument se já existir uma venda cadastrada com o mesmo ID.
     */
    void adicionarVenda(const Venda& venda);

    /**
     * @brief Busca uma venda cadastrada pelo seu ID.
     * @param idVenda Identificador único da venda.
     * @return Ponteiro para a Venda correspondente, ou nullptr se não for encontrada.
     */
    Venda* buscarVenda(int idVenda);

    /**
     * @brief Retorna o histórico de todas as vendas registradas no sistema.
     * @return Referência constante ao vetor de Vendas.
     */
    const std::vector<Venda>& getVendas() const;



    // --- geracao de ids ---

    /**
     * @brief Calcula o próximo ID disponível para um novo usuário.
     * @return O maior ID de usuário atual acrescido de 1 (ou 1 se não houver usuários).
     */
    int proximoIdUsusario() const;

    /**
     * @brief Calcula o próximo ID disponível para um novo produto.
     * @return O maior ID de produto atual acrescido de 1 (ou 1 se não houver produtos).
     */
    int proximoIdProduto() const;

    /**
     * @brief Calcula o próximo ID disponível para uma nova venda.
     * @return O maior ID de venda atual acrescido de 1 (ou 1 se não houver vendas).
     */ 
    int proximoIdVenda() const;


   // --- funcoes que envolvem varias classes ---
    
    /**
     * @brief Processa e finaliza uma compra realizada por um comprador.
     * @details Valida o carrinho e o endereço de entrega, garante a disponibilidade de estoque de cada item,
     *          dá baixa no estoque dos produtos, calcula previsões de entrega, aplica o cupom, se
     *          válido e registra a venda.
     * @param comprador Instância do Comprador que está realizando o pedido.
     * @param endereco Endereço selecionado para a entrega.
     * @param cupom Cupom de desconto aplicado (se for válido).
     * @return A Venda gerada e registrada no sistema.
     * @throw std::invalid_argument se o carrinho estiver vazio ou o destinatário do endereço não estiver informado.
     * @throw std::runtime_error se algum produto do carrinho não for encontrado ou se houver estoque insuficiente.
     */ 
    Venda finalizarPedido(
         Comprador & comprador, 
        const Endereco& endereco,
        const Desconto* cupom 
        
    );

    /**
     * @brief Devolve ao estoque do sistema os itens de uma venda cancelada.
     * @param venda Objeto Venda que foi cancelado.
     * @throw std::logic_error se o status da venda for diferente de StatusVenda::CANCELADO.
     */
    void devolverEstoque(const Venda& venda);
    


};
#endif