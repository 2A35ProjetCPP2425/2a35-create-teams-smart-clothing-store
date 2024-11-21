#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QRegularExpression>
#include <QFileDialog>





#include <QLayout>          // Pour QLayout
#include <QVBoxLayout>       // Pour QVBoxLayout
#include <QtSql/QSqlError>   // Pour QSqlError
#include <QtCharts/QChartView> // Pour QChartView et autres éléments de QChart
#include <QMessageBox> // Pour afficher des messages d'erreur


#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QMessageBox>
#include <QSqlQuery>
#include <QGraphicsScene>
#include <QPainter>




#include <QtCharts/QPieSlice>

#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QDebug>

#include "email.h"




 // Inclure votre classe Client
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tableView->setModel(csupp.afficher());
    connect(ui->lineEdit_recherche, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_recherche_textChanged);
   // connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);



    connect(ui->pushButton_statistiques, &QPushButton::clicked, this, &MainWindow::displayGenderStatistics);



  connect(&csupp, &Client::smsSent, this, &MainWindow::onSmsSent);


   // Connect the browse button for attachments
   // Configurer la QListWidget

   connect(ui->browseAttachmentsButton_2, &QPushButton::clicked, this, &MainWindow::onBrowseAttachments);
   ui->attachmentsListWidget->setIconSize(QSize(48, 48)); // Définir la taille des icônes
   ui->attachmentsListWidget->setSpacing(5);             // Ajouter de l'espacement entre les éléments


   ui->attachmentsListWidget->setViewMode(QListWidget::ListMode); // Mode liste (un élément par ligne)
      ui->attachmentsListWidget->setResizeMode(QListWidget::Adjust);

      connect(ui->attachmentsListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onAttachmentDoubleClicked);


   connect(ui->removeAttachmentButton, &QPushButton::clicked, this, &MainWindow::onRemoveAttachment);


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
    QString sexe = ui->comboBox_sexe->currentText();
    // Récupération des informations saisies dans les champs
    int cin = ui->lineEdit_CIN->text().toInt();
    QString nom_client = ui->lineEdit_nom->text();
    QString email_client = ui->lineEdit_email->text().trimmed(); // Supprime les espaces au début et à la fin
    QString telephone = ui->lineEdit_telephone->text();
    QString adresse_client = ui->lineEdit_adresse->text();
    int matricule = ui->lineEdit_matricule->text().toInt();

    // 1. Contrôle de saisie pour le CIN
    if (cin <= 0) {
        QMessageBox::warning(this, "Erreur", "Le CIN doit être un nombre entier positif.");
        return;
    }

    // 2. Contrôle de saisie pour le nom
    if (nom_client.isEmpty() || !std::all_of(nom_client.begin(), nom_client.end(), [](QChar c) {
        return c.isLetter() || c.isSpace(); })) {
        QMessageBox::warning(this, "Erreur", "Le nom ne doit contenir que des lettres et des espaces.");
        return;
    }

    // 3. Contrôle de saisie pour l'email
    if (!isValidEmail(email_client)) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse email valide.");
        return;
    }

    if (telephone.length() != 8 || !telephone.toLongLong()) {
           QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit être composé de 8 chiffres.");
           return;
       }

    // 5. Contrôle de saisie pour l'adresse
    if (adresse_client.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'adresse ne doit pas être vide.");
        return;
    }

    // 6. Contrôle de saisie pour le matricule
    if (matricule <= 0) {
        QMessageBox::warning(this, "Erreur", "Le matricule doit être un nombre entier positif.");
        return;
    }
    // Contrôle de saisie : vérifier que le sexe est bien sélectionné
        if (sexe.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un sexe.");
            return;  // Empêche l'ajout si le sexe n'est pas sélectionné
        }

    // Si tous les contrôles sont valides, création du client et ajout
    Client nouveauClient(cin, nom_client, email_client, telephone, adresse_client, matricule,sexe);
    bool test = nouveauClient.ajouter();

    if (test) {
        // Mettre à jour le modèle de la table et afficher un message de succès
        ui->tableView->setModel(csupp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

// Fonction de validation de l'email
bool MainWindow::isValidEmail(const QString &email)
{
    // Vérifier que l'email contient un "@" et un "."
    int atPos = email.indexOf('@');
    int dotPos = email.lastIndexOf('.');

    if (atPos < 1 || dotPos < atPos + 2 || dotPos + 2 >= email.length()) {
        return false; // L'email n'est pas valide
    }

    return true;
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
void MainWindow::clearClientFields()
{

    ui->lineEdit_CIN->clear();

    ui->lineEdit_nom->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_telephone->clear();
    ui->lineEdit_adresse->clear();
    ui->lineEdit_matricule->clear();

    ui->comboBox_sexe->currentText();


}
void MainWindow::on_clearButton_clicked() {
    clearClientFields(); // Appeler la méthode pour vider les champs
}



void MainWindow::on_pushButtonasupprimer_clicked() {

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
        ui->lineEdit_telephone->setText(query.value("TELEPHONE_CLIENT").toString());

        int matricule = query.value("MATRICULE").toInt();
        ui->lineEdit_matricule->setText(QString::number(matricule));

        // Remplir le QComboBox Sexe
            QString sexe = query.value("SEXE").toString();

            if (sexe == "Homme") {
                ui->comboBox_sexe->setCurrentIndex(ui->comboBox_sexe->findText("Homme"));
            } else if (sexe == "Femme") {
                ui->comboBox_sexe->setCurrentIndex(ui->comboBox_sexe->findText("Femme"));
            } else {
                ui->comboBox_sexe->setCurrentIndex(-1);  // Si aucune correspondance
            }



    } else {
        QMessageBox::warning(this, "Erreur", "Client introuvable");
    }
}

void MainWindow::on_pushButton_modif_clicked()
{
    // Récupérer les valeurs des champs d'entrée

    int cin = ui->lineEdit_CIN->text().toInt();
     ui->lineEdit_CIN->setReadOnly(true);// Champ pour le CIN
    QString nom = ui->lineEdit_nom->text();      // Champ pour le nom
    QString email = ui->lineEdit_email->text();  // Champ pour l'email
    QString telephone_c = ui->lineEdit_telephone->text();  // Champ pour le téléphone
    QString adresse = ui->lineEdit_adresse->text();  // Champ pour l'adresse
    int matricule_c = ui->lineEdit_matricule->text().toInt();  // Champ pour le matricule
    // Récupérer la valeur sélectionnée dans le QComboBox pour le sexe
        QString sexe = ui->comboBox_sexe->currentText();





    // Créer un objet de la classe Client
    Client c;

    // Appeler la méthode modifier pour mettre à jour les informations dans la base de données
    bool success = c.modifier(cin,  nom,  email,  telephone_c,  adresse,  matricule_c,sexe);

    // Afficher un message de confirmation ou d'erreur selon le résultat
    if (success) {
        ui->tableView->setModel(csupp.afficher());
        QMessageBox::information(this, "Succès", "Les informations du client ont été modifiées avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "La modification des informations a échoué.");
    }
}








void MainWindow::on_pushButton_tri_clicked()
{
    // Créer un modèle pour la table CLIENT
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("CLIENT");
    model->select();  // Charger les données de la table CLIENT

    // Appliquer le modèle à la vue (tableView)
    ui->tableView->setModel(model);

    // Vérification du contenu de comboBox
    QString critereTri = ui->comboBox_2->currentText();
    qDebug() << "Critère de tri sélectionné:" << critereTri;

    // Récupérer l'ordre de tri (Ascendant ou Descendant) depuis comboBox
        QString ordreTri = ui->comboBox_ordre->currentText();
        Qt::SortOrder sortOrder = (ordreTri == "Ascendant") ? Qt::AscendingOrder : Qt::DescendingOrder;

    // Appliquer le tri en fonction de la sélection dans le comboBox
    if (critereTri == "CIN") {
        model->setSort(0, sortOrder);  // Trier par la première colonne (CIN)
    } else if (critereTri == "Nom") {
        model->setSort(1, sortOrder);  // Trier par la deuxième colonne (Nom)  // Trier par la deuxième colonne (Nom)
    } else if (critereTri == "Téléphone") {
    model->setSort(3, sortOrder);  // Trier par la quatrième colonne (Téléphone)
}

    // Réappliquer le modèle après le tri pour garantir que le tri est pris en compte
    model->select();

    // Redéfinir les en-têtes après le tri pour s'assurer qu'ils restent cohérents
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN Client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone du Client "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Matricule employé" ));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr(" Sexe du Client" ));

    // Rafraîchir la vue
    ui->tableView->reset();
}





#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QPdfWriter>
#include <QPainter>
#include <QFile>
#include <QDebug>





//pdf


void MainWindow::on_pushButton_exporter_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer en tant que PDF", "", "Fichiers PDF (*.pdf);;Tous les fichiers (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);

    QAbstractItemModel *model = ui->tableView->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter.");
        return;
    }

    int x = 20;  // Position initiale de départ (marge gauche)
    int y = 200; // Position initiale de départ (marge haute)
    int rowHeight = 50; // Hauteur des lignes
    int columnWidth = 340; // Largeur des colonnes augmentée

    // Appliquer des couleurs douces pour les en-têtes et les cellules
    QColor headerColor(100, 149, 237); // Bleu clair
    QColor altRowColor(240, 248, 255); // Presque blanc pour alternance
    QColor textColor(25, 25, 112);     // Bleu foncé pour le texte

    // Dessiner les en-têtes des colonnes
    QFont font = painter.font();
    font.setPointSize(10); // Taille de la police pour le tableau
    painter.setFont(font);

    painter.setBrush(QBrush(headerColor)); // Couleur de fond pour l'en-tête
    painter.setPen(QPen(Qt::white)); // Texte blanc pour l'en-tête

    for (int column = 0; column < model->columnCount(); ++column) {
        QRect rect(x + column * columnWidth, y, columnWidth, rowHeight);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(column, Qt::Horizontal).toString());
    }

    y += rowHeight; // Déplacer Y après l'en-tête

    // Dessiner les lignes de données avec alternance de couleurs
    painter.setPen(QPen(textColor)); // Texte en bleu foncé
    for (int row = 0; row < model->rowCount(); ++row) {
        QColor rowColor = (row % 2 == 0) ? Qt::white : altRowColor; // Alternance de couleur
        painter.setBrush(QBrush(rowColor));

        for (int column = 0; column < model->columnCount(); ++column) {
            QRect rect(x + column * columnWidth, y + row * rowHeight, columnWidth, rowHeight);
            painter.drawRect(rect); // Dessiner la cellule
            painter.drawText(rect.adjusted(5, 0, -5, 0), Qt::AlignVCenter | Qt::AlignLeft, model->data(model->index(row, column)).toString());
        }
    }

    // Ajouter un titre
    painter.setPen(QPen(QColor(0, 51, 102))); // Couleur bleu foncé
    QFont titleFont("Arial", 25, QFont::Bold); // Titre avec police plus grande et gras
    painter.setFont(titleFont);

    QString title = "Liste des clients";
    int pageWidth = pdfWriter.width(); // Largeur totale de la page
    int textWidth = painter.fontMetrics().horizontalAdvance(title); // Largeur du texte
    int centeredX = (pageWidth - textWidth) / 2; // Calculer la position X pour centrer

    painter.drawText(centeredX, 85, title); // Titre centré

    // Ajouter un logo
    QPixmap logo("C:/Users/wassi/Desktop/projetCpp/client/loogoo.png");
    if (!logo.isNull()) {
        int logoWidth = 250;  // Largeur du logo
        int logoHeight = 200; // Hauteur du logo
        int logoX = pageWidth - logoWidth - 20; // Coin supérieur droit
        int logoY = 20; // Ajuster si besoin

        painter.drawPixmap(logoX, logoY, logoWidth, logoHeight, logo);
    }

    painter.end();

    QMessageBox::information(this, "Exportation réussie", "Les données ont été exportées avec succès.");
}







void MainWindow::on_lineEdit_recherche_textChanged()
{
    // Créer un modèle pour la table CLIENT
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("CLIENT");

    // Récupérer le texte du champ de recherche
    QString text = ui->lineEdit_recherche->text();

    // Construire un filtre dynamique pour les trois critères (CIN, Nom, Téléphone)
    QString filter;

    // Vérifier si le champ de texte n'est pas vide
    if (!text.isEmpty()) {
        // Recherche par CIN : ici on cherche CIN qui commence par le texte
        filter += QString("CIN LIKE '%1%'").arg(text); // Recherche partielle sur CIN
        filter += " OR ";  // Ajouter un "OR" pour permettre la recherche par CIN, Nom ou Téléphone

        // Recherche par Nom : ici on cherche le Nom qui contient le texte
        filter += QString("NOM_CLIENT LIKE '%1%'").arg(text);  // Recherche partielle sur le Nom
        filter += " OR ";  // Ajouter un "OR" pour permettre la recherche par CIN, Nom ou Téléphone

        // Recherche par Téléphone : on cherche un numéro de téléphone qui commence par le texte
        filter += QString("TELEPHONE_CLIENT LIKE '%1%'").arg(text); // Recherche partielle sur Téléphone
    }

    // Appliquer le filtre au modèle
    model->setFilter(filter);

    // Charger les données filtrées dans le modèle
    model->select();

    // Appliquer le modèle à la vue (tableView)
    ui->tableView->setModel(model);

    // Redéfinir les en-têtes pour conserver les titres des colonnes
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN Client "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone du Client "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Matricule employé" ));
     model->setHeaderData(6, Qt::Horizontal, QObject::tr(" Sexe du Client" ));

    // Rafraîchir la vue pour afficher les résultats
    ui->tableView->reset();
}





//STATISTIQUE par sexe
void MainWindow::displayGenderStatistics()
{
    // Préparer les variables de comptage
    int maleCount = 0;
    int femaleCount = 0;

    // Requête SQL pour récupérer le nombre d'hommes et de femmes
    QSqlQuery query;
    query.prepare("SELECT SEXE, COUNT(*) as count FROM CLIENT GROUP BY SEXE");

    if (query.exec()) {
        // Traiter les résultats de la requête
        while (query.next()) {
            QString gender = query.value(0).toString(); // Récupérer la valeur du sexe
            int count = query.value(1).toInt(); // Récupérer le nombre d'individus pour ce sexe

            // Vérifier si le sexe est "Homme" ou "Femme" et mettre à jour les variables
            if (gender == "Homme") {
                maleCount = count;  // Mettre à jour le nombre d'hommes
            } else if (gender == "Femme") {
                femaleCount = count;  // Mettre à jour le nombre de femmes
            }
        }

        // Créer la série pour le graphique
        QPieSeries *series = new QPieSeries();
        series->append("Homme", maleCount);
        series->append("Femme", femaleCount);

        // Créer un graphique et ajouter la série
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition par sexe");

        // Personnaliser les tranches du graphique
        for (QPieSlice *slice : series->slices()) {
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1: %2%")
                            .arg(slice->label())
                            .arg(slice->percentage() * 100, 0, 'f', 1)); // Afficher le pourcentage avec 1 décimale
        }

        // Créer le QChartView pour afficher le graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Assurer que ui->pie est un QGraphicsView et l'ajouter à la scène
        if (ui->pie) {
            chartView->setFixedSize(ui->pie->size()); // Adapter la taille à celle de ui->pie
            ui->pie->setScene(new QGraphicsScene());
            ui->pie->scene()->addWidget(chartView);
            ui->pie->scene()->update();
            ui->pie->show();
        }
    } else {
        // Si la requête échoue, afficher une erreur
        QMessageBox::critical(this, "Erreur", "Échec de la récupération des statistiques : " + query.lastError().text());
    }
}















//sms


void MainWindow::on_sendSMSButton_clicked()
{
    // Récupérer le numéro et le message depuis l'interface (par exemple, via des champs de texte)
    QString phoneNumber = ui->phoneNumberLineEdit->text();
    QString message = ui->messageTextEdit->toPlainText();

    Client client;

        // Appeler la méthode sendSMS du client
       csupp.sendSMS(phoneNumber, message);
}

// Slot pour afficher un message à l'utilisateur après l'envoi du SMS
void MainWindow::onSmsSent(bool success, const QString &message)
{
    // Afficher une boîte de dialogue avec le résultat
    if (success) {
        QMessageBox::information(this, "Succès", message);
    } else {
        QMessageBox::critical(this, "Erreur", message);
    }
}









//email

void MainWindow::on_email_clicked() {
    // Autres champs nécessaires pour l'e-mail
    QString destinataire = ui->dest->text();
    QString objet = ui->objetEmail->text();
    QString corps = ui->bodyEmail->toPlainText();

    // Récupérer les chemins des pièces jointes
    QStringList attachments;
    for (int i = 0; i < ui->attachmentsListWidget->count(); ++i) {
        QListWidgetItem *item = ui->attachmentsListWidget->item(i);
        QString filePath = item->data(Qt::UserRole).toString(); // Chemin complet
        attachments.append(filePath);                          // Ajouter à la liste
    }

    // Vérifier que tous les champs sont remplis
    if (destinataire.isEmpty() || objet.isEmpty() || corps.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Tous les champs doivent être remplis avant d'envoyer l'email.");
        return;
    }

    // Envoyer l'e-mail avec les pièces jointes
    int result = mailer::sendEmail(destinataire, objet, corps, attachments);

    if (result == 0) {
        QMessageBox::information(this, "Succès", "Email envoyé avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi de l'email.");
    }

    // Réinitialiser les champs
    ui->dest->clear();
    ui->objetEmail->clear();
    ui->bodyEmail->clear();
    ui->attachmentsListWidget->clear();
}



void MainWindow::onBrowseAttachments() {
    // Ouvrir un dialogue pour sélectionner plusieurs fichiers
    QStringList filePaths = QFileDialog::getOpenFileNames(
        this,
        tr("Sélectionner des pièces jointes"),
        QDir::homePath(),
        tr("Tous les fichiers (*)")
    );

    // Ajouter les fichiers dans la QListWidget avec des icônes
    for (const QString &filePath : filePaths) {
        if (!filePath.isEmpty()) {
            // Vérifier si le fichier est déjà ajouté
            QList<QListWidgetItem *> existingItems = ui->attachmentsListWidget->findItems(filePath, Qt::MatchExactly);
            if (existingItems.isEmpty()) {
                // Obtenir une icône basée sur le type de fichier
                QFileIconProvider iconProvider;
                QFileInfo fileInfo(filePath);
                QIcon fileIcon = iconProvider.icon(fileInfo);

                // Créer un nouvel élément pour la QListWidget
                QListWidgetItem *item = new QListWidgetItem(fileIcon, fileInfo.fileName(), ui->attachmentsListWidget);

                // Stocker le chemin complet comme donnée associée (utile pour récupérer les fichiers plus tard)
                item->setData(Qt::UserRole, filePath);

                // Ajouter l'élément à la QListWidget
                ui->attachmentsListWidget->addItem(item);
            }
        }
    }
}


void MainWindow::onRemoveAttachment() {
    QListWidgetItem *selectedItem = ui->attachmentsListWidget->currentItem();
    if (selectedItem) {
        delete selectedItem; // Supprimer l'élément sélectionné
    }
}



void MainWindow::onAttachmentDoubleClicked(QListWidgetItem *item) {
    QString filePath = item->data(Qt::UserRole).toString();
    if (!filePath.isEmpty()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
    }
}















































