/**
 * @file Produto.hpp
 * @brief Representação e controle de estoque de produtos no sistema.
 */
#ifndef PRODUTO 
#define PRODUTO 
#include <string>
/**
 * @class Produto
 * @brief Gerencia os dados de um item do catálogo e suas movimentações de estoque.
 */
class Produto {
private:
    int _idProduto;
    std::string _nome;
    std::string _descricao;
    std::string _categoria;
    double _preco;
    std::string enderecoImagem;
    int _quantidadeEstoque;
    int _quantidadeMinima;

public:

//construtores
    Produto();
/** @brief Inicializa um produto com todas as suas informações e limites de estoque. */
    Produto(int id, const std::string& nome, const std::string& descricao, const std::string& categoria, double preco, const std::string& enderecoImagem, int estoqueInicial, int estoqueMinimo);
    ~Produto();
};

    int getIdProduto();
    
    std::string getNome();
    void setNome(const std::string& nome);

    std::string getDescricao();
    void setDescricao(const std::string& descricao);

    std::string getCategoria();
    void setCategoria(const std::string& categoria);

    double getPreco();
    void setPreco(double preco);

    std::string getEnderecoImagem();
    void setEnderecoImagem(const std::string& enderecoImagem);

    int getQuantidadeEstoque();
    int getQuantidadeMinima();
    void setQuantidadeMinima(int quantidade);
  
/** @brief Incrementa a quantidade atual de itens no estoque. */
    void adicionarEstoque(int quantidade);
/** @brief Remove unidades do estoque se houver quantidade suficiente disponível. */
    bool removerEstoque(int quantidade);
/** @brief Checa se o estoque atual está abaixo ou igual ao nível mínimo configurado. */
    bool verificarEstoqueMinimo();
#endif
