#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVariant>
#include <QRegularExpression>   // For regular expressions in newer versions of Qt
#include "employe.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog) // Initialize the second dialog
{
    ui->setupUi(this);
    connect(ui->connexion, &QPushButton::clicked, this, &Dialog::on_loginButton_clicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_loginButton_clicked()
{
    QString identifiant = ui->nom->text();  // Get the email input from the user
    QString mdp = ui->password->text();  // Get the password input from the user

    // Check if the fields are empty
    if (identifiant.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Identifiant is empty.");
        return;
    }
    if (mdp.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Password is empty.");
        return;
    }

    // Check if the 'identifiant' contains only letters
    QRegularExpression identifiantRegex("^[A-Za-z]+$");  // Only letters (both uppercase and lowercase)
    if (!identifiantRegex.match(identifiant).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Identifiant must contain only letters.");
        return;  // Exit if the condition is not met
    }

    // Check if the 'mdp' contains only numbers
    QRegularExpression mdpRegex("^[0-9]+$");  // Only numbers
    if (!mdpRegex.match(mdp).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Password must contain only numbers.");
        return;  // Exit if the condition is not met
    }

    // Instantiate an 'Employe' object to use the method for checking credentials
    Employe emp;

    bool loginSuccess1 = emp.getemployeemailpassword(identifiant, mdp);

    if (loginSuccess1) {
        // If login is successful, display success message
        ui->label_2->setText("Login successful!");
        ui->label_2->setStyleSheet("color: green;");  // Set text color to green

        // Get the welcome message with the user's name
        QString welcomeMessage = getEmployeName();
        // Set the welcome message in label_2 after successful login
        if (!welcomeMessage.isEmpty()) {
            ui->label_2->setText(welcomeMessage);  // Display the welcome message
            ui->label_2->setStyleSheet("color: green;");  // Optionally, set green color
        } else {
            ui->label_2->setText("Failed to retrieve user name.");
            ui->label_2->setStyleSheet("color: red;");
        }

        // Simulate a delay while keeping the UI responsive
        for (int i = 0; i < 5000000; i++) {
            QCoreApplication::processEvents();  // Keeps the UI responsive
        }

        // After the delay, close the dialog
        accept();  // Close the dialog and return accepted status
    } else {
        // No matching record found, display an error message
        ui->label_2->setText("Incorrect username or password.");
        ui->label_2->setStyleSheet("color: red;"); // Set text color to red

        // Simulate delay while keeping the UI responsive
        for (int i = 0; i < 1000000; i++) {
            QCoreApplication::processEvents();  // Keeps the UI responsive
        }

        // After the delay, reset the label text
        ui->label_2->setText("");  // Clear the error message
    }
}

QString Dialog::getEmployeName()
{
    QString userName;
    QString login = ui->nom->text();  // Get the email input from the user

    // Prepare the query to fetch the user's name based on the email (id_p)
    QSqlQuery query;
    query.prepare("SELECT nom FROM employe WHERE nom = :login");
    query.bindValue(":login", login);  // Bind the login value to the query

    // Execute the query and check if it succeeded
    if (query.exec() && query.next()) {  // Ensure the query is successful and move to the first result
        // If the query is successful and we have a result, retrieve the name from the result
        userName = query.value("nom").toString();
    } else {
        // If the query fails or there are no results, print the error to the debug log
        qDebug() << "Failed to retrieve user name:" << query.lastError().text();
        return "";  // Return empty if not found
    }

    // Return the message with the user's name
    QString welcomeMessage = "Bienvenue " + userName + " dans notre application!";
    return welcomeMessage;
}

QString Dialog::getEmail() const {
    return ui->nom->text();  // Return the email entered in the QLineEdit
}
