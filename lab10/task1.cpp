#include <iostream>

using namespace std;

class Light {
public:
    void on() {
        cout << "Lights are on." << endl;
    }

    void off() {
        cout << "Lights are off." << endl;
    }
};

class Thermostat {
public:
    void setTemperature(const string& mode) {
        if (mode == "eco") {
            cout << "Thermostat is set to eco mode." << endl;
        } else if (mode == "comfort") {
            cout << "Thermostat is set to a comfortable temperature." << endl;
        }
    }
};

class SecurityCamera {
public:
    void activate() {
        cout << "Security cameras activated." << endl;
    }

    void deactivate() {
        cout << "Security cameras deactivated." << endl;
    }
};

class SmartHomeFacade {
    Light light;
    Thermostat thermostat;
    SecurityCamera securityCamera;

public:
    void leavingHome() {
        cout << "Activating 'Leaving Home' scenario..." << endl;
        light.off();
        thermostat.setTemperature("eco");
        securityCamera.activate();
    }

    void arrivingHome() {
        cout << "Activating 'Arriving Home' scenario..." << endl;
        light.on();
        thermostat.setTemperature("comfort");
        securityCamera.deactivate();
    }
};

int main() {
    SmartHomeFacade smartHome;
    cout << "Scenario: Leaving Home" << endl;
    smartHome.leavingHome();

    cout << "\nScenario: Arriving Home" << endl;
    smartHome.arrivingHome();

    return 0;
}