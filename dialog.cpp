#include "dialog.h"
#include "./ui_dialog.h"
#include "cylinder.h"


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // comboModel
    modelDropdown.append(QString("U"));
    modelDropdown.append(QString("B"));
    modelDropdown.append(QString("T"));
    ui->comboModel->addItems(modelDropdown);

    // comboSpace
    spaceDropdown.append(QString("3D"));
    spaceDropdown.append(QString("2D"));
    ui->comboSpace->addItems(spaceDropdown);

    // comboUnits
    unitsDropdown.append(QString("m"));
    unitsDropdown.append(QString("mm"));
    ui->comboUnits->addItems(unitsDropdown);

    // set default params
    ui->leP1->setText("50");
    ui->leP2->setText("80");

    // visual model
    QGraphicsScene * scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    cylinder = new Cylinder();
    scene->addItem(cylinder);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_buttonSave_clicked()
{
    QJsonObject jsonData;

    jsonData["comboModel"] = ui->comboModel->currentText();
    jsonData["comboSpace"] = ui->comboSpace->currentText();
    jsonData["comboUnits"] = ui->comboUnits->currentText();

    jsonData["leParam1"] = ui->leP1->text();
    jsonData["leParam2"] = ui->leP2->text();

    QJsonDocument saveDoc(jsonData);
    QString savePath = QFileDialog::getSaveFileName(
        this,
        "Save Configuration File",
        QDir::homePath(),
        "JSON Files (*.json)"
        );

    if (!savePath.isEmpty())
    {
        QFile saveFile(savePath);
        if (saveFile.open(QIODevice::WriteOnly))
        {
            saveFile.write(saveDoc.toJson());
            saveFile.close();
        }
        else
        {
            qInfo() << "Error: File could not be opened.\n";
        }
    }
}


void Dialog::on_comboModel_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString type = ui->comboModel->currentText();
    if (cylinder != nullptr) {
        cylinder->setType(type);
    }

    if (type == "U") {
        ui->labelP1->setText("Radius");
        ui->labelP2->setText("Height");
    } else if (type == "B" || type == "T") {
        ui->labelP1->setText("Radius");
        ui->labelP2->setText("Width");
    }
}


void Dialog::on_comboSpace_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    QString space = ui->comboSpace->currentText();
    if (space == "3D") {
        ui->comboModel->setCurrentText("U"); // default 3d model
    }
    else { // 2D
        ui->comboModel->setCurrentText("T");
    }
}

double verifyDouble(QString arg) {
    bool isNumber;
    double val = arg.toDouble(&isNumber);

    if (!isNumber) {
        return -1;
    }

    if (val <= 0) {
        return -1;
    }

    return val;
}

void Dialog::on_leP1_textChanged(const QString &arg1)
{
    double value = verifyDouble(arg1);

    if (value == -1) {
        return;
    }

    if (cylinder != nullptr) {
        cylinder->setRadius(value);
    }

}


void Dialog::on_leP2_textChanged(const QString &arg1)
{
    double value = verifyDouble(arg1);

    if (value == -1) {
        return;
    }

    if (cylinder != nullptr) {
        cylinder->setHeight(value);
    }
}

