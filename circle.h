#ifndef CIRCLE_H
#define CIRCLE_H

#include "DrawableItem.h"

class Circle : public DrawableItem
{
public:
    void draw(QPainter * painter) override;
    void setType (QString type);
private:
    QString type;

};

#endif // LINE_H

