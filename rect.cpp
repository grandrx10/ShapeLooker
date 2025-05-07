#include "rect.h"

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
