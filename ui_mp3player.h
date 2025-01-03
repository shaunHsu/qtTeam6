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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mp3Player
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Tab1;
    QTableWidget *tracksPage;
    QWidget *Tab2;
    QTableWidget *playlistPage;
    QLabel *InfoLabel;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *btnPlayTrack;
    QPushButton *btnNext;
    QPushButton *btnStop;
    QPushButton *btnPrev;
    QHBoxLayout *horizontalLayout;
    QLabel *lblVolume;
    QSlider *horizontalSlider;
    QSlider *trackPosSlider;
    QLabel *TrackTitle;
    QLabel *TrackDuration;
    QPushButton *btnScanDir;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mp3Player)
    {
        if (mp3Player->objectName().isEmpty())
            mp3Player->setObjectName("mp3Player");
        mp3Player->resize(800, 600);
        centralwidget = new QWidget(mp3Player);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 10, 781, 401));
        Tab1 = new QWidget();
        Tab1->setObjectName("Tab1");
        tracksPage = new QTableWidget(Tab1);
        tracksPage->setObjectName("tracksPage");
        tracksPage->setGeometry(QRect(0, 0, 781, 381));
        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName("Tab2");
        playlistPage = new QTableWidget(Tab2);
        playlistPage->setObjectName("playlistPage");
        playlistPage->setGeometry(QRect(0, 0, 781, 381));
        tabWidget->addTab(Tab2, QString());
        InfoLabel = new QLabel(centralwidget);
        InfoLabel->setObjectName("InfoLabel");
        InfoLabel->setGeometry(QRect(9, 550, 781, 20));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 410, 771, 141));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        btnPlayTrack = new QPushButton(widget);
        btnPlayTrack->setObjectName("btnPlayTrack");

        gridLayout->addWidget(btnPlayTrack, 0, 0, 1, 1);

        btnNext = new QPushButton(widget);
        btnNext->setObjectName("btnNext");

        gridLayout->addWidget(btnNext, 0, 3, 1, 1);

        btnStop = new QPushButton(widget);
        btnStop->setObjectName("btnStop");

        gridLayout->addWidget(btnStop, 0, 1, 1, 1);

        btnPrev = new QPushButton(widget);
        btnPrev->setObjectName("btnPrev");

        gridLayout->addWidget(btnPrev, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lblVolume = new QLabel(widget);
        lblVolume->setObjectName("lblVolume");

        horizontalLayout->addWidget(lblVolume);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setSliderPosition(20);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        gridLayout_2->addLayout(horizontalLayout, 1, 3, 1, 1);

        trackPosSlider = new QSlider(widget);
        trackPosSlider->setObjectName("trackPosSlider");
        trackPosSlider->setOrientation(Qt::Orientation::Horizontal);

        gridLayout_2->addWidget(trackPosSlider, 1, 0, 1, 1);

        TrackTitle = new QLabel(widget);
        TrackTitle->setObjectName("TrackTitle");

        gridLayout_2->addWidget(TrackTitle, 0, 0, 1, 2);

        TrackDuration = new QLabel(widget);
        TrackDuration->setObjectName("TrackDuration");

        gridLayout_2->addWidget(TrackDuration, 1, 1, 1, 1);

        btnScanDir = new QPushButton(widget);
        btnScanDir->setObjectName("btnScanDir");

        gridLayout_2->addWidget(btnScanDir, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 2, 1, 1);

        mp3Player->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mp3Player);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        mp3Player->setMenuBar(menubar);
        statusbar = new QStatusBar(mp3Player);
        statusbar->setObjectName("statusbar");
        mp3Player->setStatusBar(statusbar);

        retranslateUi(mp3Player);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(mp3Player);
    } // setupUi

    void retranslateUi(QMainWindow *mp3Player)
    {
        mp3Player->setWindowTitle(QCoreApplication::translate("mp3Player", "mp3Player", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QCoreApplication::translate("mp3Player", "Tracks", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QCoreApplication::translate("mp3Player", "Now Playing", nullptr));
        InfoLabel->setText(QString());
        btnPlayTrack->setText(QCoreApplication::translate("mp3Player", "Play/Pause", nullptr));
        btnNext->setText(QCoreApplication::translate("mp3Player", "Next", nullptr));
        btnStop->setText(QCoreApplication::translate("mp3Player", "Stop", nullptr));
        btnPrev->setText(QCoreApplication::translate("mp3Player", "Prev", nullptr));
        lblVolume->setText(QCoreApplication::translate("mp3Player", "Volume", nullptr));
        TrackTitle->setText(QString());
        TrackDuration->setText(QString());
        btnScanDir->setText(QCoreApplication::translate("mp3Player", "Scan..", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mp3Player: public Ui_mp3Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MP3PLAYER_H
