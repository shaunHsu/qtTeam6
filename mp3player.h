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

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QMap>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QRegularExpression>
#include <QCoreApplication>

#include <QDir>
#include <QStringList>


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
    void on_btnScanDir_clicked();//掃描選取目錄內的mp3檔案(目前只能選擇資料夾路徑一次掃瞄)

    void getMetaData();//取得歌曲資訊

    void on_btnPlayTrack_clicked();//載入meta後播放

    void on_horizontalSlider_valueChanged(int value);//音量條訊號

    void on_btnStop_clicked();//停止按鈕

    void on_btnNext_clicked();//下一首按鈕

    void updateTrackPos(qint64 position);//歌曲timestamp->更新時間條

    void updateTrackTime();//更新播放時間功能

    void updateTrackDur();//讀取歌曲長度

    void on_trackPosSlider_valueChanged(int value);//時間條訊號->歌曲timestamp

    void on_btnPrev_clicked();//播放上一首

    void autoplayNext();//自動播放下一首

    void loadLyrics(const QString &trackPath); // 加載歌詞

    void updateLyricsDisplay(qint64 currentTime); //顯示歌詞

    void findMp3Files(const QDir &dir, QStringList &fileList);




private:
    Ui::mp3Player *ui;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    bool    isUpdatingSlider; //防止時間條更新時觸發訊號的flag
    int     currentRow;//目前播放的歌曲位置

    QMap<qint64, QString> lyrics;
    QList<int> lyricsTimes;

};
#endif // MP3PLAYER_H
