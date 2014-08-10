#include "menugui.h"
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MenuGUI form;
    form.show();

    return app.exec();
}
