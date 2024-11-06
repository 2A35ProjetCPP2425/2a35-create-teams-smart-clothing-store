#include "client.h"
#include "qsqlerror.h"
#include "qtableview.h"
#include <QMessageBox>

Client::Client(int cin, QString nom_client, QString email_client, int telephone , QString adresse_client, int matricule){
    this->cin=cin;
    this->nom_client=nom_client;
     this->email_client=email_client;
    this->telephone=telephone;
    this->adresse_client=adresse_client;
     this->matricule=matricule;




}
bool Client::ajouter()
{
    QSqlQuery query;
    // Vérifier l'existence de l'employé associé (clé étrangère)
        query.prepare("SELECT * FROM EMPLOYÉS WHERE MATRICULE = :MATRICULE");
        query.bindValue(":MATRICULE", matricule);
        if (!query.exec() || !query.next()) {
            qDebug() << "Employee with matricule " << matricule << " not found.";
            return false;} // Employé non trouvé

    // Préparation de la requête SQL
    query.prepare("INSERT INTO CLIENT (CIN, NOM_CLIENT, EMAIL_CLIENT, TELEPHONE_CLIENT, ADRESSE_CLIENT, MATRICULE) "
                     "VALUES (:CIN, :NOM_CLIENT, :EMAIL_CLIENT, :TELEPHONE_CLIENT, :ADRESSE_CLIENT, :MATRICULE)");

    // Binding des valeurs
    query.bindValue(":CIN", QString::number(cin));
        query.bindValue(":NOM_CLIENT", nom_client);
        query.bindValue(":EMAIL_CLIENT", email_client);
        query.bindValue(":TELEPHONE_CLIENT", QString::number(telephone));
        query.bindValue(":ADRESSE_CLIENT", adresse_client);
    query.bindValue(":MATRICULE", matricule);  // La clé étrangère

    // Exécution de la requête et retour du succès ou de l'échec
    return query.exec();
    // Exécution de la requête
       if (query.exec()) {
           qDebug() << "Client ajouté avec succès";
           return true;
       } else {
           qDebug() << "Erreur lors de l'ajout du client : " << query.lastError().text();
           return false;
       }
}

bool Client::supprimerClient(int cin) {
    QSqlQuery query;

    // Vérification de l'existence du client
    query.prepare("SELECT * FROM CLIENT WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Erreur", "Le client n'existe pas.");
        return false;
    }

    // Confirmation de la suppression
    if (QMessageBox::question(nullptr, "Confirmation", "Êtes-vous sûr de vouloir supprimer ce client ?") == QMessageBox::No) {
        return false;
    }

    // Suppression du client
    query.prepare("DELETE FROM CLIENT WHERE CIN = :CIN");
    query.bindValue(":CIN", cin);
    return query.exec();
}

QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
         model->setQuery("SELECT * FROM CLIENT");
         // Ajustement des tailles des colonnes pour un affichage optimal
         QTableView *tableView = new QTableView();
         // ... autres instructions
         tableView->resizeColumnsToContents();
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN "));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("email"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Tel du Client "));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse "));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Matricule employé" ));


   return model;
}


bool Client::modifier(int cin, QString nom, QString email, int telephone_c, QString adresse, int matricule_c) {
    QSqlQuery query;

    // Préparation de la requête SQL
    query.prepare("UPDATE CLIENT SET "
                  "NOM_CLIENT = :nom, "
                  "EMAIL_CLIENT = :email, "
                  "TELEPHONE_CLIENT = :telephone_c, "
                  "ADRESSE_CLIENT = :adresse, "
                  "MATRICULE = :matricule_c "
                  "WHERE CIN = :cin");

    // Liaison des nouvelles valeurs
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":telephone_c", telephone_c);
    query.bindValue(":adresse", adresse);
    query.bindValue(":matricule_c", matricule_c);


    // Exécution de la requête SQL
        if (query.exec()) {
            // Utilisation des setters pour mettre à jour l'état interne de l'objet
            setNom_client(nom);       // Met à jour le nom du client
            setEmail_client(email);   // Met à jour l'email du client
            setTelephone(telephone_c);         // Met à jour le téléphone du client
            setAdresse_client(adresse); // Met à jour l'adresse du client
            setMatricule(matricule_c);         // Met à jour le matricule du client
            return true;                         // Indique que la mise à jour a réussi
        }
        return false; // Indique que la mise à jour a échoué
    }


