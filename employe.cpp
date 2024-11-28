#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QRandomGenerator>


// Constructeur par défaut
Employe::Employe() : matricule(0), salaire(0.0) {}

// Constructeur avec paramètres
Employe::Employe(int matricule, const QString& nom, const QString& mail,
                 const QString& poste, const QDate& dateemb, float salaire)
    : matricule(matricule), nom(nom), mail(mail), poste(poste), dateemb(dateemb), salaire(salaire) {}

// Getters
int Employe::getMatricule() const { return matricule; }
QString Employe::getNom() const { return nom; }
QString Employe::getMail() const { return mail; }
QString Employe::getPoste() const { return poste; }
QDate Employe::getDateemb() const { return dateemb; }
float Employe::getSalaire() const { return salaire; }

// Setters avec contrôle de saisie
void Employe::setMatricule(int matricule) {
    if (matricule >= 0) {
        this->matricule = matricule;
    } else {
        qDebug() << "Erreur: Le matricule doit être un entier positif.";
    }
}

void Employe::setNom(const QString& nom) {
    if (!nom.isEmpty() && nom.size() <= 50) {
        this->nom = nom;
    } else {
        qDebug() << "Erreur: Le nom ne doit pas être vide et doit contenir au maximum 50 caractères.";
    }
}

void Employe::setMail(const QString& mail) {
    static const QRegularExpression emailRegex(R"(^[\w\.\-]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,}$)"); // Déclaration statique
    if (emailRegex.match(mail).hasMatch()) {
        this->mail = mail;
    } else {
        qDebug() << "Erreur: Format d'email invalide.";
    }
}


void Employe::setPoste(const QString& poste) {
    if (!poste.isEmpty() && poste.size() <= 30) {
        this->poste = poste;
    } else {
        qDebug() << "Erreur: Le poste ne doit pas être vide et doit contenir au maximum 30 caractères.";
    }
}

void Employe::setDateemb(const QDate& dateemb) {
    if (dateemb.isValid() && dateemb <= QDate::currentDate()) {
        this->dateemb = dateemb;
    } else {
        qDebug() << "Erreur: La date d'embauche est invalide ou dans le futur.";
    }
}

void Employe::setSalaire(float salaire) {
    if (salaire > 0) {
        this->salaire = salaire;
    } else {
        qDebug() << "Erreur: Le salaire doit être un nombre positif.";
    }
}

// Vérifie si un matricule existe
bool Employe::matriculeExists(int matricule) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE matricule = :matricule");
    query.bindValue(":matricule", matricule);
    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// Génère un matricule unique
int Employe::genererMatricule() {
    QSqlQuery query;
    query.prepare("SELECT MAX(matricule) FROM EMPLOYE");

    if (query.exec()) {
        if (query.next()) {
            int maxMatricule = query.value(0).toInt();
            qDebug() << "Matricule maximum existant:" << maxMatricule;
            return maxMatricule + 1;
        } else {
            qDebug() << "Aucun résultat trouvé pour MAX(matricule).";
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête pour générer le matricule:"
                 << query.lastError().text();
    }
    return 1; // Valeur par défaut si une erreur se produit
}


// Méthode pour ajouter un employé
bool Employe::ajouter() {
    if (!validateInputs()) {
        qDebug() << "Validation des entrées échouée.";
        return false;
    }

    QSqlQuery query;
    int matricule = genererMatricule();
    qDebug() << "Matricule généré:" << matricule;

    query.prepare("INSERT INTO EMPLOYE (matricule, nom, mail, poste, dateemb, salaire) "
                  "VALUES (:matricule, :nom, :mail, :poste, TO_DATE(:dateemb, 'YYYY-MM-DD'), :salaire)");

    query.bindValue(":matricule", matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":mail", mail);
    query.bindValue(":poste", poste);
    query.bindValue(":dateemb", dateemb.toString("yyyy-MM-dd"));  // Date formatée pour Oracle
    query.bindValue(":salaire", salaire);


    qDebug() << "Requête SQL préparée:" << query.executedQuery();

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout de l'employé:" << query.lastError().text();
        return false;
    }

    qDebug() << "Employé ajouté avec succès.";
    return true;
}


// Méthode pour afficher les employés
QSqlQueryModel* Employe::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE ORDER BY matricule ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mail"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date Embauche"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
    return model;
}

// Méthode pour modifier un employé
bool Employe::modifier() {
    if (!validateInputs()) {
        return false;  // Stop if validation fails
    }

    QSqlQuery query;

    // Use TO_DATE for the date field to avoid the ORA-01861 error
    query.prepare("UPDATE EMPLOYE SET nom = :nom, mail = :mail, poste = :poste, "
                  "dateemb = TO_DATE(:dateemb, 'YYYY-MM-DD'), salaire = :salaire WHERE matricule = :matricule");

    query.bindValue(":nom", nom);
    query.bindValue(":mail", mail);
    query.bindValue(":poste", poste);
    query.bindValue(":dateemb", dateemb.toString("yyyy-MM-dd"));  // Format the date as 'YYYY-MM-DD'
    query.bindValue(":salaire", salaire);
    query.bindValue(":matricule", matricule);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la modification de l'employé:" << query.lastError().text();
        return false;
    }

    qDebug() << "Employé modifié avec succès.";
    return true;
}


// Méthode pour supprimer un employé
bool Employe::supprimer(int matricule) {
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYE WHERE matricule = :matricule");
    query.bindValue(":matricule", matricule);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression de l'employé:" << query.lastError().text();
        return false;
    }

    qDebug() << "Employé supprimé avec succès.";
    return true;
}

// Méthode pour valider les attributs
bool Employe::validateInputs() {
    if (matricule < 0) {
        qDebug() << "Erreur: Matricule invalide.";
        return false;
    }

    if (nom.isEmpty() || nom.size() > 50) {
        qDebug() << "Erreur: Nom invalide.";
        return false;
    }

    // Utilisation d'une expression régulière statique pour valider l'email
    static const QRegularExpression emailRegex(R"(^[\w\.\-]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(mail).hasMatch()) {
        qDebug() << "Erreur: Email invalide.";
        return false;
    }

    if (poste.isEmpty() || poste.size() > 30) {
        qDebug() << "Erreur: Poste invalide.";
        return false;
    }

    if (!dateemb.isValid() || dateemb > QDate::currentDate()) {
        qDebug() << "Erreur: Date d'embauche invalide.";
        return false;
    }

    if (salaire <= 0) {
        qDebug() << "Erreur: Salaire invalide.";
        return false;
    }

    return true;
}
void Employe::telechargerPDF() {
    QPdfWriter pdf("C:/Users/sarah/OneDrive - ESPRIT/Bureau/PDF/EmployeList.pdf");
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setPageOrientation(QPageLayout::Portrait);
    QPainter painter(&pdf);

    // Set background color
    painter.fillRect(QRect(0, 0, pdf.width(), pdf.height()), QColor("#B6E5E9"));

    // Title setup
    QFont titleFont("Arial", 30, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(3800, 1400, "LISTE DES EMPLOYES");

    // Set fonts for header and content
    QFont headerFont("Arial", 12, QFont::Bold);
    QFont contentFont("Times New Roman", 11);
    painter.setFont(contentFont);

    // Execute query to get all employees
    QSqlQuery query;
    query.prepare("SELECT matricule, nom, mail, poste, dateemb, salaire FROM employe");
    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError();
        return;
    }

    // Set up table positioning
    int initialYPosition = 2000;
    int currentYPosition = initialYPosition;
    int cellHeight = 500;
    int tableMargin = 300;

    // Define custom column widths based on expected content length
    int columnWidths[] = {1000, 1500, 2000, 2000, 1500, 1000};  // Adjust these widths as needed

    // Column headers
    QStringList headers = {"Matricule", "Nom", "Mail", "Poste", "Date Embauche", "Salaire"};

    // Draw header row
    painter.setFont(headerFont);
    painter.setPen(Qt::black);
    int xPosition = tableMargin;
    for (int i = 0; i < headers.size(); ++i) {
        painter.drawRect(xPosition, currentYPosition, columnWidths[i], cellHeight);
        painter.drawText(xPosition + 10, currentYPosition + cellHeight / 2 + 5, headers[i]);
        xPosition += columnWidths[i];
    }
    currentYPosition += cellHeight;  // Move to the next row

    // Set alternating row colors
    QColor rowColor1(224, 247, 250);  // #E0F7FA
    QColor rowColor2(255, 255, 255);  // #FFFFFF

    // Draw each employee's data in a table row
    painter.setFont(contentFont);
    bool alternate = false;
    while (query.next()) {
        xPosition = tableMargin;

        // Set row background color
        QColor rowColor = alternate ? rowColor1 : rowColor2;
        painter.fillRect(xPosition, currentYPosition, pdf.width() - 2 * tableMargin, cellHeight, rowColor);
        alternate = !alternate;

        // Draw each cell in the current row
        QStringList rowData = {
            query.value("matricule").toString(),
            query.value("nom").toString(),
            query.value("mail").toString(),
            query.value("poste").toString(),
            query.value("dateemb").toDate().toString("dd/MM/yyyy"),
            query.value("salaire").toString()
        };

        for (int i = 0; i < rowData.size(); ++i) {
            painter.drawRect(xPosition, currentYPosition, columnWidths[i], cellHeight);
            painter.drawText(xPosition + 10, currentYPosition + cellHeight / 2 + 5, rowData[i]);
            xPosition += columnWidths[i];
        }

        currentYPosition += cellHeight;  // Move down for the next row

        // Check if we need a new page
        if (currentYPosition > pdf.height() - 2000) {
            pdf.newPage();
            currentYPosition = initialYPosition;  // Reset to top of the new page

            // Re-draw header row on the new page
            xPosition = tableMargin;
            painter.setFont(headerFont);
            for (int i = 0; i < headers.size(); ++i) {
                painter.drawRect(xPosition, currentYPosition, columnWidths[i], cellHeight);
                painter.drawText(xPosition + 10, currentYPosition + cellHeight / 2 + 5, headers[i]);
                xPosition += columnWidths[i];
            }
            currentYPosition += cellHeight;  // Move to the next row after header
        }
    }

    painter.end();
}

bool Employe::getemployeemailpassword(const QString &nom, const QString &matricule)
{
    QSqlQuery query;

    // Prepare the SQL query to select email and password based on login and password
    query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE nom = :nom AND matricule = :matricule;");
    query.bindValue(":nom", nom);
    query.bindValue(":matricule", matricule);

    // Execute the query
    if (query.exec()) {
        // If the query succeeds, check if any record is found
        if (query.next() && query.value(0).toInt() > 0) {
            return true;  // Successfully retrieved email and password
        } else {
            return false;  // No matching record found
        }
    } else {
        // If the query fails, display the error
        qDebug() << "Query failed:" << query.lastError().text();
        return false;  // Query execution failed
    }
}



bool Employe::getEmployeeDetailsById(const QString &matricule, QString &nom, QString &mail, QString &poste)
{
    QSqlQuery query;
    query.prepare("SELECT nom, mail, poste, dateemb, salaire FROM EMPLOYE WHERE matricule = :matricule");
    query.bindValue(":matricule", matricule);

    if (query.exec()) {
        if (query.next()) {
            nom = query.value("nom").toString();
            mail = query.value("mail").toString();
            poste = query.value("poste").toString();

            return true; // Success
        } else {
            qDebug() << "No employee found with matricule:" << matricule;
            return false; // No employee found
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        return false; // Query execution failed
    }
}

// Generate a 6-digit random ID
int Employe::generateId()
{
    return QRandomGenerator::global()->bounded(100000, 1000000); // Random number between 100000 and 999999
}


bool Employe::ajouterConge(int matricule, const QString &nom, const QString &email,
                           const QString &raison, const QString &poste,
                           const QDate &date_d, const QDate &date_f) {
    int id_conge = generateId(); // Generate a unique leave ID
    QString conseilMessage = generateLeaveDecision(); // Generate leave instruction

    QSqlQuery query;
    query.prepare("INSERT INTO conge (ID_CONGE, matricule, NOM, EMAIL, RAISON, POSTE, DATE_D, DATE_F, CONSIGNE, TYPE_CONGE, ETAT) "
                  "VALUES (:id_conge, :matricule, :nom, :email, :raison, :poste, :date_d, :date_f, :consigne, 'Congé annuel', 'En attente')");

    // Bind values to placeholders
    query.bindValue(":id_conge", id_conge);
    query.bindValue(":matricule", matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":raison", raison);
    query.bindValue(":poste", poste);
    query.bindValue(":date_d", date_d);
    query.bindValue(":date_f", date_f);
    query.bindValue(":consigne", conseilMessage);

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'ajout du congé :" << query.lastError().text();
        return false; // Insertion failed
    }

    return true; // Insertion successful
}


QString Employe::generateLeaveDecision() {
    int totalEmployees = 0;
    int employeesNotOnLeave = 0;

    QSqlQuery query;

    // Step 1: Count total employees
    query.prepare("SELECT COUNT(*) FROM EMPLOYE");
    if (query.exec() && query.next()) {
        totalEmployees = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération du nombre d'employés:" << query.lastError().text();
        return "Erreur de calcul des employés.";
    }
    qDebug() << "Total employees:" << totalEmployees;

    // Step 2: Count employees who are not currently on leave
    query.prepare("SELECT COUNT(*) FROM CONGE WHERE ETAT != 'En congé'");  // Adjust this condition based on your database structure
    if (query.exec() && query.next()) {
        employeesNotOnLeave = query.value(0).toInt();
    } else {
        qDebug() << "Erreur lors de la récupération des employés non en congé:" << query.lastError().text();
        return "Erreur de calcul des employés non en congé.";
    }
    qDebug() << "Employees not on leave:" << employeesNotOnLeave;

    // Step 3: Calculate the percentage of employees currently on leave
    if (totalEmployees == 0) {
        return "Aucun employé disponible pour calculer.";
    }

    float percentageNotOnLeave = (float)employeesNotOnLeave / totalEmployees * 100;
    float percentageOnLeave = 100 - percentageNotOnLeave;
    qDebug() << "Percentage not on leave:" << percentageNotOnLeave;
    qDebug() << "Percentage on leave:" << percentageOnLeave;

    // Step 4: Decision-making logic
    if (percentageOnLeave >= 70) {  // If more than 70% are on leave
        return "N'accepte pas le congé.";
    } else {
        return "Tu peux accepter le congé.";
    }
}

QSqlQueryModel* Employe::afficherconge() {
    // Create a new instance of QSqlQueryModel
    QSqlQueryModel* model = new QSqlQueryModel();

    // SQL query to retrieve pending leave requests without the "PRENOM" field
    QString queryText = R"(
        SELECT ID_CONGE, NOM, EMAIL, POSTE, RAISON, DATE_D, DATE_F, TYPE_CONGE, CONSIGNE, ETAT
        FROM conge
        WHERE ETAT = 'En attente'
    )";

    // Set the query on the model
    model->setQuery(queryText);

    // Check for query execution errors
    if (model->lastError().isValid()) {
        qDebug() << "Erreur d'exécution de la requête SQL :" << model->lastError().text();
        delete model;  // Free memory
        return nullptr;  // Return a null pointer to indicate an error
    }

    // Configure the headers for the columns without "Prénom"
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Congé"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Raison"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date Début"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Fin"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Type Congé"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Consigne"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("État"));

    // Return the filled model for display in the view
    return model;
}

bool Employe::hasOngoingLeave(int id_emp) {
    QSqlQuery query;

    // Requête pour vérifier si l'employé a un congé en cours ou en attente
    query.prepare("SELECT COUNT(*) FROM conge WHERE matricule = :id_emp AND (etat = 'accepté' OR etat = 'En attente')");
    query.bindValue(":id_emp", id_emp);

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification du congé en cours :" << query.lastError().text();
        return false;  // En cas d'erreur de requête
    }

    // Vérification du résultat
    if (query.next()) {
        int count = query.value(0).toInt();
        qDebug() << "Nombre de congés en cours pour l'employé" << id_emp << ":" << count;
        return count > 0;  // Retourne true si au moins un congé en cours
    }

    qDebug() << "Aucun résultat pour l'employé" << id_emp;
    return false;  // Aucun résultat trouvé
}

bool Employe::updateCongeStatus(const QString &id_conge, const QString &etat)
{
    // Vérification des valeurs de l'état pour éviter les erreurs
    QStringList etatsValides = {"accepter", "refusé", "en attente", "terminé"};
    if (!etatsValides.contains(etat.toLower())) {
        qDebug() << "État invalide :" << etat;
        return false;
    }

    // Préparation de la requête SQL pour mettre à jour uniquement la colonne 'etat'
    QSqlQuery query;
    query.prepare("UPDATE conge SET etat = :etat WHERE ID_CONGE = :id_conge");

    // Liaison des valeurs aux placeholders
    query.bindValue(":etat", etat);
    query.bindValue(":id_conge", id_conge);

    // Journalisation pour le débogage
    qDebug() << "Exécution de la requête : UPDATE conge SET etat = " << etat
             << " WHERE ID_CONGE = " << id_conge;

    // Exécution de la requête et vérification du succès
    if (query.exec()) {
        qDebug() << "Mise à jour réussie pour le congé :" << id_conge;
        return true;
    } else {
        qDebug() << "Erreur lors de la mise à jour du congé :" << query.lastError().text();
        return false;
    }
}

void Employe::updateTypeConge() {
    // Obtenir la date d'aujourd'hui au format YYYY-MM-DD
    QString today = QDate::currentDate().toString("yyyy-MM-dd");

    QSqlQuery query;

    // Requête SQL pour mettre à jour l'état à 'fin' si la date de fin correspond à aujourd'hui
    query.prepare("UPDATE conge SET etat = 'fin' WHERE DATE_F = :today");
    query.bindValue(":today", today);

    // Exécuter la requête et vérifier le résultat
    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour des congés terminés :" << query.lastError().text();
        return;
    }

    // Log de confirmation
    qDebug() << "Les congés avec DATE_F =" << today << "ont été marqués comme terminés.";
}

QString Employe::getPosteById(int matricule) {
    // Vérifier si l'ID de l'employé est valide
    if (matricule <= 0) {
        qDebug() << "ID de l'employé invalide :" << matricule;
        return "";
    }

    QSqlQuery query;

    // Préparer la requête SQL pour obtenir le poste de l'employé
    query.prepare("SELECT poste FROM EMPLOYE WHERE matricule = :matricule;");
    query.bindValue(":matricule", matricule);

    // Exécuter la requête
    if (query.exec()) {
        // Vérifier si la requête retourne un résultat
        if (query.next()) {
            // Retourner le poste de l'employé
            QString poste = query.value("poste").toString();
            qDebug() << "Poste trouvé pour l'employé" << matricule << ":" << poste;
            return poste;
        } else {
            qDebug() << "Aucun employé trouvé avec l'ID:" << matricule;
            return ""; // Aucun employé trouvé
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return ""; // Erreur lors de la requête
    }
}


