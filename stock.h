#ifndef STOCK_H
#define STOCK_H
#include <QDialog>
#include "produit.h"

namespace Ui {
class stock;
}

class stock : public QDialog {
    Q_OBJECT

public:
    explicit stock(QWidget *parent = nullptr);
    ~stock();

private slots:
    void on_home_clicked();
    void on_supprimer_clicked();
    void on_ajouter_clicked();



    void on_actualiser_clicked();

    void on_modifier_clicked();

    void on_recherche_clicked();

    void on_triparprix_clicked();

    void on_triparquantite_clicked();

    void on_triparaz_clicked();

    void on_exportationPDF_clicked();

private:
    Ui::stock *ui;
    produit Etemp;

};

#endif // STOCK_H
