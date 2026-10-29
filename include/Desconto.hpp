/**
 * @file Desconto.hpp
 * @brief Gerenciamento de cupons e aplicação de descontos em compras.
 */

#ifndef DESCONTO_HPP
#define DESCONTO_HPP

#include <string>

/**
 * @class Desconto
 * @brief Representa um cupom promocional e seu percentual de abatimento.
 */
class Desconto {
private:
    std::string cupom;
    double percentual;   // de 0 a 100
    std::string dataValidade;    // formato AAAA-MM-DD

public:
    Desconto();    // compra sem desconto
    
    /** @brief Inicializa o desconto com código de cupom, porcentagem (0 a 100) e validade (AAAA-MM-DD). */
    Desconto(const std::string& cupom, double percentual, const std::string& dataValidade);
    
    ~Desconto();

    std::string getCupom() const;

    /** @brief Verifica se o cupom está dentro da validade e pode ser utilizado. */
    bool ehValido() const;

    /** @brief Aplica o desconto sobre o valor e devolve o total final se o cupom for válido. */
    double aplicar(double valorTotal) const;
};

#endif
