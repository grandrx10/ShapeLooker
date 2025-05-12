#include "line.h"
#include <QVector2D>
#include <cmath>
#include <algorithm>

void Line::draw(QPainter* painter) {
    if (initializedPoint(point1) && initializedPoint(point2)) {
        painter->drawLine(point1, point2);
    } else if (initializedPoint(point1)) {
        painter->drawLine(point1, owner->getMousePosition());
    }
}

QJsonObject Line::save() {
    QJsonObject obj = DrawableItem::save();
    if (obj.isEmpty()) {
        return obj;
    }

    obj["Shape"] = "Line";
    return obj;
}

bool Line::contains(QPointF point) {
    if (!initializedPoint(point1) || !initializedPoint(point2)) {
        return false;
    }

    QVector2D p1(point1);
    QVector2D p2(point2);
    QVector2D p(point);

    // Calculate the squared length of the line segment
    QVector2D lineVec = p2 - p1;
    float lineSegmentLengthSquared = lineVec.lengthSquared();

    if (lineSegmentLengthSquared == 0.0) {
        // p1 and p2 are the same point, so just calculate distance to that point
        return (p - p1).length() <= owner->getSelectThreshold();
    }

    // Calculate projection of point onto line segment
    // t is the normalized projection position (0 = at p1, 1 = at p2)
    float t = QVector2D::dotProduct(p - p1, lineVec) / lineSegmentLengthSquared;

    // Clamp t to [0,1] to get the closest point on the segment
    t = qBound(0.0f, t, 1.0f);

    // Calculate the closest point on the line segment
    QVector2D closestPoint = p1 + t * lineVec;

    // Calculate the distance from the point to the closest point on segment
    float distance = (p - closestPoint).length();

    // qInfo() << distance << "Threshold:" << owner->getSelectThreshold();

    return distance <= owner->getSelectThreshold();
}

bool intersectLineCircle(const QPointF& p1, const QPointF& p2,
                         const QPointF& center, double radius,
                         QVector<QPointF>& outPoints) {
    outPoints.clear();

    const double epsilon = 1e-5; // Adjusted epsilon for better handling

    // Convert to double precision for calculations
    QPointF d = p2 - p1;
    QPointF f = p1 - center;

    double a = QPointF::dotProduct(d, d);
    double b = 2 * QPointF::dotProduct(f, d);
    double c = QPointF::dotProduct(f, f) - radius * radius;

    double discriminant = b*b - 4*a*c;

    // No intersection
    if (discriminant < -epsilon) {
        return false;
    }

    // Handle case where discriminant is very small (near zero)
    if (discriminant <= epsilon) {
        discriminant = 0;
    }

    discriminant = std::max(0.0, discriminant);
    double sqrt_discriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2*a);
    double t2 = (-b + sqrt_discriminant) / (2*a);

    // Sort the t values
    if (t1 > t2) {
        std::swap(t1, t2);
    }

    // Check if t values are within the segment [0,1]
    auto addIfValid = [&](double t) {
        if (t >= -epsilon && t <= 1.0 + epsilon) {
            // Clamp to segment bounds
            t = std::clamp(t, 0.0, 1.0);
            QPointF intersection = p1 + t * (p2 - p1);

            // Avoid duplicates
            if (outPoints.isEmpty() ||
                QLineF(outPoints.last(), intersection).length() > epsilon) {
                outPoints.append(intersection);
            }
        }
    };

    addIfValid(t1);
    if (!qFuzzyCompare(t1, t2)) {
        addIfValid(t2);
    }

    return !outPoints.isEmpty();
}

QList<DrawableItem *> Line::partialEraseAt(QPointF point, int radius, bool& erase, bool& repeat) {
    QList<DrawableItem *> items;
    if (!initializedPoint(point1) || !initializedPoint(point2)) {
        return items;
    }

    QVector<QPointF> intersections;
    if (!intersectLineCircle(point1, point2, point, radius, intersections)) {
        if (contains(point)) {
            erase = true;
        }
        return items;
    }

    // Debug output
    // qDebug() << "Intersection points found:" << intersections;
    // qDebug() << "Original line:" << point1 << point2;
    // qDebug() << "Erase center:" << point << "radius:" << radius;

    if (intersections.size() == 2) {
        // Sort intersections by distance from point1 to maintain order
        std::sort(intersections.begin(), intersections.end(),
                  [this](const QPointF& a, const QPointF& b) {
                      return QLineF(point1, a).length() < QLineF(point1, b).length();
                  });

        items.append(new Line(point1, intersections[0], owner));
        items.append(new Line(intersections[1], point2, owner));
    }
    else if (intersections.size() == 1) {
        // Determine which segment is longer
        double distToP1 = QLineF(point1, intersections[0]).length();
        double distToP2 = QLineF(intersections[0], point2).length();

        if (distToP1 > distToP2) {
            items.append(new Line(point1, intersections[0], owner));
        } else {
            items.append(new Line(intersections[0], point2, owner));
        }
    }

    erase = true;
    return items;
}
