#ifndef CYLINDER_H
#define CYLINDER_H

#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "drawableItem.h"

class Cylinder : public DrawableItem {

public:
    Cylinder();
    void draw(QPainter * painter) override;
    void setType(QString shapeType);
    void setRadius(double radius);
    void setHeight(double height);
    void setScale(double scale);
    void updateScaleToFit();
signals:

private:
    const QColor light_blue = QColor(144, 224, 239);
    const QColor blue = QColor(72, 202,228);
    qreal m_radius = 50.0;
    qreal m_height = 80.0;
    qreal m_scale = 1.0;
    const qreal diagramSize = 180;
    QString type = QString("U");

    int findUniversalMultiplier();
};

#endif // CYLINDER_H
