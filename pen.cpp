#include "pen.h"
#include <QVector2D>

void Pen::draw(QPainter* painter) {
    if (splinePoints.length() < 2) { return; }

    QPainterPath path;
    path.moveTo(splinePoints[0]);

    for (int i = 1; i < splinePoints.length() - 1; i ++) {
        QPointF mid = (splinePoints[i] + splinePoints[i + 1]) / 2;
        path.quadTo(splinePoints[i], mid);
    }

    path.lineTo(splinePoints.last());

    painter->drawPath(path);
}

void Pen::addSplinePoint(QPointF point) {
    splinePoints.append(point);
}

QJsonObject Pen::save() {
    QJsonObject obj = DrawableItem::save();
    if (obj.isEmpty()) {
        return obj;
    }

    obj["Shape"] = "Pen";

    QJsonArray splineArray;
    for (const QPointF& point : splinePoints) {
        QJsonArray pointArray;
        pointArray.append(point.x());
        pointArray.append(point.y());
        splineArray.append(pointArray);
    }

    obj["Spline"] = splineArray;


    return obj;
}

bool Pen::lineSegmentContains(QPointF segP1, QPointF segP2, QPointF point, int radius) {
    QVector2D p1(segP1);
    QVector2D p2(segP2);
    QVector2D p(point);

    // Calculate the squared length of the line segment
    QVector2D lineVec = p2 - p1;
    float lineSegmentLengthSquared = lineVec.lengthSquared();

    if (lineSegmentLengthSquared == 0.0) {
        // p1 and p2 are the same point, so just calculate distance to that point
        return (p - p1).length() <= radius;
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

    return distance <= radius;
}

bool Pen::contains(QPointF point) {
    for (int i = 0; i < splinePoints.length() - 1; i ++) {
        if (lineSegmentContains(splinePoints[i], splinePoints[i+1], point, owner->getSelectThreshold())) {
            return true;
        }
    }
    return false;
}

QList<DrawableItem *> Pen::partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) {
    QList<DrawableItem *> items;
    if (splinePoints.size() < 2) {
        return items;
    }

    // First mark which segments should be erased
    QVector<bool> segmentErased(splinePoints.size() - 1, false);
    bool anyErased = false;

    for (int i = 1; i < splinePoints.size(); i++) {
        if (lineSegmentContains(splinePoints[i-1], splinePoints[i], point, radius)) {
            segmentErased[i-1] = true;
            anyErased = true;
        }
    }

    if (!anyErased) {
        return items; // No segments to erase
    }

    // Now collect consecutive non-erased points into new pens
    QList<QPointF> currentSegment;
    currentSegment.append(splinePoints[0]);

    for (int i = 1; i < splinePoints.size(); i++) {
        if (!segmentErased[i-1]) {
            // Segment is kept - add its end point
            currentSegment.append(splinePoints[i]);
        } else {
            // Segment is erased - finalize current pen if valid
            if (currentSegment.size() >= 2) {
                Pen* newPen = new Pen();
                newPen->setOwner(owner);
                for (const QPointF& pt : currentSegment) {
                    newPen->addSplinePoint(pt);
                }
                items.append(newPen);
            }
            // Start new segment at next point (if it exists)
            currentSegment.clear();
            if (i < splinePoints.size() - 1) {
                currentSegment.append(splinePoints[i]);
            }
        }
    }

    // Add the last segment if valid
    if (currentSegment.size() >= 2) {
        Pen* newPen = new Pen();
        newPen->setOwner(owner);
        for (const QPointF& pt : currentSegment) {
            newPen->addSplinePoint(pt);
        }
        items.append(newPen);
    }

    erase = true;
    repeat = !items.isEmpty();
    // qInfo() << "Erased segments. Created" << items.size() << "new pens";
    return items;
}
