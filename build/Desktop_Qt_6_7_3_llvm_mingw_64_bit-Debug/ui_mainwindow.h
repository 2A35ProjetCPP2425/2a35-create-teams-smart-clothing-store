/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *videoContainer;
    QWidget *DASHBOARD;
    QPushButton *pushstock;
    QPushButton *home;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QWidget *videoContainer_2;
    QLabel *label_4;
    QLabel *label_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        videoContainer = new QWidget(centralwidget);
        videoContainer->setObjectName("videoContainer");
        videoContainer->setGeometry(QRect(640, 160, 591, 333));
        videoContainer->setStyleSheet(QString::fromUtf8(""));
        DASHBOARD = new QWidget(centralwidget);
        DASHBOARD->setObjectName("DASHBOARD");
        DASHBOARD->setGeometry(QRect(0, 0, 1281, 91));
        DASHBOARD->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #004466;  /* Solid color background */\n"
"    border-bottom: 2px solid #003366;  /* Subtle border at the bottom */\n"
"    padding: 10px 20px;  /* Padding inside the dashboard */\n"
"    color: #d1e3f3;  /* Lighter bluish white */\n"
"    font-size: 18px;  /* Font size for text */\n"
"    font-family: 'Segoe UI', sans-serif;  /* Modern font */\n"
"    font-weight: bold;  /* Bold text */\n"
"}\n"
"\n"
""));
        pushstock = new QPushButton(DASHBOARD);
        pushstock->setObjectName("pushstock");
        pushstock->setGeometry(QRect(120, 30, 161, 41));
        home = new QPushButton(DASHBOARD);
        home->setObjectName("home");
        home->setGeometry(QRect(0, 20, 91, 61));
        home->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-image: url(:/Downloads/png-clipart-metrostation-black-home-icon-thumbnail-removebg-preview_optimized.png);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"    border: none;\n"
"    background-color: transparent;\n"
"}\n"
""));
        pushButton_6 = new QPushButton(DASHBOARD);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(300, 30, 161, 41));
        pushButton_5 = new QPushButton(DASHBOARD);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(490, 30, 161, 41));
        pushButton_7 = new QPushButton(DASHBOARD);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(680, 30, 161, 41));
        pushButton_8 = new QPushButton(DASHBOARD);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(860, 30, 161, 41));
        comboBox = new QComboBox(DASHBOARD);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(1100, 30, 141, 41));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 160, 641, 81));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #0066cc;  /* Blue text color */\n"
"    font-size: 36px;  /* Large font size */\n"
"    font-weight: bold;  /* Bold text */\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"    background-color: transparent;  /* Transparent background */\n"
"    padding: 20px;  /* Padding around the text */\n"
"    border: none;  /* No border */\n"
"}\n"
"\n"
""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 90, 1291, 631));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        videoContainer_2 = new QWidget(centralwidget);
        videoContainer_2->setObjectName("videoContainer_2");
        videoContainer_2->setGeometry(QRect(60, 460, 331, 186));
        videoContainer_2->setStyleSheet(QString::fromUtf8(""));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(40, 390, 281, 81));
        label_4->setStyleSheet(QString::fromUtf8("QLabel { \n"
"	\n"
"	\n"
"	color: rgb(86, 129, 129);\n"
"    font-size: 36px;  /* Large font size */\n"
"    font-weight: bold;  /* Bold text */\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"    background-color: transparent;  /* Transparent background */\n"
"    padding: 20px;  /* Padding around the text */\n"
"    border: none;  /* No border */\n"
"}\n"
""));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(50, 200, 621, 181));
        label_3->setStyleSheet(QString::fromUtf8("QLabel { \n"
"	\n"
"	\n"
"	color: rgb(86, 129, 129);\n"
"    font-size: 36px;  /* Large font size */\n"
"    font-weight: bold;  /* Bold text */\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"    background-color: transparent;  /* Transparent background */\n"
"    padding: 20px;  /* Padding around the text */\n"
"    border: none;  /* No border */\n"
"}\n"
"\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        label_2->raise();
        videoContainer->raise();
        DASHBOARD->raise();
        label->raise();
        videoContainer_2->raise();
        label_4->raise();
        label_3->raise();
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushstock->setText(QCoreApplication::translate("MainWindow", "STOCK", nullptr));
        home->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "FOURNISSEUR", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "LIVRAISON", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "PERSONEL", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "CLIENT", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "compte", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "d\303\251tails", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "param\303\251tres", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "d\303\251connexion", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">YOUR SMART CLOTHING STORE</span></p><p><br/></p><p><span style=\" font-size:14pt;\"><br/></span></p></body></html>", nullptr));
        label_2->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:16pt;\">powered by:</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">Encourager la cr\303\251ativit\303\251 gr\303\242ce \303\240 une gestion fluide. </span></p><p><span style=\" font-size:12pt;\">L\303\240 o\303\271 l'innovation rencontre la simplicit\303\251</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
