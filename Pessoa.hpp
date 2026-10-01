/**
 * @file Pessoa.hpp
 * @brief Declaração da classe Pessoa.
 */
#ifndef PESSOA_HPP
#define PESSOA_HPP
#include <string>
#include <vector>
#include <Endereco.hpp>

/**
 * @class Pessoa
 * @brief Representa uma pessoa genérica do sistema.
 *
 * Classe base da hierarquia de usuários. Armazena os dados de
 * identificação, contato e autenticação, além da lista de endereços
 * cadastrados. É estendida por classes mais específicas, como Gerente.
 *
 * @see Gerente
 * @see Endereco
 */
class Pessoa {
    private:
        int _idPessoa;                    ///< Identificador único da pessoa.
        std::string _nome;                ///< Nome completo.
        std::string _cpf;                 ///< CPF da pessoa.
        std::string _email;               ///< Endereço de e-mail.
        std::string _telefone;            ///< Telefone de contato.
        std::string _senha;               ///< Senha de acesso ao sistema.
        std::vector<Endereco> _enderecos; ///< Endereços cadastrados da pessoa.


    public:

        /**
         * @brief Construtor padrão.
         * @details Cria uma Pessoa com os atributos em seus valores iniciais.
         */
        Pessoa();

        /**
         * @brief Constrói uma Pessoa com todos os dados básicos.
         * @param idPessoa Identificador único.
         * @param nome Nome completo.
         * @param cpf CPF da pessoa.
         * @param email Endereço de e-mail.
         * @param telefone Telefone de contato.
         * @param senha Senha de acesso.
         */
        Pessoa(int idPessoa, const std::string& nome, const std::string& cpf, const std::string& email, const std::string& telefone, const std::string& senha);

        /**
         * @brief Destrutor virtual.
         * @details Garante a destruição correta de objetos derivados
         * quando deletados por meio de um ponteiro para Pessoa.
         */
        virtual ~Pessoa();

        //getters e setters

        /**
         * @brief Retorna o identificador da pessoa.
         * @return Identificador único.
         */
        int getIdPessoa() const;

        /**
         * @brief Retorna o nome da pessoa.
         * @return Nome completo.
         */
        std::string getNome() const;

        /**
         * @brief Define o nome da pessoa.
         * @param nome Novo nome completo.
         */
        void setNome(const std::strinf& nome);

        /**
         * @brief Retorna o CPF da pessoa.
         * @return CPF cadastrado.
         */
        std::string getCpf() const;

        /**
         * @brief Define o CPF da pessoa.
         * @param cpf Novo CPF.
         */
        void setNome(const std::strinf& cpf);

        /**
         * @brief Retorna o e-mail da pessoa.
         * @return E-mail cadastrado.
         */
        std::string getEmail() const;

        /**
         * @brief Define o e-mail da pessoa.
         * @param email Novo e-mail.
         */
        void setNome(const std::strinf& email);

        /**
         * @brief Retorna o telefone da pessoa.
         * @return Telefone cadastrado.
         */
        std::string getTelefone() const;

        /**
         * @brief Define o telefone da pessoa.
         * @param telefone Novo telefone.
         */
        void setNome(const std::strinf& telefone);

        /**
         * @brief Retorna a senha da pessoa.
         * @return Senha cadastrada.
         */
        std::string getSenha() const;

        /**
         * @brief Define a senha da pessoa.
         * @param senha Nova senha.
         */
        void setNome(const std::strinf& senha);

        /**
         * @brief Retorna o nome da pessoa.
         * @return Nome completo.
         */
        std::string getNome() const;

        /**
         * @brief Define o nome da pessoa.
         * @param nome Novo nome completo.
         */
        void setNome(const std::strinf& nome);

        //endereços

        /**
         * @brief Retorna os endereços cadastrados.
         * @return Referência constante ao vetor de endereços.
         */
        const std::vector<Endereco>& getEnderecos() const;

        /**
         * @brief Adiciona um endereço à lista da pessoa.
         * @param endereco Endereço a ser adicionado.
         */
        void adicionarEndereco(const Endereco& endereco);

        /**
         * @brief Remove um endereço da lista da pessoa.
         * @param indice Posição do endereço no vetor (começa em 0).
         * @pre indice deve ser menor que a quantidade de endereços cadastrados.
         */
        void removerEndereco(std::size_t indice);




};

#endif
