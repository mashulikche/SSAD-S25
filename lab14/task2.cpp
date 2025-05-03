#include <string>
#include <vector>
#include <iostream>

using namespace std;

class SmartHouseMediator;

class Device {
public:
    virtual void sendMessage(const string& message) = 0;
    virtual void receiveMessage(const string& message) = 0;
    virtual void setMediator(SmartHouseMediator* mediator) = 0;
    virtual ~Device() = default;
};

class SmartHouseMediator {
public:
    void addDevice(Device* device) {
        devices.push_back(device);
        device->setMediator(this);
    }

    void mediate(Device* sender, const string& message) {
        for (auto device : devices) {
            if (device != sender) {
                device->receiveMessage(message);
            }
        }
    }

private:
    vector<Device*> devices;
};

class MotionSensor : public Device {
public:
    void sendMessage(const string& message) override {
        if (mediator) {
            mediator->mediate(this, message);
        }
    }

    void receiveMessage(const string& message) override {
        cout << "MotionSensor received a " << message
             << ", the owner will be notified that they expect a visitor\n";
    }

    void setMediator(SmartHouseMediator* med) override {
        mediator = med;
    }

private:
    SmartHouseMediator* mediator = nullptr;
};

class TemperatureSensor : public Device {
public:
    void sendMessage(const string& message) override {
        if (mediator) {
            mediator->mediate(this, message);
        }
    }

    void receiveMessage(const string& message) override {
        cout << "TemperatureSensor received a " << message
             << ", the room temperature will be adjusted\n";
    }

    void setMediator(SmartHouseMediator* med) override {
        mediator = med;
    }

private:
    SmartHouseMediator* mediator = nullptr;
};

int main() {
    SmartHouseMediator mediator;
    MotionSensor motion;
    TemperatureSensor temp;

    mediator.addDevice(&motion);
    mediator.addDevice(&temp);

    motion.sendMessage("Motion detected");

    return 0;
}