#include <QApplication>

#include "AudioProcessor.h"
#include "mainwindow.h"
#include "shazamrequest.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QString fileName = "";

    AudioProcessor processor;
    processor.processAudioFile(fileName);

    while (!processor.isProcessingFinished) {
        QCoreApplication::processEvents();
    }
    ShazamRequest request;
    request.sendRequest(processor.audioData);

    // MainWindow w;
    // w.show();
    return a.exec();
}