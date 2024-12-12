#include "arduino.h"
#include <QDebug>

Arduino::Arduino() {
    serial = new QSerialPort;
    arduino_is_available = false;
}

int Arduino::connect_arduino(const QString &portName) {
    if (serial->isOpen()) {
        serial->close();
    }

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QSerialPort::ReadOnly)) {
        qDebug() << "Connected to Arduino on port:" << portName;
        return 0;
    } else {
        qDebug() << "Failed to connect:" << serial->errorString();
        return 1;
    }
}

int Arduino::close_arduino() {
    if (serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

QString Arduino::read_from_arduino() {
    if (serial->isReadable()) {
        QByteArray data = serial->readAll();
        return QString(data);
    }
    return "";
}
