#include "interface.h"

#include <QApplication>
#include <QDir>
#include <clocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::setlocale(LC_NUMERIC, "C");
    QDir::setCurrent(PASTA_PROJETO);
    Interface w;

    w.showMaximized();

    return a.exec();
}
