#include <QApplication>

#include "AudioProcessor.h"
<<<<<<< HEAD
#include "getlyrics.h"
#include "shazamrequest.h"

void apiTest() {
    QString fileName = "C:/code/qt/qtTeam6/example_audio/test1.mp3";

    AudioProcessor *processor = new AudioProcessor();
    ShazamRequest *request = new ShazamRequest();
    GetLyrics *lyrics = new GetLyrics();
=======
#include "shazamrequest.h"

void apiTest() {
    QString fileName = "C:/code/qt/qtTeam6/example_audio/test3.mp3";

    AudioProcessor *processor = new AudioProcessor();
    ShazamRequest *request = new ShazamRequest();
>>>>>>> 8fb7cdd362934e82b293973cd2788fdeab016df7

    QObject::connect(processor, &AudioProcessor::processingFinished,
                     [=]() { request->sendRequest(processor->audioData); });
    QObject::connect(request, &ShazamRequest::finished, [=]() {
<<<<<<< HEAD
        QStringList infos = request->getInfo(request->response);
        // for (QString info : infos) {
        //     qDebug() << info;
        // }
        qDebug() << lyrics->getLyrics(infos.at(0));
=======
        for (QString info : request->getInfo(request->response)) {
            qDebug() << info;
        }
>>>>>>> 8fb7cdd362934e82b293973cd2788fdeab016df7
    });

    processor->processAudioFile(fileName);
}
