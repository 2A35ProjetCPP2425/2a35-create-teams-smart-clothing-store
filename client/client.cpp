#include "client.h"
#include "qsqlerror.h"
#include "qtableview.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>

#include <QtNetwork/QSslConfiguration>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrlQuery>

Client::Client(int cin, QString nom_client, QString email_client, QString telephone , QString adresse_client,int matricule,  QString sexe){
    this->cin=cin;
    this->nom_client=nom_client;
     this->email_client=email_client;
    this->telephone=telephone;
    this->adresse_client=adresse_client;

     this->matricule=matricule;
    this->sexe=sexe;




}
bool Client::ajouter()
{
    QSqlQuery query;

    // Vérifier l'existence de l'employé associé (clé étrangère)
    query.prepare("SELECT * FROM EMPLOYÉS WHERE MATRICULE = :MATRICULE");
    query.bindValue(":MATRICULE", matricule);
    if (!query.exec() || !query.next()) {
        QMessageBox::warning(nullptr, "Erreur", "Employé avec ce matricule non trouvé.");
        qDebug() << "Employee with matricule " << matricule << " not found.";
        return false;
    }

    // Préparation de la requête SQL
    query.prepare("INSERT INTO CLIENT (CIN, NOM_CLIENT, EMAIL_CLIENT, TELEPHONE_CLIENT, ADRESSE_CLIENT, MATRICULE, SEXE ) "
                  "VALUES (:CIN, :NOM_CLIENT, :EMAIL_CLIENT, :TELEPHONE_CLIENT, :ADRESSE_CLIENT, :MATRICULE, :SEXE )");

    // Binding des valeurs
    query.bindValue(":CIN", QString::number(cin));
    query.bindValue(":NOM_CLIENT", nom_client);
    query.bindValue(":EMAIL_CLIENT", email_client);
    query.bindValue(":TELEPHONE_CLIENT",telephone);
    query.bindValue(":ADRESSE_CLIENT", adresse_client);
    query.bindValue(":MATRICULE", matricule);  // La clé étrangère
    query.bindValue(":SEXE", sexe);
    // Exécution de la requête
    if (!query.exec()) {
        // Récupérer l'erreur SQL
        QSqlError err = query.lastError();

        // Vérifier si l'erreur est liée à une violation de contrainte (unicité)
        if (err.text().contains("UNIQUE", Qt::CaseInsensitive)) {
            // Message d'erreur spécifique pour le CIN unique
            QMessageBox::critical(nullptr, "Erreur", "Le CIN saisi existe déjà.");
            qDebug() << "Erreur : CIN non unique.";
        } else {
            // Autre type d'erreur
            QMessageBox::critical(nullptr, "Erreur", "Erreur lors de l'ajout du client : " + err.text());
            qDebug() << "Erreur lors de l'ajout du client : " << err.text();
        }
        return false;
    }

    qDebug() << "Client ajouté avec succès";
    return true;
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
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN Client "));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("Telephone du Client "));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse "));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Matricule employé" ));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr(" Sexe du Client" ));



   return model;
}


bool Client::modifier(int cin, QString nom, QString email, QString telephone_c, QString adresse, int matricule_c, QString sexe_c) {
    QSqlQuery query;

    // Préparation de la requête SQL
    query.prepare("UPDATE CLIENT SET "
                  "NOM_CLIENT = :nom, "
                  "EMAIL_CLIENT = :email, "
                  "TELEPHONE_CLIENT = :telephone_c, "
                  "ADRESSE_CLIENT = :adresse, "
                  "MATRICULE = :matricule_c "
                   "SEXE = :sexe_c "
                  "WHERE CIN = :cin");

    // Liaison des nouvelles valeurs
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":email", email);
    query.bindValue(":telephone_c", telephone_c);
    query.bindValue(":adresse", adresse);
    query.bindValue(":matricule_c", matricule_c);
    query.bindValue(":sexe_c", sexe_c);


    // Exécution de la requête SQL
        if (query.exec()) {
            // Utilisation des setters pour mettre à jour l'état interne de l'objet
            setNom_client(nom);       // Met à jour le nom du client
            setEmail_client(email);   // Met à jour l'email du client
            setTelephone(telephone_c);         // Met à jour le téléphone du client
            setAdresse_client(adresse); // Met à jour l'adresse du client
            setMatricule(matricule_c);         // Met à jour le matricule du client
             setSexe_client(sexe_c);

            return true;                         // Indique que la mise à jour a réussi
        }
        return false; // Indique que la mise à jour a échoué
    }


void Client::sendSMS(const QString &phoneNumber, const QString &message)
{
    // Créer un gestionnaire de requêtes réseau
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // Utiliser ton SID et Auth Token
    QString accountSid = "ACc7bbbe7c24db05037ffca6ed749d5e47";  // SID Twilio
    QString authToken = "e4a6d6ad7aed85bd8887c4d4a83a4b66"; // Auth Token Twilio

    // URL de l'API Twilio (ajout de l'accountSid dans l'URL)
    //QUrl url("https://api.twilio.com/2010-04-01/Accounts/"+accountSid+"/Messages.json");
     QUrl url("https://api.twilio.com/2010-04-01/Accounts/ACc7bbbe7c24db05037ffca6ed749d5e47/Messages.json");


    QNetworkRequest request(url);

    // Définir les paramètres de la requête POST
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("To", phoneNumber);  // Numéro du destinataire
    params.addQueryItem("From", "+14237238633"); // Ton numéro Twilio
    params.addQueryItem("Body", message);    // Contenu du message

    QByteArray postData = params.toString(QUrl::FullyEncoded).toUtf8();

    // Authentification de l'API Twilio en base64
    QString authString = accountSid + ":" + authToken;
    QByteArray authData = authString.toUtf8().toBase64();
    request.setRawHeader("Authorization", "Basic " + authData);

    // Envoyer la requête POST
    QNetworkReply *reply = manager->post(request, postData);

    // Connecter le signal "finished" pour gérer la réponse
    QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        // Vérifier si la requête a abouti sans erreur
        if (reply->error() == QNetworkReply::NoError) {
            // Vérifier le code de statut HTTP
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (statusCode == 201) {
                // Envoi réussi
                emit smsSent(true, "SMS envoyé avec succès.");
            } else {
                // Code d'erreur HTTP retourné par Twilio
                emit smsSent(false, "Erreur HTTP : " + QString::number(statusCode));
            }
        } else {
            // Erreur d'envoi (problème de réseau ou autre)
            emit smsSent(false, "Erreur réseau : " + reply->errorString());
        }

        // Libérer les ressources
        reply->deleteLater();
    });
}













