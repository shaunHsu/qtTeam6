
#include "AudioProcessor.h"

#include <QDebug>
#include <QFile>
#include <QMediaDevices>
#include <QUrl>

AudioProcessor::AudioProcessor(QObject *parent)
    : QObject(parent),
      decoder(new QAudioDecoder(this)),
      fiveSecondsReached(false),
      totalProcessedDuration(0) {
    connect(decoder, &QAudioDecoder::bufferReady, this,
            &AudioProcessor::handleBuffer);
    connect(decoder, &QAudioDecoder::finished, this,
            &AudioProcessor::handleFinished);
    connect(decoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error),
            this, &AudioProcessor::handleError);
}

void AudioProcessor::processAudioFile(const QString &inputFile) {
    QFile file(inputFile);
    if (!file.exists()) {
        qDebug() << "Input file does not exist!";
        return;
    }

    processedData.clear();
    fiveSecondsReached = false;
    totalProcessedDuration = 0;

    // 設置目標音頻格式
    QAudioFormat targetFormat;
    targetFormat.setSampleRate(TARGET_SAMPLE_RATE);
    targetFormat.setChannelCount(TARGET_CHANNEL_COUNT);
    targetFormat.setSampleFormat(QAudioFormat::Int16);

    decoder->setAudioFormat(targetFormat);
    decoder->setSource(QUrl::fromLocalFile(inputFile));
    decoder->start();
}

QByteArray AudioProcessor::resampleBuffer(const QAudioBuffer &buffer) {
    QByteArray result;
    const qint16 *data = buffer.constData<qint16>();
    int sampleCount = buffer.sampleCount();
    int channelCount = buffer.format().channelCount();

    // 如果是多聲道，轉換為單聲道
    if (channelCount > 1) {
        for (int i = 0; i < sampleCount; i += channelCount) {
            // 混音到單聲道
            qint32 sum = 0;
            for (int ch = 0; ch < channelCount; ++ch) {
                sum += data[i + ch];
            }
            qint16 monoSample = sum / channelCount;
            result.append(reinterpret_cast<const char *>(&monoSample),
                          sizeof(qint16));
        }
    } else {
        // 已經是單聲道，直接複製
        result.append(reinterpret_cast<const char *>(data),
                      sampleCount * sizeof(qint16));
    }

    return result;
}

void AudioProcessor::handleBuffer() {
    if (fiveSecondsReached) {
        return;
    }

    QAudioBuffer buffer = decoder->read();

    // 檢查是否已達到5秒
    qreal bufferDuration = buffer.duration() / 1000000.0; // 轉換為秒
    if (totalProcessedDuration + bufferDuration > FIVE_SECONDS * 1000000) {
        // 計算需要的採樣數
        int samplesNeeded =
            (FIVE_SECONDS * TARGET_SAMPLE_RATE) -
            (totalProcessedDuration * TARGET_SAMPLE_RATE / 1000000);

        // 裁切buffer
        QByteArray resampledData = resampleBuffer(buffer);
        int bytesNeeded = samplesNeeded * sizeof(qint16);
        processedData.append(resampledData.left(bytesNeeded));

        fiveSecondsReached = true;
        decoder->stop();

        audioData = processedData.toBase64();
        isProcessingFinished = true;
        qDebug() << "audio data processed";

        // QByteArray base64Data = processedData.toBase64();
        // qDebug() << "Base64 output";

        // QFile outputFile("output_audio.txt");
        // if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //     outputFile.write(base64Data);
        //     outputFile.close();
        //     qDebug() << "Base64 data saved to output_audio.txt";
        // }
    } else {
        processedData.append(resampleBuffer(buffer));
        totalProcessedDuration += buffer.duration();
    }
}

void AudioProcessor::handleFinished() {
    if (!fiveSecondsReached) {
        audioData = processedData.toBase64();
        isProcessingFinished = true;
        qDebug() << "audio data processed";
        // QByteArray base64Data = processedData.toBase64();
        // qDebug() << "Base64 output (less than 5 seconds)";

        // QFile outputFile("output_audio.txt");
        // if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //     outputFile.write(base64Data);
        //     outputFile.close();
        //     qDebug() << "Base64 data saved to output_audio.txt";
        // }
    }
}

void AudioProcessor::handleError() { qDebug() << "Error:" << decoder->error(); }