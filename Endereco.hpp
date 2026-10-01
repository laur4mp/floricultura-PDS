/**
 * @file Endereco.hpp
 * @brief Gerenciamento de dados de endereço para entrega.
 */

#ifndef ENDERECO_HPP
#define ENDERECO_HPP

#include <string>

/**
 * @class Endereco
 * @brief Armazena e valida dados de localização e destinatário.
 */
class Endereco {
private:
    std::string nomeDest, cep, rua, numero, complemento, bairro, cidade, estado;

public:
    Endereco();
    
    /**
     * @brief Inicializa o endereço completo.
     */
    Endereco(const std::string& nomeDest, const std::string& cep, const std::string& rua, 
             const std::string& numero, const std::string& bairro, const std::string& complemento, 
             const std::string& cidade, const std::string& estado);
             
    ~Endereco();

    /** @brief Retorna o endereço completo em formato de texto para exibição. */
    std::string formatarEndereco() const;

    /** @brief Identifica a região do Brasil com base no endereço. */
    std::string regiao() const;

    std::string getNomeDest();

    /** @brief Define o CEP (retorna true se o formato for válido). */
    bool setCep(const std::string& cep);

    /** @brief Define o estado (retorna true se for válido). */
    bool setEstado(const std::string& estado);
};

#endif