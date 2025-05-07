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
    bool contains(QPointF point) {
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
