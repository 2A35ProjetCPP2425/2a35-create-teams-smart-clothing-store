#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Client
{
    QString nom_client,email_client,adresse_client;
    int cin, matricule ,telephone;
public:
    Client(){};
    Client(int , QString , QString , int , QString , int );
    //GETTERS
      QString getnom_client()
      {return nom_client;}
      QString getEmail_client()
      {return email_client;}
      QString getAdresse_client()
      {return adresse_client;}

      int getCIN(){return cin;}
      int getMatricule(){return matricule;}
      int getTelephone(){return telephone;}

      void setNom_client(QString nom) {
          nom_client = nom;
      }

      void setEmail_client(QString email) {
          email_client = email;
      }

      void setAdresse_client(QString adresse) {
          adresse_client = adresse;
      }

      void setCIN(int cin_c) {
          this->cin = cin_c;
      }

      void setMatricule(int matricule_c) {
          this->matricule = matricule_c;
      }

      void setTelephone(int telephone_c) {
          this->telephone = telephone_c;
      }

     //crud
      bool ajouter();
      QSqlQueryModel * afficher();

      bool supprimerClient(int );


      bool modifier(int cin, QString nom, QString email, int telephone_c, QString adresse, int matricule_c);



};

#endif // CLIENT_H
