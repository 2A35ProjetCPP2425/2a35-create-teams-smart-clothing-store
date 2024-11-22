#ifndef STOCK_H
#define STOCK_H
#include <QDialog>
#include <QFileDialog>
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

    void on_exportationPDF_2_clicked();

    void on_boutonGenererGraphique_clicked();

    void displayCatalogue();

    void on_tabWidget_currentChanged(int index);
    void on_recherche_textChanged(const QString &input);


    void on_exportbutton_clicked();
    bool eventFilter(QObject *obj, QEvent *event);
    void updateStatistics();
    void notifications();
    void on_pushButton_2_clicked();

    void on_deleteProductButton_clicked();

    void on_contactfourniButton_clicked();

private:
    Ui::stock *ui;
    produit Etemp;
    bool isPrixAscending = true;
    bool isQuantiteAscending = true;
    bool isAZAscending = true;

};

#endif // STOCK_H
