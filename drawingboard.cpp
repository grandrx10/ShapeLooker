#include "drawingboard.h"
#include "DrawableItem.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include "pen.h"
#include <QKeyEvent>
#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

DrawingBoard::DrawingBoard(QGraphicsItem *parent, MainWindow* mainWindow)
    : QGraphicsItem(parent)
{
    this->mainWindow = mainWindow;
    diagramSize = mainWindow->getSceneWidth();

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

}

QRectF DrawingBoard::boundingRect() const
{
    // I want to erase the entire graphicsView
    const qreal largeSize = diagramSize;
    return QRectF(-largeSize, -largeSize, 2*largeSize, 2*largeSize);
}

void DrawingBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    for (int i = 0; i < items.length(); i ++) {
        items[i]->draw(painter);
    }

}

void DrawingBoard::addItem(DrawableItem* item) {
    item->setOwner(this);
    items.append(item);
}

QPointF DrawingBoard::getMousePosition() {
    return mousePosition;
}

void DrawingBoard::deleteItemAt(QPointF point) {
    for (int i = items.length() - 1; i >= 0; i -- ) {
        if (items[i]->isDeletable() && items[i]->contains(point)) {
            delete items[i];
            items.remove(i);
            return;
        }
    }
}

void DrawingBoard::hoverMoveEvent(QGraphicsSceneHoverEvent * event) {
    if (activeTool == "None" || activeTool == "Pan") {
        QGraphicsItem::hoverMoveEvent(event);
        return;
    }
    mousePosition = event->pos();

    Pen * pen = dynamic_cast<Pen*>(currentItem);
    if (currentItem != nullptr && pen != nullptr){
        pen->addSplinePoint(mousePosition);
    }

    update();
}

void DrawingBoard::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (activeTool == "None" || activeTool == "Pan") {
        QGraphicsItem::mouseMoveEvent(event);
        return;
    }
    mousePosition = event->pos();

    Pen * pen = dynamic_cast<Pen*>(currentItem);
    if (currentItem != nullptr && pen != nullptr){
        pen->addSplinePoint(mousePosition);
    }

    update();
}

void DrawingBoard::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if (activeTool == "None" || activeTool == "Pan") {
        QGraphicsItem::mousePressEvent(event);
        return;
    }

    if (currentItem == nullptr) {

        if (activeTool == "Line") {
            currentItem = new Line();
        } else if (activeTool == "Rect") {
            currentItem = new Rect();
        } else if (activeTool == "CenterCircle") {
            currentItem = new Circle();
            Circle* circle = dynamic_cast<Circle*>(currentItem);
            circle->setType("Center");
        } else if (activeTool == "CornerCircle") {
            currentItem = new Circle();
            Circle* circle = dynamic_cast<Circle*>(currentItem);
            circle->setType("Corner");
        } else if (activeTool == "Eraser") {
            deleteItemAt(event->pos());
            return;
        } else if (activeTool == "Pen") {
            currentItem = new Pen();
        }

        addItem(currentItem);
        currentItem->setPoint1(event->pos());
    } else {
        if (drawStyle == "Click") {
            currentItem->setPoint2(event->pos());

            if (currentItem->invalidStructure()) {
                clearIncompleteDrawing();
            }

            currentItem = nullptr;
        }
    }

    update();
}



void DrawingBoard::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (activeTool == "None" || activeTool == "Pan") {
        QGraphicsItem::mouseReleaseEvent(event);
        return;
    }

    if (drawStyle == "Drag" && currentItem != nullptr) {
        currentItem->setPoint2(event->pos());
        if (currentItem->invalidStructure()) {
            clearIncompleteDrawing();
        }
        currentItem = nullptr;
    }
};

void DrawingBoard::clearIncompleteDrawing() {
    if (currentItem != nullptr) {
        items.removeLast();
        delete currentItem;
        currentItem = nullptr;
    }
}

void DrawingBoard::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        clearIncompleteDrawing();
    } else {
        QGraphicsItem::keyPressEvent(event);
    }
}

void DrawingBoard::setTool(QString tool) {
    clearIncompleteDrawing();
    activeTool = tool;

    if (activeTool != "Pan") {
        mainWindow->getUi()->graphicsView->setDragMode(QGraphicsView::NoDrag);
    }
}

QJsonArray DrawingBoard::saveItems() {
    QJsonArray arr;
    for (int i = 0; i < items.length(); i ++) {
        QJsonObject obj = items[i]->save();
        if (!obj.isEmpty()) {
            arr.append(obj);
        }
    }

    return arr;
}

void DrawingBoard::loadItem(QJsonObject obj) {
    DrawableItem * item;
    int point1_x = obj["Point1"][0].toInt();
    int point1_y = obj["Point1"][1].toInt();
    int point2_x = obj["Point2"][0].toInt();
    int point2_y = obj["Point2"][1].toInt();

    QPointF point1 = QPointF(point1_x, point1_y);
    QPointF point2 = QPointF(point2_x, point2_y);
    if (obj["Shape"].toString() == "Line") {
        item = new Line();
    } else if (obj["Shape"].toString() == "Rect") {
        item = new Rect();
    } else if (obj["Shape"].toString() == "Circle") {
        item = new Circle();
        Circle* circle = dynamic_cast<Circle*>(item);
        circle->setType(obj["Type"].toString());
    } else if (obj["Shape"].toString() == "Pen") {
        item = new Pen();
        Pen * pen = dynamic_cast<Pen*>(item);
        QJsonArray splineArray = obj["Spline"].toArray();
        for (int i = 0; i < splineArray.size(); i ++) {
            QJsonArray pointArray = splineArray[i].toArray();
            if (pointArray.size() == 2) {
                qreal x = pointArray[0].toDouble();
                qreal y = pointArray[1].toDouble();
                pen->addSplinePoint(QPointF(x, y));
            }
        }
    }

    item->setPoint1(point1);
    item->setPoint2(point2);


    items.append(item);
}

void DrawingBoard::loadItems(QJsonArray arr) {
    for (int i = items.length() - 1; i >= 1; i --) {
        items.removeLast();
    }

    for (int i = 0; i < arr.size(); i ++) {
        loadItem(arr[i].toObject());
    }
    update();
}

QString DrawingBoard::swapDrawStyle() {
    if (drawStyle == "Click") {
        drawStyle = "Drag";
    } else {
        drawStyle = "Click";
    }
    return drawStyle;
}

double DrawingBoard::getSelectThreshold() {
    return selectThreshold;
}

