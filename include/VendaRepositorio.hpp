#ifndef VENDA_REPOSITORIO_HPP
#define VENDA_REPOSITORIO_HPP

#include <string>
#include <vector>
#include "Venda.hpp"

/**
 * @class VendaRepositorio
 * @brief Lê e grava a lista de vendas em um arquivo TXT.
 *
 * Campos separados por '|'. Cada item de uma venda ocupa uma linha "I" e vem
 * ANTES da linha "V" da própria venda:
 *
 *   I|idProd|nome|descricao|categoria|preco|imagem|estoque|minimo|qtd
 *   V|id|cpf|destinatario|statusVenda|statusPagamento|data|horario
 *     |nomeDest|cep|rua|numero|bairro|complemento|cidade|estado|cupom|percentual
 */
class VendaRepositorio {
public:
    /**
     * @brief Constrói o repositório de vendas associado a um arquivo de texto.
     * @param caminho Caminho para o arquivo TXT de armazenamento.
     */
    VendaRepositorio(const std::string& caminho);

    /**
     * @brief Lê todas as vendas do arquivo (arquivo inexistente = lista vazia).
     * @return Vetor contendo as vendas carregadas.
     */
    std::vector<Venda> carregar() const;

    /**
     * @brief Reescreve o arquivo com a lista recebida.
     * @param vendas Vetor de vendas a ser gravado.
     */
    void gravar(const std::vector<Venda>& vendas) const;

private:
    std::string _caminho; ///< Caminho do arquivo de dados.

    /** @brief Remove caracteres reservados (| e quebras de linha) para não corromper o arquivo. */
    std::string limpar(std::string s) const;
};

#endif