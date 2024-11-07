#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this); // Initialisation des éléments de l'UI

    // Afficher immédiatement les fournisseurs dans la tableView
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView_4->setModel(Etmp.afficher());
    ui->tableView_5->setModel(Etmp.afficher());
    ui->tableView_2->setModel(Etmp.afficher());


}

MainWindow::~MainWindow() {
    delete ui; // Clean up the UI elements
}
void MainWindow::on_pushButton_ajouter_clicked() {
    // Récupérer les informations saisies dans les champs
    int id = ui->lineEdit_ID->text().toInt();
    QString nom_entreprise = ui->lineEdit_nom_entreprise->text();
    QString email = ui->lineEdit_email->text();
    QString telephone = ui->lineEdit_telephone->text();
    QString info_banc = ui->lineEdit_info_banc->text();

    // Créer un objet fournisseur avec les données saisies
    Fournisseur F(id, nom_entreprise, email, telephone, info_banc);

    // Ajouter le fournisseur
    bool test = F.ajouter();

    if (test) {
        // Si l'ajout est réussi, mettre à jour le modèle et l'afficher dans le tableView
        ui->tableView->setModel(Etmp.afficher());
        ui->tableView_4->setModel(Etmp.afficher());
        ui->tableView_5->setModel(Etmp.afficher());
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Ajout non effectué\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_IDS->text().toInt();
    bool test = Etmp.supprimer(id);

    qDebug() << "Résultat de la suppression:" << test;

    if (test) {
        ui->tableView->setModel(Etmp.afficher());
        ui->tableView_4->setModel(Etmp.afficher());
        ui->tableView_5->setModel(Etmp.afficher());
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée\n"
                                                                         "Click Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée.\n"
                                                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pushButton_modifier_clicked() {
    int id = ui->lineEdit_ID_3->text().toInt();
    QString nom_entreprise = ui->lineEdit_nom_entreprise_3->text();
    QString email = ui->lineEdit_email_3->text();
    QString telephone = ui->lineEdit_telephone_3->text();
    QString info_banc = ui->lineEdit_info_banc_3->text();

    // Créer un objet fournisseur avec les données saisies
    Fournisseur F(id, nom_entreprise, email, telephone, info_banc);

    // Appeler la méthode modifier
    bool test = F.modifier();

    if (test) {
        // Mettre à jour le modèle du tableView
        ui->tableView->setModel(Etmp.afficher());
        ui->tableView_5->setModel(Etmp.afficher());
        ui->tableView_4->setModel(Etmp.afficher());
        ui->tableView_2->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Modification non effectuée\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}
