#include <iostream>
#include <string>

using namespace std;

class Document {
public:
    virtual void display() = 0;
    virtual ~Document() {}
};

class RealDocument : public Document {
private:
    string content;
public:
    RealDocument(const string& content) : content(content) {}
    void display() override {
        cout << "Displaying Document Content: " << content << endl;
    }
};

class SecureDocumentProxy : public Document {
private:
    RealDocument realDocument;
    string userRole;
public:
    SecureDocumentProxy(const string& content, const string& userRole)
            : realDocument(content), userRole(userRole) {}

    void display() override {
        if (userRole == "admin" || userRole == "manager") {
            realDocument.display();
        } else {
            cout << "Access Denied: You do not have permission to view this document." << endl;
        }
    }
};

int main() {
    string content = "Sensitive Document: Top Secret";

    SecureDocumentProxy documentForAdmin(content, "admin");
    SecureDocumentProxy documentForManager(content, "manager");
    SecureDocumentProxy documentForGuest(content, "guest");

    cout << "Admin Access:\n";
    documentForAdmin.display();

    cout << "\nManager Access:\n";
    documentForManager.display();

    cout << "\nGuest Access:\n";
    documentForGuest.display();

    return 0;
}