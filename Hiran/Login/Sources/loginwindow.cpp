#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(ui->btn_confirma,SIGNAL(clicked()),this,SLOT(Confirma()));
}

LoginWindow::~LoginWindow()
{

    delete acaoSair;
    delete menuArquivo;
    delete ui;
}
void LoginWindow::criaAcao()
{
    acaoSair = new QAction(QString("&Sair"), this);
    acaoSair->setShortcut(QString("CTRL+S"));
    acaoSair->setStatusTip(QString("Encerra Cadastro."));
    connect(acaoSair, SIGNAL(triggered()), this, SLOT(implementaAcaoSair()));

}

void LoginWindow::criaMenu()
{
    menuArquivo = menuBar()->addMenu(QString("&Arquivo"));
    menuArquivo->addAction(acaoSair);
}

void LoginWindow::implementaAcaoSair()
{
    close();
}

void LoginWindow::Confirma()
{
}
