#ifndef CIRCLE_H
#define CIRCLE_H

#include "DrawableItem.h"

class Circle : public DrawableItem
{
public:
    void draw(QPainter * painter) override;
    void setType (QString type);
    QJsonObject save() override;
    bool contains(QPointF point) override;
    QList<DrawableItem *> partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) override;
private:
    QString type;
};

#endif // LINE_H

