#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>



#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrl>
#include <QtCore/QDebug>

class Client: public QObject
{
     Q_OBJECT
private:
    QString nom_client,email_client,adresse_client;
    int cin, matricule ;
    QString telephone;
    QString sexe;
public:
    Client(){};
    Client(int , QString , QString , QString , QString , int , QString);
    //GETTERS
      QString getnom_client()
      {return nom_client;}
      QString getEmail_client()
      {return email_client;}
      QString getAdresse_client()
      {return adresse_client;}
      QString getsexe_client()
      {return sexe;}

      int getCIN(){return cin;}
      int getMatricule(){return matricule;}
      QString getTelephone(){return telephone;}

      void setNom_client(QString nom) {
          nom_client = nom;
      }

      void setEmail_client(QString email) {
          email_client = email;
      }

      void setAdresse_client(QString adresse) {
          adresse_client = adresse;
      }
      void setSexe_client(QString sexe_c) {
          sexe = sexe_c;
      }

      void setCIN(int cin_c) {
          this->cin = cin_c;
      }

      void setMatricule(int matricule_c) {
          this->matricule = matricule_c;
      }

      void setTelephone(QString telephone_c) {
          this->telephone = telephone_c;
      }

     //crud
      bool ajouter();
      QSqlQueryModel * afficher();

      bool supprimerClient(int );


      bool modifier(int cin, QString nom, QString email, QString telephone_c, QString adresse, int matricule_c,QString sexe_c);


      // void sendSMS(const QString &phoneNumber, const QString &message);

signals:
    // Déclaration du signal qui sera émis après l'envoi du SMS
    void smsSent(bool success, const QString &message);


};

#endif // CLIENT_H
