#include "email.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QTextStream>
#include <QMimeDatabase>
#include <QMimeType>



QString mailer::smtpServer = "smtp.gmail.com";
int mailer::smtpPort = 465; // Port sécurisé pour SSL
QString mailer::username = "wesswass20@gmail.com"; // Votre adresse email
QString mailer::password = "yyuo xcqi itdv ffdb"; // Mot de passe d'application

mailer::mailer() {}

int mailer::sendEmail(const QString &dist, const QString &obj, const QString &bdy, const QStringList &attachments) {
    QSslSocket socket;

    // Connect to the SMTP server
    socket.connectToHostEncrypted(smtpServer, smtpPort);
    if (!socket.waitForConnected()) {
        qDebug() << "Error connecting to the server:" << socket.errorString();
        return -1;
    }
    if (!socket.waitForReadyRead()) {
        qDebug() << "Error waiting for server response:" << socket.errorString();
        return -1;
    }

    auto sendCommand = [&](const QString &command) -> bool {
        socket.write(command.toUtf8());
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Error during command:" << command << ", Error:" << socket.errorString();
            return false;
        }
        return true;
    };

    if (!sendCommand("HELO localhost\r\n")) return -1;
    if (!sendCommand("AUTH LOGIN\r\n")) return -1;
    if (!sendCommand(QByteArray(username.toUtf8()).toBase64() + "\r\n")) return -1;
    if (!sendCommand(QByteArray(password.toUtf8()).toBase64() + "\r\n")) return -1;
    if (!sendCommand("MAIL FROM:<" + username + ">\r\n")) return -1;
    if (!sendCommand("RCPT TO:<" + dist + ">\r\n")) return -1;
    if (!sendCommand("DATA\r\n")) return -1;

    // Generate MIME message
    QString boundary = "----=_Boundary_" + QString::number(rand());
    QString message =
        "From: " + username + "\r\n"
        "To: " + dist + "\r\n"
        "Subject: " + obj + "\r\n"
        "MIME-Version: 1.0\r\n"
        "Content-Type: multipart/mixed; boundary=\"" + boundary + "\"\r\n\r\n";

    // Add body
    message += "--" + boundary + "\r\n";
    message += "Content-Type: text/plain; charset=\"UTF-8\"\r\n";
    message += "Content-Transfer-Encoding: 7bit\r\n\r\n";
    message += bdy + "\r\n\r\n";

    // Add attachments
    for (const QString &filePath : attachments) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open attachment:" << filePath;
            continue;
        }

        QMimeDatabase mimeDb;
        QMimeType mimeType = mimeDb.mimeTypeForFile(filePath);
        QString fileName = QFileInfo(filePath).fileName();

        message += "--" + boundary + "\r\n";
        message += "Content-Type: " + mimeType.name() + "; name=\"" + fileName + "\"\r\n";
        message += "Content-Transfer-Encoding: base64\r\n";
        message += "Content-Disposition: attachment; filename=\"" + fileName + "\"\r\n\r\n";

        message += file.readAll().toBase64();
        message += "\r\n\r\n";
    }

    // End of email
    message += "--" + boundary + "--\r\n.\r\n";

    if (!sendCommand(message)) return -1;

    // Quit the session
    sendCommand("QUIT\r\n");
    socket.close();

    qDebug() << "Email sent successfully with attachments.";
    return 0;
}
