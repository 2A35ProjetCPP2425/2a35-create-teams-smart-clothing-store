#include "fournisseur.h"
#include <QSqlError>
#include <QRegularExpression>
#include <QMessageBox>

Fournisseur::Fournisseur(int id, QString nom_entreprise, QString email, QString telephone, QString info_banc)
{
    this->id = id;
    this->nom_entreprise = nom_entreprise;
    this->email = email;
    this->telephone = telephone;
    this->info_banc = info_banc;
}


bool Fournisseur::ajouter()
{
    // Vérifier que l'ID est supérieur à 0 et contient uniquement des chiffres
    QRegularExpression idRegex("^[0-9]+$");
    if (id <= 0 || !idRegex.match(QString::number(id)).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "ID invalide. L'ID doit être un nombre positif et contenir uniquement des chiffres.");
        return false;
    }

    // Vérifier si l'ID existe déjà dans la base de données
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM FOURNISSEURS WHERE ID = :id");
    checkQuery.bindValue(":id", id);
    if (checkQuery.exec()) {
        if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
            QMessageBox::warning(nullptr, "Erreur", "L'ID existe déjà. Veuillez utiliser un autre ID.");
            return false;
        }
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Erreur lors de la vérification de l'ID: " + checkQuery.lastError().text());
        return false;
    }

    // Vérifier que les champs essentiels ne sont pas vides
    if (nom_entreprise.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Le champ 'Nom de l'entreprise' ne doit pas être vide.");
        return false;
    }
    if (email.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Le champ 'Email' ne doit pas être vide.");
        return false;
    }
    if (telephone.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Le champ 'Téléphone' ne doit pas être vide.");
        return false;
    }
    if (info_banc.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Le champ 'Nom de la banque' ne doit pas être vide.");
        return false;
    }

    // Vérifier que le nom de l'entreprise contient uniquement des lettres et des espaces
    QRegularExpression textRegex("^[A-Za-zÀ-ÿÉéÈèÊêËëÔôÙùÇç ]+$");
    if (!textRegex.match(nom_entreprise).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Le nom de l'entreprise doit contenir uniquement des lettres et des espaces.");
        return false;
    }

    // Vérifier que le nom de la banque contient uniquement des lettres et des espaces
    if (!textRegex.match(info_banc).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Le nom de la banque doit contenir uniquement des lettres et des espaces.");
        return false;
    }

    // Vérifier que l'email est valide
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "L'email est invalide. Il doit contenir un '@' et un domaine correct.");
        return false;
    }

    // Vérifier que le téléphone contient uniquement des chiffres
    QRegularExpression phoneRegex("^[0-9]+$");
    if (!phoneRegex.match(telephone).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur", "Le numéro de téléphone doit contenir uniquement des chiffres.");
        return false;
    }

    QSqlQuery query;
    // Convertir l'ID en QString
    QString res = QString::number(id);

    // Préparer la requête SQL
    query.prepare("INSERT INTO FOURNISSEURS (id, nom_entreprise, email, telephone, info_banc) "
                  "VALUES (:id, :nom_entreprise, :email, :telephone, :info_banc)");

    // Lier les valeurs
    query.bindValue(":id", res);
    query.bindValue(":nom_entreprise", nom_entreprise);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":info_banc", info_banc);
    if (!query.exec()) {
        qDebug() << "Erreur d'insertion: " << query.lastError().text();
        return false;
    }

    return true;
}

bool Fournisseur::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISSEURS WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "Nombre de lignes supprimées:" << query.numRowsAffected();
        return query.numRowsAffected() > 0;  // Vérifie si une ligne a été supprimée
    }
    return false;
}


QSqlQueryModel* Fournisseur::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM FOURNISSEURS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_ENTREPRISE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Info_Banc"));
    return model;
}


bool Fournisseur::modifier() {
    QSqlQuery query;

    // Charger les valeurs existantes pour cet ID
    query.prepare("SELECT NOM_ENTREPRISE, TELEPHONE, EMAIL, INFO_BANC FROM FOURNISSEURS WHERE ID = :ID");
    query.bindValue(":ID", id);
    if (!query.exec() || !query.next()) {
        qDebug() << "Erreur lors du chargement des données actuelles: " << query.lastError().text();
        return false;
    }

    // Utiliser les valeurs actuelles si les champs sont vides
    QString nom_entreprise_modifie = nom_entreprise.isEmpty() ? query.value("NOM_ENTREPRISE").toString() : nom_entreprise;
    QString telephone_modifie = telephone.isEmpty() ? query.value("TELEPHONE").toString() : telephone;
    QString email_modifie = email.isEmpty() ? query.value("EMAIL").toString() : email;
    QString info_banc_modifie = info_banc.isEmpty() ? query.value("INFO_BANC").toString() : info_banc;

    // Préparer et exécuter la requête de mise à jour
    query.prepare("UPDATE FOURNISSEURS SET NOM_ENTREPRISE = :NOM_ENTREPRISE, "
                  "TELEPHONE = :TELEPHONE, EMAIL = :EMAIL, INFO_BANC = :INFO_BANC "
                  "WHERE ID = :ID");
    query.bindValue(":ID", id);
    query.bindValue(":NOM_ENTREPRISE", nom_entreprise_modifie);
    query.bindValue(":TELEPHONE", telephone_modifie);
    query.bindValue(":EMAIL", email_modifie);
    query.bindValue(":INFO_BANC", info_banc_modifie);

    if (!query.exec()) {
        qDebug() << "Erreur de modification: " << query.lastError().text();
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "Nombre de lignes affectées:" << rowsAffected;
    return rowsAffected > 0;  // Retourne vrai si la mise à jour a affecté au moins une ligne
}

