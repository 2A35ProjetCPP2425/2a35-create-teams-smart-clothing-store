# Configuration des modules Qt nécessaires
QT       += core gui widgets sql printsupport charts network
QT       += core gui  serialport

# Vérification pour Qt5 ou supérieur (ajoute widgets si version Qt >= 5)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Utilisation du standard C++17
CONFIG += c++17

# Option pour inclure les API obsolètes uniquement si nécessaire
# Pour désactiver les API obsolètes avant une certaine version :
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Sources du projet
SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    dialog.cpp \
    email.cpp \
    employe.cpp \
    main.cpp \
    mainwindow.cpp

# Headers du projet
HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    dialog.h \
    email.h \
    employe.h \
    mainwindow.h

# Fichiers UI (interfaces graphiques)
FORMS += \
    mainwindow.ui \
    mainwindow_copy.ui

# Fichiers de traduction
TRANSLATIONS += \
    client_en_GB.ts

# Configuration pour gérer les traductions
CONFIG += lrelease
CONFIG += embed_translations

# Ressources du projet
RESOURCES += \
    background.qrc \
    bbackg.qrc \
    icones.qrc \
    loogoo.qrc

# Règles de déploiement par défaut
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
