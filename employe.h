#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QDate>
#include <QString>
#include <QSqlQueryModel>

class Employe {
public:
    // Constructeur par défaut
    Employe();

    // Constructeur avec paramètres
    Employe(int matricule, const QString& nom, const QString& mail, const QString& poste, const QDate& dateemb, float salaire);

    // Getters
    int getMatricule() const;
    QString getNom() const;
    QString getMail() const;
    QString getPoste() const;
    QDate getDateemb() const;
    float getSalaire() const;

    // Setters
    void setMatricule(int matricule);
    void setNom(const QString& nom);
    void setMail(const QString& mail);
    void setPoste(const QString& poste);
    void setDateemb(const QDate& dateemb);
    void setSalaire(float salaire);

    // Méthodes
    bool matriculeExists(int matricule);
    int genererMatricule();
    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier();
    bool supprimer(int matricule);
    bool validateInputs();
    void telechargerPDF();
    bool getemployeemailpassword(const QString &nom, const QString &matricule);
    bool getEmployeeDetailsById(const QString &matricule, QString &nom, QString &mail, QString &poste);
    int generateId();  // Method to generate a 6-digit random ID
    bool ajouterConge(int matricule, const QString &nom, const QString &email,
                               const QString &raison, const QString &poste,
                               const QDate &date_d, const QDate &date_f);
    QString generateLeaveDecision();
    QSqlQueryModel* afficherconge();
    bool hasOngoingLeave(int id_emp);
    bool updateCongeStatus(const QString &id_conge, const QString &etat);
    void updateTypeConge();
    QString getPosteById(int matricule);






private:
    int matricule;
    QString nom;
    QString mail;
    QString poste;
    QDate dateemb;
    float salaire;
};

#endif // EMPLOYE_H
