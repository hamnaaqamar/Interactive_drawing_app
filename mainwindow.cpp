#include "MainWindow.h"
#include "Canvas.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>
#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QActionGroup>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    canvas(new Canvas(this)),
    actionBrush(nullptr),
    actionEraser(nullptr),
    actionLine(nullptr),
    actionRectangle(nullptr),
    actionCircle(nullptr),
    actionColorPicker(nullptr),
    actionNew(nullptr),
    actionOpen(nullptr),
    actionSave(nullptr),
    actionUndo(nullptr),
    actionRedo(nullptr),
    actionClear(nullptr),
    actionAbout(nullptr)
{
    // Set up UI elements programmatically
    createActions();
    setupMenuBar();
    setupToolBar();
    setupConnections();

    // Set up canvas
    setCentralWidget(canvas);
    canvas->setColor(currentColor);
    statusBar()->showMessage("Ready", 2000);
}

MainWindow::~MainWindow() {
    // Clean up actions
    delete actionBrush;
    delete actionEraser;
    delete actionLine;
    delete actionRectangle;
    delete actionCircle;
    delete actionColorPicker;
    delete actionNew;
    delete actionOpen;
    delete actionSave;
    delete actionUndo;
    delete actionRedo;
    delete actionClear;
    delete actionAbout;
}

void MainWindow::createActions() {
    // Tool actions
    actionBrush = new QAction(QIcon(":/icons/brush.png"), "&Brush", this);
    actionEraser = new QAction(QIcon(":/icons/eraser.png"), "&Eraser", this);
    actionLine = new QAction(QIcon(":/icons/line.png"), "&Line", this);
    actionRectangle = new QAction(QIcon(":/icons/rectangle.png"), "&Rectangle", this);
    actionCircle = new QAction(QIcon(":/icons/circle.png"), "&Circle", this);
    actionColorPicker = new QAction(QIcon(":/icons/color.png"), "&Color", this);

    // File actions
    actionNew = new QAction(QIcon(":/icons/new.png"), "&New", this);
    actionOpen = new QAction(QIcon(":/icons/open.png"), "&Open", this);
    actionSave = new QAction(QIcon(":/icons/save.png"), "&Save", this);

    // Edit actions
    actionUndo = new QAction(QIcon(":/icons/undo.png"), "&Undo", this);
    actionRedo = new QAction(QIcon(":/icons/redo.png"), "&Redo", this);
    actionClear = new QAction(QIcon(":/icons/clear.png"), "&Clear", this);

    // Help action
    actionAbout = new QAction("&About", this);

    // Set shortcuts
    actionNew->setShortcut(QKeySequence::New);
    actionOpen->setShortcut(QKeySequence::Open);
    actionSave->setShortcut(QKeySequence::Save);
    actionUndo->setShortcut(QKeySequence::Undo);
    actionRedo->setShortcut(QKeySequence::Redo);

    // Group tools for mutual exclusivity
    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->addAction(actionBrush);
    toolGroup->addAction(actionEraser);
    toolGroup->addAction(actionLine);
    toolGroup->addAction(actionRectangle);
    toolGroup->addAction(actionCircle);
    actionBrush->setCheckable(true);
    actionEraser->setCheckable(true);
    actionLine->setCheckable(true);
    actionRectangle->setCheckable(true);
    actionCircle->setCheckable(true);
    actionBrush->setChecked(true);
}

void MainWindow::setupMenuBar() {
    // File menu
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(actionNew);
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close);

    // Edit menu
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(actionUndo);
    editMenu->addAction(actionRedo);
    editMenu->addSeparator();
    editMenu->addAction(actionClear);

    // Tools menu
    QMenu *toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(actionBrush);
    toolsMenu->addAction(actionEraser);
    toolsMenu->addAction(actionLine);
    toolsMenu->addAction(actionRectangle);
    toolsMenu->addAction(actionCircle);
    toolsMenu->addSeparator();
    toolsMenu->addAction(actionColorPicker);

    // Help menu
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(actionAbout);
}

void MainWindow::setupToolBar() {
    QToolBar *toolBar = addToolBar("Tools");
    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
    toolBar->addSeparator();
    toolBar->addAction(actionUndo);
    toolBar->addAction(actionRedo);
    toolBar->addAction(actionClear);
    toolBar->addSeparator();
    toolBar->addAction(actionBrush);
    toolBar->addAction(actionEraser);
    toolBar->addAction(actionLine);
    toolBar->addAction(actionRectangle);
    toolBar->addAction(actionCircle);
    toolBar->addSeparator();
    toolBar->addAction(actionColorPicker);
}

void MainWindow::setupConnections() {
    // Tools
    connect(actionBrush, &QAction::triggered, this, &MainWindow::selectBrush);
    connect(actionEraser, &QAction::triggered, this, &MainWindow::selectEraser);
    connect(actionLine, &QAction::triggered, this, &MainWindow::selectLine);
    connect(actionRectangle, &QAction::triggered, this, &MainWindow::selectRectangle);
    connect(actionCircle, &QAction::triggered, this, &MainWindow::selectCircle);
    connect(actionColorPicker, &QAction::triggered, this, &MainWindow::selectColor);

    // File
    connect(actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveFile);

    // Edit
    connect(actionUndo, &QAction::triggered, this, &MainWindow::undo);
    connect(actionRedo, &QAction::triggered, this, &MainWindow::redo);
    connect(actionClear, &QAction::triggered, this, &MainWindow::clearCanvas);

    // Help
    connect(actionAbout, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::selectBrush() {
    canvas->setTool(Canvas::Brush);
    statusBar()->showMessage("Brush selected", 2000);
}

void MainWindow::selectEraser() {
    canvas->setTool(Canvas::Eraser);
    statusBar()->showMessage("Eraser selected", 2000);
}

void MainWindow::selectLine() {
    canvas->setTool(Canvas::Line);
    statusBar()->showMessage("Line selected", 2000);
}

void MainWindow::selectRectangle() {
    canvas->setTool(Canvas::Rectangle);
    statusBar()->showMessage("Rectangle selected", 2000);
}

void MainWindow::selectCircle() {
    canvas->setTool(Canvas::Circle);
    statusBar()->showMessage("Circle selected", 2000);
}

void MainWindow::selectColor() {
    QColor color = QColorDialog::getColor(currentColor, this, "Select Drawing Color");
    if (color.isValid()) {
        currentColor = color;
        canvas->setColor(color);
        statusBar()->showMessage("Color changed", 2000);
    }
}

void MainWindow::clearCanvas() {
    canvas->clear();
    statusBar()->showMessage("Canvas cleared", 2000);
}

void MainWindow::undo() {
    if (canvas->undo()) {
        statusBar()->showMessage("Undo successful", 2000);
    } else {
        statusBar()->showMessage("Nothing to undo", 2000);
    }
}

void MainWindow::redo() {
    if (canvas->redo()) {
        statusBar()->showMessage("Redo successful", 2000);
    } else {
        statusBar()->showMessage("Nothing to redo", 2000);
    }
}

void MainWindow::newFile() {
    if (canvas->isModified()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "New File",
                                      "Current drawing has unsaved changes. Start new file anyway?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }
    canvas->clear();
    statusBar()->showMessage("New file created", 2000);
}

void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Drawing",
                                                    QDir::homePath(),
                                                    "PNG Image (*.png);;JPEG Image (*.jpg *.jpeg);;Bitmap Image (*.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap pixmap = canvas->grab();
        if (pixmap.save(fileName)) {
            canvas->setModified(false);
            statusBar()->showMessage("File saved successfully", 2000);
        } else {
            QMessageBox::warning(this, "Save Error", "Could not save file");
        }
    }
}

void MainWindow::openFile() {
    if (canvas->isModified()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Open File",
                                      "Current drawing has unsaved changes. Open anyway?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open Image",
                                                    QDir::homePath(),
                                                    "Image Files (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty()) {
        QPixmap image(fileName);
        if (!image.isNull()) {
            canvas->setImage(image.toImage());
            statusBar()->showMessage("File opened successfully", 2000);
        } else {
            QMessageBox::warning(this, "Open Error", "Could not open file");
        }
    }
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About Drawing App",
                       "<h2>Drawing Application</h2>"
                       "<p>Version 1.0</p>"
                       "<p>A simple drawing application created with Qt</p>"
                       "<p>&copy; 2023 Your Name</p>");
}
