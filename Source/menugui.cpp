#include "menugui.h"
#include "ui_menugui.h"
#include <QMessageBox>
#include <QtGui>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

MenuGUI::MenuGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuGUI)
{
    ui->setupUi(this);

    this->setWindowTitle("Otimizador de Horário");
    habilita_query(false);
    ui->cmb_db->setFocus();
    ui->cmb_db->setCurrentIndex(-1);

    valores_iniciais();

    connect(ui->btn_conectar, SIGNAL(clicked()), this, SLOT(conectar_db()));
    connect(ui->btn_desconectar, SIGNAL(clicked()), this, SLOT(desconectar_db()));
    connect(ui->btn_executar, SIGNAL(clicked()), this, SLOT(exec_sql()));
}

MenuGUI::~MenuGUI()
{
    delete ui;
}

void MenuGUI::valores_iniciais()
{
    ui->cmb_db->setCurrentIndex(0);
    ui->edt_schema->setText("Schema.db");
}

void MenuGUI::conectar_db()
{
    if ( ui->cmb_db->currentIndex() == -1)
    {
        QMessageBox::information(this, "Campo nao informado", "Campo [" + ui->lbl_db->text() + "] nao informado");
        ui->cmb_db->setFocus();
        return;
    }

    // Atualmente só há suporte para o SQLITE
    if (ui->cmb_db->currentIndex() > 0)
    {
        QMessageBox::information(this, "Indisponivel", "Banco [" + ui->cmb_db->currentText() + "] nao implementado");
        ui->cmb_db->setFocus();
        return;
    }

    // Só valida o campo IP se selecionou um banco diferente do SQLITE
    if (ui->cmb_db->currentIndex() != 0 && ui->edt_ip->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "Campo nao informado", "Campo [" + ui->lbl_ip->text() + "] nao informado");
        ui->edt_ip->setFocus();
        return;
    }

    // Verifica se o campo Schema foi informado
    if (ui->edt_schema->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "Campo nao informado", "Campo [" + ui->lbl_schema->text() + "] nao informado");
        ui->edt_schema->setFocus();
        return;
    }

    // Se selecionou o SQLITE não é necessário
    // usuário e senha
    if (ui->cmb_db->currentIndex() == 0)
    {
        concluir_conectar();
        return;
    }

    // Verifica se o campo Usuário foi informado
    if (ui->edt_usuario->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "Campo nao informado", "Campo [" + ui->lbl_usuario->text() + "] nao informado");
        ui->edt_usuario->setFocus();
        return;
    }

    // Verifica se o campo senha foi informado
    if (ui->edt_senha->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "Campo nao informado", "Campo [" + ui->lbl_senha->text() + "] nao informado");
        ui->edt_senha->setFocus();
        return;
    }
}

void MenuGUI::concluir_conectar()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(ui->edt_schema->text().trimmed());

    if (!db.open())
    {
        QMessageBox::critical(this, "Falha ao Conectar", QString("Falha na conexão com o banco\n[Schema: " + ui->edt_schema->text() + "]\n" + db.lastError().text()), QMessageBox::Cancel);
        return;
    }

    QSqlQuery qry;
    qry.prepare("select datetime('now')");
    if (!qry.exec())
    {
        QString erro = db.lastError().text();
        QMessageBox::critical(this, "Fallha ao Conectar", QString("Falha ao efetuar query para validacao da conexao\n" + qry.lastError().text()), QMessageBox::Cancel);

        return;
    }
    else if (qry.next())
        QMessageBox::information(this, "SOQH DB", "Conexão efetuada com sucesso!\n[" + qry.value(0).toDateTime().toString() + "]");

    habilita_query(true);
    ui->txt_sql->setFocus();
}

void MenuGUI::desconectar_db()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();

    habilita_query(false);

    ui->cmb_db->setFocus();
    valores_iniciais();
}

void MenuGUI::exec_sql()
{
    //Executar função em SQL
}

void MenuGUI::habilita_query(bool ind_executa)
{
    ui->btn_conectar->setEnabled(!ind_executa);
    ui->lbl_db->setEnabled(!ind_executa);
    ui->lbl_ip->setEnabled(!ind_executa);
    ui->lbl_schema->setEnabled(!ind_executa);
    ui->lbl_usuario->setEnabled(!ind_executa);
    ui->lbl_senha->setEnabled(!ind_executa);

    ui->cmb_db->setEnabled(!ind_executa);
    ui->edt_ip->setEnabled(!ind_executa);
    ui->edt_schema->setEnabled(!ind_executa);
    ui->edt_usuario->setEnabled(!ind_executa);
    ui->edt_senha->setEnabled(!ind_executa);

    // Formulario inferior
    ui->btn_desconectar->setEnabled(ind_executa);
    ui->btn_executar->setEnabled(ind_executa);
    ui->txt_sql->setEnabled(ind_executa);
    ui->tbl_sql->setEnabled(ind_executa);
}

void MenuGUI::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
