QT += core gui
QT += sql
CONFIG += console
CONFIG += qt console
QT += charts



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    dialog.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    connection.h \
    dialog.h \
    employe.h \
    mainwindow.h

FORMS += \
    dialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    Gcommande_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target