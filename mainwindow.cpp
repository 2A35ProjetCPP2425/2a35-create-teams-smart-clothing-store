#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlError>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "statistiquesdialog.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QPageSize>
#include "qrcodegen.hpp"
#include <QPixmap>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this); // Initialisation des éléments de l'UI
    int ret = A.connect_arduino(); // Connect to Arduino
    switch (ret) {
    case 0:
        qDebug() << "Arduino connected to:" << A.getarduino_port_name();
        break;
    case 1:
        qDebug() << "Arduino is available but not connected.";
        break;
    case -1:
        qDebug() << "Arduino not found.";
        return;
    }
    connect(A.getserial(), &QSerialPort::readyRead, this, &::MainWindow::update_label);
    connect(ui->pushButton_tri, &QPushButton::clicked, this, &MainWindow::triParColonne);
    connect(ui->pushButton_tri_2, &QPushButton::clicked, this, &MainWindow::triParEmail);
    connect(ui->lineEdit_recherche, &QLineEdit::textChanged, this, &MainWindow::on_recherche_textChanged);


    // Afficher immédiatement les fournisseurs dans la tableView
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView_4->setModel(Etmp.afficher());
    ui->tableView_5->setModel(Etmp.afficher());
    ui->tableView_6->setModel(Etmp.afficher());
    ui->tableView_7->setModel(Etmp.afficher());
}
void MainWindow::update_label()
{
    QByteArray data = A.read_from_arduino();
    QString message = QString::fromUtf8(data).trimmed();

    qDebug() << "Received data:" << message;

    if (message == "1") {
        ui->label_4->setText("Motion Detected");
        ui->label_4->repaint();
        updateDatabase("1");
        sendDataToArduino("1");
    } else if (message == "0") {
        ui->label_4->setText("No Motion");
        ui->label_4->repaint();
        updateDatabase("0");
        sendDataToArduino("0");
    } else {
        qDebug() << "Unexpected message:" << message;
    }
}

void MainWindow::sendDataToArduino(const QString &data)
{
    QByteArray command = data.toUtf8();
    A.write_to_arduino(command);
    qDebug() << "Sent command to Arduino:" << command;
}

void MainWindow::updateDatabase(const QString &movementStatus)
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEURS SET MOUV = :movement WHERE ID = :id");

    if (movementStatus == "1") {
        query.bindValue(":movement", 1);
    } else {
        query.bindValue(":movement", 0);
    }

    // Remplacez `1` par l'ID que vous souhaitez mettre à jour.
    query.bindValue(":id", 1);

    if (query.exec()) {
        qDebug() << "Database updated successfully!";
    } else {
        qDebug() << "Error updating database:" << query.lastError().text();
    }
}
void MainWindow::checkIDExistence(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM FOURNISSEURS WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            qDebug() << "ID exists in the database.";
        } else {
            qDebug() << "ID does not exist in the database.";
        }
    } else {
        qDebug() << "Error checking ID existence:" << query.lastError().text();
    }
}
MainWindow::~MainWindow() {
    delete ui; // Clean up the UI elements
}

void MainWindow::enregistrerHistorique(const QString &action, const QString &details) {
    // Chemin du fichier texte
    QString cheminFichierTexte = "C:/Users/moetaz/Documents/fournisseur/historique.txt";

    // Ajouter l'entrée au fichier texte
    QFile file(cheminFichierTexte);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss");
        out << "Date et Heure : " << timestamp << "\n";
        out << "Action : " << action << "\n";
        out << "Détails : " << details << "\n";
        out << "----------------------------\n";
        file.close();
    } else {
        qWarning("Échec d'ouverture du fichier texte.");
        return;
    }

    // Générer le PDF à partir du fichier texte
    QString cheminFichierPDF = "C:/Users/moetaz/Documents/fournisseur/historique.pdf";
    QPdfWriter writer(cheminFichierPDF);
    writer.setPageSize(QPageSize(QPageSize::A4)); // Format A4

    QPainter painter(&writer);

    if (!painter.isActive()) {
        qWarning("Échec de la création du fichier PDF.");
        return;
    }

    // Police et dimensions définies
    painter.setFont(QFont("Arial", 16)); // Police Arial, taille 16
    int y = 290;                         // Position verticale initiale
    int x = 100;                         // Position horizontale fixe
    int lineSpacing = 300;               // Espacement entre les lignes

    // Lire le fichier texte et écrire dans le PDF
    QFile inputFile(cheminFichierTexte);
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&inputFile);

        while (!in.atEnd()) {
            QString line = in.readLine();
            painter.drawText(x, y, line); // Dessiner la ligne
            y += lineSpacing;

            // Gérer le saut de page si la position dépasse les limites
            if (y > writer.height() - 50) {
                writer.newPage();
                y = 290; // Réinitialiser la position verticale
            }
        }
        inputFile.close();
    } else {
        qWarning("Échec de l'ouverture du fichier texte.");
    }

    painter.end(); // Terminer le dessin
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
        ui->tableView_6->setModel(Etmp.afficher());
        ui->tableView_7->setModel(Etmp.afficher());
        enregistrerHistorique("Ajout", "Fournisseur ajouté: " + nom_entreprise + ", ID: " + QString::number(id));

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Succès,Fournisseur ajouté avec succès\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked() {
    int id = ui->lineEdit_IDS->text().toInt();
    bool test = Etmp.supprimer(id);

    qDebug() << "Résultat de la suppression:" << test;

    if (test) {

        ui->tableView->setModel(Etmp.afficher());
        ui->tableView_4->setModel(Etmp.afficher());
        ui->tableView_5->setModel(Etmp.afficher());
        ui->tableView_6->setModel(Etmp.afficher());
        ui->tableView_7->setModel(Etmp.afficher());

        enregistrerHistorique("Suppression", "Fournisseur supprimé, ID: " + QString::number(id));

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
        ui->tableView_6->setModel(Etmp.afficher());
        ui->tableView_7->setModel(Etmp.afficher());

        enregistrerHistorique("Modification", "Fournisseur modifié: " + nom_entreprise + ", ID: " + QString::number(id));

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Modification non effectuée\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}

void MainWindow::triParColonne() {
    // Créer une instance de QSqlQueryModel
    QSqlQueryModel *model = new QSqlQueryModel();

    // Construire la requête SQL en fonction de l'état du tri
    QString queryString = triCroissant
                              ? "SELECT * FROM fournisseurs ORDER BY id ASC"   // Tri croissant
                              : "SELECT * FROM fournisseurs ORDER BY id DESC"; // Tri décroissant

    // Exécuter la requête
    model->setQuery(queryString);

    // Vérifier si la requête a échoué
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << model->lastError();
    } else {
        // Mettre à jour le modèle de la tableView
        ui->tableView_6->setModel(model);
        qDebug() << (triCroissant ? "Tri croissant effectué." : "Tri décroissant effectué.");
    }

    // Inverser l'état pour le prochain clic
    triCroissant = !triCroissant;
}

void MainWindow::triParEmail() {
    // Créer une instance de QSqlQueryModel
    QSqlQueryModel *model = new QSqlQueryModel();

    // Construire la requête SQL pour trier par email
    QString queryString = triEmailAsc
                              ? "SELECT * FROM fournisseurs ORDER BY email ASC"   // Tri croissant
                              : "SELECT * FROM fournisseurs ORDER BY email DESC"; // Tri décroissant

    // Exécuter la requête
    model->setQuery(queryString);

    // Vérifier si la requête a échoué
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << model->lastError();
    } else {
        // Mettre à jour le modèle de la tableView
        ui->tableView_6->setModel(model);
        qDebug() << (triEmailAsc ? "Tri croissant par email effectué." : "Tri décroissant par email effectué.");
    }

    // Inverser l'état pour le prochain clic
    triEmailAsc = !triEmailAsc;
}

void MainWindow::on_pushButton_exporter_clicked() {
    // Ouvrir la boîte de dialogue pour choisir où sauvegarder le fichier CSV
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en CSV", "", "Fichiers CSV (*.csv)");

    if (!fileName.isEmpty()) {
        // Créer un fichier avec le chemin spécifié
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier pour l'écriture.");
            return;
        }

        QTextStream out(&file);

        // Ajouter l'entête du fichier CSV (optionnel)
        out << "ID,nom_entreprise,Email,Telephone,Infos Bancaires\n";

        // Récupérer les données de la table
        QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView_6->model());
        if (model) {
            for (int row = 0; row < model->rowCount(); ++row) {
                for (int column = 0; column < model->columnCount(); ++column) {
                    // Récupérer chaque valeur de la cellule
                    QString value = model->data(model->index(row, column)).toString();

                    // Vérifier si la valeur contient une virgule ou un saut de ligne et l'entourer de guillemets si nécessaire
                    if (value.contains(',') || value.contains('\n') || value.contains('"')) {
                        value = "\"" + value.replace("\"", "\"\"") + "\""; // Remplacer les guillemets existants
                    }

                    // Écrire la valeur dans le fichier
                    out << value;

                    // Ajouter une virgule entre les colonnes, sauf après la dernière colonne
                    if (column < model->columnCount() - 1) {
                        out << ",";
                    }
                }
                out << "\n";  // Saut de ligne après chaque ligne de données
            }
        }

        file.close();
        QMessageBox::information(this, "Succès", "Fichier CSV exporté avec succès.");
    }
}
void MainWindow::on_pushButtonStatistiques_clicked()
{
    StatistiquesDialog dialog(this);
    dialog.exec();  // Afficher la fenêtre des statistiques
}

void MainWindow::on_recherche_textChanged(const QString &input) {
    if (input.isEmpty()) {
        // Si le champ est vide, afficher tous les enregistrements.
        ui->tableView_6->setModel(Etmp.afficher());
        return;
    }

    // Préparer une requête pour rechercher par INFO_BANC ou NOM_ENTREPRISE
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM fournisseurs WHERE INFO_BANC LIKE :input OR NOM_ENTREPRISE LIKE :input");
    query.bindValue(":input", "%" + input + "%");
    query.exec();
    model->setQuery(std::move(query));


    // Mettre à jour le modèle de la tableView avec les résultats
    ui->tableView_6->setModel(model);
}

void MainWindow::on_genererQRCodeButton_clicked() {
    using qrcodegen::QrCode;

    QString id = ui->lineEditID->text(); // Récupérer l'ID saisi par l'utilisateur
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID.");
        return;
    }

    // Vérifier si l'ID existe et récupérer ses informations
    QSqlQuery query;
    query.prepare("SELECT ID, NOM_ENTREPRISE, EMAIL, TELEPHONE, INFO_BANC FROM fournisseurs WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur", "ID inexistant ou erreur lors de la vérification.");
        return;
    }

    // Récupérer les informations
    QString nomEntreprise = query.value("NOM_ENTREPRISE").toString();
    QString email = query.value("EMAIL").toString();
    QString telephone = query.value("TELEPHONE").toString();
    QString infoBanc = query.value("INFO_BANC").toString();

    // Formater les informations en JSON
    QString informations = QString(
                               "{ \"ID\": \"%1\", \"NOM_ENTREPRISE\": \"%2\", \"EMAIL\": \"%3\", \"TELEPHONE\": \"%4\", \"INFO_BANC\": \"%5\" }")
                               .arg(id)
                               .arg(nomEntreprise)
                               .arg(email)
                               .arg(telephone)
                               .arg(infoBanc);

    // Générer le QR code avec toutes les informations
    QrCode qr = QrCode::encodeText(informations.toUtf8().constData(), QrCode::Ecc::LOW);

    // Spécifiez les dimensions du QLabel
    const int labelWidth = 291;  // Largeur du QLabel
    const int labelHeight = 291; // Hauteur du QLabel

    const int qrSize = qr.getSize(); // Taille d'origine du QR code

    // Créer l'image pour le QR code
    QImage image(qrSize, qrSize, QImage::Format_RGB32);
    image.fill(Qt::white);

    for (int y = 0; y < qrSize; y++) {
        for (int x = 0; x < qrSize; x++) {
            image.setPixelColor(x, y, qr.getModule(x, y) ? Qt::black : Qt::white);
        }
    }

    // Convertir l'image en QPixmap
    QPixmap pixmap = QPixmap::fromImage(image.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio));

    // Afficher le QR code dans le QLabel
    ui->qrCodeLabel->setPixmap(pixmap);
}



void MainWindow::on_telechargerQRCodeButton_clicked() {
    // Récupérer l'image du QR code depuis le QLabel
    QPixmap pixmap = ui->qrCodeLabel->pixmap();

    // Vérifier si l'image existe
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Erreur", "Aucun QR code généré à télécharger.");
        return;
    }

    // Demander à l'utilisateur où sauvegarder l'image
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer l'image", "", "Images (*.png *.xpm *.jpg)");

    if (fileName.isEmpty()) {
        // Si l'utilisateur annule la sauvegarde, on ne fait rien
        return;
    }

    // Sauvegarder le QR code en tant que fichier image (ici en PNG)
    if (!pixmap.save(fileName, "PNG")) {
        QMessageBox::warning(this, "Erreur", "Erreur lors de la sauvegarde de l'image.");
    } else {
        QMessageBox::information(this, "Succès", "QR code téléchargé avec succès.");
    }
}

