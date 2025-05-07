#include "circle.h"

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

void Circle::setType(QString circType) {
    type = circType;
}
