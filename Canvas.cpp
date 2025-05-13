#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "FreehandStroke.h"

Canvas::Canvas(QWidget* parent) : QWidget(parent) {
    setFixedSize(800, 600);
    historyManager = new UndoRedoManager();
    setAttribute(Qt::WA_StaticContents);
}

// Convert enum to string for your existing code
QString Canvas::toolToString(Tool tool) const {
    switch(tool) {
    case Brush: return "brush";
    case Eraser: return "eraser";
    case Line: return "line";
    case Rectangle: return "rectangle";
    case Circle: return "circle";
    default: return "brush";
    }
}

void Canvas::setTool(Tool tool) {
    currentTool = tool;
}

void Canvas::setColor(const QColor& color) {
    currentColor = color;
}

void Canvas::clear() {
    // Clear all shapes
    for (int i = 0; i < shapeCount; i++) {
        delete shapes[i];  // Free memory for each shape
    }
    shapeCount = 0;

    // Clear the undo/redo history
    historyManager->clear();

    update();  // Refresh the display
}

bool Canvas::isModified() const {
    return modified;
}

void Canvas::setModified(bool modified) {
    this->modified = modified;
}

void Canvas::setImage(const QImage& image) {
    clear();
    this->backgroundImage = image;
    modified = true;
    update();
}

// Update mouse events to use enum
void Canvas::mousePressEvent(QMouseEvent* event) {
    QString tool = toolToString(currentTool);

    if (tool == "brush") {
        currentShape = new FreehandStroke(currentColor, brushSize);
    } else if (tool == "eraser") {
        currentShape = new FreehandStroke(Qt::white, brushSize);
    } else if (tool == "line") {
        currentShape = new ::Line(currentColor, brushSize);
    } else if (tool == "rectangle") {
        currentShape = new ::Rectangle(currentColor, brushSize);
    } else if (tool == "circle") {
        currentShape = new ::Circle(currentColor, brushSize);
    }

    if (currentShape) {
        currentShape->addPoint(event->pos());
        modified = true;
    }
}

// [Rest of your existing mouseMoveEvent, mouseReleaseEvent, paintEvent]

bool Canvas::undo() {
    Shape* shape = historyManager->undo();
    if (shape && shapeCount > 0) {
        delete shapes[shapeCount-1];  // Free memory if needed
        --shapeCount;
        modified = true;
        update();
        return true;
    }
    return false;
}

bool Canvas::redo() {
    if (Shape* shape = historyManager->redo()) {
        if (shapeCount < MAX_SHAPES) {
            shapes[shapeCount++] = shape;
            modified = true;
            update();
            return true;
        }
    }
    return false;
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if (currentShape) {
        currentShape->addPoint(event->pos());
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {
    if (currentShape && shapeCount < MAX_SHAPES) {
        currentShape->addPoint(event->pos());
        shapes[shapeCount++] = currentShape;
        historyManager->pushShape(currentShape);
        currentShape = nullptr;
        update();
    }
}

void Canvas::paintEvent(QPaintEvent* /*event*/) {
    QPainter painter(this);
    painter.drawImage(0, 0, backgroundImage);

    for (int i = 0; i < shapeCount; ++i) {
        if (shapes[i]) {
            shapes[i]->draw(painter);
        }
    }

    if (currentShape) {
        currentShape->draw(painter);
    }
}




