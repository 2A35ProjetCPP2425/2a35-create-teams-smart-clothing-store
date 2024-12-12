#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    bool isLoginSuccessful() const;  // Getter for loginSuccessful

private slots:
    void on_login_clicked();

private:
    Ui::Dialog *ui;
    bool loginSuccessful;  // Flag to track login success
};

#endif // DIALOG_H
