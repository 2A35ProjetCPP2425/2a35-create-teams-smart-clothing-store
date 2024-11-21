#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include "email.h"

#include <QStringList>

#include <QMainWindow>
#include <QMimeDatabase>     // Pour détecter les types MIME des fichiers
#include <QFileIconProvider> // Pour générer des icônes pour différents fichiers
#include <QListWidgetItem>   // Pour manipuler les éléments de QListWidget
#include <QFileInfo>         // Pour extraire des informations sur les fichiers
#include <QDesktopServices> // Assurez-vous que cette ligne est présente
#include <QUrl>

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
private slots:
    void on_pushButtonajouter_clicked();

  //  int getClientCIN();
    void on_pushButtonasupprimer_clicked();
    void on_tableView_clicked();
    void on_pushButton_modif_clicked();
    void on_pushButton_tri_clicked();
     void clearClientFields();
     void on_clearButton_clicked();
     void on_pushButton_exporter_clicked();
      void on_lineEdit_recherche_textChanged();
     //void on_searchButton_clicked();
    /* void on_sendSMSButton_clicked();  // Slot pour envoyer le SMS
         void onSmsSent(bool success, const QString &message);  // Slot pour afficher un message après envoi*/


        //email
        void on_email_clicked();          // Slot pour envoyer l'email
        void onBrowseAttachments();       // Slot pour parcourir les pièces jointes
       void onRemoveAttachment();
      void onAttachmentDoubleClicked(QListWidgetItem *item); // Déclaration du slot


        //stat
        void displayGenderStatistics();


     //void on_pushButton_modif_clicked();
private:
    Ui::MainWindow *ui;
   Client csupp;
 int getClientCIN();

};

#endif // MAINWINDOW_H
