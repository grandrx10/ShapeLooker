#ifndef PEN_H
#define PEN_H

#include "DrawableItem.h"

class Pen : public DrawableItem
{
public:
    QJsonObject save() override;
    void draw(QPainter * painter) override;
    void addSplinePoint(QPointF point);

    bool contains(QPointF point) override;
    QList<DrawableItem *> partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) override;

private:
    bool lineSegmentContains(QPointF segP1, QPointF segP2, QPointF point, int radius);
    QList<QPointF> splinePoints;
};

#endif // PEN_H
