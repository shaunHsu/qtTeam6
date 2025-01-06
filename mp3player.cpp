#include "mp3player.h"
#include "ui_mp3player.h"
#include <QAudioDevice>
#include <QDebug>
#include <QStatusBar>
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


void mp3Player::getMetaData()
{
    if (ui->tracksPage->currentRow() < 0) return;

    // 獲取當前正在播放的歌曲路徑
    QString currentTrackPath = ui->tracksPage->item(ui->tracksPage->currentRow(), 2)->text();

    // 設定播放器的來源
    player->setSource(QUrl::fromLocalFile(currentTrackPath));

    // 將路徑傳遞到 test 函式
    test(currentTrackPath);
    test1(currentTrackPath);

    // 連接 metadataChanged 信號以處理元數據
    connect(player, &QMediaPlayer::metaDataChanged, this, [this]() {
        QMediaMetaData meta = player->metaData();
        QString title = meta.stringValue(QMediaMetaData::Title);
        QString duration = QTime(0, 0).addMSecs(static_cast<int>(player->duration())).toString("mm:ss");
        QTime t;
        t.setHMS(duration.split(":").at(0).toInt(), duration.split(":").at(1).toInt(), 0);
        ui->TrackDuration->setText(duration);
        ui->TrackTitle->setText(title);
    });
}


void mp3Player::on_btnPlayTrack_clicked()
{
    if(currentRow != ui->tracksPage->currentRow()) {
        getMetaData();//如果換歌，重新取得meta
        qDebug()<<"Detected Change currentRow:"<<currentRow<<"-->"<<ui->tracksPage->currentRow()<<" reload meta data";
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

#include "apiTest.cpp"

void mp3Player::test(QString mus)//中文
{
    // apiTest();
    /// 假设 musicpage 是 QTextEdit 类型的对象
    if (ui->musicpage) {
        QString fileName = mus;

        AudioProcessor *processor = new AudioProcessor();
        ShazamRequest *request = new ShazamRequest();
        GetLyrics *lyrics = new GetLyrics();

        QObject::connect(processor, &AudioProcessor::processingFinished,
                         [=]() { request->sendRequest(processor->audioData); });
        QObject::connect(request, &ShazamRequest::finished, [=]() {
            QStringList infos = request->getInfo(request->response);
            if (!infos.isEmpty()) {
                QString songName = infos.at(0);
                QString songLyrics = lyrics->getLyrics(songName);

                QString formattedLyrics;
                for (int i = 0; i < songLyrics.size(); ++i) {
                    QChar ch = songLyrics.at(i);

                    if (ch.unicode() >= 0x4E00 && ch.unicode() <= 0x9FFF) {
                        // 中文字符范围
                        if (ch.isSpace()) {
                            formattedLyrics += "<br>";  // 中文空格换行
                        } else {
                            formattedLyrics += ch;  // 其他字符直接追加
                        }
                    } else {
                        // 非中文字符直接追加
                        if (ch.isSpace()) {
                            formattedLyrics += "<br>";  // 非中文空格换行
                        } else {
                            formattedLyrics += ch;  // 其他字符直接追加
                        }
                    }
                }

                // 在歌词前后加上 <font> 标签设置字体大小
                formattedLyrics = "<div style='text-align: center;'><font size='5'>" + formattedLyrics + "</font></div>";

                // 确保 musicpage 可以显示 HTML 格式内容
                ui->musicpage->setAcceptRichText(true);  // 支持富文本
                ui->musicpage->setHtml(formattedLyrics); // 用 HTML 格式显示歌词

                qDebug() << "Set musicpage to display lyrics of the song (Chinese): " << formattedLyrics;
            } else {
                qDebug() << "No song information retrieved.";
            }
        });

        processor->processAudioFile(fileName);
    } else {
        qDebug() << "musicpage is null";
    }
}

void mp3Player::test1(QString mus)//英文
{
    // apiTest();
    /// 假设 musicpageEn 是 QTextEdit 类型的对象
    if (ui->musicpageEn) {
        QString fileName = mus;

        AudioProcessor *processor = new AudioProcessor();
        ShazamRequest *request = new ShazamRequest();
        GetLyrics *lyrics = new GetLyrics();

        QObject::connect(processor, &AudioProcessor::processingFinished,
                         [=]() { request->sendRequest(processor->audioData); });
        QObject::connect(request, &ShazamRequest::finished, [=]() {
            QStringList infos = request->getInfo(request->response);
            if (!infos.isEmpty()) {
                QString songName = infos.at(0);
                QString songLyrics = lyrics->getLyrics(songName);

                QString formattedLyrics;
                bool lastCharWasSpace = true; // 标记前一个字符是否为空格
                bool lastCharWasNewline = false; // 标记前一个字符是否是换行符

                for (int i = 0; i < songLyrics.size(); ++i) {
                    QChar ch = songLyrics.at(i);

                    if (ch.isSpace()) {
                        // 空格
                        formattedLyrics += " ";
                        lastCharWasSpace = true;
                        lastCharWasNewline = false;
                    } else if (ch.isUpper()) {
                        // 英文字母大写
                        if (!lastCharWasSpace && !lastCharWasNewline) {
                            formattedLyrics += "<br>"; // 换行，但仅在前一个字符不是空格或换行时
                        }
                        formattedLyrics += ch;
                        lastCharWasSpace = false;
                        lastCharWasNewline = false;
                    } else {
                        // 其他字符直接追加
                        formattedLyrics += ch;
                        lastCharWasSpace = false;
                        lastCharWasNewline = false;
                    }
                }

                // 在歌词前后加上 <font> 标签设置字体大小
                formattedLyrics = "<div style='text-align: center;'><font size='5'>" + formattedLyrics + "</font></div>";

                // 确保 musicpageEn 可以显示 HTML 格式内容
                ui->musicpageEn->setAcceptRichText(true);  // 支持富文本
                ui->musicpageEn->setHtml(formattedLyrics); // 用 HTML 格式显示歌词

                qDebug() << "Set musicpageEn to display lyrics of the song (English): " << formattedLyrics;
            } else {
                qDebug() << "No song information retrieved.";
            }
        });

        processor->processAudioFile(fileName);
    } else {
        qDebug() << "musicpageEn is null";
    }
}

