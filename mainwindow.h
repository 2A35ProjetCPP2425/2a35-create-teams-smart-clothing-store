#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fournisseur.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateDatabase(const QString &movementStatus);
    void sendDataToArduino(const QString &data);
    void checkIDExistence(int id);

private slots:
    void enregistrerHistorique(const QString &action, const QString &details);
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void triParColonne();
    void on_pushButton_exporter_clicked();
    void on_pushButtonStatistiques_clicked();
    void triParEmail();
    void on_recherche_textChanged(const QString &input);
    void on_genererQRCodeButton_clicked();
    void on_telechargerQRCodeButton_clicked();
    void update_label();
private:
    Ui::MainWindow *ui;
    Fournisseur Etmp;
    bool triCroissant = true;
    bool triEmailAsc = true; // Initialisation pour le tri croissant
    QList<QString> historiqueActions;
    Arduino A;
};

#endif // MAINWINDOW_H
