#ifndef PRODUTO 
#define PRODUTO 
#include <string>
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
    Produto(int id, const std::string& nome, const std::string& descricao, const std::string& categoria, double preco, const std::string& enderecoImagem, int estoqueInicial, int estoqueMinimo);
    ~Produto();
};
    //recuperar e add
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

    //estoque
    int getQuantidadeEstoque();
    int getQuantidadeMinima();
    void setQuantidadeMinima(int quantidade);

    //tabalhar no estoque 
    void adicionarEstoque(int quantidade);
    bool removerEstoque(int quantidade);
    bool verificarEstoqueMinimo();
#endif