#include <QApplication>

#include "AudioProcessor.h"
#include "shazamrequest.h"

void apiTest() {
    QString fileName = "C:/code/qt/qtTeam6/example_audio/test3.mp3";

    AudioProcessor *processor = new AudioProcessor();
    ShazamRequest *request = new ShazamRequest();

    QObject::connect(processor, &AudioProcessor::processingFinished,
                     [=]() { request->sendRequest(processor->audioData); });
    QObject::connect(request, &ShazamRequest::finished, [=]() {
        for (QString info : request->getInfo(request->response)) {
            qDebug() << info;
        }
    });

    processor->processAudioFile(fileName);
}
