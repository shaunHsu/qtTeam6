#include "shazamrequest.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

ShazamRequest::ShazamRequest() {}
void ShazamRequest::sendRequest(const QByteArray &audioData) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url(
        "https://shazam.p.rapidapi.com/songs/v2/detect"); //?timezone=America%2FChicago&locale=en-US
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    request.setRawHeader("X-Rapidapi-Key",
                         "0e50f43eb2msh907beb2f8507bbcp117913jsnd8093405498e");
    request.setRawHeader("X-Rapidapi-Host", "shazam.p.rapidapi.com");

    QNetworkReply *reply = manager->post(request, audioData);
    qDebug() << "Request sent";

    // Connect signals for handling the response
    connect(reply, &QNetworkReply::finished, [=]() {
        int statusCode =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            qDebug() << "Response:" << response;
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}