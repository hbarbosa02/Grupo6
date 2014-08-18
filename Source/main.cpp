#include "menuSQL.h"
#include <QtWidgets>

int main(int argc, char *argv[]) {
    //  Base para inicializar a aplicação
    QApplication app(argc, argv);

    // Formulario principal
    menuSQL form;

    // Exibe formulario principal
    form.show();

    // Inicializa a aplicação
    return app.exec();
}
