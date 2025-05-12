#include "rect.h"
#include "line.h"

void Rect::draw(QPainter* painter) {
    if (initializedPoint(point1) && initializedPoint(point2)) {
        int width = point2.x() - point1.x();
        int height = point2.y() - point1.y();
        painter->drawRect(point1.x(), point1.y(), width, height);
    } else if (initializedPoint(point1)) {
        int width = owner->getMousePosition().x() - point1.x();
        int height = owner->getMousePosition().y() - point1.y();
        painter->drawRect(point1.x(), point1.y(), width, height);
    }
}

QJsonObject Rect::save() {
    QJsonObject obj = DrawableItem::save();
    if (obj.isEmpty()) {
        return obj;
    }

    obj["Shape"] = "Rect";
    return obj;
}

QList<DrawableItem *> Rect::partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) {
    QList<DrawableItem *> items;
    if (!initializedPoint(point1) || !initializedPoint(point2)) {
        return items;
    }

    if (!contains(point)) {
        return items;
    }

    erase = true;
    repeat = true;
    QRectF potentialRect(point1, point2);
    QPointF topLeft = potentialRect.topLeft();
    QPointF topRight = potentialRect.topRight();
    QPointF bottomLeft = potentialRect.bottomLeft();
    QPointF bottomRight = potentialRect.bottomRight();

    // Top edge
    items.append(new Line(topLeft, topRight, owner));
    // Right edge
    items.append(new Line(topRight, bottomRight, owner));
    // Bottom edge
    items.append(new Line(bottomRight, bottomLeft, owner));
    // Left edge
    items.append(new Line(bottomLeft, topLeft, owner));
    return items;

}
