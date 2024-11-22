#include "produit.h"

produit::produit(int ref, QString nom_prod, QString categ, float prx, int quant,QString path) {
    this->reference = ref;
    this->nom_prod = nom_prod;
    this->categorie = categ;
    this->prix = prx;
    this->quantite = quant;
    this->photopath = path;
}

int produit::getref() {
    return reference;
}

QString produit::getnom() {
    return nom_prod;
}

QString produit::getcateg() {
    return categorie;
}

float produit::getprix() {
    return prix;
}

int produit::getquant() {
    return quantite;
}
QString produit::getphotopath(){
    return photopath;
}
void produit::setref(int ref){
    this->reference=ref;
}
void produit::setnom(const QString& n){
    this->nom_prod=n;
}
void produit::setcateg(const QString& cat){
    this->categorie=cat;
}
void produit::setprix(float prx){
    this->prix=prx;
}
void produit::setquant(int qant){
    this->quantite=qant;
}
void produit::setphotopath(const QString& path){
    this->photopath=path;
}
bool produit::ajouter() {
    QSqlQuery query;
    query.prepare("INSERT INTO PRODUITS (REFERENCE, NOM_PRODUIT, CATEGORIE, PRIX, QUANTITE, PHOTO_PATH) "
                  "VALUES (:reference, :nom_prod, :categorie, :prix, :quantite, :photo_path)");
    query.bindValue(":reference", reference);
    query.bindValue(":nom_prod", nom_prod);
    query.bindValue(":categorie", categorie);
    query.bindValue(":prix", prix);
    query.bindValue(":quantite", quantite);
    query.bindValue(":photo_path",photopath);
    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error inserting product:" << query.lastError().text();
        return false;
    }
}
bool produit::modifier() {
    QString prix_string = QString::number(prix);
    QString quantite_string = QString::number(quantite);
    QString reference_string = QString::number(reference);
    QSqlQuery query;
    query.prepare("UPDATE PRODUITS SET NOM_PRODUIT = :NOM_PRODUIT, CATEGORIE = :CATEGORIE, PRIX = :PRIX, QUANTITE = :QUANTITE, PHOTO_PATH = :PHOTO_PATH WHERE REFERENCE = :REFERENCE");
    query.bindValue(":NOM_PRODUIT", nom_prod);  // String to VARCHAR2
    query.bindValue(":CATEGORIE", categorie);    // String to VARCHAR2
    query.bindValue(":PRIX", prix);              // Double to NUMBER(10,2)
    query.bindValue(":QUANTITE", quantite);      // Int to NUMBER
    query.bindValue(":REFERENCE", reference);    // Int to NUMBER(38)
    query.bindValue(":PHOTO_PATH",photopath);
    return query.exec();
}

bool produit::supprimer(int reff) {
    QSqlQuery query;

    // Prepare the query to delete a product by its reference
    query.prepare("DELETE FROM PRODUITS WHERE REFERENCE = :reference");

    // Bind the integer value directly to the query
    query.bindValue(":reference", reff);

    // Execute the query
    if (query.exec()) {
        // Check if any row was affected
        if (query.numRowsAffected() > 0) {
            return true; // Return true only if a record was deleted
        }
    }

    // Log an error for debugging purposes if needed
    qDebug() << "Error deleting product or no matching reference found:" << query.lastError().text();
    return false; // Return false if no rows were deleted or an error occurred
}

QSqlQueryModel * produit::afficher(){
    QSqlQueryModel* model = new QSqlQueryModel();

    // Fetch the data from the database table 'produit' with correct column names
    model->setQuery("SELECT REFERENCE, NOM_PRODUIT, CATEGORIE, PRIX, QUANTITE FROM PRODUITS");

    // Set headers for each column, as per the correct names
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_PRODUIT"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CATEGORIE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}
bool produit::recherche(const QString &reference)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PRODUITS WHERE REFERENCE = :REFERENCE");
    query.bindValue(":REFERENCE", reference);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // If count > 0, the product exists
        }
    }
    return false;
}
