#include "cadastro.h"
#include "ui_cadastro.h"
#include "menucadastro.h"

cadastro::cadastro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cadastro)
{
    ui->setupUi(this);
}

cadastro::~cadastro()
{
    delete ui;
}

void cadastro::on_btn_restricoes_clicked()
{
   // menucadastro restricao;
   // restricao.setModal(true);
   // restricao.exec();
   // restricao = new menucadastro(this);
    restricao->show();

}
