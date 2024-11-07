#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"  // Include this to show the main window

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    loginSuccessful = false;  // Initialize the login flag
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::isLoginSuccessful() const {
    return loginSuccessful;  // Return the login success flag
}

void Dialog::on_login_clicked() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    // Check if fields are empty
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, tr("Input Error"), tr("Please fill in both login and password."));
        return;
    }

    // Check if the database connection is open
    if (!QSqlDatabase::database().isOpen()) {
        QMessageBox::critical(this, tr("Database Error"), tr("Database connection is not open."));
        return;
    }

    // Prepare the SQL query with placeholders
    QSqlQuery query;
    query.prepare("SELECT login FROM account WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    // Execute the query and check for success
    if (query.exec()) {
        if (query.next()) {
            // User found, login successful
            QMessageBox::information(this, tr("Login Success"), tr("Login successful!"));
            loginSuccessful = true;
            accept();  // Close the dialog and signal success
        } else {
            // No matching user found, login failed
            QMessageBox::critical(this, tr("Login Failed"), tr("Incorrect login or password."));
        }
    } else {
        // Handle query execution error
        qDebug() << "Query failed:" << query.lastError().text();
        QMessageBox::critical(this, tr("Database Error"), tr("Unable to execute query. Please try again later."));
    }
}

