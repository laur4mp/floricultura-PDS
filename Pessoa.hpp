#ifndef PESSOA_HPP
#define PESSOA_HPP
#include <string>
#include <vector>
#include <Endereco.hpp>

class Pessoa {
    private:
        int _idPessoa;
        std::string _nome;
        std::string _cpf;
        std::string _email;
        std::string _telefone;
        std::string _senha;
        std::vector<Endereco> _enderecos;


    public:

        Pessoa();
        Pessoa(int idPessoa, const std::string& nome, const std::string& cpf, const std::string& email, const std::string& telefone, const std::string& senha);
        virtual ~Pessoa();

        //getters e setters
        int getIdPessoa() const;

        std::string getNome() const;
        void setNome(const std::strinf& nome);

        std::string getCpf() const;
        void setNome(const std::strinf& cpf);

        std::string getEmail() const;
        void setNome(const std::strinf& email);

        std::string getTelefone() const;
        void setNome(const std::strinf& telefone);

        std::string getSenha() const;
        void setNome(const std::strinf& senha);

        std::string getNome() const;
        void setNome(const std::strinf& nome);

        //endereços
        const std::vector<Endereco>& getEnderecos() const;
        void adicionarEndereco(const Endereco& endereco);
        void removerEndereco(std::size_t indice);




};

#endif