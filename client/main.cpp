#include "mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "connection.h"







int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
     MainWindow w;

    if(test)
    {w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

//employe
    // Show the login dialog
    // Show the login dialog
    /*   Dialog dialog;
       if (dialog.exec() == QDialog::Accepted) {
           QString email="admin";
          // MainWindow w(email);
           w.show();
           return a.exec(); // Start the application event loop
       } else {
           return 0; // Exit if login fails
      }*/

//client
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
  Client csupp;




    return a.exec();
}
