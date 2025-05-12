#ifndef LINE_H
#define LINE_H

#include "DrawableItem.h"

class Line : public DrawableItem
{
public:
    Line() : DrawableItem() {}
    Line(QPointF p1, QPointF p2, DrawingBoard * drawingBoard) : DrawableItem(p1, p2, drawingBoard) {}
    void draw(QPainter * painter) override;
    QJsonObject save() override;
    bool contains(QPointF point) override;
    QList<DrawableItem *> partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) override;

private:

};

#endif // LINE_H
