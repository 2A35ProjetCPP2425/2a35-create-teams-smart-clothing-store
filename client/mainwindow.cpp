#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QSqlTableModel>
#include <QSqlRecord>
 // Inclure votre classe Client
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//kent haka mlwl jwha bh
    ui->tableView->setModel(csupp.afficher());



    // Ajuster la largeur de toutes les colonnes (en augmentant de 50 pixels)
    int columnCount = ui->tableView->model()->columnCount();
    for (int i = 0; i < columnCount; ++i) {
        int currentWidth = ui->tableView->columnWidth(i);
        ui->tableView->setColumnWidth(i, currentWidth + 50);
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonajouter_clicked()
{
    // Récupération des informations saisies dans les champs
    int cin = ui->lineEdit_CIN->text().toInt();               // Conversion du texte en entier pour le CIN
    QString nom_client = ui->lineEdit_nom->text();             // Nom du client
    QString email_client = ui->lineEdit_email->text();         // Email du client
    int telephone = ui->lineEdit_telephone->text().toInt();    // Téléphone (conversion en entier)
    QString adresse_client = ui->lineEdit_adresse->text();     // Adresse du client
   int matricule = ui->lineEdit_matricule->text().toInt();    // Matricule (clé étrangère vers la table employé)

    // Instanciation d'un objet de la classe Client
    Client nouveauClient( cin, nom_client, email_client, telephone, adresse_client, matricule);

    // Appel de la méthode ajouter() pour insérer l'objet dans la base de données
    bool test = nouveauClient.ajouter();

    // Affichage d'une boîte de dialogue en fonction du résultat
    if (test) {
        ui->tableView->setModel(csupp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
}
int MainWindow::getClientCIN() {

    QModelIndex index = ui->tableView->currentIndex();

    int cin;
    if (index.isValid()) {
        QSqlTableModel* model = (QSqlTableModel*)ui->tableView->model();
        // Si une ligne est sélectionnée, on récupère le CIN depuis la ligne
        cin = model->data(index).toInt();
    } else {
        // Sinon, on récupère le CIN à partir du lineEdit
        bool ok;
        cin = ui->lineEdit_CIN_2->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un CIN valide.");
            return -1;
        }
    }

    return cin;
}

void MainWindow::on_pushButtonasupprimer_clicked() {
    // Priorité à la suppression via la sélection dans le QTableView
   /* QModelIndex index = ui->tableView->currentIndex();

    int cin;
    if (index.isValid()) {
        QSqlTableModel* model = (QSqlTableModel*)ui->tableView->model();
        // Si une ligne est sélectionnée, on récupère le CIN depuis la ligne
        cin = model->data(index).toInt();
    } else {
        // Sinon, on récupère le CIN à partir du lineEdit
        bool ok;
        cin = ui->lineEdit_CIN_2->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un CIN valide.");
            return;
        }
    }*/

    // Confirmation de la suppression
    int cin = getClientCIN();
        if (cin == -1) return;
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Êtes-vous sûr de vouloir supprimer ce client ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // Appel de la fonction de suppression
        bool success = csupp.supprimerClient(cin);

        if (success) {
            // Mise à jour du tableau
            ui->tableView->setModel(csupp.afficher());
            QMessageBox::information(this, "Succès", "Client supprimé avec succès.");
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression. Veuillez vérifier le CIN.");
        }
    }
}
void MainWindow::on_tableView_clicked() {
    // Vérifier que l'index est valide
  /*  if (!index.isValid()) {
        return; // Sortir si l'index n'est pas valide
    }

    // Récupérer le CIN du client sélectionné (à adapter selon votre modèle)
    int cin = index.data(Qt::DisplayRole).toInt();*/
    int cin = getClientCIN();
        if (cin == -1) return; // Si une erreur a été rencontrée, sortir de la méthode

    // Requête SQL pour récupérer les informations du client
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE CIN = :cin");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        // Remplir les champs de l'interface avec les données récupérées
        int cin = query.value("CIN").toInt();
        ui->lineEdit_CIN->setText(QString::number(cin));

        ui->lineEdit_nom->setText(query.value("NOM_CLIENT").toString());
        ui->lineEdit_email->setText(query.value("EMAIL_CLIENT").toString());

        ui->lineEdit_adresse->setText(query.value("ADRESSE_CLIENT").toString());


        // Si vous avez besoin de convertir un int à QString pour le téléphone
        int telephone = query.value("TELEPHONE_CLIENT").toInt();
        ui->lineEdit_telephone->setText(QString::number(telephone));
        int matricule = query.value("MATRICULE").toInt();
        ui->lineEdit_matricule->setText(QString::number(matricule));

    } else {
        QMessageBox::warning(this, "Erreur", "Client introuvable");
    }
}

void MainWindow::on_pushButton_modif_clicked()
{
    // Récupérer les valeurs des champs d'entrée
    int cin = ui->lineEdit_CIN->text().toInt();  // Champ pour le CIN
    QString nom = ui->lineEdit_nom->text();      // Champ pour le nom
    QString email = ui->lineEdit_email->text();  // Champ pour l'email
    int telephone_c = ui->lineEdit_telephone->text().toInt();  // Champ pour le téléphone
    QString adresse = ui->lineEdit_adresse->text();  // Champ pour l'adresse
    int matricule_c = ui->lineEdit_matricule->text().toInt();  // Champ pour le matricule

    // Vérifier si les champs sont valides (optionnel mais recommandé)
    if (cin == 0 || nom.isEmpty() || email.isEmpty() || telephone_c == 0 || adresse.isEmpty() || matricule_c == 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement.");
        return;
    }

    // Créer un objet de la classe Client
    Client c;

    // Appeler la méthode modifier pour mettre à jour les informations dans la base de données
    bool success = c.modifier(cin,  nom,  email,  telephone_c,  adresse,  matricule_c);

    // Afficher un message de confirmation ou d'erreur selon le résultat
    if (success) {
        ui->tableView->setModel(csupp.afficher());
        QMessageBox::information(this, "Succès", "Les informations du client ont été modifiées avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "La modification des informations a échoué.");
    }
}








/*void onRowSelected(const QModelIndex &index,Ui::MainWindow *ui) {
       // Récupérer les données de la ligne sélectionnée
       QSqlTableModel* model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
       Client client;

          if (model && index.isValid()) {
              QSqlRecord record = model->record(index.row());
              client.setCIN(record.value("cin").toInt());
              client.setNom_client(record.value("nom").toString());

              client.setEmail_client(record.value("email_client").toString());
              client.setTelephone(record.value("telephone").toInt());
              client.setAdresse_client(record.value("adresse_client").toString());
              client.setMatricule(record.value("matricule").toInt());


          }}*/



