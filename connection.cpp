#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db= QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("sarah");
    db.setUserName("testuser");
    db.setPassword("test123");

    if (db.open()) test=true;

    return test;

}
void Connection::closeConnection(){db.close();}
