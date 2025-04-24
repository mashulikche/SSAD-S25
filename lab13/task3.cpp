#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

using namespace std;

class File {
public:
    string path;
    File(const string& path) : path(path) {}
};

class EventListener {
public:
    virtual ~EventListener() = default;
    virtual void update(const string& eventType, const File& file) = 0;
};

class EventManager {
private:
    map<string, vector<EventListener*>> listeners;

public:
    EventManager(const vector<string>& operations) {
        for (const auto& op : operations) {
            listeners[op] = vector<EventListener*>();
        }
    }

    void subscribe(const string& eventType, EventListener* listener) {
        if (listeners.find(eventType) != listeners.end()) {
            listeners[eventType].push_back(listener);
        }
    }

    void unsubscribe(const string& eventType, EventListener* listener) {
        auto it = listeners.find(eventType);
        if (it != listeners.end()) {
            auto& vec = it->second;
            vec.erase(remove(vec.begin(), vec.end(), listener), vec.end());
        }
    }

    void notify(const string& eventType, const File& file) {
        auto it = listeners.find(eventType);
        if (it != listeners.end()) {
            for (auto listener : it->second) {
                listener->update(eventType, file);
            }
        }
    }
};

class Editor {
public:
    unique_ptr<EventManager> events;
    unique_ptr<File> file;

    Editor() {
        events = make_unique<EventManager>(vector<string>{"open", "save"});
    }

    void openFile(const string& filePath) {
        file = make_unique<File>(filePath);
        events->notify("open", *file);
        cout << "Opened file: " << file->path << endl;
    }

    void saveFile() {
        if (!file) {
            cerr << "No file is open!" << endl;
            return;
        }
        cout << "Saving file: " << file->path << endl;
        events->notify("save", *file);
    }
};

class LoggingListener : public EventListener {
private:
    string logFileName;

public:
    LoggingListener(const string& filename) : logFileName(filename) {}
    ~LoggingListener() override { cout << "LoggingListener destroyed" << endl; }

    void update(const string& eventType, const File& file) override {
        cout << "[" << logFileName << "] "
             << "File operation: " << eventType
             << " on " << file.path << endl;
    }
};

class EmailNotificationListener : public EventListener {
private:
    string email;

public:
    EmailNotificationListener(const string& email) : email(email) {}
    ~EmailNotificationListener() override { cout << "EmailListener destroyed" << endl; }

    void update(const string& eventType, const File& file) override {
        cout << "Email to " << email << ": "
             << "File " << file.path
             << " was " << eventType << "ed" << endl;
    }
};

int main() {
    Editor editor;

    LoggingListener logger("file_ops.log");
    EmailNotificationListener emailAlert("admin@example.com");


    editor.events->subscribe("open", &logger);
    editor.events->subscribe("save", &logger);
    editor.events->subscribe("save", &emailAlert);

    cout << "--- Opening test.txt ---" << endl;
    editor.openFile("test.txt");

    cout << "\n--- Saving test.txt ---" << endl;
    editor.saveFile();

    cout << "\n--- Unsubscribing email alerts ---" << endl;
    editor.events->unsubscribe("save", &emailAlert);

    cout << "\n--- Opening data.csv ---" << endl;
    editor.openFile("data.csv");

    return 0;
}