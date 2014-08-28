#include "menucadastro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    menucadastro w;
    w.show();

    return a.exec();
}
