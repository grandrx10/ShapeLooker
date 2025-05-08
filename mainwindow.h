#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "cylinder.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include "drawingboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow * getUi();
    int getSceneWidth();


private:
    Ui::MainWindow *ui;
    int sceneWidth = 2000;
    int sceneHeight = 2000;

    Cylinder * cylinder;
    DrawingBoard * drawingBoard;
    QList<QString> spaceDropdown;
    QList<QString> unitsDropdown;
    QList<QString> modelDropdown;

    void onSaveClicked();
    void onLoadClicked();
    void onComboModelChanged(int index);
    void onComboSpaceChanged(int index);
    void onParam1Changed(const QString &arg1);
    void onParam2Changed(const QString &arg2);


};

#endif // MAINWINDOW_H
