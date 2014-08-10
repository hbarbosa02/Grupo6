#ifndef MENUGUI_H
#define MENUGUI_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
    class MenuGUI;
}

class MenuGUI : public QDialog
{
    Q_OBJECT
public slots:
    void conectar_db();
    void desconectar_db();
    void exec_sql();

public:
    explicit MenuGUI(QWidget *parent = 0);
    ~MenuGUI();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MenuGUI *ui;
    QSqlQueryModel *mdl_qry;
    void habilita_query(bool ind_executa);
    void valores_iniciais();
    void concluir_conectar();
};

#endif // MENUGUI_H
