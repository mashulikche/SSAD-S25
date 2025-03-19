#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const string& message) {
        cout << "Log: " << message << endl;
    }

private:
    Logger() {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

class DocumentState {
public:
    virtual void handleInput(const string& input) = 0;
    virtual ~DocumentState() = default;
};

class DraftState : public DocumentState {
public:
    void handleInput(const string& input) override {
        Logger::getInstance().log("DraftState: Handling input - " + input);
    }
};

class ReviewState : public DocumentState {
public:
    void handleInput(const string& input) override {
        Logger::getInstance().log("ReviewState: Handling input - " + input);
    }
};

class FinalState : public DocumentState {
public:
    void handleInput(const string& input) override {
        Logger::getInstance().log("FinalState: Handling input - " + input);
    }
};

class Document {
public:
    Document() : state(make_unique<DraftState>()) {}

    void changeState(unique_ptr<DocumentState> newState) {
        state = move(newState);
        Logger::getInstance().log("Document state changed");
    }

    void handleInput(const string& input) {
        state->handleInput(input);
    }

private:
    unique_ptr<DocumentState> state;
};

int main() {
    Logger::getInstance().log("Application started");

    Document doc;
    doc.handleInput("First input in Draft State");

    doc.changeState(make_unique<ReviewState>());
    doc.handleInput("Second input in Review State");

    doc.changeState(make_unique<FinalState>());
    doc.handleInput("Third input in Final State");

    return 0;
}