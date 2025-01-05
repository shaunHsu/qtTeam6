#include <QApplication>
#include <QDebug>
#include "AudioProcessor.h"
#include "getlyrics.h"
#include "shazamrequest.h"

void apiTest() {
    QString fileName = "C:/code/qt/qtTeam6/example_audio/test1.mp3";

    AudioProcessor *processor = new AudioProcessor();
    ShazamRequest *request = new ShazamRequest();
    GetLyrics *lyrics = new GetLyrics();

    QObject::connect(processor, &AudioProcessor::processingFinished,
                     [=]() { request->sendRequest(processor->audioData); });
    QObject::connect(request, &ShazamRequest::finished, [=]() {
        QStringList infos = request->getInfo(request->response);

        qDebug() << infos.at(0); // 取得歌名

        QString lyricText = lyrics->getLyrics(infos.at(0)); // 取得完整歌詞
        QStringList lyricLines = lyricText.split('\n');     // 按行分隔歌詞

        for (const QString &line : lyricLines) {
            qDebug() << line.trimmed(); // 去掉首尾多餘空白後逐行輸出
        }
    });

    processor->processAudioFile(fileName);
}
