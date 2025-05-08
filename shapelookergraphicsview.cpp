#include "shapelookergraphicsview.h"
#include <QWheelEvent>
#include <QtMath>

ShapeLookerGraphicsView::ShapeLookerGraphicsView(QWidget *parent) {

}

void ShapeLookerGraphicsView::wheelEvent(QWheelEvent * event) {
    double angle = event->angleDelta().y();
    double factor = qPow(zoomFactor, angle/120.0);

    scale(factor, factor);

    event->accept();

}
