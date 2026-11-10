#ifndef PESSOA_REPOSITORIO_HPP
#define PESSOA_REPOSITORIO_HPP

#include <string>
#include <vector>
#include "Pessoa.hpp"

/**
 * @class PessoaRepositorio
 * @brief Lê e grava a lista de pessoas em um arquivo TXT.
 *
 * Campos separados por '|'.
 *
 *   P|id|nome|cpf|email|telefone|senha
 *   E|idPessoa|nomeDest|cep|rua|numero|bairro|complemento|cidade|estado
 */
class PessoaRepositorio {
public:
    /**
     * @brief Constrói o repositório de pessoas associado a um arquivo de texto.
     * @param caminho Caminho para o arquivo TXT de armazenamento.
     */
    PessoaRepositorio(const std::string& caminho);

    /**
     * @brief Lê todas as pessoas do arquivo (arquivo inexistente = lista vazia).
     * @return Vetor contendo as pessoas carregadas, já com seus endereços.
     */
    std::vector<Pessoa> carregar() const;

    /**
     * @brief Reescreve o arquivo com a lista recebida.
     * @param pessoas Vetor de pessoas a ser gravado.
     */
    void gravar(const std::vector<Pessoa>& pessoas) const;

private:
    std::string _caminho; ///< Caminho do arquivo de dados.

    /** @brief Remove caracteres reservados (| e quebras de linha) para não corromper o arquivo. */
    std::string limpar(std::string s) const;
};

#endif