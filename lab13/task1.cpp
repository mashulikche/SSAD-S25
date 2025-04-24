#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Command {
public:
    virtual ~Command() {}
    virtual bool execute() = 0;
    virtual void undo() = 0;
};

class TextEditor {
private:
    string text;
    string clipboard;

public:
    void addText(const string& newText) {
        text += newText;
    }

    void replaceText(const string& newText) {
        text = newText;
    }

    string getText() const {
        return text;
    }

    void setClipboard(const string& text) {
        clipboard = text;
    }

    string getClipboard() const {
        return clipboard;
    }
};

class CopyCommand : public Command {
private:
    TextEditor* editor;
    string backup;

public:
    CopyCommand(TextEditor* editor) : editor(editor) {}

    bool execute() override {
        backup = editor->getClipboard();
        editor->setClipboard(editor->getText());
        return true;
    }

    void undo() override {
        editor->setClipboard(backup);
    }
};

class PasteCommand : public Command {
private:
    TextEditor* editor;
    string backup;

public:
    PasteCommand(TextEditor* editor) : editor(editor) {}

    bool execute() override {
        backup = editor->getText();
        string clipboardContent = editor->getClipboard();
        editor->replaceText(backup + clipboardContent);
        return true;
    }

    void undo() override {
        editor->replaceText(backup);
    }
};

class CommandHistory {
private:
    vector<unique_ptr<Command>> history;

public:
    void push(Command* cmd) {
        history.emplace_back(cmd);
    }

    Command* pop() {
        if (history.empty()) return nullptr;
        auto cmd = history.back().release();
        history.pop_back();
        return cmd;
    }

    bool isEmpty() const {
        return history.empty();
    }
};

int main() {
    TextEditor editor;
    CommandHistory history;

    cout << "Enter text: ";
    string input;
    getline(cin, input);
    editor.addText(input);

    Command* copy = new CopyCommand(&editor);
    Command* paste = new PasteCommand(&editor);

    copy->execute();
    paste->execute();
    history.push(copy);
    history.push(paste);

    cout << "Current text: " << editor.getText() << endl;

    if (!history.isEmpty()) {
        Command* cmd = history.pop();
        cmd->undo();
        delete cmd;
        cout << "Text after undo: " << editor.getText() << endl;
    }

    while (!history.isEmpty()) {
        delete history.pop();
    }

    return 0;
}