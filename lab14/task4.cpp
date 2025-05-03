#include <iostream>
#include <memory>

using namespace std;

class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() = default;
};

class WinButton : public Button {
public:
    void render() override {
        cout << "Windows Button" << endl;
    }
};

class MacButton : public Button {
public:
    void render() override {
        cout << "Mac Button" << endl;
    }
};

class WinCheckbox : public Checkbox {
public:
    void render() override {
        cout << "Windows Checkbox" << endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        cout << "Mac Checkbox" << endl;
    }
};

class GUIFactory {
public:
    virtual unique_ptr<Button> createButton() = 0;
    virtual unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

class WinFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<WinButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<WinCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    unique_ptr<Button> createButton() override {
        return make_unique<MacButton>();
    }
    unique_ptr<Checkbox> createCheckbox() override {
        return make_unique<MacCheckbox>();
    }
};

void createUI(unique_ptr<GUIFactory> factory) {
    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();
    button->render();
    checkbox->render();
}

int main() {
    unique_ptr<GUIFactory> factory = make_unique<WinFactory>();
    createUI(move(factory));

    factory = make_unique<MacFactory>();
    createUI(move(factory));

    return 0;
}