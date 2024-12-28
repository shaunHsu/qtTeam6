#ifndef SHAZAMREQUEST_H
#define SHAZAMREQUEST_H

#include <QObject>
#include <QString>

class ShazamRequest : public QObject {
        Q_OBJECT
    public:
        ShazamRequest();
        void sendRequest(const QByteArray& audioData);
};

#endif // SHAZAMREQUEST_H
