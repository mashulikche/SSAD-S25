#include <iostream>
using namespace std;

class Animal {
protected:
    string name;
    int age;

public:
    Animal(const string &name, int age):
            name(name), age(age) {};
    virtual void makeSound() {
        cout << "Some sound" << endl;
    }
};

class landAnimal: public Animal {
public:
    landAnimal(const string &name, int age) : Animal(name, age) {}
    virtual void walk() {
        cout << "Land animal is walking" << endl;
    }
    void makeSound() override {
        cout << "land" << endl;
    }
};

class waterAnimal: public Animal {
public:
    waterAnimal(const string &name, int age) : Animal(name, age) {}
    virtual void swim() {
        cout << "Water animal is swimming" << endl;
    }
    void makeSound() override {
        cout << "water" << endl;
    }
};

class Lion: public landAnimal {
public:
    Lion(const string &name, int age) : landAnimal(name, age) {}
    void walk() override {
        cout << "Lion is walking" << endl;
    }
    void makeSound() override {
        cout << "RUAAR" << endl;
    }
};

class Dolphin: public waterAnimal {
public:
    Dolphin(const string &name, int age) : waterAnimal(name, age) {}
    void swim() override {
        cout << "Dolphin is swimming" << endl;
    }
    void makeSound() override {
        cout << "Whistle-whistle" << endl;
    }
};

class Frog: public landAnimal, public waterAnimal {
public:
    Frog(const string &name, int age) : landAnimal(name, age), waterAnimal(name, age) {}
    void walk() override {
        cout << "Frog is walking" << endl;
    }
    void swim() override {
        cout << "Frog is swimming" << endl;
    }
    void makeSound() override {
        cout << "Kva-kva" << endl;
    }
};

int main() {
    string lionName = "Dinno";
    Lion lion(lionName, 1);
    lion.walk();
    lion.makeSound();

    string dolphinName = "Mashulik";
    Dolphin dolphin(dolphinName, 2);
    dolphin.swim();
    dolphin.makeSound();

    string frogName = "Kvakushka";
    Frog frog(frogName, 3);
    frog.walk();
    frog.swim();
    frog.makeSound();

    return 0;
}



