#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Confirma();
    void implementaAcaoSair();



public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    QAction *acaoSair;
    QMenu *menuArquivo;
    void criaAcao();
    void criaMenu();

};

#endif // LOGINWINDOW_H
