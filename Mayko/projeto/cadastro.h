#ifndef CADASTRO_H
#define CADASTRO_H

#include <QDialog>
#include "menucadastro.h"

namespace Ui {
class cadastro;
}

class cadastro : public QDialog
{
    Q_OBJECT

public:
    explicit cadastro(QWidget *parent = 0);
    ~cadastro();

private slots:
    void on_btn_restricoes_clicked();

private:
    Ui::cadastro *ui;
    menucadastro *restricao;
};

#endif // CADASTRO_H
