#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include "email.h"
#include "arduino.h"


#include <QMainWindow>
#include <QMimeDatabase>     // Pour détecter les types MIME des fichiers
#include <QFileIconProvider> // Pour générer des icônes pour différents fichiers
#include <QListWidgetItem>   // Pour manipuler les éléments de QListWidget
#include <QFileInfo>         // Pour extraire des informations sur les fichiers
#include <QDesktopServices> // Assurez-vous que cette ligne est présente
#include <QUrl>
#include <QList>
#include <QString>
#include <QSqlQuery>


#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    bool isValidEmail(const QString &email);
    ~MainWindow();
    void connectArduino();  // Déclaration de la méthode connectArduino()
    void compareuid();
    bool compareUIDWithDatabase();
    bool compareUIDWithDatabasepro();
    void comparepro();
    void sendredLEDSignal();
    QString getArduinoData();
    void compare();
    void sendGreenLEDSignal();





private slots:
    void on_pushButtonajouter_clicked();

  //  int getClientCIN();
    void on_pushButtonasupprimer_clicked();
    void on_tableViewcl_clicked();
    void on_pushButton_modif_clicked();
    void on_pushButton_tri_clicked();
     void clearClientFields();
     void on_clearButton_clicked();
     void on_exporter_clicked();
      void on_lineEdit_recherche_textChanged();
     //void on_searchButton_clicked();
    void on_sendSMSButton_clicked();  // Slot pour envoyer le SMS
         void onSmsSent(bool success, const QString &message);  // Slot pour afficher un message après envoi*/


        //email
        void on_email_clicked();          // Slot pour envoyer l'email
        void onBrowseAttachments();       // Slot pour parcourir les pièces jointes
       void onRemoveAttachment();
      void onAttachmentDoubleClicked(QListWidgetItem *item); // Déclaration du slot



        //stat
        void displayGenderStatistics();
        void readFromArduino(); // Slot to read data from Arduino
             //void sendGreenLEDSignal();  // Function to send a signal to start the

signals:
        void cardScanned();


private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;  // Serial port for Arduino
        QString arduinoData;   // Data received from Arduino
        QString cardCode;

   Client csupp;
 int getClientCIN();




};

#endif // MAINWINDOW_H
