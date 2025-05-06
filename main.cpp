#include "dialog.h"

#include <QApplication>

const QColor BLUE = QColor(72, 202,228);
const QColor WHITE = QColor("#FAF6E9");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    // pallet intialization
    QPalette palette;
    // label text
    palette.setColor(QPalette::WindowText, Qt::black);
    // window background
    palette.setColor(QPalette::Window, WHITE);
    // dropdown
    palette.setColor(QPalette::Base, BLUE);
    palette.setColor(QPalette::Text, Qt::black);
    // button
    palette.setColor(QPalette::Button, BLUE);
    palette.setColor(QPalette::ButtonText, Qt::black);

    w.setPalette(palette);  // Applies to ALL widgets

    w.show();
    return a.exec();
}
