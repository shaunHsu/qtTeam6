#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTableWidgetItem>
#include <QStringList>
#include <QMediaPlayer>
#include <QtMultimedia>


QT_BEGIN_NAMESPACE
namespace Ui {
class mp3Player;
}
QT_END_NAMESPACE

class mp3Player : public QMainWindow
{
    Q_OBJECT

public:
    mp3Player(QWidget *parent = nullptr);
    ~mp3Player();

private slots:
    void on_btnScanDir_clicked();
    void getMetaData();
    void on_btnPlayTrack_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_btnPause_clicked();

    void on_btnStop_clicked();

    void on_btnNext_clicked();

    void updateTrackPos(qint64 position);

    void updateTrackTime();

    void updateTrackDur();

    void on_trackPosSlider_valueChanged(int value);


    void on_btnPrev_clicked();

    void autoplayNext();

private:
    Ui::mp3Player *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool isUpdatingSlider;
};
#endif // MP3PLAYER_H
