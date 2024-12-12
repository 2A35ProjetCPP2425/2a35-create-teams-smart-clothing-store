#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QString>

class Arduino {
private:
    QSerialPort *serial;         // Serial port instance
    QString arduino_port_name;   // Port name
    bool arduino_is_available;   // Check availability

public:
    Arduino();
    int connect_arduino(const QString &portName); // Connect to Arduino
    int close_arduino();                          // Disconnect Arduino
    QString read_from_arduino();                  // Read data from Arduino
};

#endif // ARDUINO_H


