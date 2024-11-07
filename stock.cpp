#include "stock.h"
#include "ui_stock.h"
#include "produit.h"
#include "QMessageBox"
#include <QTableWidget>
#include <QDebug>

stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);
    ui->model->setModel(Etemp.afficher());
    ui->model_2->setModel(Etemp.afficher());
}

stock::~stock() {
    delete ui;
}

void stock::on_home_clicked() {
    this->hide();       // Hide the stock window

}
void stock::on_ajouter_clicked() {
    // Get product details from input fields
    QString nomProduit = ui->nomProduitLineEdit->text();
    QString categorie = ui->categorieLineEdit->text();

    produit P;
    bool ok = false, ok1 = false, ok2 = false;
    int ref;
    float prx;
    int quant;

    // Validate and set reference
    while (!ok) {
        QString reference = ui->referenceLineEdit->text();
        ref = reference.toInt(&ok);
        if (ok) {
            P.setref(ref);
        } else {
            ui->referenceLineEdit->clear();
            ui->referenceLineEdit->setPlaceholderText("Entrer une reference valide");
        }
    }

    // Set product name and category
    P.setnom(nomProduit);
    P.setcateg(categorie);

    // Validate and set price
    while (!ok1) {
        QString prix = ui->prixLineEdit->text();
        prx = prix.toFloat(&ok1);
        if (ok1) {
            P.setprix(prx);
        } else {
            ui->prixLineEdit->clear();
            ui->prixLineEdit->setPlaceholderText("Entrer un prix valide");
        }
    }

    // Validate and set quantity
    while (!ok2) {
        QString quantite = ui->quantiteLineEdit->text();
        quant = quantite.toInt(&ok2);
        if (ok2) {
            P.setquant(quant);
        } else {
            ui->quantiteLineEdit->clear();
            ui->quantiteLineEdit->setPlaceholderText("Entrer une quantité valide");
        }
    }

    // Add the product to the table only if validation passes
    if (ok && ok1 && ok2) {
        bool test = P.ajouter();
        if (test) {
            ui->model->setModel(Etemp.afficher());
            ui->referenceLineEdit->clear();
            ui->nomProduitLineEdit->clear();
            ui->categorieLineEdit->clear();
            ui->prixLineEdit->clear();
            ui->quantiteLineEdit->clear();
            // Display the success message and prevent exit
            QMessageBox::information(this, tr("Success"), tr("Ajout effectué\nClick OK to continue."), QMessageBox::Ok);
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Ajout non effectué.\nClick OK to continue."), QMessageBox::Ok);
        }
    }
}


void stock::on_supprimer_clicked()
{
    // Get the reference number from the input field
    int reff = ui->supprimerLineEdit->text().toInt();

    // Call the supprimer() method to remove the product by its reference
    bool test = Etemp.supprimer(reff);

    if (test)
    {
        // Refresh the model to reflect the changes after deletion
        ui->model->setModel(Etemp.afficher());

        // Show a success message
        QMessageBox::information(this, tr("Success"), tr("supprimer effectué\nClick OK to continue."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, tr("Error"), tr("supprimer non effectué.\nClick OK to continue."), QMessageBox::Ok);
    }
}




void stock::on_actualiser_clicked()
{
    ui->model->setModel(Etemp.afficher());
    ui->referenceLineEdit->clear();
    ui->nomProduitLineEdit->clear();
    ui->categorieLineEdit->clear();
    ui->prixLineEdit->clear();
    ui->quantiteLineEdit->clear();
}


void stock::on_modifier_clicked() {
    int reference = ui->referenceLineEdit->text().toInt();
    QString nom_prod = ui->nomProduitLineEdit->text();
    QString categorie = ui->categorieLineEdit->text();
    double prix = ui->prixLineEdit->text().toFloat();
    int quantite = ui->quantiteLineEdit->text().toInt();
    produit p(reference, nom_prod, categorie, prix, quantite);
    bool test = p.modifier();
    if (test)
    {
        ui->model->setModel(Etemp.afficher());
        ui->referenceLineEdit->clear();
        ui->nomProduitLineEdit->clear();
        ui->categorieLineEdit->clear();
        ui->prixLineEdit->clear();
        ui->quantiteLineEdit->clear();
        QMessageBox::information(this, tr("Success"), tr("modifer effectué\nClick OK to continue."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, tr("Error"), tr("modifier non effectué.\nClick OK to continue."), QMessageBox::Ok);
    }
}



void stock::on_recherche_clicked()
{
    QString reference = ui->rechercheLineEdit->text();

    // Check if the product exists using the 'recherche' method
    bool found = Etemp.recherche(reference);

    if (found) {
        ui->commentLabel->setStyleSheet("color: black;");
        ui->commentLabel->setText("Product found.");

        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM PRODUITS WHERE REFERENCE = :REFERENCE");
        query.bindValue(":REFERENCE", reference);
        query.exec();
        model->setQuery(query);
        ui->model_2->setModel(model);
    } else {
        ui->commentLabel->setStyleSheet("color: red;");
        ui->commentLabel->setText("Product not found.");
        ui->model_2->setModel(nullptr);
    }
}

void stock::on_triparprix_clicked()
{
    produit P;

    // Get the model for all products
    QSqlQueryModel *model = P.afficher();  // Use the instance 'P' to call 'afficher'

    // Set the model to the TableView (model_2)
    ui->model_2->setModel(model);

    // Sort the table by the 'prix' column (index 3) in ascending order (cheapest to most expensive)
    model->sort(3, Qt::AscendingOrder);
}

void stock::on_triparquantite_clicked()
{
    produit P;
    QSqlQueryModel *model = P.afficher();
    ui->model_2->setModel(model);
    model->sort(4, Qt::AscendingOrder);
}


void stock::on_triparaz_clicked()
{
    produit P;

    // Retrieve the model for all products
    QSqlQueryModel *model = P.afficher();  // Use 'P' instance to call 'afficher()'

    // Set the model to the TableView (model_2)
    ui->model_2->setModel(model);

    // Sort the table by the 'nom_prod' column (index 2) in ascending order (A-Z)
    model->sort(2, Qt::AscendingOrder);
}


void stock::on_exportationPDF_clicked()
{

}

