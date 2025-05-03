#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Memento {
public:
    Memento(const string& state) : state(state) {}
    string getState() const { return state; }
private:
    string state;
};

class TextEditor {
public:
    TextEditor() : text("") {}
    void appendText(const string& newText) { text += newText; }
    string getText() const { return text; }

    Memento save() const {
        return Memento(text);
    }

    void restore(const Memento& memento) {
        text = memento.getState();
    }
private:
    string text;
};

class UndoRedoManager {
public:
    UndoRedoManager() {}

    void saveState(TextEditor& editor) {
        undoStack.push(editor.save());
        while (!redoStack.empty()) {
            redoStack.pop();
        }
    }

    void undo(TextEditor& editor) {
        if (!undoStack.empty()) {
            redoStack.push(editor.save());
            editor.restore(undoStack.top());
            undoStack.pop();
        }
    }

    void redo(TextEditor& editor) {
        if (!redoStack.empty()) {
            undoStack.push(editor.save());
            editor.restore(redoStack.top());
            redoStack.pop();
        }
    }
private:
    stack<Memento> undoStack;
    stack<Memento> redoStack;
};

int main() {
    TextEditor editor;
    UndoRedoManager undoRedoManager;

    cout << "Initial text: " << editor.getText() << endl;

    editor.appendText("Hello");
    undoRedoManager.saveState(editor);
    cout << "After appending 'Hello': " << editor.getText() << endl;

    editor.appendText(" World");
    undoRedoManager.saveState(editor);
    cout << "After appending ' World': " << editor.getText() << endl;

    undoRedoManager.undo(editor);
    cout << "After undoing: " << editor.getText() << endl;

    undoRedoManager.redo(editor);
    cout << "After redoing: " << editor.getText() << endl;

    return 0;
}