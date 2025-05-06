#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QList>
#include "cylinder.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_buttonSave_clicked();

    void on_comboModel_currentIndexChanged(int index);

    void on_comboSpace_currentIndexChanged(int index);

    void on_leP1_textChanged(const QString &arg1);

    void on_leP2_textChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
    Cylinder * cylinder;
    QList<QString> spaceDropdown;
    QList<QString> unitsDropdown;
    QList<QString> modelDropdown;
};
#endif // DIALOG_H
