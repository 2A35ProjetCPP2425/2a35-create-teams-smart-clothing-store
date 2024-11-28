#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"  // Ensure the Employe class is included
#include <QMessageBox> // For displaying messages
#include <QSqlQueryModel> // To display data
#include <QSqlQuery>  // Make sure this is included for QSqlQuery
#include <QSqlError>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>



MainWindow::MainWindow(const QString &email, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize the proxy model only once
    proxyModel = new QSortFilterProxyModel(this);
    ui->tableView->setModel(proxyModel);  // Set the proxy model to the table view

    // Setup the search functionality
    setupSearchFunctionality();

    // Connect buttons to corresponding slots
    connect(ui->ajouterButton, &QPushButton::clicked, this, &MainWindow::on_ajouterButton_clicked);
    connect(ui->supprimerButton, &QPushButton::clicked, this, &MainWindow::on_supprimerButton_clicked);
    connect(ui->modifierButton, &QPushButton::clicked, this, &MainWindow::on_modifierButton_clicked);
    connect(ui->trierButton, &QPushButton::clicked, this, &MainWindow::on_trierButton_clicked);
    connect(ui->telechargerButton, &QPushButton::clicked, this, &MainWindow::on_telechargerButton_clicked);
    connect(ui->stats1, &QPushButton::clicked, this, &MainWindow::displayPosteStatistics);
    connect(ui->stats2, &QPushButton::clicked, this, &MainWindow::displayEmployeeStatsByYear);
    connect(ui->matricule, &QLineEdit::editingFinished, this, &MainWindow::on_idEmpChanged);
    connect(ui->soumettre_3, &QPushButton::clicked, this, &MainWindow::on_soumettreButton_clicked);
    connect(ui->matricule, &QLineEdit::textChanged, this, &::MainWindow::onIdChanged);
    connect(ui->acceptation_2, &QPushButton::clicked, this, &MainWindow::on_acceptation_clicked);
    connect(ui->refuser_2, &QPushButton::clicked, this, &MainWindow::on_refuser_clicked);

    // Remplir la QComboBox avec des postes prédéfinis
    ui->comboBox->addItems({"Manager", "Développeur", "Analyste", "Comptable", "Technicien"});

    // Display existing employees on startup
    Employe employe;
    QSqlQueryModel* model = employe.afficher();  // Get the model from the database
    proxyModel->setSourceModel(model);  // Set the source model for proxy model
}

MainWindow::~MainWindow() {
    delete ui;
}
// Fonction d'ajout d'un employé
void MainWindow::on_ajouterButton_clicked() {
    QString nom = ui->lineEdit_2->text();
    QString mail = ui->lineEdit_3->text();
    QString poste = ui->comboBox->currentText();  // Récupérer le poste sélectionné
    QDate dateEmb = ui->dateEdit->date();
    float salaire = ui->lineEdit_5->text().toFloat();

    Employe employe(0, nom, mail, poste, dateEmb, salaire);

    if (employe.ajouter()) {
        QMessageBox::information(this, "Ajout réussi", "L'employé a été ajouté avec succès.");
        ui->tableView->setModel(employe.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé.");
    }
}

// Fonction de modification d'un employé
void MainWindow::on_modifierButton_clicked() {
    int matricule = ui->lineEdit_10->text().toInt();
    if (matricule == 0) {
        QMessageBox::warning(this, "Erreur d'entrée", "L'ID de l'employé pour modification est vide ou invalide.");
        return;
    }

    QString nom = ui->lineEdit_2->text().trimmed();
    QString mail = ui->lineEdit_3->text().trimmed();
    QString poste = ui->comboBox->currentText();  // Récupérer le poste sélectionné
    QDate dateEmb = ui->dateEdit->date();
    float salaire = ui->lineEdit_5->text().toFloat();

    Employe employe;
    employe.setMatricule(matricule);
    employe.setNom(nom);
    employe.setMail(mail);
    employe.setPoste(poste);
    employe.setDateemb(dateEmb);
    employe.setSalaire(salaire);

    if (employe.matriculeExists(matricule)) {
        if (employe.modifier()) {
            QMessageBox::information(this, "Succès", "Les informations de l'employé ont été modifiées avec succès.");
            ui->tableView->setModel(employe.afficher());
        } else {
            QMessageBox::warning(this, "Échec", "Échec de la modification des informations de l'employé.");
        }
    } else {
        QMessageBox::information(this, "Échec", "L'ID de l'employé pour modification n'existe pas.");
    }
}

// Fonction de suppression d'un employé
void MainWindow::on_supprimerButton_clicked() {
    int matricule = ui->lineEdit_10->text().toInt();

    Employe employe;

    if (employe.supprimer(matricule)) {
        QMessageBox::information(this, "Suppression réussie", "L'employé a été supprimé avec succès.");
        ui->tableView->setModel(employe.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'employé.");
    }
}


void MainWindow::on_trierButton_clicked() {
    // Retrieve the selected criterion and sort order
    QString critere = ui->comboBoxTri->currentText();  // Single combo box for sorting criteria
    QString ordre = ui->comboBoxOrdre->currentText();   // Order (Ascending or Descending)

    // Debugging output to confirm selected criteria and order
    qDebug() << "Selected criterion:" << critere;
    qDebug() << "Selected order:" << ordre;

    // Determine the sort order (ascending or descending)
    Qt::SortOrder sortOrder;
    if (ordre == "Croissant") {
        sortOrder = Qt::AscendingOrder;
    } else if (ordre == "Décroissant") {
        sortOrder = Qt::DescendingOrder;
    } else {
        QMessageBox::warning(this, "Erreur", "Ordre de tri invalide.");
        return;
    }

    qDebug() << "SortOrder value:" << (sortOrder == Qt::AscendingOrder ? "Ascending" : "Descending");

    // Map criterion to column index
    int sortColumnIndex = -1;
    if (critere == "Salaire") {
        sortColumnIndex = 5;  // Assuming "salaire" is in column 5
    } else if (critere == "Matricule") {
        sortColumnIndex = 0;  // Assuming "matricule" is in column 0
    } else if (critere == "Date d'embauche") {
        sortColumnIndex = 4;  // Assuming "dateemb" is in column 4
    } else {
        QMessageBox::warning(this, "Erreur", "Critère de tri invalide.");
        return;
    }

    qDebug() << "Sorting column:" << sortColumnIndex;

    // Ensure proxy model is created and reused
    static QSortFilterProxyModel* proxyModel = nullptr;
    if (!proxyModel) {
        proxyModel = new QSortFilterProxyModel(this);
        proxyModel->setSourceModel(ui->tableView->model());
        ui->tableView->setModel(proxyModel);
    }

    // Apply sorting based on the selected criterion
    if (sortColumnIndex != -1) {
        proxyModel->sort(sortColumnIndex, sortOrder);
    }
}

void MainWindow::setupSearchFunctionality() {
    // Connect the lineEdit for dynamic searching
    connect(ui->lineEditRecherche, &QLineEdit::textChanged, this, [this](const QString &text) {
        // Set the filter to search across all columns
        proxyModel->setFilterKeyColumn(-1);  // -1 means search all columns
        proxyModel->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
        // Optionally, you can log or print the text being searched
        qDebug() << "Searching for:" << text;
    });
}

void MainWindow::on_telechargerButton_clicked() {
    Employe employe;
    employe.telechargerPDF();  // Call the method to generate and download the PDF
}

void MainWindow::displayPosteStatistics() {
    // Query to get the count of employees by poste
    QSqlQuery query;
    query.prepare(
        "SELECT poste, COUNT(*) as count "
        "FROM employe "
        "GROUP BY poste"
        );

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Create a Pie Chart Series
    QPieSeries *series = new QPieSeries();

    // Process the query results and populate the pie chart series
    while (query.next()) {
        QString poste = query.value("poste").toString();
        int count = query.value("count").toInt();

        // Add each poste and its count as a slice in the pie chart
        QPieSlice *slice = series->append(poste, count);

        // Optionally, customize the slice (e.g., show labels and percentages)
        slice->setLabelVisible(true);
        slice->setLabel(QString("%1: %2 employees (%3%)")
                            .arg(poste)
                            .arg(count)
                            .arg(slice->percentage() * 100, 0, 'f', 1));
    }

    // Create the chart and add the pie series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employee Distribution by Poste");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create a chart view and set antialiasing for better visuals
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set a fixed size for the chart view to make it smaller
    chartView->setFixedSize(600, 400); // Adjust the size as needed

    // Set up the QGraphicsView
    ui->graphicsView->setScene(new QGraphicsScene());

    // Add the chart view to the scene
    ui->graphicsView->scene()->addWidget(chartView);

    // Use fitInView to make sure the chart fits within the view's scene, but keep the aspect ratio
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);

    // Refresh the scene and display the chart
    ui->graphicsView->scene()->update();
    ui->graphicsView->show();
}

void MainWindow::displayEmployeeStatsByYear() {
    // Query to get the count of employees hired by year
    QSqlQuery query;
    query.prepare(
        "SELECT TO_CHAR(dateemb, 'YYYY') AS year, COUNT(*) AS employee_count "
        "FROM employe "
        "GROUP BY TO_CHAR(dateemb, 'YYYY') "
        "ORDER BY year"
        );

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    // Create a Bar Series
    QBarSeries *series = new QBarSeries();

    // Create a bar set for the employee count
    QBarSet *set = new QBarSet("Employees Hired");

    // List to hold the years for the X-axis
    QStringList years;

    // Process the query results and populate the bar set
    while (query.next()) {
        QString year = query.value("year").toString();
        int count = query.value("employee_count").toInt();

        // Add the employee count to the bar set
        *set << count;

        // Add the year to the list for the X-axis categories
        years << year;
    }

    // Add the bar set to the series
    series->append(set);

    // Create the chart and add the bar series
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Employees Hired per Year");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Set categories for the X-axis (actual years from the query)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(years);  // Set actual years as categories on the X-axis
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Set the Y-axis (employee count)
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);  // Adjust the range according to your data
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create the chart view and set antialiasing for better visuals
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set a fixed size for the chart view
    chartView->setFixedSize(600, 400);  // Adjust the size as needed

    // Set up the QGraphicsView
    ui->graphicsView->setScene(new QGraphicsScene());

    // Add the chart view to the scene
    ui->graphicsView->scene()->addWidget(chartView);

    // Use fitInView to make sure the chart fits within the view's scene, but keep the aspect ratio
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);

    // Refresh the scene and display the chart
    ui->graphicsView->scene()->update();
    ui->graphicsView->show();
}
void MainWindow::populateEmployeeInfo() {
    // Créer une instance de la classe Employe
    Employe emp;

    // Récupérer et nettoyer l'entrée utilisateur
    QString matricule = ui->matricule->text().trimmed();  // Changed from id_p to matricule

    // Vérifier si le matricule est vide
    if (matricule.isEmpty()) {
        QMessageBox::warning(this, "Entrée invalide", "Veuillez saisir un matricule d'employé.");
        return;
    }

    // Variables pour stocker les détails de l'employé
    QString nom, email, poste;

    // Tenter de récupérer les détails de l'employé via le matricule
    bool employeeFound = emp.getEmployeeDetailsById(matricule, nom, email, poste);  // Method name updated

    // Afficher les détails pour vérification dans la console
    qDebug() << "Matricule:" << matricule << ", Nom:" << nom
             << ", Email:" << email << ", Poste:" << poste;

    if (employeeFound) {
        // Si l'employé est trouvé, mettre à jour les champs de l'interface utilisateur
        ui->nom_conge_3->setText(nom);
        ui->email_conge_3->setText(email);
        ui->date_debut_3->setDate(QDate::currentDate());
        ui->date_fin_3->setDate(QDate::currentDate());
        ui->poste_conge_3->setText(poste);


    } else {
        // Si l'employé n'est pas trouvé, afficher un message d'erreur
        QMessageBox::warning(this, "Erreur", "Aucun employé trouvé avec le matricule " + matricule + ".");
        ui->matricule->clear(); // Effacer l'entrée de l'utilisateur pour une nouvelle tentative
    }
}

void MainWindow::on_idEmpChanged() {
    populateEmployeeInfo();  // Call the function when the ID is changed
}

void MainWindow::on_soumettreButton_clicked()
{
    // Créer une instance de la classe Personel
    Employe emp;

    // Récupérer les valeurs des champs du formulaire
    QString matricule = ui->matricule->text().trimmed();  // Changed from id_p to matricule
    QString nom = ui->nom_conge_3->text().trimmed();
    QString email = ui->email_conge_3->text().trimmed();
    QString raison = ui->raison_conge_3->text().trimmed();
    QString poste = ui->poste_conge_3->text().trimmed();
    QDate date_d = ui->date_debut_3->date();
    QDate date_f = ui->date_fin_3->date();

    // Conversion de matricule en entier
    int id_emp = matricule.toInt();

    // Vérification des champs obligatoires
    if (matricule.isEmpty() || nom.isEmpty() || email.isEmpty() ||
        raison.isEmpty() || poste.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs avant de soumettre.");
        return;
    }

    // Validation de l'email (expression régulière)
    QRegularExpression emailRegex(
        R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir une adresse email valide.");
        return;
    }

    // Vérification de la logique des dates
    if (date_d > date_f) {
        QMessageBox::warning(this, "Erreur", "La date de début doit être antérieure à la date de fin.");
        return;
    }

    // Vérifier si l'employé a déjà un congé en cours
    if (emp.hasOngoingLeave(id_emp)) {
        QMessageBox::warning(this, "Erreur", "Cet employé a déjà un congé en cours.");
        return;
    }

    // Appeler la méthode ajouterconge pour insérer le congé (without prenom)
    if (emp.ajouterConge(id_emp, nom, email, raison, poste, date_d, date_f)) {
        QMessageBox::information(this, "Succès", "Le congé a été ajouté avec succès !");
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du congé. Veuillez réessayer.");
    }

    // Rafraîchir le modèle de la vue après l'ajout
    QSqlQueryModel *model = emp.afficherconge();
    ui->afficher_conge_2->setModel(model);
    ui->afficher_conge_2->resizeColumnsToContents();

    refreshTableView();  // Assuming this updates the view/UI elements
}

void MainWindow::refreshTableView()
{
    // Refresh the table model
    QSqlQueryModel *model = cmp.afficherconge();
    ui->afficher_conge_2->setModel(model);

    // Resize the columns to fit content
    ui->afficher_conge_2->resizeColumnsToContents();

    // Reconnect the selection model to the onSelectionChanged slot
    connect(ui->afficher_conge_2->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::onSelectionChanged);
}
void MainWindow::onSelectionChanged(const QItemSelection &selected)
{
    // Check if something is selected
    if (!selected.isEmpty()) {
        // Get the first selected index (row, column)
        QModelIndex index = selected.indexes().first();

        // Check if the selected column is the one containing the 'id_conge' (assuming column 0)
        if (index.column() == 0) {
            // Retrieve the 'id_conge' from the model (assuming it's the first column)
            QString id_conge = ui->afficher_conge_2->model()->data(index).toString();
            // Set the 'id_conge' value in the QLineEdit (id_emp_3)
            ui->id_emp_7->setText(id_conge);

            // Enable the buttons (assuming buttons are named acceptation and refuser)
            ui->acceptation_2->setEnabled(true);
            ui->refuser_2->setEnabled(true);


        }
    }
    else {
        // If no row is selected (i.e., selection is cleared), clear the QLineEdit
        ui->id_emp_7->clear();

        // Disable the buttons when no row is selected
        ui->acceptation_2->setEnabled(false);
        ui->refuser_2->setEnabled(false);
    }
}

void MainWindow::onIdChanged()
{
    // Enable all other fields if the matricule field is not empty
    QString matricule = ui->matricule->text();  // Changed from id_p to matricule

    if (matricule.isEmpty()) {
        // Clear and disable fields if matricule is empty
        ui->nom_conge_3->clear();
        ui->email_conge_3->clear();
        // ui->poste_conge_3->setCurrentIndex(0);  // Uncomment if needed
        ui->date_debut_3->setDate(QDate::currentDate());
        ui->date_fin_3->setDate(QDate::currentDate());

        // Disable relevant fields
        ui->nom_conge_3->setEnabled(false);
        ui->email_conge_3->setEnabled(false);
        ui->poste_conge_3->setEnabled(false);
        ui->raison_conge_3->setEnabled(false);
        ui->date_debut_3->setEnabled(false);
        ui->date_fin_3->setEnabled(false);
        ui->soumettre_3->setEnabled(false);
    } else {
        // Enable relevant fields if matricule is not empty
        ui->nom_conge_3->setEnabled(true);
        ui->email_conge_3->setEnabled(true);
        ui->poste_conge_3->setEnabled(true);
        ui->raison_conge_3->setEnabled(true);
        ui->date_debut_3->setEnabled(true);
        ui->date_fin_3->setEnabled(true);
        ui->soumettre_3->setEnabled(true);
    }
}

void MainWindow::on_acceptation_clicked()
{
    // Get the selected index from the table view
    QModelIndexList selectedIndexes = ui->afficher_conge_2->selectionModel()->selectedRows();

    // Check if there is a selection
    if (!selectedIndexes.isEmpty()) {
        // Get the first selected row (we assume it's a single row selection)
        QModelIndex index = selectedIndexes.first();

        // Get the 'id_conge' from the selected row (assuming it's in column 0)
        QString id_conge = ui->afficher_conge_2->model()->data(index.sibling(index.row(), 0)).toString();

        // Call the method in Personel.cpp to update the 'etat' column
        Employe emp;
        if (emp.updateCongeStatus(id_conge, "accepter")) {
            qDebug() << "Record updated successfully!";
        } else {
            qDebug() << "Error updating record!";
        }
    }

    // Refresh the table view
    QSqlQueryModel *model = cmp.afficherconge();
    ui->afficher_conge_2->setModel(model);

    // Optionally, resize the columns to fit the content
    ui->afficher_conge_2->resizeColumnsToContents();
    ui->acceptation_2->setEnabled(false);
    ui->refuser_2->setEnabled(false);
    // Clear any input fields (if applicable)
    ui->matricule->clear();
    refreshTableView();
}

void MainWindow::on_refuser_clicked()
{
    // Get the selected index from the table view
    QModelIndexList selectedIndexes = ui->afficher_conge_2->selectionModel()->selectedRows();

    // Check if there is a selection
    if (!selectedIndexes.isEmpty()) {
        // Get the first selected row (we assume it's a single row selection)
        QModelIndex index = selectedIndexes.first();

        // Get the 'id_conge' from the selected row (assuming it's in column 0)
        QString id_conge = ui->afficher_conge_2->model()->data(index.sibling(index.row(), 0)).toString();

        // Call the method in Personel.cpp to update the database
        Employe employe;
        if (employe.updateCongeStatus(id_conge, "refuser")) {
            qDebug() << "Record updated successfully!";
        } else {
            qDebug() << "Error updating record!";
        }
    }

    // Refresh the table view to reflect database changes
    QSqlQueryModel *model = cmp.afficherconge();
    ui->afficher_conge_2->setModel(model);

    // Optionally, resize the column to fit the content
    ui->afficher_conge_2->resizeColumnsToContents();

    // Clear the selection after update
    ui->afficher_conge_2->selectionModel()->clearSelection();
    // Disable the buttons when no row is selected
    ui->acceptation_2->setEnabled(false);
    ui->refuser_2->setEnabled(false);
    ui->matricule->clear();
    refreshTableView();

}

void MainWindow::onUpdateTypeCongeClicked() {
    Employe emp;
    emp.updateTypeConge();
}
