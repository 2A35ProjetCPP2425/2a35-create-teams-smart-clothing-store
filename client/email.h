#ifndef EMAIL_H
#define EMAIL_H


#include <QString>
#include <QtNetwork/QSslSocket>
#include <QStringList>

class mailer {
public:
    mailer();
    static int sendEmail(const QString &dist, const QString &obj, const QString &bdy, const QStringList &attachments = {});

private:
    static QString smtpServer;
    static int smtpPort;
    static QString username;
    static QString password;
};

#endif // EMAIL_H
