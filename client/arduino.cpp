#include "arduino.h"

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial = new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}

int Arduino::connect_arduino()
{
    // Recherche du port Arduino parmi les ports disponibles
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                break; // Arduino trouvé, pas besoin de continuer la recherche
            }
        }
    }

    qDebug() << "Nom du port Arduino : " << arduino_port_name;

    if (arduino_is_available) {
        // Configuration du port série
        serial->setPortName(arduino_port_name);
        if (serial->isOpen()) {
            serial->close(); // Fermer tout port ouvert précédemment
        }
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);

            qDebug() << "Connexion série réussie à : " << arduino_port_name;
            return 0; // Connexion réussie
        } else {
            qDebug() << "Erreur : Impossible d'ouvrir le port série : " << serial->errorString();
            return 1; // Port non ouvert
        }
    } else {
        qDebug() << "Erreur : Aucun Arduino détecté.";
        return -1; // Arduino non trouvé
    }
}


int Arduino::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0; // Succès
    }
    return 1; // Échec si déjà fermé
}

QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data = serial->readAll(); // Récupérer toutes les données reçues
        return data;
    }
    return QByteArray(); // Retourner un QByteArray vide si aucune donnée n'est disponible
}

void Arduino::write_to_arduino(const QString &command)
{
    if (serial && serial->isWritable()) {
        serial->write(command.toUtf8() + '\n');
        qDebug() << "Commande envoyée:" << command;
    } else {
        qDebug() << "Port série non prêt à écrire.";
    }
}
