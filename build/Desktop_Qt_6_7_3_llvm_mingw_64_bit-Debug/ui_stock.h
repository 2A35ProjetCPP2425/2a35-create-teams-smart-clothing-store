/********************************************************************************
** Form generated from reading UI file 'stock.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCK_H
#define UI_STOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_stock
{
public:
    QWidget *DASHBOARD;
    QPushButton *pushstock2;
    QPushButton *home;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QComboBox *comboBox;
    QLabel *label_2;
    QTabWidget *tabWidget;
    QWidget *tab_7;
    QLabel *label_21;
    QLabel *label_22;
    QPushButton *actualiser;
    QPushButton *modifier;
    QPushButton *ajouter;
    QPushButton *supprimer;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLineEdit *referenceLineEdit;
    QLineEdit *nomProduitLineEdit;
    QLineEdit *prixLineEdit;
    QLineEdit *quantiteLineEdit;
    QLabel *label;
    QLabel *label_6;
    QPushButton *exportationPDF;
    QLineEdit *supprimerLineEdit;
    QLabel *label_36;
    QTableView *model;
    QLabel *label_17;
    QLineEdit *photoPathLineEdit;
    QPushButton *exportbutton;
    QComboBox *categoriecombo;
    QWidget *tab_8;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *rechercheLineEdit;
    QPushButton *recherche;
    QLabel *label_30;
    QPushButton *triparprix;
    QPushButton *triparquantite;
    QPushButton *triparaz;
    QLabel *label_31;
    QLabel *label_3;
    QLabel *label_7;
    QTableView *model_2;
    QPushButton *exportationPDF_2;
    QLabel *label_5;
    QLabel *commentLabel;
    QPushButton *pushButton;
    QWidget *catalogue;
    QLabel *label_32;
    QLabel *label_35;
    QLabel *label_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *catalogueContainer;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *catalogueLayout;
    QWidget *stat;
    QLabel *label_37;
    QPushButton *boutonGenererGraphique;
    QGroupBox *groupBox;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *plusdisponible;
    QLabel *pluschere;
    QLabel *label_9;
    QLabel *produitreptureenstock;
    QLabel *label_8;
    QLabel *espacerest;
    QWidget *conteneurGraphique;
    QLabel *label_16;
    QWidget *tab_10;
    QLabel *label_38;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *deleteProductButton;
    QPushButton *contactfourniButton;
    QListWidget *notificationsListWidget;
    QPushButton *pushButton_2;

    void setupUi(QDialog *stock)
    {
        if (stock->objectName().isEmpty())
            stock->setObjectName("stock");
        stock->resize(1283, 727);
        DASHBOARD = new QWidget(stock);
        DASHBOARD->setObjectName("DASHBOARD");
        DASHBOARD->setGeometry(QRect(-10, 0, 1301, 91));
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
        pushstock2 = new QPushButton(DASHBOARD);
        pushstock2->setObjectName("pushstock2");
        pushstock2->setGeometry(QRect(120, 30, 161, 41));
        home = new QPushButton(DASHBOARD);
        home->setObjectName("home");
        home->setGeometry(QRect(10, 20, 91, 61));
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
        pushButton_6->setGeometry(QRect(310, 30, 161, 41));
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
        label_2 = new QLabel(stock);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(-10, 90, 1291, 631));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        tabWidget = new QTabWidget(stock);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 90, 1280, 621));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane {\n"
"                border: 1px solid lightblue; /* Border around the tab pane */\n"
"                border-radius: 10px;         /* Rounded corners */\n"
"                background: white;           /* Background for the pane */\n"
"                padding: 5px;                /* Padding around the pane */\n"
"            }\n"
"            QTabBar::tab {\n"
"                background: lightblue;              /* Normal tab background */\n"
"                color: darkblue;                    /* Normal tab text color */\n"
"                padding: 10px;                      /* Tab padding */\n"
"                border: 1px solid lightblue;        /* Tab border */\n"
"                border-radius: 10px;                /* Rounded corners for tabs */\n"
"                margin-right: 5px;                  /* Space between tabs */\n"
"            }\n"
"            QTabBar::tab:hover {\n"
"                background: #B2D8E0;                /* Hover tab background */\n"
"                borde"
                        "r: 1px solid darkblue;         /* Darker border on hover */\n"
"            }\n"
"            QTabBar::tab:selected {\n"
"                background: white;                  /* Active tab background */\n"
"                color: darkblue;                    /* Active tab text color */\n"
"                font-weight: bold;                  /* Bold text for active tab */\n"
"                border-bottom: 1px solid white;     /* Border for active tab */\n"
"                border-top-left-radius: 10px;      /* Rounded corners for selected tab */\n"
"                border-top-right-radius: 10px;     /* Rounded corners for selected tab */\n"
"            }\n"
"            QTabBar::tab:disabled {\n"
"                background: lightgrey;              /* Disabled tab background */\n"
"                color: lightblue;                   /* Disabled tab text color */\n"
"            }"));
        tab_7 = new QWidget();
        tab_7->setObjectName("tab_7");
        label_21 = new QLabel(tab_7);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(-10, -30, 1280, 720));
        label_21->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        label_22 = new QLabel(tab_7);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(1050, 370, 221, 211));
        label_22->setStyleSheet(QString::fromUtf8("image: url(:/D:/img/logo_meta-removebg-preview.png);"));
        actualiser = new QPushButton(tab_7);
        actualiser->setObjectName("actualiser");
        actualiser->setGeometry(QRect(820, 490, 101, 41));
        actualiser->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        modifier = new QPushButton(tab_7);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(680, 490, 121, 41));
        modifier->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        ajouter = new QPushButton(tab_7);
        ajouter->setObjectName("ajouter");
        ajouter->setGeometry(QRect(560, 490, 101, 41));
        ajouter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        supprimer = new QPushButton(tab_7);
        supprimer->setObjectName("supprimer");
        supprimer->setGeometry(QRect(360, 490, 41, 41));
        supprimer->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        label_23 = new QLabel(tab_7);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(10, 60, 131, 41));
        label_23->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        label_24 = new QLabel(tab_7);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(0, 110, 161, 41));
        label_24->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        label_25 = new QLabel(tab_7);
        label_25->setObjectName("label_25");
        label_25->setGeometry(QRect(0, 170, 131, 41));
        label_25->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        label_26 = new QLabel(tab_7);
        label_26->setObjectName("label_26");
        label_26->setGeometry(QRect(0, 230, 121, 41));
        label_26->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        label_27 = new QLabel(tab_7);
        label_27->setObjectName("label_27");
        label_27->setGeometry(QRect(-10, 290, 181, 51));
        label_27->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        referenceLineEdit = new QLineEdit(tab_7);
        referenceLineEdit->setObjectName("referenceLineEdit");
        referenceLineEdit->setGeometry(QRect(150, 60, 191, 41));
        referenceLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        nomProduitLineEdit = new QLineEdit(tab_7);
        nomProduitLineEdit->setObjectName("nomProduitLineEdit");
        nomProduitLineEdit->setGeometry(QRect(150, 110, 191, 41));
        nomProduitLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        prixLineEdit = new QLineEdit(tab_7);
        prixLineEdit->setObjectName("prixLineEdit");
        prixLineEdit->setGeometry(QRect(152, 227, 191, 41));
        prixLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        quantiteLineEdit = new QLineEdit(tab_7);
        quantiteLineEdit->setObjectName("quantiteLineEdit");
        quantiteLineEdit->setGeometry(QRect(150, 300, 191, 41));
        quantiteLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        label = new QLabel(tab_7);
        label->setObjectName("label");
        label->setGeometry(QRect(-10, -50, 1280, 720));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/Bureau/iamgesssss/Design sans titre (1).png);"));
        label_6 = new QLabel(tab_7);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(1100, 450, 151, 91));
        label_6->setStyleSheet(QString::fromUtf8("image: url(:/Pictures/img/logo_meta-removebg-preview.png);"));
        exportationPDF = new QPushButton(tab_7);
        exportationPDF->setObjectName("exportationPDF");
        exportationPDF->setGeometry(QRect(940, 490, 131, 41));
        exportationPDF->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        supprimerLineEdit = new QLineEdit(tab_7);
        supprimerLineEdit->setObjectName("supprimerLineEdit");
        supprimerLineEdit->setGeometry(QRect(150, 490, 191, 41));
        supprimerLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        label_36 = new QLabel(tab_7);
        label_36->setObjectName("label_36");
        label_36->setGeometry(QRect(0, 490, 161, 41));
        label_36->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        model = new QTableView(tab_7);
        model->setObjectName("model");
        model->setGeometry(QRect(460, 40, 731, 371));
        model->setStyleSheet(QString::fromUtf8(""));
        label_17 = new QLabel(tab_7);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(-10, 380, 171, 41));
        label_17->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        photoPathLineEdit = new QLineEdit(tab_7);
        photoPathLineEdit->setObjectName("photoPathLineEdit");
        photoPathLineEdit->setGeometry(QRect(150, 380, 191, 41));
        photoPathLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        exportbutton = new QPushButton(tab_7);
        exportbutton->setObjectName("exportbutton");
        exportbutton->setGeometry(QRect(360, 380, 41, 41));
        exportbutton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 25px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        categoriecombo = new QComboBox(tab_7);
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->addItem(QString());
        categoriecombo->setObjectName("categoriecombo");
        categoriecombo->setGeometry(QRect(150, 170, 191, 41));
        tabWidget->addTab(tab_7, QString());
        label->raise();
        label_21->raise();
        label_22->raise();
        actualiser->raise();
        modifier->raise();
        ajouter->raise();
        supprimer->raise();
        label_23->raise();
        label_24->raise();
        label_25->raise();
        label_26->raise();
        label_27->raise();
        referenceLineEdit->raise();
        nomProduitLineEdit->raise();
        prixLineEdit->raise();
        quantiteLineEdit->raise();
        label_6->raise();
        exportationPDF->raise();
        supprimerLineEdit->raise();
        label_36->raise();
        model->raise();
        label_17->raise();
        photoPathLineEdit->raise();
        exportbutton->raise();
        categoriecombo->raise();
        tab_8 = new QWidget();
        tab_8->setObjectName("tab_8");
        label_28 = new QLabel(tab_8);
        label_28->setObjectName("label_28");
        label_28->setGeometry(QRect(-10, 0, 1280, 720));
        label_28->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        label_29 = new QLabel(tab_8);
        label_29->setObjectName("label_29");
        label_29->setGeometry(QRect(0, 40, 131, 41));
        label_29->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        rechercheLineEdit = new QLineEdit(tab_8);
        rechercheLineEdit->setObjectName("rechercheLineEdit");
        rechercheLineEdit->setGeometry(QRect(140, 40, 161, 41));
        rechercheLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"                background-color: lightblue;          /* Background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding inside the line edit */\n"
"                border: 2px solid darkblue;          /* Border color */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"            }\n"
"            QLineEdit:focus {\n"
"                border: 2px solid #B2D8E0;           /* Border color on focus */\n"
"            }\n"
"            QLineEdit::placeholder {\n"
"                color: gray;                         /* Placeholder text color */\n"
"            }"));
        recherche = new QPushButton(tab_8);
        recherche->setObjectName("recherche");
        recherche->setGeometry(QRect(320, 40, 41, 41));
        recherche->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        label_30 = new QLabel(tab_8);
        label_30->setObjectName("label_30");
        label_30->setGeometry(QRect(0, 140, 181, 41));
        label_30->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        triparprix = new QPushButton(tab_8);
        triparprix->setObjectName("triparprix");
        triparprix->setGeometry(QRect(30, 210, 101, 41));
        triparprix->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        triparquantite = new QPushButton(tab_8);
        triparquantite->setObjectName("triparquantite");
        triparquantite->setGeometry(QRect(150, 210, 101, 41));
        triparquantite->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        triparaz = new QPushButton(tab_8);
        triparaz->setObjectName("triparaz");
        triparaz->setGeometry(QRect(270, 210, 91, 41));
        triparaz->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        label_31 = new QLabel(tab_8);
        label_31->setObjectName("label_31");
        label_31->setGeometry(QRect(1050, 380, 221, 211));
        label_31->setStyleSheet(QString::fromUtf8("image: url(:/D:/img/logo_meta-removebg-preview.png);"));
        label_3 = new QLabel(tab_8);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 0, 1280, 720));
        label_3->setStyleSheet(QString::fromUtf8("background-image: url(:/Bureau/iamgesssss/Design sans titre (1).png);"));
        label_7 = new QLabel(tab_8);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(1100, 450, 151, 91));
        label_7->setStyleSheet(QString::fromUtf8("image: url(:/Pictures/img/logo_meta-removebg-preview.png);"));
        model_2 = new QTableView(tab_8);
        model_2->setObjectName("model_2");
        model_2->setGeometry(QRect(490, 20, 681, 361));
        model_2->setStyleSheet(QString::fromUtf8(""));
        exportationPDF_2 = new QPushButton(tab_8);
        exportationPDF_2->setObjectName("exportationPDF_2");
        exportationPDF_2->setGeometry(QRect(920, 480, 131, 41));
        exportationPDF_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        label_5 = new QLabel(tab_8);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 90, 91, 41));
        label_5->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        commentLabel = new QLabel(tab_8);
        commentLabel->setObjectName("commentLabel");
        commentLabel->setGeometry(QRect(120, 80, 191, 51));
        pushButton = new QPushButton(tab_8);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1190, 30, 61, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	            image: url(:/Pictures/img/trier.png);\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"           "
                        " }"));
        tabWidget->addTab(tab_8, QString());
        label_3->raise();
        label_28->raise();
        label_29->raise();
        rechercheLineEdit->raise();
        recherche->raise();
        label_30->raise();
        triparprix->raise();
        triparquantite->raise();
        triparaz->raise();
        label_31->raise();
        label_7->raise();
        model_2->raise();
        exportationPDF_2->raise();
        label_5->raise();
        commentLabel->raise();
        pushButton->raise();
        catalogue = new QWidget();
        catalogue->setObjectName("catalogue");
        label_32 = new QLabel(catalogue);
        label_32->setObjectName("label_32");
        label_32->setGeometry(QRect(0, -10, 1280, 720));
        label_32->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        label_35 = new QLabel(catalogue);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(1050, 120, 221, 211));
        label_35->setStyleSheet(QString::fromUtf8("image: url(:/D:/img/logo_meta-removebg-preview.png);"));
        label_4 = new QLabel(catalogue);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(-10, 0, 1280, 720));
        label_4->setStyleSheet(QString::fromUtf8("background-image: url(:/Bureau/iamgesssss/Design sans titre (1).png);"));
        scrollArea = new QScrollArea(catalogue);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(290, 100, 600, 400));
        scrollArea->setAutoFillBackground(false);
        scrollArea->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 598, 398));
        scrollAreaWidgetContents->setAcceptDrops(false);
        scrollAreaWidgetContents->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        catalogueContainer = new QWidget(scrollAreaWidgetContents);
        catalogueContainer->setObjectName("catalogueContainer");
        catalogueContainer->setEnabled(true);
        catalogueContainer->setGeometry(QRect(0, 0, 600, 400));
        catalogueContainer->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        catalogueContainer->setAutoFillBackground(false);
        verticalLayoutWidget = new QWidget(catalogueContainer);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 601, 401));
        catalogueLayout = new QVBoxLayout(verticalLayoutWidget);
        catalogueLayout->setObjectName("catalogueLayout");
        catalogueLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(catalogue, QString());
        label_35->raise();
        label_4->raise();
        label_32->raise();
        scrollArea->raise();
        stat = new QWidget();
        stat->setObjectName("stat");
        label_37 = new QLabel(stat);
        label_37->setObjectName("label_37");
        label_37->setGeometry(QRect(-10, -60, 1280, 720));
        label_37->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        boutonGenererGraphique = new QPushButton(stat);
        boutonGenererGraphique->setObjectName("boutonGenererGraphique");
        boutonGenererGraphique->setGeometry(QRect(850, 480, 231, 51));
        boutonGenererGraphique->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        groupBox = new QGroupBox(stat);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 581, 531));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 40, 261, 61));
        label_13->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 110, 231, 61));
        label_14->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        plusdisponible = new QLabel(groupBox);
        plusdisponible->setObjectName("plusdisponible");
        plusdisponible->setGeometry(QRect(260, 50, 321, 41));
        plusdisponible->setStyleSheet(QString::fromUtf8("QLabel { \n"
"    font-size: 20px;  /* Large font size */\n"
"	color: rgb(0, 0, 0);\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"}"));
        pluschere = new QLabel(groupBox);
        pluschere->setObjectName("pluschere");
        pluschere->setGeometry(QRect(220, 120, 361, 41));
        pluschere->setStyleSheet(QString::fromUtf8("QLabel { \n"
"    font-size: 20px;  /* Large font size */\n"
"	color: rgb(0, 0, 0);\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"}"));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 190, 361, 51));
        label_9->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        produitreptureenstock = new QLabel(groupBox);
        produitreptureenstock->setObjectName("produitreptureenstock");
        produitreptureenstock->setGeometry(QRect(360, 190, 181, 41));
        produitreptureenstock->setStyleSheet(QString::fromUtf8("QLabel { \n"
"    font-size: 20px;  /* Large font size */\n"
"	color: rgb(0, 0, 0);\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"}"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(10, 260, 281, 41));
        label_8->setStyleSheet(QString::fromUtf8("QLabel {\n"
"                color: darkblue;                   /* Text color */\n"
"                font-size: 18px;                   /* Font size */\n"
"                font-family: 'Arial', sans-serif;  /* Font family */\n"
"                padding: 10px;                     /* Padding around the text */\n"
"            }"));
        espacerest = new QLabel(groupBox);
        espacerest->setObjectName("espacerest");
        espacerest->setGeometry(QRect(290, 260, 281, 41));
        espacerest->setStyleSheet(QString::fromUtf8("QLabel { \n"
"    font-size: 20px;  /* Large font size */\n"
"	color: rgb(0, 0, 0);\n"
"    font-family: 'Arial', sans-serif;  /* Modern, clean font */\n"
"    text-align: center;  /* Center the text */\n"
"}"));
        conteneurGraphique = new QWidget(stat);
        conteneurGraphique->setObjectName("conteneurGraphique");
        conteneurGraphique->setGeometry(QRect(600, 20, 621, 431));
        label_16 = new QLabel(stat);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(1120, 460, 151, 91));
        label_16->setStyleSheet(QString::fromUtf8("image: url(:/Pictures/img/logo_meta-removebg-preview.png);"));
        tabWidget->addTab(stat, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName("tab_10");
        label_38 = new QLabel(tab_10);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(0, 0, 1280, 720));
        label_38->setStyleSheet(QString::fromUtf8("background-image: url(:/D:/img/Design sans titre (1).png);"));
        label_10 = new QLabel(tab_10);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(-10, 0, 1280, 720));
        label_10->setStyleSheet(QString::fromUtf8("background-image: url(:/Pictures/img/Design sans titre (1).png);"));
        label_11 = new QLabel(tab_10);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(1030, 420, 151, 91));
        label_11->setStyleSheet(QString::fromUtf8("image: url(:/Bureau/iamgesssss/logo_meta-removebg-preview.png);"));
        label_12 = new QLabel(tab_10);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(1090, 450, 171, 101));
        label_12->setStyleSheet(QString::fromUtf8("image: url(:/Pictures/img/logo_meta-removebg-preview.png);"));
        deleteProductButton = new QPushButton(tab_10);
        deleteProductButton->setObjectName("deleteProductButton");
        deleteProductButton->setGeometry(QRect(1070, 380, 191, 41));
        deleteProductButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        contactfourniButton = new QPushButton(tab_10);
        contactfourniButton->setObjectName("contactfourniButton");
        contactfourniButton->setGeometry(QRect(1070, 310, 191, 51));
        contactfourniButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        notificationsListWidget = new QListWidget(tab_10);
        notificationsListWidget->setObjectName("notificationsListWidget");
        notificationsListWidget->setGeometry(QRect(30, 10, 1021, 521));
        notificationsListWidget->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: #f0f0f0;\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 5px;\n"
"    font-size: 14px;\n"
"    color: #333;\n"
"    padding: 5px;\n"
"    min-height: 150px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    background-color: #ffffff;\n"
"    border-bottom: 1px solid #ddd;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #4CAF50;  /* Green for selected item */\n"
"    color: white;\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #e0e0e0;\n"
"    cursor: pointer;\n"
"}\n"
"\n"
"QListWidget::item:!selected:hover {\n"
"    background-color: #f5f5f5;\n"
"}"));
        pushButton_2 = new QPushButton(tab_10);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(1070, 50, 191, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                background-color: lightblue;          /* Button background color */\n"
"                color: darkblue;                      /* Text color */\n"
"                font-size: 16px;                     /* Font size */\n"
"                font-family: 'Segoe UI', sans-serif;  /* Font family */\n"
"                padding: 10px;                       /* Padding around the text */\n"
"                border: none;                        /* No border */\n"
"                border-radius: 8px;                  /* Rounded corners */\n"
"                transition: background-color 0.3s;   /* Smooth background color transition */\n"
"            }\n"
"            QPushButton:hover {\n"
"                background-color: #B2D8E0;           /* Background color on hover */\n"
"            }\n"
"            QPushButton:pressed {\n"
"                background-color: #A0C4D3;           /* Background color when pressed */\n"
"            }"));
        tabWidget->addTab(tab_10, QString());
        label_10->raise();
        label_11->raise();
        label_38->raise();
        label_12->raise();
        deleteProductButton->raise();
        contactfourniButton->raise();
        notificationsListWidget->raise();
        pushButton_2->raise();
        label_2->raise();
        DASHBOARD->raise();
        tabWidget->raise();

        retranslateUi(stock);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(stock);
    } // setupUi

    void retranslateUi(QDialog *stock)
    {
        stock->setWindowTitle(QCoreApplication::translate("stock", "Dialog", nullptr));
        pushstock2->setText(QCoreApplication::translate("stock", "STOCK", nullptr));
        home->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("stock", "FOURNISSEUR", nullptr));
        pushButton_5->setText(QCoreApplication::translate("stock", "LIVRAISON", nullptr));
        pushButton_7->setText(QCoreApplication::translate("stock", "PERSONEL", nullptr));
        pushButton_8->setText(QCoreApplication::translate("stock", "CLIENT", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("stock", "compte", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("stock", "d\303\251tails", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("stock", "param\303\251tres", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("stock", "d\303\251connexion", nullptr));

        label_2->setText(QString());
#if QT_CONFIG(tooltip)
        tabWidget->setToolTip(QCoreApplication::translate("stock", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_21->setText(QString());
        label_22->setText(QString());
        actualiser->setText(QCoreApplication::translate("stock", "actualiser", nullptr));
        modifier->setText(QCoreApplication::translate("stock", "modifier", nullptr));
        ajouter->setText(QCoreApplication::translate("stock", "ajouter", nullptr));
        supprimer->setText(QCoreApplication::translate("stock", "\342\234\224", nullptr));
        label_23->setText(QCoreApplication::translate("stock", "R\303\251f\303\251rence:", nullptr));
        label_24->setText(QCoreApplication::translate("stock", "Nom de produit:", nullptr));
        label_25->setText(QCoreApplication::translate("stock", "Cat\303\251gorie:", nullptr));
        label_26->setText(QCoreApplication::translate("stock", "Prix:", nullptr));
        label_27->setText(QCoreApplication::translate("stock", "Quantit\303\251 en stock:", nullptr));
        label->setText(QString());
        label_6->setText(QString());
        exportationPDF->setText(QCoreApplication::translate("stock", "exportation PDF", nullptr));
        label_36->setText(QCoreApplication::translate("stock", "supprimer:", nullptr));
        label_17->setText(QCoreApplication::translate("stock", "Chemin de photo:", nullptr));
#if QT_CONFIG(tooltip)
        exportbutton->setToolTip(QCoreApplication::translate("stock", "<html><head/><body><p><span style=\" font-size:72pt;\">\342\254\216</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        exportbutton->setText(QCoreApplication::translate("stock", "\342\207\262", nullptr));
        categoriecombo->setItemText(0, QCoreApplication::translate("stock", "Vestes & Manteaux", nullptr));
        categoriecombo->setItemText(1, QCoreApplication::translate("stock", "Ensembles", nullptr));
        categoriecombo->setItemText(2, QCoreApplication::translate("stock", "Gilets & Sweats", nullptr));
        categoriecombo->setItemText(3, QCoreApplication::translate("stock", "Chemises", nullptr));
        categoriecombo->setItemText(4, QCoreApplication::translate("stock", "Pulls", nullptr));
        categoriecombo->setItemText(5, QCoreApplication::translate("stock", "Polos", nullptr));
        categoriecombo->setItemText(6, QCoreApplication::translate("stock", "T-shirts", nullptr));
        categoriecombo->setItemText(7, QCoreApplication::translate("stock", "Pantalons", nullptr));
        categoriecombo->setItemText(8, QCoreApplication::translate("stock", "Shorts & Bermudas", nullptr));
        categoriecombo->setItemText(9, QCoreApplication::translate("stock", "Chaussures", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("stock", "CRUD ", nullptr));
        label_28->setText(QString());
        label_29->setText(QCoreApplication::translate("stock", "Recherche:", nullptr));
        recherche->setText(QCoreApplication::translate("stock", "\342\234\224", nullptr));
        label_30->setText(QCoreApplication::translate("stock", "TRI PAR:", nullptr));
        triparprix->setText(QCoreApplication::translate("stock", "PRIX", nullptr));
        triparquantite->setText(QCoreApplication::translate("stock", "Quantit\303\251", nullptr));
        triparaz->setText(QCoreApplication::translate("stock", "A-Z", nullptr));
        label_31->setText(QString());
        label_3->setText(QString());
        label_7->setText(QString());
        exportationPDF_2->setText(QCoreApplication::translate("stock", "exportation PDF", nullptr));
        label_5->setText(QCoreApplication::translate("stock", "Statue:", nullptr));
        commentLabel->setText(QString());
        pushButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QCoreApplication::translate("stock", "Recherche et tri ", nullptr));
        label_32->setText(QString());
        label_35->setText(QString());
        label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(catalogue), QCoreApplication::translate("stock", "catalogue", nullptr));
        label_37->setText(QString());
        boutonGenererGraphique->setText(QCoreApplication::translate("stock", "G\303\251nerer  diagramme circulaire", nullptr));
        groupBox->setTitle(QString());
        label_13->setText(QCoreApplication::translate("stock", "Le produit le plus disponible:", nullptr));
        label_14->setText(QCoreApplication::translate("stock", "Le produit le plus ch\303\251re:", nullptr));
        plusdisponible->setText(QString());
        pluschere->setText(QString());
        label_9->setText(QCoreApplication::translate("stock", "Nombre des produits en repture en stock:", nullptr));
        produitreptureenstock->setText(QString());
        label_8->setText(QCoreApplication::translate("stock", "Espace restant dans le r\303\251serve :", nullptr));
        espacerest->setText(QString());
        label_16->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(stat), QCoreApplication::translate("stock", "statistiques", nullptr));
        label_38->setText(QString());
        label_10->setText(QString());
        label_11->setText(QString());
        label_12->setText(QString());
        deleteProductButton->setText(QCoreApplication::translate("stock", "supprimer", nullptr));
        contactfourniButton->setText(QCoreApplication::translate("stock", "contacter le fournisseur", nullptr));
        pushButton_2->setText(QCoreApplication::translate("stock", "actualiser", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_10), QCoreApplication::translate("stock", "Notifications ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class stock: public Ui_stock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCK_H
