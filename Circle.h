#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <QPoint>
#include <QPainter>
#include <QColor>

class Circle : public Shape {
private:
    QPoint center;
    int radius;

public:
    Circle(const QColor& color = "black", int thickness = 1);
    
    // Override the draw method
    void draw(QPainter& painter) override;

    // Capture center and radius of the circle
    void addPoint(const QPoint& point) override;
};

#endif
