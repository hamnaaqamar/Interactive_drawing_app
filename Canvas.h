#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QColor>
#include "Shape.h"
#include "UndoRedoManager.h"


const int MAX_SHAPES = 1000;

class Canvas : public QWidget {
    Q_OBJECT

public:
    enum Tool { Brush, Eraser, Line, Rectangle, Circle };
    Q_ENUM(Tool)

    explicit Canvas(QWidget* parent = nullptr);

    // Tool methods
    void setTool(Tool tool);  // Changed from setCurrentTool
    void setColor(const QColor& color);  // Changed from setCurrentColor
    void setBrushSize(int size);

    // Actions
    bool undo();
    bool redo();
    void clear();
    bool isModified() const;
    void setModified(bool modified);
    void setImage(const QImage& image);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    Shape* shapes[MAX_SHAPES];
    int shapeCount = 0;
    Shape* currentShape = nullptr;
    Tool currentTool = Brush;  // Changed to enum
    QColor currentColor = Qt::black;
    int brushSize = 3;
    bool modified = false;
    UndoRedoManager* historyManager;
    QImage backgroundImage;

    QString toolToString(Tool tool) const;
};
#endif
