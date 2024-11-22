#include "stock.h"
#include "ui_stock.h"
#include "produit.h"
#include "QMessageBox"
#include <QTableWidget>
#include <QTableView>
#include <QFileDialog>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QColor>
#include <QRandomGenerator>
#include <QPixmap>
#include <QEvent>
#include <QSoundEffect>
#include <QListWidgetItem>
#include <QTimer>
#include <QDesktopServices>
stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);
    ui->model->setModel(Etemp.afficher());
    ui->model_2->setModel(Etemp.afficher());
    connect(ui->rechercheLineEdit, &QLineEdit::textChanged, this, &stock::on_recherche_textChanged);
    updateStatistics();
    notifications();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &stock::notifications);
    timer->start(60000);
}

stock::~stock() {
    delete ui;
}

void stock::on_home_clicked() {
    this->hide();       // Hide the stock window

}
void stock::on_ajouter_clicked() {
    produit P;
    bool ok = false, ok1 = false, ok2 = false, ok3 = false, ok5 = false;
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
            ui->referenceLineEdit->setText("Entrer une reference valide");
            return;
        }
    }
    while (!ok3){
        QString nomProduit = ui->nomProduitLineEdit->text();
        QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s]+$"); // Allows alphabets, accented characters, and spaces
        QRegularExpressionMatch match = regex.match(nomProduit);
        if (nomProduit.isEmpty() || !match.hasMatch()) {
            ui->nomProduitLineEdit->clear();
            ui->nomProduitLineEdit->setPlaceholderText("Entrer un nom valide (lettres uniquement)");
            return;
        }else{
            P.setnom(nomProduit);
            ok3=true;
        }
    }
    // Validate and set price
    while (!ok1) {
        QString prix = ui->prixLineEdit->text();
        prx = prix.toFloat(&ok1);
        if (ok1) {
            P.setprix(prx);
        } else {
            ui->prixLineEdit->clear();
            ui->prixLineEdit->setText("Entrer un prix valide");
            return;
        }
    }

    // Validate and set quantity
    while (!ok2) {
        QString quantite = ui->quantiteLineEdit->text();
        quant = quantite.toInt(&ok2);

        if (ok2) {
            // Calculate the total quantity of all products in the database
            QSqlQuery query;
            query.prepare("SELECT SUM(quantite) FROM produits");
            if (query.exec() && query.next()) {
                int totalQuantite = query.value(0).toInt();

                // Check if adding this product exceeds the limit
                if (totalQuantite + quant <= 1000) {
                    P.setquant(quant); // Set the quantity if it's valid
                } else {
                    ui->quantiteLineEdit->clear();
                    ui->quantiteLineEdit->setText("Capacité dépassée !");
                    return; // Exit if the limit is exceeded
                }
            } else {
                qDebug() << "Failed to calculate total quantity: " << query.lastError().text();
                QMessageBox::critical(this, tr("Database Error"), tr("Erreur lors de la vérification de la quantité totale."));
                return;
            }
        } else {
            ui->quantiteLineEdit->clear();
            ui->quantiteLineEdit->setText("Entrer une quantité valide");
            return;
        }
    }
    // Get selected category from the combo box
    QString categorie = ui->categoriecombo->currentText();
    P.setcateg(categorie);
    QString photoPath = ui->photoPathLineEdit->text();
    QFile file(photoPath);
    if (file.exists()) {
        P.setphotopath(photoPath);
        ok5 = true;
    } else {
        ui->photoPathLineEdit->clear();
        ui->photoPathLineEdit->setText("Entrer un chemin de photo valide");
    }

    // Add the product to the table only if validation passes
    if (ok && ok1 && ok2 && ok3 && ok5) {
        bool test = P.ajouter();
        if (test) {
            ui->model->setModel(Etemp.afficher());
            ui->referenceLineEdit->clear();
            ui->nomProduitLineEdit->clear();
            ui->prixLineEdit->clear();
            ui->quantiteLineEdit->clear();
            ui->photoPathLineEdit->clear();
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
    ui->prixLineEdit->clear();
    ui->quantiteLineEdit->clear();
}


void stock::on_modifier_clicked() {
    int reference = ui->referenceLineEdit->text().toInt();
    QString nom_prod = ui->nomProduitLineEdit->text();
    QString categorie = ui->categoriecombo->currentText();
    double prix = ui->prixLineEdit->text().toFloat();
    int quantite = ui->quantiteLineEdit->text().toInt();
    QString photopath = ui->photoPathLineEdit->text();
    produit p(reference, nom_prod, categorie, prix, quantite,photopath);
    bool test = p.modifier();
    if (test)
    {
        ui->model->setModel(Etemp.afficher());
        ui->referenceLineEdit->clear();
        ui->nomProduitLineEdit->clear();
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

    // Prepare the query to fetch products sorted by 'prix'
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (isPrixAscending) {
        query.prepare("SELECT * FROM PRODUITS ORDER BY PRIX ASC"); // Ascending order
    } else {
        query.prepare("SELECT * FROM PRODUITS ORDER BY PRIX DESC"); // Descending order
    }

    query.exec();

    // Set the query result to the model
    model->setQuery(query);

    // Set the model to the TableView (model_2)
    ui->model_2->setModel(model);

    // Toggle the sorting state
    isPrixAscending = !isPrixAscending;
}

void stock::on_triparquantite_clicked()
{
    produit P;

    // Prepare the query to fetch products sorted by 'quantite'
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (isQuantiteAscending) {
        query.prepare("SELECT * FROM PRODUITS ORDER BY QUANTITE ASC"); // Ascending order
    } else {
        query.prepare("SELECT * FROM PRODUITS ORDER BY QUANTITE DESC"); // Descending order
    }

    query.exec();

    // Set the query result to the model
    model->setQuery(query);

    // Set the model to the TableView (model_2)
    ui->model_2->setModel(model);

    // Toggle the sorting state
    isQuantiteAscending = !isQuantiteAscending;
}

void stock::on_triparaz_clicked()
{
    produit P;

    // Prepare the query to fetch products sorted by 'nom_prod'
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    if (isAZAscending) {
        query.prepare("SELECT * FROM PRODUITS ORDER BY NOM_PRODUIT ASC"); // Ascending (A-Z)
    } else {
        query.prepare("SELECT * FROM PRODUITS ORDER BY NOM_PRODUIT DESC"); // Descending (Z-A)
    }

    query.exec();

    // Set the query result to the model
    model->setQuery(query);

    // Set the model to the TableView (model_2)
    ui->model_2->setModel(model);

    // Toggle the sorting state
    isAZAscending = !isAZAscending;
}




void stock::on_exportationPDF_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "", tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) {
        return; // L'utilisateur a annulé l'enregistrement
    }

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&writer);

    if (!painter.isActive()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de créer le fichier PDF."));
        return;
    }

    // Charger et afficher le logo
    QImage logo("C:/Users/chahi/OneDrive/Pictures/img/logo_meta-removebg-preview.png");
    if (!logo.isNull()) {
        // Positionner le logo en haut à droite
        int logoWidth = 1500; // Largeur du logo
        int logoHeight = 500; // Hauteur du logo
        painter.drawImage(writer.width() - logoWidth - 50, 0, logo.scaled(logoWidth, logoHeight, Qt::KeepAspectRatio));
    }

    // Définir la police et la taille
    QFont font("Arial", 12);
    painter.setFont(font);

    // Titre
    painter.drawText(3000, 100, "Liste des Produits");
    painter.drawLine(50, 150, writer.width() - 50, 150); // Ligne sous le titre

    // Espacement initial
    int y = 500;
    int margin = 100; // Marge de gauche
    int rowHeight = 400; // Hauteur entre les lignes

    // Écrire les en-têtes de colonnes
    painter.drawText(margin, y, "Reference");
    painter.drawText(margin + 2000, y, "Nom");
    painter.drawText(margin + 4000, y, "Categorie");
    painter.drawText(margin + 6000, y, "Prix");
    painter.drawText(margin + 8000, y, "Quantite");
    y += rowHeight;

    // Parcourir le modèle de table pour les données
    for (int row = 0; row < ui->model->model()->rowCount(); ++row) {
        QString reference = ui->model->model()->index(row, 0).data().toString();
        QString nom = ui->model->model()->index(row, 1).data().toString();
        QString categorie = ui->model->model()->index(row, 2).data().toString();
        QString prix = ui->model->model()->index(row, 3).data().toString();
        QString quantite = ui->model->model()->index(row, 4).data().toString();

        // Écrire les données dans le PDF
        painter.drawText(margin, y, reference);
        painter.drawText(margin + 2000, y, nom);
        painter.drawText(margin + 4000, y, categorie);
        painter.drawText(margin + 6000, y, prix);
        painter.drawText(margin + 8000, y, quantite);

        // Aller à la ligne suivante
        y += rowHeight;

        // Vérifier si la position y dépasse la hauteur de la page
        if (y > writer.height() - 100) {
            painter.end();
            writer.newPage(); // Nouvelle page si nécessaire
            painter.begin(&writer);
            painter.setFont(font); // Redéfinir la police
            y = 100; // Réinitialiser la position y
        }
    }

    painter.end();

    // Afficher un message de succès
    QMessageBox::information(this, tr("Succès"), tr("Les données ont été exportées vers le PDF avec succès."));
}






void stock::on_exportationPDF_2_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "", tr("PDF Files (*.pdf)"));
    if (filePath.isEmpty()) {
        return; // L'utilisateur a annulé l'enregistrement
    }

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&writer);

    if (!painter.isActive()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de créer le fichier PDF."));
        return;
    }

    // Charger et afficher le logo
    QImage logo("C:/Users/chahi/OneDrive/Pictures/img/logo_meta-removebg-preview.png");
    if (!logo.isNull()) {
        // Positionner le logo en haut à droite
        int logoWidth = 1500; // Largeur du logo
        int logoHeight = 500; // Hauteur du logo
        painter.drawImage(writer.width() - logoWidth - 50, 0, logo.scaled(logoWidth, logoHeight, Qt::KeepAspectRatio));
    }

    // Définir la police et la taille
    QFont font("Arial", 12);
    painter.setFont(font);

    // Titre
    painter.drawText(3000, 100, "Liste des Produits");
    painter.drawLine(50, 150, writer.width() - 50, 150); // Ligne sous le titre

    // Espacement initial
    int y = 500;
    int margin = 100; // Marge de gauche
    int rowHeight = 400; // Hauteur entre les lignes

    // Écrire les en-têtes de colonnes
    painter.drawText(margin, y, "Reference");
    painter.drawText(margin + 1000, y, "Nom");
    painter.drawText(margin + 2000, y, "Categorie");
    painter.drawText(margin + 3000, y, "Prix");
    painter.drawText(margin + 4000, y, "Quantite");
    y += rowHeight;

    // Parcourir le modèle de table pour les données
    for (int row = 0; row < ui->model_2->model()->rowCount(); ++row) {
        QString reference = ui->model_2->model()->index(row, 0).data().toString();
        QString nom = ui->model_2->model()->index(row, 1).data().toString();
        QString categorie = ui->model_2->model()->index(row, 2).data().toString();
        QString prix = ui->model_2->model()->index(row, 3).data().toString();
        QString quantite = ui->model_2->model()->index(row, 4).data().toString();

        // Écrire les données dans le PDF
        painter.drawText(margin, y, reference);
        painter.drawText(margin + 1000, y, nom);
        painter.drawText(margin + 2000, y, categorie);
        painter.drawText(margin + 3000, y, prix);
        painter.drawText(margin + 4000, y, quantite);

        // Aller à la ligne suivante
        y += rowHeight;

        // Vérifier si la position y dépasse la hauteur de la page
        if (y > writer.height() - 100) {
            painter.end();
            writer.newPage(); // Nouvelle page si nécessaire
            painter.begin(&writer);
            painter.setFont(font); // Redéfinir la police
            y = 100; // Réinitialiser la position y
        }
    }

    painter.end();

    // Afficher un message de succès
    QMessageBox::information(this, tr("Succès"), tr("Les données ont été exportées vers le PDF avec succès."));
}

void stock::on_boutonGenererGraphique_clicked() {
    // Clear the previous layout in conteneurGraphique to avoid conflicts
    QLayout *existingLayout = ui->conteneurGraphique->layout();
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0))) {
            delete item->widget();
            delete item;
        }
        delete existingLayout;
    }

    // Create a new pie series for the chart
    QPieSeries *series = new QPieSeries();

    // Get the model from the QTableView (assuming your model is assigned to the table view)
    QAbstractItemModel *tableModel = ui->model->model(); // Assuming ui->tableView is your QTableView

    // Loop through the model data and add each product's quantity to the pie chart
    int rowCount = tableModel->rowCount();  // Get row count from the model
    for (int row = 0; row < rowCount; ++row) {
        QString productName = tableModel->data(tableModel->index(row, 1)).toString();  // Assuming 'nom_prod' is in column 1
        int quantity = tableModel->data(tableModel->index(row, 4)).toInt();  // Assuming 'quantite' is in column 4

        if (quantity > 0) {  // Only add products with a non-zero quantity
            QPieSlice *slice = series->append(productName, quantity);
            slice->setLabelVisible(true);  // Show the label on the slice
        }
    }

    // If the series has no data, log an error and return
    if (series->count() == 0) {
        qDebug() << "No data found in the model for the pie chart!";
        return;
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des stocks par produit");

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  // For smooth rendering

    // Set the chart view into a new layout for conteneurGraphique
    QVBoxLayout *layout = new QVBoxLayout(ui->conteneurGraphique);
    ui->conteneurGraphique->setLayout(layout);
    layout->addWidget(chartView);

    // Resize the chart view to fit the container
    chartView->resize(ui->conteneurGraphique->size());
}

void stock::displayCatalogue()
{
    // Make sure we're working with the correct tab layout
    QWidget *catalogueTab = ui->tabWidget->widget(2);  // Assuming the Catalogue tab is at index 2 (3rd tab)

    if (!catalogueTab) {
        qDebug() << "Error: Catalogue tab not found!";
        return;
    }

    // Create a new catalogue container and grid layout
    QWidget *catalogueContainer = new QWidget();
    QGridLayout *catalogueLayout = new QGridLayout(catalogueContainer);

    // Query the database to fetch product details
    QSqlQuery query;
    query.prepare("SELECT nom_produit, reference, prix, quantite, photo_path FROM produits");

    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
        return;
    }

    int row = 0, col = 0;

    // Loop over the results and create widgets for each product
    while (query.next()) {
        QString nomProduit = query.value(0).toString();
        QString reference = query.value(1).toString();
        double prix = query.value(2).toDouble();
        int quantite = query.value(3).toInt();
        QString photoPath = query.value(4).toString();

        // Create a product container
        QWidget *productWidget = new QWidget();
        QVBoxLayout *productLayout = new QVBoxLayout(productWidget);

        // Set the background color for the product widget (light gray)
        productWidget->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 10px; padding: 10px;");

        // Photo
        QLabel *photoLabel = new QLabel();
        if (!photoPath.isEmpty()) {
            QPixmap photo(photoPath);
            photoLabel->setPixmap(photo.scaled(150, 150, Qt::KeepAspectRatio)); // Adjust size to your needs
        } else {
            photoLabel->setText("No image");
            photoLabel->setAlignment(Qt::AlignCenter);
        }

        // Product name
        QLabel *nomProduitLabel = new QLabel(nomProduit);
        nomProduitLabel->setAlignment(Qt::AlignCenter);
        nomProduitLabel->setStyleSheet("font-weight: bold; font-size: 14px;");

        // Product reference
        QLabel *referenceLabel = new QLabel("Référence: " + reference);
        referenceLabel->setAlignment(Qt::AlignCenter);
        referenceLabel->setStyleSheet("font-size: 12px;");

        // Price
        QLabel *prixLabel = new QLabel(QString::number(prix, 'f', 2) + " DT");
        prixLabel->setAlignment(Qt::AlignCenter);
        prixLabel->setStyleSheet("color: red; font-size: 12px;");

        // Stock availability (Disponible or Rupture en stock)
        QLabel *availabilityLabel = new QLabel();
        if (quantite > 0) {
            availabilityLabel->setText("Disponible");
            availabilityLabel->setStyleSheet("color: green; font-size: 12px;");
        } else {
            availabilityLabel->setText("Rupture en stock");
            availabilityLabel->setStyleSheet("color: red; font-size: 12px;");
        }

        // Add components to the product layout
        productLayout->addWidget(photoLabel);
        productLayout->addWidget(nomProduitLabel);
        productLayout->addWidget(referenceLabel);  // Add reference under the product name
        productLayout->addWidget(prixLabel);
        productLayout->addWidget(availabilityLabel);  // Add availability status

        // Add the product widget to the grid layout
        catalogueLayout->addWidget(productWidget, row, col);

        // Adjust the grid layout position
        col++;
        if (col == 3) { // Adjust this number for the number of columns in a row
            col = 0;
            row++;
        }

        // Set hover effect on product widget
        productWidget->setCursor(Qt::PointingHandCursor);  // Change cursor to hand on hover

        // Connect hover events to handle border color and zoom effect
        productWidget->installEventFilter(this); // Install an event filter to handle hover
        productWidget->setProperty("defaultStyle", true); // Set a custom property to identify the product widget
    }

    // Create a scroll area for the catalogue and set its widget to the catalogue container
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(catalogueContainer);
    scrollArea->setWidgetResizable(true);

    // Clear previous content in the catalogue tab before adding new content
    QVBoxLayout *tabLayout = qobject_cast<QVBoxLayout *>(catalogueTab->layout());
    if (tabLayout) {
        // Clear the layout before adding the new scroll area
        QLayoutItem *child;
        while ((child = tabLayout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    } else {
        // If there's no layout yet, create one
        tabLayout = new QVBoxLayout(catalogueTab);
    }

    // Add the scroll area to the layout of the Catalogue tab
    tabLayout->addWidget(scrollArea);
}

bool stock::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter || event->type() == QEvent::Leave) {
        QWidget *productWidget = qobject_cast<QWidget *>(obj);
        if (productWidget) {
            // Handle hover effect (border color change and photo zoom)
            if (event->type() == QEvent::Enter) {
                // Change background and border color on hover
                productWidget->setStyleSheet("background-color: #e0e0e0; border: 2px solid darkblue; border-radius: 10px; padding: 10px;");

                // Find the QLabel containing the photo
                QLabel *photoLabel = productWidget->findChild<QLabel *>();
                if (photoLabel) {
                    QPixmap pixmap = photoLabel->pixmap(); // Get the pixmap by value
                    if (!pixmap.isNull()) {
                        QPixmap scaledPixmap = pixmap.scaled(180, 180, Qt::KeepAspectRatio);
                        photoLabel->setPixmap(scaledPixmap);  // Zoom the image slightly on hover
                    } else {
                        qDebug() << "No valid pixmap found for photoLabel.";
                    }
                } else {
                    qDebug() << "No QLabel found in product widget.";
                }
            } else if (event->type() == QEvent::Leave) {
                // Reset background and border color when hover ends
                productWidget->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 10px; padding: 10px;");

                // Find the QLabel containing the photo
                QLabel *photoLabel = productWidget->findChild<QLabel *>();
                if (photoLabel) {
                    QPixmap pixmap = photoLabel->pixmap(); // Get the pixmap by value
                    if (!pixmap.isNull()) {
                        QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio);
                        photoLabel->setPixmap(scaledPixmap);  // Reset the image size when not hovered
                    } else {
                        qDebug() << "No valid pixmap found for photoLabel.";
                    }
                } else {
                    qDebug() << "No QLabel found in product widget.";
                }
            }
        }
        return true; // Return true to indicate the event was handled
    }
    return QObject::eventFilter(obj, event); // Pass the event on to the parent handler
}



void stock::on_tabWidget_currentChanged(int index)
{
    if (index == 2) { // Index 2 is the Catalogue tab
        displayCatalogue(); // Display catalogue when Catalogue tab is selected
    }
}

void stock::on_recherche_textChanged(const QString &input) {
    if (input.isEmpty()) {
        // If the input is empty, clear the table view or show all products.
        ui->model_2->setModel(Etemp.afficher());
        return;
    }

    // Prepare a query to find matching products by reference or name.
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM PRODUITS WHERE REFERENCE LIKE :input OR NOM_PRODUIT LIKE :input");
    query.bindValue(":input", "%" + input + "%");
    query.exec();
    model->setQuery(query);

    // Set the model to display the results.
    ui->model_2->setModel(model);
}

void stock::on_exportbutton_clicked()
{
    // Open a file dialog for selecting a photo
    QString photoPath = QFileDialog::getOpenFileName(this, tr("Select Photo"), "", tr("Images (*.png *.jpg *.jpeg)"));

    if (!photoPath.isEmpty()) {
        // Set the chosen photo path in the line edit
        ui->photoPathLineEdit->setText(photoPath);
    } else {
        // Display a placeholder message if no photo is chosen
        ui->photoPathLineEdit->setText("choisir photo");
    }
}
void stock::updateStatistics()
{
    // Variables to store results
    QString mostAvailableProduct;
    int mostAvailableQuantity = 0;

    QString mostExpensiveProduct;
    double highestPrice = 0.0;

    int outOfStockCount = 0;

    int totalQuantity = 0; // Total quantity of all products in the store

    // Query to fetch all required data
    QSqlQuery query;
    query.prepare("SELECT nom_produit, quantite, prix FROM produits");

    if (!query.exec()) {
        qDebug() << "Error fetching product statistics:" << query.lastError().text();
        ui->plusdisponible->setText("Erreur");
        ui->pluschere->setText("Erreur");
        ui->produitreptureenstock->setText("Erreur");
        ui->espacerest->setText("Erreur");
        return;
    }

    // Process the results
    while (query.next()) {
        QString nomProduit = query.value(0).toString();
        int quantite = query.value(1).toInt();
        double prix = query.value(2).toDouble();

        // Find the most available product
        if (quantite > mostAvailableQuantity) {
            mostAvailableProduct = nomProduit;
            mostAvailableQuantity = quantite;
        }

        // Find the most expensive product
        if (prix > highestPrice) {
            mostExpensiveProduct = nomProduit;
            highestPrice = prix;
        }

        // Count products with quantity = 0
        if (quantite == 0) {
            outOfStockCount++;
        }

        // Calculate the total quantity in the store
        totalQuantity += quantite;
    }

    // Update the UI with results
    if (!mostAvailableProduct.isEmpty()) {
        ui->plusdisponible->setText(mostAvailableProduct + " (" + QString::number(mostAvailableQuantity) + ")");
    } else {
        ui->plusdisponible->setText("Aucun produit disponible");
    }

    if (!mostExpensiveProduct.isEmpty()) {
        ui->pluschere->setText(mostExpensiveProduct + " (" + QString::number(highestPrice, 'f', 2) + " DT)");
    } else {
        ui->pluschere->setText("Aucun produit cher");
    }

    ui->produitreptureenstock->setText(QString::number(outOfStockCount));

    // Calculate remaining space in the storage
    int espaceTotal = 1000; // Maximum storage capacity
    int espaceRestant = espaceTotal - totalQuantity;

    // Display the remaining space
    if (espaceRestant >= 0) {
        ui->espacerest->setText(QString::number(espaceRestant) + " places restantes");
    } else {
        ui->espacerest->setText("Dépassement de capacité !");
    }
}
void stock::notifications() {
    // Query to get all products that have quantity 0 (rupture de stock)
    QSqlQuery query;
    query.prepare("SELECT * FROM produits WHERE quantite = 0");
    if (query.exec()) {
        // Create a set to store product references that have triggered the sound
        static QSet<int> soundPlayedForProductRefs;

        // Clear the notifications list widget before updating it
        ui->notificationsListWidget->clear();

        bool noProductInStock = true;

        while (query.next()) {
            QString nomProduit = query.value("nom_produit").toString();
            int refProduit = query.value("reference").toInt();

            // Add product to the list widget
            QString notificationText = QString("Le produit \"%1\" est en rupture de stock.").arg(nomProduit);
            ui->notificationsListWidget->addItem(notificationText);

            // Check if sound has already been played for this product
            if (!soundPlayedForProductRefs.contains(refProduit)) {
                // Play sound for the product if it's not already played
                QSoundEffect *soundEffect = new QSoundEffect(this);
                soundEffect->setSource(QUrl::fromLocalFile("C:/Users/chahi/Downloads/mixkit-software-interface-start-2574.wav"));
                soundEffect->play();

                // Mark the product as having played the sound
                soundPlayedForProductRefs.insert(refProduit);
            }

            noProductInStock = false; // At least one product in rupture de stock
        }

        // If no product is in rupture de stock, show a message
        if (noProductInStock) {
            ui->notificationsListWidget->addItem("Aucun produit n'est en rupture de stock.");
        }
    } else {
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}



void stock::on_pushButton_2_clicked()
{
    notifications();
}


void stock::on_deleteProductButton_clicked()
{
    // Get the selected product's reference from the list widget
    QListWidgetItem *selectedItem = ui->notificationsListWidget->currentItem();

    if (!selectedItem) {
        QMessageBox::warning(this, "Suppression", "Veuillez sélectionner un produit à supprimer.");
        return;
    }

    // Extract the reference from the notification text (assuming the format: "Le produit 'Nike Air Jordan'...")
    QString notificationText = selectedItem->text();
    QString productName;

    // Adjust extraction based on the expected format
    QString prefix = "Le produit \"";
    QString suffix = "\" est en rupture de stock.";

    if (notificationText.startsWith(prefix) && notificationText.endsWith(suffix)) {
        int startIndex = prefix.length();
        int endIndex = notificationText.length() - suffix.length();
        productName = notificationText.mid(startIndex, endIndex - startIndex);
    } else {
        QMessageBox::warning(this, "Erreur", "Format de notification invalide.");
        return;
    }
    // Confirmation dialog
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Confirmation de suppression",
        "Vous êtes sur le point de supprimer le produit '" + productName + "'. Êtes-vous sûr ?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::No) {
        return; // User canceled the deletion
    }

    // Query the database to get the reference for the product name
    QSqlQuery query;
    query.prepare("SELECT REFERENCE FROM PRODUITS WHERE NOM_PRODUIT = :nomProduit");
    query.bindValue(":nomProduit", productName);

    if (query.exec() && query.next()) {
        int productRef = query.value(0).toInt();

        // Call the supprimer function directly
        if (produit().supprimer(productRef)) {
            QMessageBox::information(this, "Succès", "Le produit '" + productName + "' a été supprimé avec succès.");
            delete selectedItem; // Remove the item from the list widget
        } else {
            QMessageBox::critical(this, "Échec", "Échec de la suppression du produit.");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Produit non trouvé dans la base de données.");
    }
}


void stock::on_contactfourniButton_clicked()
{
    // Get the selected product's reference from the list widget
    QListWidgetItem *selectedItem = ui->notificationsListWidget->currentItem();

    if (!selectedItem) {
        QMessageBox::warning(this, "Contact Fournisseur", "Veuillez sélectionner un produit pour contacter son fournisseur.");
        return;
    }

    // Extract the product name from the notification text
    QString notificationText = selectedItem->text();
    QString productName;

    // Adjust extraction based on the expected format
    QString prefix = "Le produit \"";
    QString suffix = "\" est en rupture de stock.";

    if (notificationText.startsWith(prefix) && notificationText.endsWith(suffix)) {
        int startIndex = prefix.length();
        int endIndex = notificationText.length() - suffix.length();
        productName = notificationText.mid(startIndex, endIndex - startIndex);
    } else {
        QMessageBox::warning(this, "Erreur", "Format de notification invalide.");
        return;
    }

    // Query the database for supplier details
    QSqlQuery query;
    query.prepare("SELECT F.ID_FOURNISSEUR, F.adresse FROM PRODUITS P INNER JOIN FOURNISSEURS F ON P.ID_FOURNISSEUR = F.ID_FOURNISSEUR WHERE P.NOM_PRODUIT = :nomProduit");
    query.bindValue(":nomProduit", productName);

    if (query.exec() && query.next()) {
        int supplierId = query.value(0).toInt();
        QString supplierEmail = query.value(1).toString();

        // Create a message box with a custom button to access Gmail
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fournisseur Contact");
        msgBox.setText(
            "Fournisseur ID: " + QString::number(supplierId) +
            "\nEmail: " + supplierEmail +
            "\n\nCliquez sur le bouton ci-dessous pour accéder à Gmail."
            );

        QPushButton *openGmailButton = msgBox.addButton("Ouvrir Gmail", QMessageBox::ActionRole);
        QPushButton *closeButton = msgBox.addButton(QMessageBox::Close);

        msgBox.exec();

        if (msgBox.clickedButton() == openGmailButton) {
            // Open the Gmail URL
            QDesktopServices::openUrl(QUrl("https://workspace.google.com/intl/fr/gmail/"));
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Fournisseur non trouvé pour ce produit.");
    }
}

