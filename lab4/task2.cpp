#include <iostream>
#include <cmath>

using namespace std;

class Shape {
public:
    virtual double area() const = 0; 
    virtual double perimeter() const = 0; 
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};

int main() {
    Rectangle rectangle(5.0, 3.0);
    Circle circle(4.0);
    Shape* shape = &rectangle;

    // [1] Demonstrate static casting
    const Shape* shapePtr = &rectangle;
    const Rectangle* rectPtr = static_cast<const Rectangle*>(shapePtr);
    cout << "Rectangle Area: " << rectPtr->area() << endl;
    cout << "Rectangle Perimeter: " << rectPtr->perimeter() << endl;

    // [2] Demonstrate dynamic casting
    shape = &circle;
    if (Circle* circlePtr = dynamic_cast<Circle*>(shape)) {
        cout << "shape is a Circle" << endl;
    } else {
        cout << "shape is not a Circle" << endl;
    }

    // [3] Demonstrate const casting
    const Rectangle* constRectPtr = &rectangle;
    Rectangle* nonConstRectPtr = const_cast<Rectangle*>(constRectPtr);
    cout << "Rectangle Area after const cast: " << nonConstRectPtr->area() << endl;

    // [4] Demonstrate reinterpret casting
    int intValue = 42;
    double* doublePtr = reinterpret_cast<double*>(&intValue);
    cout << "Reinterpreted double value: " << *doublePtr << endl;

    return 0;
}