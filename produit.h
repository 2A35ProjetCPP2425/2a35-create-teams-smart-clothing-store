#ifndef PRODUIT_H
#define PRODUIT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlError>
class produit
{
    int reference;
    QString nom_prod,categorie;
    float prix;
    int quantite;
    QString photopath;
public:
    produit(){}
    produit(int ref, QString nom, QString categ, float p, int quant,QString path);
    int getref();
    QString getnom();
    QString getcateg();
    float getprix();
    int getquant();
    QString getphotopath();
    void setref(int ref);
    void setnom(const QString& n);
    void setcateg(const QString& cat);
    void setprix(float prx);
    void setquant(int qant);
    void setphotopath(const QString& path);
    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer(int reff);
    bool recherche(const QString &reference);
};

#endif // PRODUIT_H
