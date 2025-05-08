#ifndef LINE_H
#define LINE_H

#include "DrawableItem.h"

class Line : public DrawableItem
{
public:
    void draw(QPainter * painter) override;
    QJsonObject save() override;
    bool contains(QPointF point) override;

private:

};

#endif // LINE_H
