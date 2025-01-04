#include "mp3player.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mp3Player w;
    w.show();
    return a.exec();
}
