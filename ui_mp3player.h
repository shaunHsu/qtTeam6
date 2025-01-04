/********************************************************************************
** Form generated from reading UI file 'mp3player.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MP3PLAYER_H
#define UI_MP3PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mp3Player
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *btnPlayTrack;
    QPushButton *btnNext;
    QPushButton *btnStop;
    QPushButton *btnPrev;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *lblVolume;
    QSlider *horizontalSlider;
    QTabWidget *tabWidget;
    QWidget *Tab1;
    QTableWidget *tracksPage;
    QWidget *Tab2;
    QTableWidget *playlistPage;
    QWidget *tab;
    QTableWidget *musicpage;
    QTextEdit *lyricsDisplay;
    QPushButton *btnScanDir;
    QLabel *TrackDuration;
    QLabel *TrackTitle;
    QSlider *trackPosSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mp3Player)
    {
        if (mp3Player->objectName().isEmpty())
            mp3Player->setObjectName("mp3Player");
        mp3Player->resize(800, 600);
        centralwidget = new QWidget(mp3Player);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(100, 510, 631, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btnPlayTrack = new QPushButton(gridLayoutWidget);
        btnPlayTrack->setObjectName("btnPlayTrack");

        gridLayout->addWidget(btnPlayTrack, 0, 0, 1, 1);

        btnNext = new QPushButton(gridLayoutWidget);
        btnNext->setObjectName("btnNext");

        gridLayout->addWidget(btnNext, 0, 3, 1, 1);

        btnStop = new QPushButton(gridLayoutWidget);
        btnStop->setObjectName("btnStop");

        gridLayout->addWidget(btnStop, 0, 1, 1, 1);

        btnPrev = new QPushButton(gridLayoutWidget);
        btnPrev->setObjectName("btnPrev");

        gridLayout->addWidget(btnPrev, 0, 2, 1, 1);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(530, 440, 211, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblVolume = new QLabel(horizontalLayoutWidget);
        lblVolume->setObjectName("lblVolume");

        horizontalLayout->addWidget(lblVolume);

        horizontalSlider = new QSlider(horizontalLayoutWidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setSliderPosition(20);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(40, 0, 751, 411));
        Tab1 = new QWidget();
        Tab1->setObjectName("Tab1");
        tracksPage = new QTableWidget(Tab1);
        tracksPage->setObjectName("tracksPage");
        tracksPage->setGeometry(QRect(0, 0, 701, 391));
        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName("Tab2");
        playlistPage = new QTableWidget(Tab2);
        playlistPage->setObjectName("playlistPage");
        playlistPage->setGeometry(QRect(0, 0, 701, 381));
        tabWidget->addTab(Tab2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        musicpage = new QTableWidget(tab);
        musicpage->setObjectName("musicpage");
        musicpage->setGeometry(QRect(0, 0, 691, 381));
        lyricsDisplay = new QTextEdit(tab);
        lyricsDisplay->setObjectName("lyricsDisplay");
        lyricsDisplay->setGeometry(QRect(80, 0, 521, 381));
        tabWidget->addTab(tab, QString());
        btnScanDir = new QPushButton(centralwidget);
        btnScanDir->setObjectName("btnScanDir");
        btnScanDir->setGeometry(QRect(690, 410, 97, 28));
        TrackDuration = new QLabel(centralwidget);
        TrackDuration->setObjectName("TrackDuration");
        TrackDuration->setGeometry(QRect(430, 450, 91, 21));
        TrackTitle = new QLabel(centralwidget);
        TrackTitle->setObjectName("TrackTitle");
        TrackTitle->setGeometry(QRect(90, 420, 431, 20));
        trackPosSlider = new QSlider(centralwidget);
        trackPosSlider->setObjectName("trackPosSlider");
        trackPosSlider->setGeometry(QRect(100, 450, 321, 21));
        trackPosSlider->setOrientation(Qt::Orientation::Horizontal);
        mp3Player->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mp3Player);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        mp3Player->setMenuBar(menubar);
        statusbar = new QStatusBar(mp3Player);
        statusbar->setObjectName("statusbar");
        mp3Player->setStatusBar(statusbar);

        retranslateUi(mp3Player);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(mp3Player);
    } // setupUi

    void retranslateUi(QMainWindow *mp3Player)
    {
        mp3Player->setWindowTitle(QCoreApplication::translate("mp3Player", "mp3Player", nullptr));
        btnPlayTrack->setText(QCoreApplication::translate("mp3Player", "Play/Pause", nullptr));
        btnNext->setText(QCoreApplication::translate("mp3Player", "Next", nullptr));
        btnStop->setText(QCoreApplication::translate("mp3Player", "Stop", nullptr));
        btnPrev->setText(QCoreApplication::translate("mp3Player", "Prev", nullptr));
        lblVolume->setText(QCoreApplication::translate("mp3Player", "Volume", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QCoreApplication::translate("mp3Player", "Tracks", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QCoreApplication::translate("mp3Player", "Now Playing", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("mp3Player", "musicpage", nullptr));
        btnScanDir->setText(QCoreApplication::translate("mp3Player", "Scan..", nullptr));
        TrackDuration->setText(QString());
        TrackTitle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mp3Player: public Ui_mp3Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MP3PLAYER_H
