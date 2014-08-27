#include "menusql.h"
#include "ui_menusql.h"

#include <QMessageBox>
#include <QtGui>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

MenuSQL::MenuSQL(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuSQL)
{
    ui->setupUi(this);

    this->setWindowTitle("Organizador de Horários");
    habilitar_query(false);
    valoresIniciais();

    connect(ui->btn_conectar, SIGNAL(clicked()), this, SLOT(validarCampos()));
    connect(ui->btn_desconectar, SIGNAL(clicked()), this, SLOT(desconectar()));
    connect(ui->btn_executar, SIGNAL(clicked()), this, SLOT(enviarQuery()));

    txt_query = new QSqlQueryModel;
}

MenuSQL::~MenuSQL()
{
    delete txt_query;
    delete ui;
}

void MenuSQL::valoresIniciais()
{
    ui->edt_schema->setText("Banco.db");
}

void MenuSQL::validarCampos()
{
    if(ui->edt_schema->text().trimmed().isEmpty())
    {
        QMessageBox::information(this, "Campos em Branco", "Preencha o campo Schema");
        ui->edt_schema->setFocus();
        return;
    }
    else
        conectarSQL();
}

void MenuSQL::habilitar_query(bool ativo)
{
    //true
    ui->txt_sql->setEnabled(ativo);
    ui->tbl_sql->setEnabled(ativo);
    ui->btn_executar->setEnabled(ativo);
    ui->btn_desconectar->setEnabled(ativo);

    //false
    ui->btn_conectar->setDisabled(ativo);
    ui->edt_schema->setDisabled(ativo);
}

void MenuSQL::conectarSQL()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(ui->edt_schema->text().trimmed());

    if (!db.open())
    {
        QMessageBox::critical(this, "Falha na Conexão",
                              "Falha na conexão com o Banco [" + ui->edt_schema->text() + "]\n" + db.lastError().text(),
                              QMessageBox::Cancel);
        return;
    }

    QSqlQuery qry;
    qry.prepare("SELECT datetime('now')");
    if (!qry.exec()){
        QString erro = qry.lastError().text();
        QMessageBox::critical(this, "Falha na Conexão",
                              "Falha ao preparar consulta do banco" + erro + "\n",
                              QMessageBox::Cancel);
    }
    else if (qry.next())
        QMessageBox::information(this, "Banco Tutorial",
                                 "Conexão realizada com sucesso com o Banco ["
                                 + ui->edt_schema->text() + "]\n[" + qry.value(0).toDateTime().toString() + "]" ,
                                 QMessageBox::Ok);

    habilitar_query(true);
    ui->txt_sql->setFocus();
}

void MenuSQL::desconectar()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();

    habilitar_query(false);
    ui->edt_schema->setFocus();
}

void MenuSQL::enviarQuery()
{
    txt_query->clear();
    ui->tbl_sql->setModel(NULL);

    if(ui->txt_sql->toPlainText().trimmed().isEmpty())
    {
        QMessageBox::information(this, "Instrução SQL",
                                 "Não há instrução SQL a ser executada");
        ui->txt_sql->setFocus();
        return;
    }

    QString sql = ui->txt_sql->toPlainText();
    if (sql.toUpper().startsWith("SELECT"))
    {
        txt_query->setQuery(sql);
        ui->tbl_sql->setModel(txt_query);
        if (txt_query->lastError().isValid())
        {
            QMessageBox::critical(this, "SOQH SQL - ERRO",
                                  txt_query->lastError().text());
            ui->txt_sql->setFocus();
            return;
        }

        QMessageBox::information(this, "SOQH SQL",
                                 "Instrução SQL executada com sucesso");

    }
    else
    {
        QStringList sqls = sql.split(";");
        QString strRows;

        int numRows = 0;
        for (int i = 0; i < sqls.size(); i++)
        {
            QString tmpSql = sqls.at(i);
            if (tmpSql.trimmed().isEmpty())
                continue;

            QSqlQuery qry;
            qry.prepare(sqls.at(i));
            if (!qry.exec())
            {
                strRows.setNum(numRows);
                QString numScript;
                numScript.setNum(i+1);
                QMessageBox::critical(this, "SOQH SQL - ERRO",
                                      "Falha ao executar script [" + numScript + "]\n[" + strRows +
                                      "] linha(s) afetada(s)\n" + qry.lastError().text());
                ui->txt_sql->setFocus();
                return;
            }

            numRows += qry.numRowsAffected();
        }

        strRows.setNum(numRows);
        QMessageBox::information(this, "SOQH SQL",
                                 "Instrução SQL executada com sucesso\n[" + strRows +
                                 "] linha(s) afetadas(s)");
    }


}
