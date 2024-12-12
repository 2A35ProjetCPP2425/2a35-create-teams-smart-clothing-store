QT       += core gui sql
QT       += core gui quick quickwidgets
QT += multimedia
QT += sql
QT += core gui widgets
QT += multimedia multimediawidgets
QT += charts
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connected.cpp \
    connection.cpp \
    dialog.cpp \
    four.cpp \
    fournisseur.cpp \
    livraison.cpp \
    main.cpp \
    mainwindow.cpp \
    produit.cpp \
    statistiquesdialog.cpp \
    stock.cpp \
    qrcodegen.cpp \
    videobackground.cpp

HEADERS += \
    arduino.h \
    connected.h \
    connection.h \
    dialog.h \
    four.h \
    fournisseur.h \
    livraison.h \
    mainwindow.h \
    produit.h \
    statistiquesdialog.h \
    stock.h \
    qrcodegen.hpp \
    videobackground.h

FORMS += \
    connected.ui \
    dialog.ui \
    four.ui \
    mainwindow.ui \
    statistiquesdialog.ui \
    stock.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Maps.qrc \
    iimg.qrc

DISTFILES += \
    ../../../Downloads/acceder.png \
    ../../../Downloads/png-clipart-greater-than-sign-less-than-sign-at-sign-equals-sign-character-mathematics-angle-sign-thumbnail-removebg-preview.png \
    ../../../Downloads/png-clipart-greater-than-sign-less-than-sign-at-sign-equals-sign-character-mathematics-angle-sign-thumbnail.png \
    ../../Pictures/img/Design sans titre (1).png \
    ../../Pictures/img/Design sans titre (1).png \
    ../../Pictures/img/est-inferieur-a.png \
    ../../Pictures/img/information.png \
    ../../Pictures/img/livraison.png \
    ../../Pictures/img/logo_meta-removebg-preview.png \
    ../../Pictures/img/plus (1).png \
    ../../Pictures/img/plus (1).png \
    ../../Pictures/img/plus.png \
    ../../Pictures/img/production.png \
    ../../Pictures/img/randomqr-256.png \
    ../../Pictures/img/trier.png \
    xxx.qml


