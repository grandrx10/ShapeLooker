#include "cylinder.h"
#include <algorithm>

Cylinder::Cylinder() {
    deletable = false;
}

int countDecimalPlaces(float value) {
    if (value == std::round(value)) return 0;

    const float epsilon = 1e-5f;  // Precision threshold
    int decimals = 0;
    float temp = std::abs(value);

    while (temp - std::floor(temp) > epsilon && decimals < 6) {
        temp *= 10;
        decimals++;
        if (temp > 1e6) break;  // Prevent infinite loops
    }

    return decimals;
}

// Find the universal multiplier for a set of values
int Cylinder::findUniversalMultiplier() {
    const std::vector<float>& values = {
        static_cast<float>(m_height),
        static_cast<float>(m_radius),
        static_cast<float>(m_radius / 2),
        static_cast<float>(m_height / 2),
    };
    int max_decimals = 0;
    for (float val : values) {
        max_decimals = std::max(max_decimals, countDecimalPlaces(val));
    }
    return static_cast<int>(std::pow(10, max_decimals));
}

void Cylinder::updateScaleToFit() {
    const double targetSize = diagramSize;

    // The cylinder's original bounding size (unscaled)
    int universalMultiplier = findUniversalMultiplier();

    int height = m_height * universalMultiplier;
    int radius = m_radius * universalMultiplier;
    double cylinderWidth = 2 * radius;
    double cylinderHeight = height + (radius / 2);
    if (type == "T") {
        cylinderHeight = height;
    }

    double maxDimension = std::max(cylinderWidth, cylinderHeight);
    m_scale = targetSize / maxDimension;

    owner->update(); // Trigger repaint
}


void Cylinder::setType(QString shapeType) {
    type = shapeType;
    owner->update();
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
    owner->update();
}

void Cylinder::draw(QPainter *painter) {
    painter->save(); // Save the current painter state
    QPen originalPen = painter->pen();
    painter->scale(m_scale, m_scale); // Apply uniform scaling
    if (m_scale != 0) {
        originalPen.setWidthF(originalPen.widthF() / m_scale);
        painter->setPen(originalPen);
    }

    int universalMultiplier = findUniversalMultiplier();

    int height = m_height * universalMultiplier;
    int radius = m_radius * universalMultiplier;
    int ellipseWidth = radius * 2;
    int ellipseHeight = radius / 2;

    if (type == "U") {
        // Bottom ellipse
        painter->setBrush(this->blue);
        painter->setPen(originalPen);
        painter->drawEllipse(QPointF(0, height / 2), radius, ellipseHeight);

        // Cylinder side
        painter->setPen(Qt::NoPen);
        painter->drawRect(-radius, -height / 2, ellipseWidth, height);

        // Top ellipse
        painter->setPen(originalPen);
        painter->setBrush(this->light_blue);
        painter->drawEllipse(QPointF(0, -height / 2), radius, ellipseHeight);

        // Side Lines
        painter->drawLine(-radius, -height / 2, -radius, height / 2);
        painter->drawLine(radius, -height / 2, radius, height / 2);
    }
    else if (type == "B") {
        painter->setBrush(this->blue);
        painter->setPen(originalPen);
        painter->drawEllipse(QPointF(height/2, 0), ellipseHeight, radius);

        // Cylinder side
        painter->setPen(Qt::NoPen);
        painter->drawRect(-height/2, -radius, height, 2*radius);

        // Right ellipse
        painter->setPen(originalPen);
        painter->setBrush(this->light_blue);
        painter->drawEllipse(QPointF(-height/2, 0), ellipseHeight, radius);

        // Side Lines
        painter->drawLine(-height/2, -radius, height/2, -radius);
        painter->drawLine(-height/2, radius, height/2, radius);

    }
    else if (type == "T") {
        painter->setBrush(this->blue);
        painter->setPen(originalPen);
        painter->drawRect(-height/2, -height/2, height, height);

        // Draw the circle
        painter->setBrush(Qt::white);
        painter->drawEllipse(
            QPointF(0, 0),
            radius,
            radius
            );

    } else {
        qInfo() << "Unused type, check for err.";
    }

    painter->restore(); // Restore the original painter state
}
