/********************************************************************************
** Form generated from reading UI file 'mp3player.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mp3Player
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QGridLayout *mainlay;
    QGridLayout *playerctrl;
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
    QTabWidget *tabWidget;
    QWidget *Tab1;
    QGridLayout *gridLayout_2;
    QTableWidget *tracksPage;
    QWidget *Tab2;
    QGridLayout *gridLayout_5;
    QTextBrowser *lyrBrowser;
    QLabel *InfoLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mp3Player)
    {
        if (mp3Player->objectName().isEmpty())
            mp3Player->setObjectName("mp3Player");
        mp3Player->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mp3Player->sizePolicy().hasHeightForWidth());
        mp3Player->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(mp3Player);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        mainlay = new QGridLayout();
        mainlay->setObjectName("mainlay");
        mainlay->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        playerctrl = new QGridLayout();
        playerctrl->setObjectName("playerctrl");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        btnPlayTrack = new QPushButton(centralwidget);
        btnPlayTrack->setObjectName("btnPlayTrack");

        gridLayout->addWidget(btnPlayTrack, 0, 0, 1, 1);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName("btnNext");

        gridLayout->addWidget(btnNext, 0, 3, 1, 1);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");

        gridLayout->addWidget(btnStop, 0, 1, 1, 1);

        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName("btnPrev");

        gridLayout->addWidget(btnPrev, 0, 2, 1, 1);


        playerctrl->addLayout(gridLayout, 2, 0, 1, 4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lblVolume = new QLabel(centralwidget);
        lblVolume->setObjectName("lblVolume");

        horizontalLayout->addWidget(lblVolume);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setSliderPosition(20);
        horizontalSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        playerctrl->addLayout(horizontalLayout, 1, 3, 1, 1);

        trackPosSlider = new QSlider(centralwidget);
        trackPosSlider->setObjectName("trackPosSlider");
        trackPosSlider->setOrientation(Qt::Orientation::Horizontal);

        playerctrl->addWidget(trackPosSlider, 1, 0, 1, 1);

        TrackTitle = new QLabel(centralwidget);
        TrackTitle->setObjectName("TrackTitle");

        playerctrl->addWidget(TrackTitle, 0, 0, 1, 2);

        TrackDuration = new QLabel(centralwidget);
        TrackDuration->setObjectName("TrackDuration");

        playerctrl->addWidget(TrackDuration, 1, 1, 1, 1);

        btnScanDir = new QPushButton(centralwidget);
        btnScanDir->setObjectName("btnScanDir");

        playerctrl->addWidget(btnScanDir, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        playerctrl->addItem(horizontalSpacer, 1, 2, 1, 1);


        mainlay->addLayout(playerctrl, 1, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        Tab1 = new QWidget();
        Tab1->setObjectName("Tab1");
        sizePolicy.setHeightForWidth(Tab1->sizePolicy().hasHeightForWidth());
        Tab1->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(Tab1);
        gridLayout_2->setObjectName("gridLayout_2");
        tracksPage = new QTableWidget(Tab1);
        tracksPage->setObjectName("tracksPage");
        sizePolicy.setHeightForWidth(tracksPage->sizePolicy().hasHeightForWidth());
        tracksPage->setSizePolicy(sizePolicy);
        tracksPage->setMaximumSize(QSize(20000, 20000));

        gridLayout_2->addWidget(tracksPage, 0, 0, 1, 1);

        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName("Tab2");
        sizePolicy.setHeightForWidth(Tab2->sizePolicy().hasHeightForWidth());
        Tab2->setSizePolicy(sizePolicy);
        gridLayout_5 = new QGridLayout(Tab2);
        gridLayout_5->setObjectName("gridLayout_5");
        lyrBrowser = new QTextBrowser(Tab2);
        lyrBrowser->setObjectName("lyrBrowser");

        gridLayout_5->addWidget(lyrBrowser, 0, 0, 1, 1);

        tabWidget->addTab(Tab2, QString());

        mainlay->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_4->addLayout(mainlay, 0, 0, 1, 1);

        InfoLabel = new QLabel(centralwidget);
        InfoLabel->setObjectName("InfoLabel");

        gridLayout_4->addWidget(InfoLabel, 1, 0, 1, 1);

        mp3Player->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mp3Player);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        mp3Player->setMenuBar(menubar);
        statusbar = new QStatusBar(mp3Player);
        statusbar->setObjectName("statusbar");
        mp3Player->setStatusBar(statusbar);

        retranslateUi(mp3Player);

        tabWidget->setCurrentIndex(1);


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
        TrackTitle->setText(QString());
        TrackDuration->setText(QString());
        btnScanDir->setText(QCoreApplication::translate("mp3Player", "Scan..", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QCoreApplication::translate("mp3Player", "Tracks", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QCoreApplication::translate("mp3Player", "Now Playing", nullptr));
        InfoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mp3Player: public Ui_mp3Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MP3PLAYER_H
