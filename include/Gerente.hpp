/**
 * @file Gerente.hpp
 * @brief Declaração da classe Gerente.
 */
#ifndef GERENTE_HPP
#define GERENTE_HPP

#include "Pessoa.hpp"
#include "Produto.hpp"
#include "Venda.hpp"
#include "Desconto.hpp"

/**
 * @class Gerente
 * @brief Pessoa com permissão para administrar produtos, estoque, vendas e cupons.
 *
 * Herda de Pessoa e concentra as operações de gestão da loja:
 * cadastro e edição de produtos, controle de estoque, atualização
 * de status de vendas e pagamentos, e criação/aplicação de cupons de desconto.
 *
 * @see Pessoa
 * @see Produto
 * @see Venda
 * @see Desconto
 */
class Gerente : public Pessoa {
public:
    /**
     * @brief Cria o gerente padrão do sistema (login fixo: admin@tell.com - admin)
     */
    Gerente();

    /**
     * @brief Constrói um Gerente com seus dados básicos.
     * @param idPessoa Identificador único.
     * @param nome Nome completo.
     * @param cpf CPF do gerente.
     * @param email Endereço de e-mail.
     * @param telefone Telefone de contato.
     * @param senha Senha de acesso.
     */
    Gerente(int idPessoa, const std::string& nome, const std::string& cpf, 
            const std::string& email, const std::string& telefone, const std::string& senha);

    /**
     * @brief Destrutor.
     */
    ~Gerente() override;

    // produtos e estoques

    /**
     * @brief Instancia e cadastra um novo produto com os dados fornecidos.
     * @param IdProduto Identificador único do produto.
     * @param nome Nome do produto.
     * @param descricao Descrição detalhada.
     * @param categoria Categoria do produto.
     * @param preco Preço unitário.
     * @param imagem Caminho para a imagem do produto.
     * @param estoqueInicial Quantidade inicial em estoque.
     * @param estoqueMinimo Quantidade mínima para controle de alerta de estoque.
     * @return Objeto Produto instanciado com os dados passados.
     */
    Produto cadastrarProduto(int IdProduto, const std::string& nome, const std::string& descricao,
                             const std::string& categoria, double preco, const std::string& imagem,
                             int estoqueInicial, int estoqueMinino);

    /**
     * @brief Edita os dados de um produto existente.
     * @param produto Produto a ser editado.
     * @param nome Novo nome.
     * @param descricao Nova descrição.
     * @param preco Novo preço.
     * @param categoria Nova categoria.
     */
    void editarProduto(Produto& produto, const std::string& nome, const std::string& descricao, double preco, const std::string& categoria);

    /**
     * @brief Adiciona unidades ao estoque de um produto.
     * @param produto Produto que receberá o estoque.
     * @param quantidade Quantidade a adicionar.
     * @pre quantidade > 0
     */
    void adicionarEstoqueProduto(Produto& produto, int quantidade);

    /**
     * @brief Remove unidades do estoque de um produto.
     * @param produto Produto que terá o estoque reduzido.
     * @param quantidade Quantidade a remover.
     * @return true se a remoção foi realizada; false caso contrário
     *         (por exemplo, estoque insuficiente).
     */
    bool removerEstoqueProduto(Produto& produto, int quantidade);

    /**
     * @brief Define o estoque mínimo de um produto.
     * @param produto Produto a ser configurado.
     * @param quantidadeMinima Quantidade mínima desejada em estoque.
     */
    void definirEstoqueMinimoProduto(Produto& produto, int quantidadeMinima);


    /**
     * @brief Ajusta o estoque de um produto para um novo valor absoluto.
     * @details Calcula a diferença entre a nova quantidade e o estoque atual,
     *          chamando adicionarEstoqueProduto ou removerEstoqueProduto conforme necessário.
     * @param produto Produto que terá o estoque ajustado.
     * @param novaQuantidade Nova quantidade total desejada para o estoque.
     * @throw std::invalid_argument se novaQuantidade for menor que zero.
     */
    void ajustarEstoqueProduto(Produto& produto, int novaQuantidade);


    // vendas

    /**
     * @brief Atualiza o status de uma venda.
     * @param venda Venda a ser atualizada.
     * @param novoStatus Novo status da venda.
     * @see StatusVenda
     */
    void atualizarStatusVenda(Venda& venda, StatusVenda novoStatus);

    /**
     * @brief Atualiza o status de pagamento de uma venda.
     * @param venda Venda a ser atualizada.
     * @param novoStatus Novo status do pagamento.
     * @see StatusPagamento
     */
    void atualizarStatusPagamento(Venda& venda, StatusPagamento novoStatus);

    // cupons

    /**
     * @brief Cadastra um novo cupom de desconto.
     * @param codigo Código do cupom.
     * @param porcentagem Porcentagem de desconto (ex.: 10.0 para 10%).
     * @param dataValidade Data de validade do cupom.
     * @return O cupom (Desconto) criado.
     */
    Desconto cadastrarCupom(const std::string& codigo, double porcentagem, const std::string& dataValidade);

    /**
     * @brief Aplica um cupom de desconto a uma venda.
     * @param venda Venda que receberá o desconto.
     * @param cupom Cupom a ser aplicado.
     */
    void aplicarCupomVenda(Venda& venda, const Desconto& cupom);
};

#endif
