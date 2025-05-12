#include "circle.h"
#include "pen.h"

void Circle::draw(QPainter* painter) {
    // Complete drawing
    if (initializedPoint(point1) && initializedPoint(point2)) {
        if (type == "Corner") {
            int width = point2.x() - point1.x();
            int height = point2.y() - point1.y();
            painter->drawEllipse(point1.x(), point1.y(), width, height);
        } else { // center
            qreal dist = QLineF(point1, point2).length();
            painter->drawEllipse(point1, dist, dist);
        }

    // Semi complete
    } else if (initializedPoint(point1)) {
        if (type == "Corner") {
            int width = owner->getMousePosition().x() - point1.x();
            int height = owner->getMousePosition().y() - point1.y();
            painter->drawEllipse(point1.x(), point1.y(), width, height);
        } else {
            qreal dist = QLineF(point1, owner->getMousePosition()).length();
            painter->drawEllipse(point1, dist, dist);
        }

    }
}

bool Circle::contains(QPointF point) {
    if (type == "Center") {
        return QLineF(point1, point).length() <= QLineF(point1, point2).length();
    } else {
        // simply plug in the ellipse equation!
        QPointF center = (point1 + point2) / 2;
        double width = qAbs(point2.x() - point1.x());
        double height = qAbs(point2.y() - point1.y());

        double a = width / 2.0;
        double b = height / 2.0;

        // transform so that the elliptical center is the center of the
        // coord system.
        double x = point.x() - center.x();
        double y = point.y() - center.y();

        return (x*x)/(a*a) + (y*y)/(b*b) <= 1.0;
    }
}

QList<DrawableItem *> Circle::partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) {
    QList<DrawableItem *> items;
    Pen* pen = new Pen();
    pen->setOwner(owner);

    if (type == "Corner") {
        // Corner-to-corner circle (ellipse in rectangle)
        QRectF rect(point1, point2);
        qreal a = rect.width() / 2.0;
        qreal b = rect.height() / 2.0;
        QPointF center = rect.center();

        // Generate points along the ellipse
        const int numPoints = 36; // Points per full circle
        for (int i = 0; i <= numPoints; i++) {
            qreal angle = 2 * M_PI * i / numPoints;
            QPointF p(
                center.x() + a * cos(angle),
                center.y() + b * sin(angle)
                );
            pen->addSplinePoint(p);
        }
    }
    else if (type == "Center") {
        // Center-radius circle
        qreal r = QLineF(point1, point2).length();

        // Generate points along the circle
        const int numPoints = 36; // Points per full circle
        for (int i = 0; i <= numPoints; i++) {
            qreal angle = 2 * M_PI * i / numPoints;
            QPointF p(
                point1.x() + r * cos(angle),
                point1.y() + r * sin(angle)
                );
            pen->addSplinePoint(p);
        }
    }

    items.append(pen);
    erase = true;
    repeat = true;
    return items;
}

void Circle::setType(QString circType) {
    type = circType;
}

QJsonObject Circle::save() {
    QJsonObject obj = DrawableItem::save();
    if (obj.isEmpty()) {
        return obj;
    }

    obj["Shape"] = "Circle";
    obj["Type"] = type;
    return obj;
}
