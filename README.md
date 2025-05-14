# 🖌️ Interactive Drawing App (Qt C++)

An interactive desktop drawing application built using **C++** and **Qt**, offering a variety of tools like brush, eraser, shapes (line, rectangle, circle), undo/redo functionality, and support for freehand drawing.

---

## 🚀 Features

- ✏️ **Drawing Tools**
  - Brush
  - Eraser
  - Line
  - Rectangle
  - Circle
- 🎨 Customizable color 
- ↩️ Undo and Redo functionality
- 🧼 Clear canvas option
- 💾 Save work as an image file

## 🧱 Project Structure

INTERACTIVE_DRAWING_APP/
├── main.cpp                   # Entry point of the application
├── mainwindow.h / .cpp        # Main window with UI components and actions
├── Canvas.h / .cpp            # Canvas widget that handles drawing and user interaction
├── Shape.h                    # Abstract base class for drawable shapes
├── Line.h / .cpp              # Line shape class
├── Rectangle.h / .cpp         # Rectangle shape class
├── Circle.h / .cpp            # Circle shape class
├── FreehandStroke.h / .cpp    # Freehand drawing (brush/eraser) shape class
├── UndoRedoManager.h / .cpp   # Manages undo/redo history of drawn shapes
├── resources.qrc              # Resource file (icons, images)
├── INTERACTIVE_DRAWING_APP.pro  # Qt project configuration file
└── README.md                  # Project documentation (you’re reading it!)

---

## 🛠️ How to Build

### Prerequisites

- Qt 5 or 6 (Qt Creator is recommended)
- C++11 or later

### Steps

1. Clone this repository or download the source.
2. Open the `.pro` file in **Qt Creator**.
3. Click `Configure Project` and then `Build`.
4. Run the project from within Qt Creator.

---

## 📸 Screenshot

![qt_cs112_project2](https://github.com/user-attachments/assets/7b705961-6263-4a0d-b00c-0dc397826e25)


---

## 🧠 Known Issues

- No support for saving projects (only images can be saved).
- Undo/redo works only with recent drawing session (not persisted).

---

## 📌 TODO (Future Improvements)

- Add shape resizing and moving.
- Enable zoom and pan features.
- Improve file import/export handling.
- Add shortcut keys for tools and undo/redo.

---

## 🧑‍💻 Author

- **Your Name**
- GitHub: (https://github.com/hamnaaqamar)

---

## 📄 License

This project is open-source and available under the MIT License.
