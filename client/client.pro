QT       += core gui
QT += sql
QT += printsupport
QT += widgets sql charts
QT += charts

QT += core gui network




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    connection.cpp \
    email.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    client.h \
    connection.h \
    email.h \
    mainwindow.h

FORMS += \
    mainwindow.ui \
    mainwindow_copy.ui

TRANSLATIONS += \
    client_en_GB.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc \
    bbackg.qrc \
    icones.qrc \
    loogoo.qrc
