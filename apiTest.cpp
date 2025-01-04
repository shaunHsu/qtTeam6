#include <QApplication>

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
        // for (QString info : infos) {
        //     qDebug() << info;
        // }
        qDebug() << lyrics->getLyrics(infos.at(0)); // 取得歌名
    });

    processor->processAudioFile(fileName);
}
