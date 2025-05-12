#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPointF>
#include <QDoubleValidator>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // qss setup
    QFile styleFile(":/styles/style.qss");  // ":" indicates resource path
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);  // Apply to entire app
        styleFile.close();
    } else {
        qWarning() << "Could not open stylesheet file";
    }

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
    scene->setSceneRect(-sceneWidth / 2, -sceneHeight / 2, sceneWidth, sceneHeight);
    ui->graphicsView->setScene(scene);
    drawingBoard = new DrawingBoard(nullptr, this);
    cylinder = new Cylinder();
    drawingBoard->addItem(cylinder);
    scene->addItem(drawingBoard);

    // Adding the connections
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveClicked);
    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::onLoadClicked);

    connect(ui->comboModel, &QComboBox::currentIndexChanged, this, &MainWindow::onComboModelChanged);
    connect(ui->comboSpace, &QComboBox::currentIndexChanged, this, &MainWindow::onComboSpaceChanged);
    connect(ui->leP1, &QLineEdit::textChanged, this, &MainWindow::onParam1Changed);
    connect(ui->leP2, &QLineEdit::textChanged, this, &MainWindow::onParam2Changed);

    // Adding validators
    ui->leP1->setValidator(new QDoubleValidator(0.000001, 1e9, 6, this));
    ui->leP2->setValidator(new QDoubleValidator(0.000001, 1e9, 6, this));
    // Tool buttons
    connect(ui->actionLineTool, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Line");
    });
    connect(ui->actionRectTool, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Rect");
    });
    connect(ui->actionCornerCircleTool, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Corner Circle");
    });
    connect(ui->actionCenterCircleTool, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Center Circle");
    });
    connect(ui->actionEraseFull, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Full Eraser");
    });
    connect(ui->actionErasePartial, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Partial Eraser");
    });
    connect(ui->actionNoTool, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("None");
    });
    connect(ui->actionPenTool, &QAction::triggered, this, [this]() {
        drawingBoard->setTool("Pen");
    });
    connect(ui->drawStyleButton, &QPushButton::clicked, this, [this]() {
        ui->drawStyleButton->setText("Style: " + drawingBoard->swapDrawStyle());
    });
    connect(ui->actionPanTool, &QAction::triggered, this, [this](){
        drawingBoard->setTool("Pan");
    });

    // quick access buttons
    auto connectToolButton = [this](QAbstractButton* button, const QString& toolName) {
        button->setCheckable(true);
        connect(button, &QAbstractButton::clicked, this, [this, toolName]() {
            drawingBoard->setTool(toolName);
        });
    };
    connectToolButton(ui->toolSelect, "None");
    connectToolButton(ui->toolPan, "Pan");
    connectToolButton(ui->toolErase, "Full Eraser");
    connectToolButton(ui->toolPartialErase, "Partial Eraser");

    connectToolButton(ui->toolLine, "Line");
    connectToolButton(ui->toolRect, "Rect");
    connectToolButton(ui->toolCircleCenter, "Center Circle");
    connectToolButton(ui->toolCircleCorner, "Corner Circle");
    connectToolButton(ui->toolPen, "Pen");

    QButtonGroup* toolButtonGroup = new QButtonGroup(this);
    toolButtonGroup->setExclusive(true);  // Critical: Only one button can be checked

    // Add all tool buttons to the group
    toolButtonGroup->addButton(ui->toolSelect);
    toolButtonGroup->addButton(ui->toolPan);
    toolButtonGroup->addButton(ui->toolErase);
    toolButtonGroup->addButton(ui->toolPartialErase);
    toolButtonGroup->addButton(ui->toolLine);
    toolButtonGroup->addButton(ui->toolRect);
    toolButtonGroup->addButton(ui->toolCircleCenter);
    toolButtonGroup->addButton(ui->toolCircleCorner);
    toolButtonGroup->addButton(ui->toolPen);

    // In your MainWindow constructor:
    ui->graphicsView->setFocus();  // Make sure the view has focus
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);  // Accept keyboard focus

}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::getUi() {
    return ui;
}

int MainWindow::getSceneWidth(){
    return sceneWidth;
}

void MainWindow::onSaveClicked()
{
    QJsonObject jsonData;

    jsonData["comboModel"] = ui->comboModel->currentText();
    jsonData["comboSpace"] = ui->comboSpace->currentText();
    jsonData["comboUnits"] = ui->comboUnits->currentText();

    jsonData["leParam1"] = ui->leP1->text();
    jsonData["leParam2"] = ui->leP2->text();

    jsonData["drawings"] = drawingBoard->saveItems();

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


void MainWindow::onLoadClicked()
{
    QString loadPath = QFileDialog::getOpenFileName(
        this,
        "Load Configuration File",
        QDir::homePath(),
        "JSON Files (*.json)"
        );

    if (loadPath.isEmpty()) return;

    // Read file
    QFile loadFile(loadPath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }

    // Parse JSON
    QByteArray jsonData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(jsonData));
    QJsonObject jsonObj = loadDoc.object();

    // Restore combobox values
    if (jsonObj.contains("drawings")) {
        drawingBoard->loadItems(jsonObj["drawings"].toArray());
    }

    if (jsonObj.contains("comboModel"))
        ui->comboModel->setCurrentText(jsonObj["comboModel"].toString());

    if (jsonObj.contains("comboSpace"))
        ui->comboSpace->setCurrentText(jsonObj["comboSpace"].toString());

    if (jsonObj.contains("comboUnits"))
        ui->comboUnits->setCurrentText(jsonObj["comboUnits"].toString());

    // Restore line edits
    if (jsonObj.contains("leParam1"))
        ui->leP1->setText(jsonObj["leParam1"].toString());

    if (jsonObj.contains("leParam2"))
        ui->leP2->setText(jsonObj["leParam2"].toString());


    loadFile.close();
    statusBar()->showMessage("Configuration loaded", 3000);
}


void MainWindow::onComboModelChanged(int index)
{
    Q_UNUSED(index);
    QString type = ui->comboModel->currentText();
    if (cylinder != nullptr) {
        cylinder->setType(type);
    }

    if (type == "U") {
        ui->labelP1->setText("Radius");
        ui->labelP2->setText("Height");
        ui->comboSpace->setCurrentText("3D");
    } else if (type == "B") {
        ui->labelP1->setText("Radius");
        ui->labelP2->setText("Width");
        ui->comboSpace->setCurrentText("3D");
    } else {
        ui->labelP1->setText("Radius");
        ui->labelP2->setText("Width");
        ui->comboSpace->setCurrentText("2D");
    }
}


void MainWindow::onComboSpaceChanged(int index)
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

    return val;
}

void MainWindow::onParam1Changed(const QString &arg1)
{
    double value = verifyDouble(arg1);

    if (value == -1) {
        return;
    }

    if (cylinder != nullptr) {
        cylinder->setRadius(value);
    }

}


void MainWindow::onParam2Changed(const QString &arg1)
{
    double value = verifyDouble(arg1);

    if (value == -1) {
        return;
    }

    if (cylinder != nullptr) {
        cylinder->setHeight(value);
    }
}

