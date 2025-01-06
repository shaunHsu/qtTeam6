#ifndef AUDIOPROCESSOR_H
#define AUDIOPROCESSOR_H

#include <QAudioDecoder>
#include <QByteArray>
#include <QObject>

class AudioProcessor : public QObject {
        Q_OBJECT

    public:
        explicit AudioProcessor(QObject *parent = nullptr);
        void processAudioFile(const QString &inputFile);
        QByteArray resampleBuffer(const QAudioBuffer &buffer);
        bool isProcessingFinished = false;
        QByteArray audioData;

    signals:
        void processingFinished();

    private slots:
        void handleBuffer();
        void handleFinished();
        void handleError();

    private:
        static constexpr int TARGET_SAMPLE_RATE = 44100;
        static constexpr int TARGET_CHANNEL_COUNT = 1;
        static constexpr int TARGET_SAMPLE_SIZE = 16;
        static constexpr qreal FIVE_SECONDS = 5.0;

        QAudioDecoder *decoder;
        QByteArray processedData;
        bool fiveSecondsReached;
        qint64 totalProcessedDuration;
};

#endif // AUDIOPROCESSOR_H