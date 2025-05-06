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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


private:
    Ui::MainWindow *ui;
    Cylinder * cylinder;
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
