#ifndef RECT_H
#define RECT_H

#include "DrawableItem.h"

class Rect : public DrawableItem
{
public:
    QJsonObject save() override;
    void draw(QPainter * painter) override;
};

#endif // RECT_H
