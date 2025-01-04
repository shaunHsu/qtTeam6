#ifndef GETLYRICS_H
#define GETLYRICS_H

#include <QNetworkAccessManager>
#include <QObject>
#include <QString>

class GetLyrics : public QObject {
        Q_OBJECT

    public:
        explicit GetLyrics(QObject* parent = nullptr);
        QString getLyrics(const QString& title);

    private:
        QString url;
        QByteArray html;
        int getLyricsUrl(const QString& title);
        void getLyricsHtml();
        QString getLyricsText();
};

#endif // GETLYRICS_H