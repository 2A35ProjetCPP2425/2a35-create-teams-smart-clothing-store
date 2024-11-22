/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QLineEdit *passwordLineEdit;
    QPushButton *login;
    QLineEdit *loginLineEdit;
    QLabel *label;
    QLabel *label_3;
    QPushButton *showpasswordLineEdit;
    QLabel *showpasswordLabel;
    QLabel *label_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(1280, 720);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 80, 301, 541));
        groupBox->setStyleSheet(QString::fromUtf8("/* Style for QGroupBox */\n"
"QGroupBox {\n"
"    border: 2px solid black; /* Black border */\n"
"    border-radius: 5px; /* Rounded corners (adjust as needed) */\n"
"    margin-top: 10px; /* Space between the border and the title */\n"
"    font-size: 14px; /* Font size for the title */\n"
"    color: #333333; /* Dark grey text color for the title */\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Title text style for QGroupBox */\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left; /* Position title at the top-left */\n"
"    padding: 0 5px; /* Adjust padding for title positioning */\n"
"    color: #ffffff; /* White text for the title */\n"
"    background-color: #333333; /* Dark grey background for the title */\n"
"    font-weight: bold; /* Bold title */\n"
"}\n"
""));
        passwordLineEdit = new QLineEdit(groupBox);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(60, 320, 171, 51));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("/* Style for the main widget */\n"
"QWidget {\n"
"    font-family: Arial, sans-serif;\n"
"    background-color: #f0f0f0; /* Light grey background */\n"
"}\n"
"\n"
"/* Style for labels */\n"
"QLabel {\n"
"    font-size: 10px;\n"
"    color: #888888; /* Medium grey color */\n"
"    text-transform: uppercase;\n"
"    margin-bottom: 4px;\n"
"}\n"
"\n"
"/* Style for input fields */\n"
"QLineEdit {\n"
"    padding: 8px;\n"
"    font-size: 16px;\n"
"    color: #333333; /* Darker grey text color */\n"
"    background-color: #e6e6e6; /* Light grey input background */\n"
"    border: 1px solid #cccccc; /* Light grey border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"/* Change border color on focus */\n"
"QLineEdit:focus {\n"
"    border: 1px solid #888888; /* Medium grey color on focus */\n"
"    outline: none;\n"
"}\n"
""));
        login = new QPushButton(groupBox);
        login->setObjectName("login");
        login->setGeometry(QRect(120, 450, 51, 51));
        login->setStyleSheet(QString::fromUtf8("image: url(:/Downloads/images__1_-removebg-preview.png);\n"
"background-color: rgb(0, 0, 127);\n"
"\n"
"\n"
""));
        loginLineEdit = new QLineEdit(groupBox);
        loginLineEdit->setObjectName("loginLineEdit");
        loginLineEdit->setGeometry(QRect(60, 240, 171, 51));
        loginLineEdit->setStyleSheet(QString::fromUtf8("/* Style for the main widget */\n"
"QWidget {\n"
"    font-family: Arial, sans-serif;\n"
"    background-color: #f0f0f0; /* Light grey background */\n"
"}\n"
"\n"
"/* Style for labels */\n"
"QLabel {\n"
"    font-size: 10px;\n"
"    color: #888888; /* Medium grey color */\n"
"    text-transform: uppercase;\n"
"    margin-bottom: 4px;\n"
"}\n"
"\n"
"/* Style for input fields */\n"
"QLineEdit {\n"
"    padding: 8px;\n"
"    font-size: 16px;\n"
"    color: #333333; /* Darker grey text color */\n"
"    background-color: #e6e6e6; /* Light grey input background */\n"
"    border: 1px solid #cccccc; /* Light grey border */\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"/* Change border color on focus */\n"
"QLineEdit:focus {\n"
"    border: 1px solid #888888; /* Medium grey color on focus */\n"
"    outline: none;\n"
"}\n"
"\n"
""));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 170, 111, 61));
        label->setStyleSheet(QString::fromUtf8("/* Style for QLabel */\n"
"QLabel {\n"
"    font-size: 14px; /* Adjust font size */\n"
"    color: #333333; /* Dark grey text color */\n"
"    padding: 5px; /* Adjust padding as necessary */\n"
"}\n"
""));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 40, 141, 181));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/Pictures/img/logo_meta-removebg-preview.png);"));
        showpasswordLineEdit = new QPushButton(groupBox);
        showpasswordLineEdit->setObjectName("showpasswordLineEdit");
        showpasswordLineEdit->setGeometry(QRect(60, 390, 21, 21));
        showpasswordLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        showpasswordLabel = new QLabel(groupBox);
        showpasswordLabel->setObjectName("showpasswordLabel");
        showpasswordLabel->setGeometry(QRect(90, 380, 131, 41));
        showpasswordLabel->setStyleSheet(QString::fromUtf8("/* Style for QLabel */\n"
"QLabel {\n"
"    font-size: 14px; /* Adjust font size */\n"
"    color: #333333; /* Dark grey text color */\n"
"    padding: 5px; /* Adjust padding as necessary */\n"
"}\n"
""));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, -10, 1291, 731));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/Downloads/istockphoto-1715503982-612x612 (1).jpg);"));
        label_2->raise();
        groupBox->raise();

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox->setTitle(QString());
        login->setText(QString());
        label->setText(QCoreApplication::translate("Dialog", "<html><head/><body><p><span style=\" font-size:18pt; font-weight:700;\">Sign in</span></p></body></html>", nullptr));
        label_3->setText(QString());
        showpasswordLineEdit->setText(QString());
        showpasswordLabel->setText(QCoreApplication::translate("Dialog", "show password", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
