#include <iostream>
#include <string>
#include <unordered_map>
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
    virtual void handle() = 0;
    virtual unique_ptr<DocumentState> clone() const = 0;
    virtual ~DocumentState() = default;
};

class DraftState : public DocumentState {
public:
    void handle() override {
        Logger::getInstance().log("Document is in Draft State");
    }

    unique_ptr<DocumentState> clone() const override {
        return make_unique<DraftState>(*this);
    }
};

class ReviewState : public DocumentState {
public:
    void handle() override {
        Logger::getInstance().log("Document is in Review State");
    }

    unique_ptr<DocumentState> clone() const override {
        return make_unique<ReviewState>(*this);
    }
};

class PublishedState : public DocumentState {
public:
    void handle() override {
        Logger::getInstance().log("Document is in Published State");
    }

    unique_ptr<DocumentState> clone() const override {
        return make_unique<PublishedState>(*this);
    }
};

class Document {
public:
    Document() : state(make_unique<DraftState>()) {}

    void setState(unique_ptr<DocumentState> newState) {
        state = move(newState);
    }

    void handleState() {
        state->handle();
    }

    unique_ptr<Document> clone() const {
        auto newDoc = make_unique<Document>();
        newDoc->state = state->clone();
        return newDoc;
    }

private:
    unique_ptr<DocumentState> state;
};

class DocumentPrototype {
public:
    void registerPrototype(const string& key, unique_ptr<Document> doc) {
        prototypes[key] = move(doc);
    }

    unique_ptr<Document> createDocument(const string& key) {
        if (prototypes.find(key) != prototypes.end()) {
            return prototypes[key]->clone();
        }
        return nullptr;
    }

private:
    unordered_map<string, unique_ptr<Document>> prototypes;
};

int main() {
    DocumentPrototype docPrototype;
    auto draftDoc = make_unique<Document>();
    docPrototype.registerPrototype("Draft", move(draftDoc));

    auto newDoc = docPrototype.createDocument("Draft");
    newDoc->handleState();

    newDoc->setState(make_unique<ReviewState>());
    newDoc->handleState();

    newDoc->setState(make_unique<PublishedState>());
    newDoc->handleState();

    return 0;
}