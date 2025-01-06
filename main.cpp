#include <QApplication>

#include "apiTest.cpp"
#include "mp3player.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

     apiTest();

    mp3Player w;
    w.show();
    return a.exec();
}
