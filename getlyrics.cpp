#include "getlyrics.h"

#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QTextDocument>
#include <QXmlStreamReader>
#define FILEPATH "./lyricsTemp.txt"
#define HTMLPATH "./urlTemp.html"

GetLyrics::GetLyrics(QObject* parent) : QObject(parent) {}
int GetLyrics::getLyricsUrl(const QString& title) {
    QNetworkAccessManager manager;
    QNetworkRequest request(
        "https://api.genius.com/search?q=" + title +
        "&access_token=51C-_"
        "I4M0EwWXwJVVmlEruTZiQXOlHh67ZxhJtwJmz5HSlc65Ve9Yv6qnQYES7fH");
    QNetworkReply* reply = manager.get(request);
    qDebug() << "Getting lyrics URL...";
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Got lyrics URL.";
        QByteArray response = reply->readAll();

         QString jsonString = QString::fromUtf8(response);
         QFile jsonFile("response1.json");
         if (jsonFile.open(QIODevice::WriteOnly)) {
             jsonFile.write(jsonString.toUtf8());
             jsonFile.close();
             qDebug() << "Response written to JSON file.";
         } else {
             qDebug() << "Failed to open file for writing.";
         }
         qDebug() << response;

        QJsonDocument jsonDoc(QJsonDocument::fromJson(response));
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray hitsArray = jsonObj["response"].toObject()["hits"].toArray();
        if (!hitsArray.isEmpty()) {
            url =
                hitsArray[0].toObject()["result"].toObject()["url"].toString();
        } else {
            qDebug() << "No hits found in the response.";
        }
        return 0;
    } else {
        qDebug() << "Error: " << reply->errorString();
        return 1;
    }
    reply->deleteLater();
}
void GetLyrics::getLyricsHtml() {
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setRawHeader(
        "User-Agent",
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 "
        "(KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36");
    qDebug() << "Getting lyrics HTML..." << url;
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Got lyrics HTML.";
        html = reply->readAll();


         QString htmlString = QString::fromUtf8(html);
         QFile htmlFile(HTMLPATH);
         if (htmlFile.open(QIODevice::WriteOnly)) {
             htmlFile.write(htmlString.toUtf8());
             htmlFile.close();
            qDebug() << "Lyrics written to HTML file."<<HTMLPATH;
         } else {
            qDebug() << "Failed to open file for writing.";
         }

    } else {
        qDebug() << "Error: " << reply->errorString();
    }
}
QString GetLyrics::getLyricsText() {
    qDebug() << "Starting Parse lyrics text...";
    QStringList results;

    QRegularExpression regex(
        R"(<div data-lyrics-container="true" class="Lyrics-sc-1bcc94c6-1 bzTABU">(.*?)</div>)",
        QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator match = regex.globalMatch(html);

    while (match.hasNext()) {
        QRegularExpressionMatch i = match.next();
        QString lyricsWithHtml = i.captured(1); // 獲取 <div> 的內容

        // 移除 HTML 標籤
        QRegularExpression tagRegex(R"(<[^>]+>)");
        QString lyricsPlainText = lyricsWithHtml.remove(tagRegex);

        results.append(lyricsPlainText.trimmed());
    }

    QString tempFile = FILEPATH;
    QFile lyricsFile(tempFile);
    if (lyricsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        lyricsFile.write(results.join("\n").toUtf8());
        lyricsFile.close();
        qDebug() << "Lyrics written to text file."<<tempFile;
     }

    qDebug() << "Parse lyrics text done.";
    return results.join(" ");
}
QString GetLyrics::getLyrics(const QString& title) {
    getLyricsUrl(title);
    getLyricsHtml();
    return getLyricsText();
}
