#include "Desconto.hpp"
#include <ctime>

using namespace std;

static string dataAtual(){
    time_t agora = time(nullptr);
    tm* t = localtime(&agora);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);
    return string(buffer);
}

bool Desconto::ehValido() const{
    if((dataValidade == "") || (dataValidade < dataAtual())){
        return false;
    } else {
        return true;
    }
}

Desconto::Desconto() : cupom(""), percentual(0.0), dataValidade("") {}

Desconto::Desconto(const string& cupom, double percentual, const string& dataValidade) : cupom(cupom), percentual(0.0), dataValidade(dataValidade){
    if(percentual > 0.0 && percentual <= 100.0){
        this->percentual = percentual;
    }
}

Desconto::~Desconto() {}

string Desconto::getCupom() const{
    return cupom;
}

double Desconto::aplicar(double valorTotal) const{
    if(!ehValido()){
        return valorTotal;
    } else {
        return valorTotal * ((100.0 - percentual) / 100.0);
    }
}