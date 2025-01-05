#include "shazamrequest.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
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
            response = reply->readAll();
            emit finished();
            // QString jsonString = QString::fromUtf8(response);
            // QFile jsonFile("response.json");

            // if (jsonFile.open(QIODevice::WriteOnly)) {
            //     jsonFile.write(jsonString.toUtf8());
            //     jsonFile.close();
            //     qDebug() << "Response written to JSON file.";
            // } else {
            //     qDebug() << "Failed to open file for writing.";
            // }
            // qDebug() << "Response:" << response;
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
QStringList ShazamRequest::getInfo(const QByteArray &response) {
    // Parse the response
    QJsonDocument jsonDoc(QJsonDocument::fromJson(response));
    QJsonObject jsonObj = jsonDoc.object();
    QJsonObject trackObj = jsonObj["track"].toObject();
    QString title = trackObj["title"].toString().trimmed();
    QString artist = trackObj["subtitle"].toString().trimmed();
    QString url = trackObj["url"].toString().trimmed();
    QStringList info;
    info << title << artist << url;

    return info;
}