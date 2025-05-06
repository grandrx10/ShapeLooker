/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboSpace;
    QLabel *label_2;
    QComboBox *comboUnits;
    QLabel *label_3;
    QComboBox *comboModel;
    QLabel *labelP1;
    QLineEdit *leP1;
    QLabel *labelP2;
    QLineEdit *leP2;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QGraphicsView *graphicsView;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonSave;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(839, 574);
        gridLayout_2 = new QGridLayout(Dialog);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(Dialog);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboSpace = new QComboBox(Dialog);
        comboSpace->setObjectName("comboSpace");
        comboSpace->setFont(font);

        gridLayout->addWidget(comboSpace, 0, 1, 1, 1);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        comboUnits = new QComboBox(Dialog);
        comboUnits->setObjectName("comboUnits");
        comboUnits->setFont(font);

        gridLayout->addWidget(comboUnits, 1, 1, 1, 1);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        comboModel = new QComboBox(Dialog);
        comboModel->setObjectName("comboModel");
        comboModel->setFont(font);

        gridLayout->addWidget(comboModel, 2, 1, 1, 1);

        labelP1 = new QLabel(Dialog);
        labelP1->setObjectName("labelP1");
        labelP1->setFont(font);

        gridLayout->addWidget(labelP1, 3, 0, 1, 1);

        leP1 = new QLineEdit(Dialog);
        leP1->setObjectName("leP1");
        leP1->setFont(font);

        gridLayout->addWidget(leP1, 3, 1, 1, 1);

        labelP2 = new QLabel(Dialog);
        labelP2->setObjectName("labelP2");
        labelP2->setFont(font);

        gridLayout->addWidget(labelP2, 4, 0, 1, 1);

        leP2 = new QLineEdit(Dialog);
        leP2->setObjectName("leP2");
        leP2->setFont(font);

        gridLayout->addWidget(leP2, 4, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        line = new QFrame(Dialog);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_2->addWidget(line, 0, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        label_6 = new QLabel(Dialog);
        label_6->setObjectName("label_6");
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 98, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        graphicsView = new QGraphicsView(Dialog);
        graphicsView->setObjectName("graphicsView");

        gridLayout_3->addWidget(graphicsView, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(1, 3);

        gridLayout_2->addLayout(gridLayout_3, 0, 2, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalSpacer = new QSpacerItem(118, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 0, 1, 1);

        buttonSave = new QPushButton(Dialog);
        buttonSave->setObjectName("buttonSave");
        QPalette palette;
        QBrush brush(QColor(55, 197, 240, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::HighlightedText, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::HighlightedText, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::HighlightedText, brush1);
        buttonSave->setPalette(palette);
        buttonSave->setFont(font);

        gridLayout_4->addWidget(buttonSave, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(118, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout_4, 1, 0, 1, 3);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Space", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Units", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Model", nullptr));
        labelP1->setText(QCoreApplication::translate("Dialog", "Radius", nullptr));
        labelP2->setText(QCoreApplication::translate("Dialog", "Height", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "Visual Representation", nullptr));
        buttonSave->setText(QCoreApplication::translate("Dialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
