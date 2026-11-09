#ifndef PRODUTO_REPOSITORIO_HPP
#define PRODUTO_REPOSITORIO_HPP
 
#include <string>
#include <vector>
#include "Produto.hpp"
 
/**
 * @class ProdutoRepositorio
 * @brief Le e grava a lista de produtos em um arquivo TXT (um produto por linha).
 *
 * Formato: id|nome|descricao|categoria|preco|imagem|estoque|estoqueMinimo
 */
class ProdutoRepositorio {
public:
    ProdutoRepositorio(const std::string& caminho);
 
    /** Le todos os produtos do arquivo (arquivo inexistente = lista vazia). */
    std::vector<Produto> carregar() const;
 
    /** Reescreve o arquivo com a lista recebida. */
    void gravar(const std::vector<Produto>& produtos) const;
 
private:
    std::string _caminho;

    /** @brief Remove caracteres reservados (| e quebras de linha) para não corromper o arquivo. */
    std::string limpar(std::string s) const;
};
 
#endif