#include "mp3player.h"
#include "ui_mp3player.h"
#include <QAudioDevice>
#include <QDebug>

#include <QScrollBar>
#include <QFileDialog>
#include <QFileInfo>
#include <QTableWidgetItem>


mp3Player::mp3Player(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mp3Player)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this); //實體化player
    audioOutput = new QAudioOutput(this);//加入audioOut
    player->setAudioOutput(audioOutput);//設定player的audioOutput
    audioOutput->setVolume(0.2);//設定音量
    //設定上方欄位tag
    ui->tracksPage->setColumnCount(3);//曲名 長度 檔案路徑
    ui->playlistPage->setColumnCount(3);
    //set first column width
    ui->tracksPage->setColumnWidth(0,200);
    ui->tracksPage->setColumnWidth(2,500);
    QStringList colTitle;
    colTitle<<QStringLiteral("曲名")<<QStringLiteral("檔案大小")<<QStringLiteral("檔案路徑");
    ui->tracksPage->setHorizontalHeaderLabels(colTitle);
    ui->playlistPage->setHorizontalHeaderLabels(colTitle);
    //SIGNAL SLOT
    connect(player, &QMediaPlayer::positionChanged, this, &mp3Player::updateTrackPos);//播放->更新進度條
    connect(player, &QMediaPlayer::durationChanged, this, &mp3Player::updateTrackDur);//播放->更新進度條
    connect(player, &QMediaPlayer::mediaStatusChanged,this,&mp3Player::autoplayNext);

}

mp3Player::~mp3Player()
{
    delete ui;
}

void mp3Player::findMp3Files(const QDir &dir, QStringList &fileList)
{
    // 讀取當前目錄中的檔案
    QStringList filters;
    filters << "*.mp3";
    QStringList files = dir.entryList(filters, QDir::Files);
    for (const QString &file : files)
    {
        fileList.append(dir.filePath(file));  // 使用 filePath() 來獲取檔案的絕對路徑
    }

    // 遍歷子目錄
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &subDir : subDirs)
    {
        QDir subDirPath = dir.filePath(subDir);
        findMp3Files(subDirPath, fileList);  // 遞迴搜尋子目錄
    }
}

void mp3Player::on_btnScanDir_clicked() //掃描目錄
{
    QDir dirpath = QFileDialog::getExistingDirectory(this, QStringLiteral("選擇目錄"), "E:/music", QFileDialog::ShowDirsOnly);
    if (dirpath.isEmpty()) return; // 空目錄

    QStringList fileList;
    findMp3Files(dirpath, fileList);  // 找到所有的 .mp3 檔案

    qDebug() << "Found files: " << fileList;

    ui->tracksPage->setRowCount(fileList.size()); // 設置行數
    for (int i = 0; i < fileList.size(); i++)
    {
        QFileInfo fileInfo(fileList.at(i));  // 直接使用絕對路徑
        qDebug() << "Processing file: " << fileInfo.absoluteFilePath(); // 顯示檔案的絕對路徑

        if (fileInfo.exists()) // 確保檔案存在
        {
            float filesize = fileInfo.size();
            qDebug() << "File size: " << filesize; // 顯示檔案大小

            QString filesizeMB;
            filesizeMB.setNum(filesize / (1024 * 1024), 'f', 2);  // 大小轉換為MB
            QTableWidgetItem *trackname = new QTableWidgetItem(fileInfo.fileName());
            QTableWidgetItem *size = new QTableWidgetItem(filesizeMB + "MB");
            QTableWidgetItem *trackPath = new QTableWidgetItem(fileInfo.absoluteFilePath());
            ui->tracksPage->setItem(i, 0, trackname);
            ui->tracksPage->setItem(i, 1, size);
            ui->tracksPage->setItem(i, 2, trackPath);
        }
        else
        {
            qDebug() << "File does not exist: " << fileInfo.absoluteFilePath();
        }
    }
    ui->tracksPage->selectColumn(0);
    audioOutput->setVolume(0.2);
    qDebug() << "volume:" << audioOutput->volume();
}





void mp3Player::getMetaData()
{
    if(ui->tracksPage->currentRow()<0)return;
    player->setSource(QUrl::fromLocalFile(ui->tracksPage->item(ui->tracksPage->currentRow(),2)->text()));
    connect(player, &QMediaPlayer::metaDataChanged, this, [this]() {
        QMediaMetaData meta = player->metaData();
        QString title = meta.stringValue(QMediaMetaData::Title);
        QString duration = QTime(0, 0).addMSecs(static_cast<int>(player->duration())).toString("mm:ss");
        QTime t; t.setHMS(duration.split(":").at(0).toInt(),duration.split(":").at(1).toInt(),0);
        ui->TrackDuration->setText(duration);
        ui->TrackTitle->setText(title);

        // 加載歌詞
        QString trackPath = ui->tracksPage->item(ui->tracksPage->currentRow(), 2)->text();
        loadLyrics(trackPath);
    });
    QString filePath = ui->tracksPage->item(ui->tracksPage->currentRow(), 2)->text();
    player->setSource(QUrl::fromLocalFile(filePath));

    // 從播放器中提取中繼資料


    // 如果標籤資料不存在，使用檔案名稱作為歌曲標題

}

void mp3Player::on_btnPlayTrack_clicked()
{
    // 如果當前選擇的曲目與先前的曲目不同，則重新載入元數據
    if (currentRow != ui->tracksPage->currentRow()) {
        getMetaData();  // 如果換歌，重新取得meta
        qDebug() << "Detected Change currentRow:" << currentRow << "-->" << ui->tracksPage->currentRow() << " reload meta data";
    }

    // 播放或暫停音樂
    if (player->playbackState() == QMediaPlayer::StoppedState) {
        currentRow = ui->tracksPage->currentRow();  // 紀錄目前位置
        qDebug() << "currentRow:" << currentRow;

        // 設置並開始播放音樂
        player->play();
        ui->btnPlayTrack->setText("Pause");  // 更新按鈕文字為暫停
        qDebug() << "Playing" << ui->tracksPage->item(ui->tracksPage->currentRow(), 0)->text();
        qDebug() << "track duration:" << player->duration();
        qDebug() << "volume:" << audioOutput->volume();

        // 初始化定時器來更新歌詞
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            qint64 currentTime = player->position();  // 獲取當前播放時間（毫秒）
            updateLyricsDisplay(currentTime);  // 更新歌詞顯示
        });
        timer->start(100);  // 每 100 毫秒更新一次歌詞顯示
    } else if (player->playbackState() == QMediaPlayer::PausedState) {
        player->play();  // 恢復播放
        ui->btnPlayTrack->setText("Pause");  // 更新按鈕文字為暫停
        qDebug() << "Resumed";
    } else if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();  // 暫停播放
        ui->btnPlayTrack->setText("Play");  // 更新按鈕文字為播放
        qDebug() << "Paused";
    }
}


void mp3Player::autoplayNext()
{
    if(player->mediaStatus()==QMediaPlayer::EndOfMedia)//check if the signal is endofmedia
    {
        ui->tracksPage->setCurrentCell(ui->tracksPage->currentRow()+1,0); //do autoplay
        getMetaData();
        player->play();
    }
}

void mp3Player::on_horizontalSlider_valueChanged(int value)
{
        qreal volume = static_cast<qreal>(value) / 100.0;
        qDebug() << "Slider Value:" << value << "Volume:" << volume;
        audioOutput->setVolume(volume);
}

void mp3Player::on_btnStop_clicked()
{
    player->stop();
    qDebug() << "Stopped";
}


void mp3Player::on_btnNext_clicked()
{
    ui->tracksPage->setCurrentCell(ui->tracksPage->currentRow()+1,0);
    getMetaData();
    player->play();
}

void mp3Player::on_btnPrev_clicked()
{
    ui->tracksPage->setCurrentCell(ui->tracksPage->currentRow()-1,0);
    getMetaData();
    player->play();
}


void mp3Player::updateTrackPos(qint64 position)//隨播放進度更新時間條
{
   // if (!isUpdatingSlider) {
        isUpdatingSlider = true;
        ui->trackPosSlider->setValue(static_cast<int>(position));
        isUpdatingSlider = false;
   // }
}

void mp3Player::updateTrackTime()//當前進度->更新顯示時間
{
    QString currentTime = QTime(0, 0).addMSecs(static_cast<int>(player->position())).toString("mm:ss");
    QString duration = QTime(0, 0).addMSecs(static_cast<int>(player->duration())).toString("mm:ss");
    ui->TrackDuration->setText(currentTime+"/"+duration);
}

void mp3Player::updateTrackDur()
{
    if(player->duration()>0){
    ui->trackPosSlider->setRange(0,static_cast<int>(player->duration()));
        qDebug()<<"Duration updated to:"<<player->duration();
    }
}

void mp3Player::on_trackPosSlider_valueChanged(int value)//進度條->主要更新時間的方式
{
    if (!isUpdatingSlider) {
        player->setPosition(static_cast<qint64>(value));
        qDebug() << "Slider moved to position:" << value;
    }
    updateTrackTime();
    qDebug() << "Player state after setPosition:" << player->playbackState();
    qDebug() << "Audio volume:" << audioOutput->volume();
}

void mp3Player::loadLyrics(const QString &trackPath) {
    QString baseDirectory = QCoreApplication::applicationDirPath();
    QDir projectDir(baseDirectory);
    projectDir.cdUp();
    QString lyricsFilePath = projectDir.absolutePath() + "/test/" + QFileInfo(trackPath).baseName() + ".lrc";

    QFile lyricsFile(lyricsFilePath);
    if (!lyricsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "無法開啟檔案：" << lyricsFilePath;
        ui->lyricsDisplay->setText(QStringLiteral("無法找到歌詞檔案"));
        lyrics.clear();  // 確保清空歌詞資料
        return;
    }

    QTextStream in(&lyricsFile);
    lyrics.clear();  // 確保清空之前的歌詞資料
    QRegularExpression regex(R"(\[(\d+):(\d+)(?:\.(\d+))?\](.+))");

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatch match = regex.match(line);

        if (match.hasMatch()) {
            int minutes = match.captured(1).toInt();
            int seconds = match.captured(2).toInt();
            int milliseconds = match.captured(3).isEmpty() ? 0 : match.captured(3).toInt();
            qint64 timestamp = minutes * 60000 + seconds * 1000 + milliseconds;

            QString text = match.captured(4).trimmed();
            lyrics.insert(timestamp, text);  // 將時間戳和歌詞內容加入 QMap
        }
    }

    lyricsFile.close();
    qDebug() << "歌詞載入成功：" << lyrics;  // 除錯訊息，確認載入的歌詞內容
}

void mp3Player::updateLyricsDisplay(qint64 currentTime) {
    if (lyrics.isEmpty()) {
        ui->lyricsDisplay->setText(QStringLiteral("無歌詞顯示"));
        return;
    }

    QString formattedLyrics;
    auto it = lyrics.constBegin();

    bool isHighlighted = false;
    qint64 totalHeight = 0;  // 用來計算總的歌詞高度
    qint64 highlightedHeight = 0;  // 用來記錄高亮歌詞的高度

    while (it != lyrics.constEnd()) {
        qint64 timestamp = it.key();
        QString text = it.value();

        // 判斷當前時間是否在這一行歌詞的範圍內，並高亮顯示
        auto next = it;
        ++next;

        // 計算這一行歌詞的顯示高度
        QString style = (currentTime >= timestamp && (next == lyrics.constEnd() || currentTime < next.key()))
                            ? "<p style='color:red;text-align:center; font-size:20px; line-height:1.5;'>" + text + "</p>"
                            : "<p style='color:black;text-align:center; font-size:18px; line-height:1.5;'>" + text + "</p>";

        formattedLyrics += style;

        // 如果這一行是高亮歌詞，記錄它的高度
        if (currentTime >= timestamp && (next == lyrics.constEnd() || currentTime < next.key())) {
            highlightedHeight = totalHeight;
        }

        // 更新總高度
        totalHeight += 40; // 假設每行歌詞的高度大約為40，這個值可根據需要調整

        ++it;
    }

    // 更新歌詞顯示區域
    ui->lyricsDisplay->setText(formattedLyrics);

    // 讓滾動條自動滾動
    QScrollBar *scrollBar = ui->lyricsDisplay->verticalScrollBar();
    int viewHeight = ui->lyricsDisplay->height();
    int targetScrollPosition = highlightedHeight - viewHeight / 4;  // 滾動到高亮歌詞的中間位置
    scrollBar->setValue(qMax(0, targetScrollPosition));
}


