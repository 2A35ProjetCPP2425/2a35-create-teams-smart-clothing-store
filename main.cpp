#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include <QMessageBox>
#include "dialog.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnect();
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
    Dialog dialog;
    dialog.exec();
    if (dialog.isLoginSuccessful()) {
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        return 0;
    }
    return a.exec();
}
