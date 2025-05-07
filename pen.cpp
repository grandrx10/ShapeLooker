#include "pen.h"

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
