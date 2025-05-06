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
