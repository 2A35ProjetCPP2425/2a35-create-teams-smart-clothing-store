#ifndef STATISTIQUEDIALOG_H
#define STATISTIQUEDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

namespace Ui {
class StatistiquesDialog;
}

class StatistiquesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatistiquesDialog(QWidget *parent = nullptr);
    ~StatistiquesDialog();

private:
    Ui::StatistiquesDialog *ui;
    void genererGraphiqueFournisseursParBanque();  // Conserver uniquement cette fonction pour générer le graphique
};

#endif // STATISTIQUEDIALOG_H
