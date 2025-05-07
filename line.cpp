#include "line.h"

void Line::draw(QPainter* painter) {
    if (initializedPoint(point1) && initializedPoint(point2)) {
        painter->drawLine(point1, point2);
    } else if (initializedPoint(point1)) {
        painter->drawLine(point1, owner->getMousePosition());
    }
}


