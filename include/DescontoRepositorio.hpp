#ifndef DESCONTO_REPOSITORIO_HPP
#define DESCONTO_REPOSITORIO_HPP

#include <string>
#include <vector>
#include "Desconto.hpp"

/**
 * @class DescontoRepositorio
 * @brief Lê e grava a lista de cupons de desconto em um arquivo TXT (um cupom por linha).
 *
 * Formato: cupom|percentual|dataValidade
 */
class DescontoRepositorio {
public:
    /**
     * @brief Constrói o repositório de cupons associado a um arquivo de texto.
     * @param caminho Caminho para o arquivo TXT de armazenamento.
     */
    DescontoRepositorio(const std::string& caminho);

    /**
     * @brief Lê todos os cupons do arquivo (arquivo inexistente = lista vazia).
     * @return Vetor contendo os cupons carregados.
     */
    std::vector<Desconto> carregar() const;

    /**
     * @brief Reescreve o arquivo com a lista recebida.
     * @param descontos Vetor de cupons a ser gravado.
     */
    void gravar(const std::vector<Desconto>& descontos) const;

private:
    std::string _caminho; ///< Caminho do arquivo de dados.

    /** @brief Remove caracteres reservados (| e quebras de linha) para não corromper o arquivo. */
    std::string limpar(std::string s) const;
};

#endif