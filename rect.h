#ifndef RECT_H
#define RECT_H

#include "DrawableItem.h"

class Rect : public DrawableItem
{
public:
    void draw(QPainter * painter) override;
};

#endif // RECT_H
