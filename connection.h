#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QApplication>
#include <QMessageBox>
#include <QtSql>
class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeConnection();
};

#endif // CONNECTION_H
