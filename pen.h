#ifndef PEN_H
#define PEN_H

#include "DrawableItem.h"

class Pen : public DrawableItem
{
public:
    QJsonObject save() override;
    void draw(QPainter * painter) override;
    void addSplinePoint(QPointF);

private:
    QList<QPointF> splinePoints;
};

#endif // PEN_H
