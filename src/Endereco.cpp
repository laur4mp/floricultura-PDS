#include "Endereco.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

Endereco::Endereco() {}

Endereco::Endereco(const string& nomeDest, const string& cep, const string& rua, const string& numero, const string& bairro, const string& complemento,
                   const string& cidade, const string& estado)
    : _nomeDest(nomeDest), _cep(""), _rua(rua), _numero(numero), _bairro(bairro), _complemento(complemento), _cidade(cidade), _estado(""){
    if(nomeDest.empty() || rua.empty() || numero.empty() || bairro.empty() || cidade.empty()){
        throw invalid_argument("Preencha todos os dados obrigatorios");
    }

    if(!setCep(cep)){
        throw invalid_argument("CEP invalido!");
    }

    if(!setNumero(numero)){
        throw invalid_argument("Numero invalido!");
    }

    if(!setEstado(estado)){
        throw invalid_argument("Estado invalido!");
    }
}

Endereco::~Endereco() {}

string Endereco::formatarEndereco() const{
    string semComplemento = _rua + ", " + _numero + " - " + _bairro + ", " + _cidade + " - " + _estado + ", " + "CEP " + _cep;
    string comComplemento = _rua + ", " + _numero + " - " + _complemento + " - " + _bairro + ", " + _cidade + " - " + _estado + ", " + "CEP " + _cep;

    if(_complemento == ""){
        return semComplemento;
    } else {
        return comComplemento;
    }
}

string Endereco::regiao() const{
    if(_estado == "AC" || _estado == "AP" || _estado == "AM" || _estado == "PA" || _estado == "RO" || _estado == "RR" || _estado == "TO"){
        return "Norte";
    } else if(_estado == "AL" || _estado == "BA" || _estado == "CE" || _estado == "MA" || _estado == "PB" || _estado == "PE"
            || _estado == "PI" || _estado == "RN" || _estado == "SE") {
        return "Nordeste";
    } else if(_estado == "MT" || _estado == "MS" || _estado == "GO" || _estado == "DF"){
        return "Centro-Oeste";
    } else if(_estado == "MG" || _estado == "ES" || _estado == "SP" || _estado == "RJ"){
        return "Sudeste";
    } else if(_estado == "PR" || _estado == "SC" || _estado == "RS"){
        return "Sul";
    } else {
    return "Estado invalido";
    }
}

const string& Endereco::getNomeDest() const {
    return _nomeDest;
}

const string& Endereco::getCep() const {
    return _cep;
}

const string& Endereco::getRua() const {
    return _rua;
}

const string& Endereco::getNumero() const {
    return _numero;
}

const string& Endereco::getComplemento() const {
    return _complemento;
}

const string& Endereco::getBairro() const {
    return _bairro;
}

const string& Endereco::getCidade() const {
    return _cidade;
}

const string& Endereco::getEstado() const {
    return _estado;
}

bool Endereco::setCep(const string& cep){
    if(cep.size() != 8){
        return false;
    }

    for(char c : cep){
        if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9'){
            return false;
        }
    }

    this->_cep = cep;
    return true;
}

bool Endereco::setNumero(const string& numero){
    for(char c : numero){
        if (c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9'){
            cout << c << endl;
            return false;
        }
    }

    this->_numero = numero;
    return true;
}

bool Endereco::setEstado(const string& estado){
    if(estado == "AC" || estado == "AP" || estado == "AM" || estado == "PA" || estado == "RO" || estado == "RR" || estado == "TO" || estado == "AL" ||
       estado == "BA" || estado == "CE" || estado == "MA" || estado == "PB" || estado == "PE" || estado == "PI" || estado == "RN" || estado == "SE" ||
       estado == "MT" || estado == "MS" || estado == "GO" || estado == "DF" || estado == "MG" || estado == "ES" || estado == "SP" || estado == "RJ" ||
       estado == "PR" || estado == "SC" || estado == "RS"){
        this->_estado = estado;
        return true;
    }
    return false;
}