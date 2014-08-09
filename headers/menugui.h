#ifndef MENUGUI_H
#define MENUGUI_H

#include <QDialog>

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

private:
    Ui::MenuGUI *ui;
    void habilita_query(bool ind_executa);
};

#endif // MENUGUI_H
