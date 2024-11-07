#include "fournisseur.h"
#include <QSqlError>

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
    // Vérifier que l'ID est supérieur à 0
    if (id <= 0) {
        qDebug() << "ID invalide. L'ID doit être supérieur à 0.";
        return false;
    }

    // Vérifier que les champs essentiels ne sont pas vides
    if (nom_entreprise.isEmpty() || email.isEmpty() || telephone.isEmpty() || info_banc.isEmpty()) {
        qDebug() << "Certains champs sont vides. Tous les champs doivent être remplis.";
        return false;
    }

    QSqlQuery query;
    // Convertir l'ID en QString
    QString res = QString::number(id);

    // Préparer la requête SQL
    query.prepare("insert into FOURNISSEURS (id, nom_entreprise, email, telephone, info_banc) "
                  "VALUES (:id, :nom_entreprise, :email, :telephone, :info_banc)");

    // Lier les valeurs
    query.bindValue(":id", res);
    query.bindValue(":nom_entreprise", nom_entreprise);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":info_banc", info_banc);

    // Exécuter la requête et vérifier si elle réussit
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
    query.prepare("UPDATE FOURNISSEURS SET NOM_ENTREPRISE = :NOM_ENTREPRISE, "
                  "TELEPHONE = :TELEPHONE, EMAIL = :EMAIL, INFO_BANC = :INFO_BANC "
                  "WHERE ID = :ID");

    // Lien des valeurs aux paramètres
    query.bindValue(":ID", id);
    query.bindValue(":NOM_ENTREPRISE", nom_entreprise);
    query.bindValue(":TELEPHONE", telephone);
    query.bindValue(":EMAIL", email);
    query.bindValue(":INFO_BANC", info_banc);

    // Exécution de la requête
    if (query.exec()) {
        // Vérifiez le nombre de lignes affectées
        int rowsAffected = query.numRowsAffected();
        qDebug() << "Nombre de lignes affectées:" << rowsAffected;
        return rowsAffected > 0;  // Retourne vrai si la mise à jour a affecté au moins une ligne
    } else {
        // Affichez l'erreur SQL si la requête échoue
        qDebug() << "Erreur de modification: " << query.lastError().text();
        return false;
    }
}
