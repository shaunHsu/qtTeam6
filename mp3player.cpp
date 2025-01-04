#include "mp3player.h"
#include "ui_mp3player.h"

#include <QThread>
#include <QAudioDevice>
#include <QDebug>
#include <QStatusBar>

#define LYRFILE "./lyricsTemp.txt"
#define LYRHTML "./urlTemp.html"
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
    ui->statusbar->showMessage(QStringLiteral("請按下Scan選擇目標資料夾掃描mp3檔案..."));
    existingCount = 0;
    ui->tracksPage->setColumnCount(3);//曲名 長度 檔案路徑
    //set first column width
    ui->tracksPage->setColumnWidth(0,200);
    ui->tracksPage->setColumnWidth(2,500);
    QStringList colTitle;
    colTitle<<QStringLiteral("曲名")<<QStringLiteral("檔案大小")<<QStringLiteral("檔案路徑");
    ui->tracksPage->setHorizontalHeaderLabels(colTitle);
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
    //custom file dialog
    QFileDialog fileview;
    fileview.setFileMode(QFileDialog::Directory);
    fileview.setViewMode(QFileDialog::Detail); //需要看見內容
    QDir dirpath = QFileDialog::getExistingDirectory(this,QStringLiteral("選擇目錄"),"",QFileDialog::ShowDirsOnly);
    if(dirpath.isEmpty())return;//空目錄
    ui->statusbar->showMessage(QStringLiteral("掃描目錄: ")+dirpath.absolutePath());

    QDir dir(dirpath);
    QStringList filters;//過濾條件
    filters<<"*.mp3";
    //讀入檔案
    QStringList fileList = dir.entryList(filters,QDir::Files);
    qDebug()<<"reading filelist size: "<<fileList.size();//debug告知讀取筆數
    qDebug()<<"existingCount: "<<existingCount;
    //設定歌單
    ui->tracksPage->setRowCount(existingCount+fileList.size());//有幾筆設幾列，加上已存在的歌單
    qDebug()<<"setting rowCount+ "<<fileList.size();
    qDebug()<<"rowCount: "<<ui->tracksPage->rowCount();

    for(int i=0;i<fileList.size();i++)
    {
        QFileInfo fileInfo(dirpath.absolutePath()+"/"+fileList.at(i));//絕對路徑
        qDebug()<<"reading file"<<fileInfo.fileName()<<" at filelist:"<<i;
        float filesize = fileInfo.size();
        QString filesizeMB;filesizeMB.setNum(filesize/(1024*1024),'f',2);//大小轉換至MB
        //從stringlist取得檔案資訊
        QTableWidgetItem *trackname = new QTableWidgetItem(fileInfo.fileName());
        QTableWidgetItem *size = new QTableWidgetItem(filesizeMB+"MB");
        QTableWidgetItem *trackPath = new QTableWidgetItem(fileInfo.absoluteFilePath());
        int row = existingCount+i;
        ui->tracksPage->setItem(row,0,trackname);
        ui->tracksPage->setItem(row,1,size);
        ui->tracksPage->setItem(row,2,trackPath);
        qDebug()<<"inserted row: "<<row<<"with item:"<<fileInfo.fileName();
        ui->tracksPage->resizeRowsToContents(); //自動調整列長度
    }
    existingCount+=fileList.size();//更新已存在數量
    qDebug()<<"existing count: "<<existingCount;
    //檢查table有沒有row重複
       for(int i=0;i<ui->tracksPage->rowCount();i++)
        {
        for(int j=i+1;j<ui->tracksPage->rowCount();j++){
           if(ui->tracksPage->item(i,2)->text()==ui->tracksPage->item(j,2)->text()){ //如果檔案路徑重複
                ui->tracksPage->removeRow(j);
                existingCount--;
                QString errmsg = "detected duplicate at row: "+ QString::number(j+1)+", removed row "+QString::number(j+1);
                ui->statusbar->showMessage(errmsg);
                qDebug()<<errmsg;
                qDebug()<<"existing count: "<<existingCount;
                ui->InfoLabel->setText(errmsg);
                }
            }
        }


    //預備第一首
    ui->tracksPage->selectColumn(0);
    qDebug()<<fileList;
    audioOutput->setVolume(0.2);
    qDebug()<<"volume:"<<audioOutput->volume();
}


void mp3Player::apiTest(QString fileName) {
    ui->statusbar->clearMessage();
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

    QFile lyricsFile,lyricsHtml;; //目前選擇兩種都讀
    lyricsFile.setFileName(LYRFILE);
    lyricsHtml.setFileName(LYRHTML);
    processor->processAudioFile(fileName); //處理音檔
    //成功獲取線上歌詞
    //從檔案讀取歌詞頁

    if(lyricsFile.open(QIODevice::ReadOnly|QIODevice::Text)&&lyricsHtml.open(QIODevice::ReadOnly))
    {   qDebug()<<"lyrics HTML file opened"<< LYRHTML;
        QTextStream in(&lyricsFile);
        QTextStream inHtml(&lyricsHtml);
        ui->lyrBrowser->setHtml(inHtml.readAll()); //優先選擇HTML
        qDebug()<<"lyrics page set";
        QString statusUpdate = QStringLiteral("歌詞載入成功，顯示本地HTML  ")+LYRHTML;
        ui->statusbar->showMessage(statusUpdate);
        lyricsFile.close();lyricsHtml.close();
    }
    else qDebug()<<"Failed to open lyr file";


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
    //取得線上歌詞
    processor = new AudioProcessor(); //建立processor
    QString trackPath = ui->tracksPage->item(ui->tracksPage->currentRow(),2)->text();
    apiTest(trackPath); //測試API並輸出至debug
    ui->lyrBrowser->reload();
}

void mp3Player::on_btnPlayTrack_clicked()
{
    QString trackPath = ui->tracksPage->item(ui->tracksPage->currentRow(),2)->text();
    if(currentRow != ui->tracksPage->currentRow()) {
        getMetaData();//如果換歌，重新取得meta
        qDebug()<<"Detected Change currentRow:"<<currentRow<<"-->"<<ui->tracksPage->currentRow()<<" reload meta data";
        apiTest(trackPath); //重新獲取
        ui->lyrBrowser->reload();
    }
    //if not playing, play track
    if(player->playbackState()==QMediaPlayer::StoppedState)
    {
        currentRow = ui->tracksPage->currentRow(); //紀錄目前位置判斷有沒有換首
        qDebug()<<"currentRow:"<<currentRow;
        player->play();
        //console output
        qDebug() << "Playing"<<ui->tracksPage->item(ui->tracksPage->currentRow(),0)->text();
        qDebug()<<"track duration:"<<player->duration();
        qDebug()<<"volume:"<<audioOutput->volume();
    }
    else if(player->playbackState()==QMediaPlayer::PausedState)//if paused, resume
    {
        player->play();
        qDebug() << "Resumed";
    }
    else if(player->playbackState()==QMediaPlayer::PlayingState)
    {
    //pause button function
        player->pause();
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





void mp3Player::on_tracksPage_cellDoubleClicked(int row, int column)
{
    ui->tracksPage->setCurrentCell(row,0);
    getMetaData();
    player->play();
}
