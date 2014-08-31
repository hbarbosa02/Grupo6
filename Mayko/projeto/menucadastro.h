#ifndef MENUCADASTRO_H
#define MENUCADASTRO_H

#include <QMainWindow>

namespace Ui 
{
class menucadastro;
}

class menucadastro : public QMainWindow
{
    Q_OBJECT
public slots:
    void Confirma();
    void Cancelar();

public:
    explicit menucadastro(QWidget *parent = 0);
    ~menucadastro();

private:
    Ui::menucadastro *ui;
    QAction *acaoSair;
    QMenu *menuArquivo;

    void criaAcao();
    void implementaAcaoSair();
    void criaMenu();
    void selecionados();
};

#endif // MENUCADASTRO_H
