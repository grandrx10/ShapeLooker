#ifndef SHAPELOOKERGRAPHICSVIEW_H
#define SHAPELOOKERGRAPHICSVIEW_H
#include <QGraphicsView>

class ShapeLookerGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ShapeLookerGraphicsView(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent * event) override;

private:
    const double zoomFactor = 1.1; // perhaps a smooth zoom in and out factor?
    // double zoom;

};

#endif // SHAPELOOKERGRAPHICSVIEW_H
