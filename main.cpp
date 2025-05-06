#include "mainwindow.h"

#include <QApplication>

const QColor BLUE = QColor(72, 202,228);
const QColor WHITE = QColor("#FAF6E9");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
