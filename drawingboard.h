#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>

class DrawableItem;

class DrawingBoard : public QGraphicsItem
{
public:
    explicit DrawingBoard(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addItem(DrawableItem * item);
    QPointF getMousePosition();
    void setTool(QString tool);
    void clearIncompleteDrawing();
    void deleteItemAt(QPointF point);
    QJsonArray saveItems();
    void loadItems(QJsonArray items);

private:
    const qreal diagramSize = 180;
    QList<DrawableItem *> items;
    QPointF mousePosition;
    QString activeTool = "None";
    DrawableItem * currentItem = nullptr;

    void loadItem(QJsonObject item);

protected:
    // void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // DRAWINGBOARD_H
