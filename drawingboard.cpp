#include "drawingboard.h"
#include "DrawableItem.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include <QKeyEvent>
#include <QWidget>


DrawingBoard::DrawingBoard(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
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

void DrawingBoard::hoverMoveEvent(QGraphicsSceneHoverEvent * event) {
    mousePosition = event->pos();
    update();
}

void DrawingBoard::deleteItemAt(QPointF point) {
    for (int i = items.length() - 1; i >= 0; i -- ) {
        if (items[i]->isDeletable() && items[i]->contains(point)) {
            free(items[i]);
            items.remove(i);
            return;
        }
    }
}

void DrawingBoard::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    if (activeTool == "None") {
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
        }

        addItem(currentItem);
        currentItem->setPoint1(event->pos());
    } else {
        currentItem->setPoint2(event->pos());
        currentItem = nullptr;
    }

    update();
}

void DrawingBoard::clearIncompleteDrawing() {
    if (currentItem != nullptr) {
        items.removeLast();
        free(currentItem);
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
}

