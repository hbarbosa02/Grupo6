#include "menucadastro.h"
#include "ui_menucadastro.h"

menucadastro::menucadastro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menucadastro)
{
    ui->setupUi(this);

    this->criaAcao();
    this->criaMenu();

    connect(ui->btn_Confirma, SIGNAL(clicked()), this, SLOT(Confirma()));
    connect(ui->btn_Cancelar, SIGNAL(clicked()), this, SLOT(Cancelar()));
}

menucadastro::~menucadastro()
{
    delete acaoSair;
    delete menuArquivo;
    delete ui;
}
void menucadastro::criaAcao()
{
    acaoSair = new QAction(QString("&Sair"), this);
    acaoSair->setShortcut(QString("CTRL+S"));
    acaoSair->setStatusTip(QString("Encerra o aplicativo."));
    connect(acaoSair, SIGNAL(triggered()),this,SLOT(implementaAcaoSair()));
}
void menucadastro::criaMenu()
{
    menuArquivo = menuBar()->addMenu(QString("&Arquivo"));
    menuArquivo->addAction(acaoSair);
}
void menucadastro::implementaAcaoSair()
{
    close();
}
void menucadastro::selecionados()
{

}

void menucadastro::Confirma()
{

}
void menucadastro::Cancelar()
{
    close();
}
