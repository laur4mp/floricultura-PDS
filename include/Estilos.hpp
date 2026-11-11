#ifndef ESTILOS_HPP
#define ESTILOS_HPP

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QFrame>
#include <QWidget>

void aplicarFonteTitulo(QLabel *label);
void aplicarFonteDescricao(QLabel *label);
void aplicarFonteDestaque(QLabel *label);
void aplicarFonteBotaoMenu(QPushButton *btn);
void aplicarFonteBotaoConta(QPushButton *btn);
void aplicarEstiloBotaoRosa(QPushButton *btn);
void aplicarEstiloBotaoTransparente(QPushButton *btn);
void aplicarEstiloBotaoVerde(QPushButton *btn);
void aplicarEstiloCard(QFrame *card);
void aplicarEstiloInput(QLineEdit *input);
void aplicarEstiloCardCarrinho(QFrame *card);
void aplicarEstiloCardResumo(QWidget *card);
void aplicarEstiloBotaoQuantidade(QPushButton *btn);
void aplicarEstiloQuantidade(QLabel *label);
void aplicarEstiloSeletor(QPushButton *diminuir, QLabel *quantidade, QPushButton *aumentar);

#endif