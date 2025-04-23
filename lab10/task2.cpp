#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Text {
public:
    virtual string write() const = 0;
    virtual ~Text() {}
};

class PlainText : public Text {
private:
    string text;
public:
    PlainText(const string& text) : text(text) {}
    string write() const override {
        return text;
    }
};

class TextDecorator : public Text {
protected:
    shared_ptr<Text> wrappedText;
public:
    TextDecorator(shared_ptr<Text> text) : wrappedText(text) {}
    virtual string write() const override {
        return wrappedText->write();
    }
};

class Bold : public TextDecorator {
public:
    Bold(shared_ptr<Text> text) : TextDecorator(text) {}
    string write() const override {
        
        return "\033[1m" + TextDecorator::write() + "\033[0m";
    }
};

class Italic : public TextDecorator {
public:
    Italic(shared_ptr<Text> text) : TextDecorator(text) {}
    string write() const override {
        return "\033[3m" + TextDecorator::write() + "\033[0m";
    }
};

class Underline : public TextDecorator {
public:
    Underline(shared_ptr<Text> text) : TextDecorator(text) {}
    string write() const override {
        return "\033[4m" + TextDecorator::write() + "\033[0m";
    }
};

int main() {
    shared_ptr<Text> plainText = make_shared<PlainText>("Hello, World!");

    shared_ptr<Text> boldText = make_shared<Bold>(plainText);
    shared_ptr<Text> italicBoldText = make_shared<Italic>(boldText);
    shared_ptr<Text> underlinedItalicBoldText = make_shared<Underline>(italicBoldText);

    cout << plainText->write() << endl;
    cout << boldText->write() << endl;
    cout << italicBoldText->write() << endl;
    cout << underlinedItalicBoldText->write() << endl;

    return 0;
}