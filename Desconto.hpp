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

public:
    Desconto();                                          // sem desconto
    
    /** @brief Inicializa o desconto com código de cupom e porcentagem (0 a 100). */
    Desconto(const std::string& cupom, double percentual);
    
    ~Desconto();

    std::string getCupom() const;

    /** @brief Aplica o desconto sobre o valor e devolve o total final. */
    double aplicar(double valorTotal) const;
};

#endif