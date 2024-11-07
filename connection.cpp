#include "connection.h"
#include<QSqlError>
Connection::Connection()
{

}

bool Connection::createconnect()
{
    db= QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Projet2A35smartvetapp");//inserer le nom de la source de données
    db.setUserName("chahine");//inserer nom de l'utilisateur
    db.setPassword("Esprit2003");//inserer mot de passe de cet utilisateur
    if(db.open())test=true;
    return test;


}
void Connection::closeConnection(){db.close();}
