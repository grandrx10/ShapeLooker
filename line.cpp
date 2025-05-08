#include "line.h"
#include <QVector2D>

void Line::draw(QPainter* painter) {
    if (initializedPoint(point1) && initializedPoint(point2)) {
        painter->drawLine(point1, point2);
    } else if (initializedPoint(point1)) {
        painter->drawLine(point1, owner->getMousePosition());
    }
}

QJsonObject Line::save() {
    QJsonObject obj = DrawableItem::save();
    if (obj.isEmpty()) {
        return obj;
    }

    obj["Shape"] = "Line";
    return obj;
}

bool Line::contains(QPointF point) {
    if (!initializedPoint(point1) || !initializedPoint(point2)) {
        return false;
    }

    QVector2D p1(point1);
    QVector2D p2(point2);
    QVector2D p(point);

    // Calculate the squared length of the line segment
    QVector2D lineVec = p2 - p1;
    float lineSegmentLengthSquared = lineVec.lengthSquared();

    if (lineSegmentLengthSquared == 0.0) {
        // p1 and p2 are the same point, so just calculate distance to that point
        return (p - p1).length() <= owner->getSelectThreshold();
    }

    // Calculate projection of point onto line segment
    // t is the normalized projection position (0 = at p1, 1 = at p2)
    float t = QVector2D::dotProduct(p - p1, lineVec) / lineSegmentLengthSquared;

    // Clamp t to [0,1] to get the closest point on the segment
    t = qBound(0.0f, t, 1.0f);

    // Calculate the closest point on the line segment
    QVector2D closestPoint = p1 + t * lineVec;

    // Calculate the distance from the point to the closest point on segment
    float distance = (p - closestPoint).length();

    // qInfo() << distance << "Threshold:" << owner->getSelectThreshold();

    return distance <= owner->getSelectThreshold();
}

