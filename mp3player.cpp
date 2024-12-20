#include "mp3player.h"
#include "ui_mp3player.h"
#include <QAudioDevice>
#include <QDebug>
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

void mp3Player::on_btnScanDir_clicked() //掃描目錄
{
    QDir dirpath = QFileDialog::getExistingDirectory(this,QStringLiteral("選擇目錄"),"C:/");
    if(dirpath.isEmpty())return;//空目錄

    QDir dir(dirpath);
    QStringList filters;//過濾條件
    filters<<"*.mp3";
    //讀入檔案
    QStringList fileList = dir.entryList(filters,QDir::Files);
    ui->tracksPage->setRowCount(fileList.size());//有幾筆設幾列
    for(int i=0;i<fileList.size();i++)
    {
        QFileInfo fileInfo(dirpath.absolutePath()+"/"+fileList.at(i));//絕對路徑
        float filesize = fileInfo.size();
        QString filesizeMB;filesizeMB.setNum(filesize/(1024*1024),'f',2);//大小轉換至MB
        QTableWidgetItem *trackname = new QTableWidgetItem(fileInfo.fileName());
        QTableWidgetItem *size = new QTableWidgetItem(filesizeMB+"MB");
        QTableWidgetItem *trackPath = new QTableWidgetItem(fileInfo.absoluteFilePath());
        ui->tracksPage->setItem(i,0,trackname);
        ui->tracksPage->setItem(i,1,size);
        ui->tracksPage->setItem(i,2,trackPath);
    }
    ui->tracksPage->selectColumn(0);
    qDebug()<<fileList;
    audioOutput->setVolume(0.2);
    qDebug()<<"volume:"<<audioOutput->volume();
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
    });
}

void mp3Player::on_btnPlayTrack_clicked()
{
    getMetaData();
    player->play();
    qDebug() << "Playing"<<ui->tracksPage->item(ui->tracksPage->currentRow(),0)->text();
    qDebug()<<"track duration:"<<player->duration();
    qDebug()<<"volume:"<<audioOutput->volume();
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


void mp3Player::on_btnPause_clicked()
{
    player->pause();
    qDebug() << "Paused";
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


void mp3Player::updateTrackPos(qint64 position)
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




