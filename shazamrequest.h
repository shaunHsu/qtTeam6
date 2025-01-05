#ifndef SHAZAMREQUEST_H
#define SHAZAMREQUEST_H

#include <QObject>
#include <QString>

class ShazamRequest : public QObject {
        Q_OBJECT
    public:
        QByteArray response;
        ShazamRequest();
        void sendRequest(const QByteArray& audioData);
        QStringList getInfo(const QByteArray& response);
    signals:
        void finished();
};

#endif // SHAZAMREQUEST_H
