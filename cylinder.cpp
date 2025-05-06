#include "cylinder.h"
#include <algorithm>

Cylinder::Cylinder(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    // Initialize any default values here if needed
}

QRectF Cylinder::boundingRect() const
{
    // I want to erase the entire graphicsView
    const qreal largeSize = diagramSize;
    return QRectF(-largeSize, -largeSize, 2*largeSize, 2*largeSize);
}

void Cylinder::updateScaleToFit() {
    const double targetSize = diagramSize;

    // The cylinder's original bounding size (unscaled)
    double cylinderWidth = 2 * m_radius;
    double cylinderHeight = m_height + (m_radius / 2);
    if (type == "T") {
        cylinderHeight = m_height;
    }

    double maxDimension = std::max(cylinderWidth, cylinderHeight);
    m_scale = targetSize / maxDimension;

    this->update(); // Trigger repaint
}


void Cylinder::setType(QString shapeType) {
    type = shapeType;
    this->update();
}

void Cylinder::setRadius(double radius) {
    m_radius = radius;

    updateScaleToFit();
}

void Cylinder::setHeight(double height) {
    m_height = height;
    updateScaleToFit();
}

void Cylinder::setScale(double scale) {
    m_scale = scale;
    this->update();
}

void Cylinder::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->save(); // Save the current painter state
    QPen originalPen = painter->pen();
    painter->scale(m_scale, m_scale); // Apply uniform scaling
    if (m_scale != 0) {
        originalPen.setWidthF(originalPen.widthF() / m_scale);
        painter->setPen(originalPen);
    }

    double ellipseWidth = m_radius * 2;
    double ellipseHeight = m_radius / 2;

    if (type == "U") {
        // Bottom ellipse
        painter->setBrush(this->blue);
        painter->setPen(originalPen);
        painter->drawEllipse(QPointF(0, m_height / 2), m_radius, ellipseHeight);

        // Cylinder side
        painter->setPen(Qt::NoPen);
        painter->drawRect(-m_radius, -m_height / 2, ellipseWidth, m_height);

        // Top ellipse
        painter->setPen(originalPen);
        painter->setBrush(this->light_blue);
        painter->drawEllipse(QPointF(0, -m_height / 2), m_radius, ellipseHeight);

        // Side Lines
        painter->drawLine(-m_radius, -m_height / 2, -m_radius, m_height / 2);
        painter->drawLine(m_radius, -m_height / 2, m_radius, m_height / 2);
    }
    else if (type == "B") {
        painter->setBrush(this->blue);
        painter->setPen(originalPen);
        painter->drawEllipse(QPointF(m_height/2, 0), ellipseHeight, m_radius);

        // Cylinder side
        painter->setPen(Qt::NoPen);
        painter->drawRect(-m_height/2, -m_radius, m_height, 2*m_radius);

        // Right ellipse
        painter->setPen(originalPen);
        painter->setBrush(this->light_blue);
        painter->drawEllipse(QPointF(-m_height/2, 0), ellipseHeight, m_radius);

        // Side Lines
        painter->drawLine(-m_height/2, -m_radius, m_height/2, -m_radius);
        painter->drawLine(-m_height/2, m_radius, m_height/2, m_radius);

    }
    else if (type == "T") {
        painter->setBrush(this->blue);
        painter->setPen(originalPen);
        painter->drawRect(-m_height/2, -m_height/2, m_height, m_height);

        // Draw the circle
        painter->setBrush(Qt::white);
        painter->drawEllipse(
            QPointF(0, 0),
            m_radius,
            m_radius
            );

    } else {
        qInfo() << "Unused type, check for err.";
    }

    painter->restore(); // Restore the original painter state
}
