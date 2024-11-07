#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Fournisseur {
private:
    int id;
    QString nom_entreprise;
    QString email;
    QString telephone;
    QString info_banc;
public:
    // Constructors
    Fournisseur() {}
    Fournisseur(int id, QString nom_entreprise, QString email, QString telephone, QString info_banc);
    // Getters
    int getID(){ return id; }
    QString getNomEntreprise(){ return nom_entreprise; }
    QString getEmail(){ return email; }
    QString getTelephone(){ return telephone; }
    QString getInfoBanc(){ return info_banc; }
    // Setters
    void setID(int id) { this->id = id; }
    void setNomEntreprise(QString nom) { nom_entreprise = nom; }
    void setEmail(QString e) { email = e; }
    void setTelephone(QString t) { telephone = t; }
    void setInfoBanc(QString info) { info_banc = info; }
    // Basic functionalities related to the Fournisseur entity
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool modifier();

};

#endif // FOURNISSEUR_H
