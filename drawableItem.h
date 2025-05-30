#ifndef DRAWABLEITEM_H
#define DRAWABLEITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include "drawingboard.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class DrawableItem {
public:
    explicit DrawableItem(): owner(nullptr) {};
    DrawableItem(QPointF p1, QPointF p2, DrawingBoard * drawingBoard) : point1(p1), point2(p2), owner(drawingBoard){}
    virtual ~DrawableItem() = default;
    virtual void draw(QPainter * painter) = 0;
    void setPoint1(QPointF point) {
        point1 = point;
    }

    // Concrete implementation for setting point2
    void setPoint2(QPointF point) {
        point2 = point;
    }
    void setOwner(DrawingBoard * newOwner) {
        owner = newOwner;
    }

    bool initializedPoint(QPointF point) {
        if (point == QPointF(-5000, -5000)) {
            return false;
        }
        return true;
    }
    \
    bool invalidStructure() {
        if (!initializedPoint(point1) || !initializedPoint(point2)) {
            return false;
        }

        if (point1 == point2) {
            return true;
        }
        return false;
    }

    // base hitbox detection
    virtual bool contains(QPointF point) {
        if (!initializedPoint(point1) || !initializedPoint(point2)) {
            return false;
        }

        qreal left = std::min(point1.x(), point2.x());
        qreal right = std::max(point1.x(), point2.x());
        qreal top = std::min(point1.y(), point2.y());
        qreal bottom = std::max(point1.y(), point2.y());

        return point.x() >= left && point.x() <= right &&
               point.y() >= top && point.y() <= bottom;
    }

    virtual QList<DrawableItem *> partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat){
        QList<DrawableItem *> items;
        return items;
    }

    bool isDeletable() {
        return deletable;
    }

    virtual QJsonObject save() {
        QJsonObject obj;

        if (!initializedPoint(point1) || !initializedPoint(point2)) {
            return obj;
        }

        QJsonArray point1Array;
        point1Array.append(point1.x());
        point1Array.append(point1.y());

        QJsonArray point2Array;
        point2Array.append(point2.x());
        point2Array.append(point2.y());

        obj["Point1"] = point1Array;
        obj["Point2"] = point2Array;

        return obj;
    }

private:

protected:
    DrawingBoard * owner;
    bool deletable = true;
    QPointF point1 = QPointF(-5000, -5000);
    QPointF point2 = QPointF(-5000, -5000);
};

#endif // DRAWABLEITEM_H
