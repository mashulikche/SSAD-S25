#include <iostream>
#include <string>

using namespace std;

class Handler {
public:
    virtual ~Handler() {}
    virtual Handler* setNext(Handler* nextHandler) = 0;
    virtual bool handle(const string& request) = 0;
};

class AbstractHandler : public Handler {
private:
    Handler* nextHandler;

public:
    AbstractHandler() : nextHandler(nullptr) {}

    Handler* setNext(Handler* nextHandler) override {
        this->nextHandler = nextHandler;
        return nextHandler;
    }

    bool handle(const string& request) override {
        if (nextHandler) {
            return nextHandler->handle(request);
        }
        return true;
    }
};

class AuthenticationHandler : public AbstractHandler {
public:
    bool handle(const string& request) override {
        if (request == "invalid") {
            cout << "Authentication failed: Invalid credentials." << endl;
            return false;
        }
        cout << "Authentication successful." << endl;
        return AbstractHandler::handle(request);
    }
};

class RoleCheckHandler : public AbstractHandler {
public:
    bool handle(const string& request) override {
        if (request == "admin") {
            cout << "Role check: Admin privileges granted." << endl;
            return true;
        }
        else if (request == "valid") {
            cout << "Role check: User has standard privileges." << endl;
            return AbstractHandler::handle(request);
        }
        cout << "Role check failed: Unknown role." << endl;
        return false;
    }
};

void processRequest(const string& request, Handler* handler) {
    cout << "Processing: " << request << endl;
    if (!handler->handle(request)) {
        cout << "Request denied.\n" << endl;
    } else {
        cout << "Request approved.\n" << endl;
    }
}

int main() {
    Handler* roleCheck = new RoleCheckHandler();
    Handler* auth = new AuthenticationHandler();

    auth->setNext(roleCheck);

    processRequest("valid", auth);
    processRequest("invalid", auth);
    processRequest("admin", auth);

    delete auth;
    delete roleCheck;

    return 0;
}