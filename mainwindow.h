#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QAction>
#include <QMenu>
#include <QToolBar>

#include "Canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Tool selection
    void selectBrush();
    void selectEraser();
    void selectLine();
    void selectRectangle();
    void selectCircle();
    void selectColor();

    // Canvas operations
    void clearCanvas();
    void undo();
    void redo();

    // File operations
    void newFile();
    void saveFile();
    void openFile();

    // Help
    void showAbout();

private:
    void createActions();
    void setupMenuBar();
    void setupToolBar();
    void setupConnections();

    // UI Elements
    QAction *actionBrush;
    QAction *actionEraser;
    QAction *actionLine;
    QAction *actionRectangle;
    QAction *actionCircle;
    QAction *actionColorPicker;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionClear;
    QAction *actionAbout;

    // Core components
    Canvas* canvas;
    QColor currentColor;
};

#endif // MAINWINDOW_H

