#ifndef MENUSQL_H
#define MENUSQL_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
    class MenuSQL;
}

class MenuSQL : public QDialog
{
    Q_OBJECT
public slots:
    void validarCampos();
    void desconectar();
    void enviarQuery();

public:
    explicit MenuSQL(QWidget *parent = 0);
    ~MenuGUI();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MenuSQL *ui;
    QSqlQueryModel *txt_query;
    void habilitar_query(bool ativo);
    void valoresIniciais();
    void conectarSQL();
};

#endif // MENUSQL_H
