#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QMainWindow>

class MainWindow;

class DrawableItem;

class DrawingBoard : public QGraphicsItem
{
public:
    explicit DrawingBoard(QGraphicsItem *parent = nullptr, MainWindow* mainWindow = nullptr);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void addItem(DrawableItem * item);
    QPointF getMousePosition();
    void setTool(QString tool);
    void clearIncompleteDrawing();
    void deleteItemAt(QPointF point);
    void partialEraseAt(QPointF point, int radius);
    QJsonArray saveItems();
    void loadItems(QJsonArray items);
    QString swapDrawStyle();
    double getSelectThreshold();

private:
    MainWindow * mainWindow;
    int diagramSize = 180;
    double selectThreshold = 10;
    QList<DrawableItem *> items;
    QPointF mousePosition;
    QString activeTool = "None";
    QString toolOnHold = "None";
    QString drawStyle = "Click";
    DrawableItem * currentItem = nullptr;

    void loadItem(QJsonObject item);


protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // DRAWINGBOARD_H
