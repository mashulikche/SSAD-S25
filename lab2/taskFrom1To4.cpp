#include <iostream>
#include <algorithm>

using namespace std;

class Box {
    unsigned int length, width, height;
public:

    Box() : length(1), width(2), height(3) {}

    Box(const Box& other) :  length(other.length), width(other.width), height(other.height) {}

    Box(unsigned int a, unsigned int b, unsigned int c) : length(a), width(b), height(c) {}

    Box& operator=(const Box& other) {
        if (this != &other) {
            length = other.length;
            width = other.width;
            height = other.height;
        }
        return *this;
    }

    void display() const {
        cout << "Box dimensions: " << "Length = " << length << ", Width = " << width << ", Height = " << height << endl;
    }

    unsigned int getVolume() const {
        return length * width * height;
    }

    void scale(unsigned int scaleValue) {
        length *= scaleValue;
        width *= scaleValue;
        height *= scaleValue;
    }

    bool isBigger(const Box& other) const {
        return getVolume() > other.getVolume();
    }

    bool isSmaller(const Box& other) const {
        return getVolume() < other.getVolume();
    }

    Box operator*(unsigned int scaleValue) const {
        return Box(length * scaleValue, width * scaleValue, height * scaleValue);
    }

    bool operator==(const Box& other) const {
        unsigned int thisDimensions[3] = {length, width, height};
        unsigned int otherDimensions[3] = {other.length, other.width, other.height};

        std::sort(thisDimensions, thisDimensions + 3);
        std::sort(otherDimensions, otherDimensions + 3);

        return (thisDimensions[0] == otherDimensions[0] &&
                thisDimensions[1] == otherDimensions[1] &&
                thisDimensions[2] == otherDimensions[2]);
    }
};

class Cube {
private:
    unsigned int side;

public:
    Cube() : side(0) {}

    Cube(unsigned int s) : side(s) {}

    operator Box() const {
        return Box(side, side, side);
    }

    void display() const {
        std::cout << "Cube side length: " << side << std::endl;
    }
};



int main() {

    Cube cube(8);
    cube.display();

    Box boxFromCube = cube;
    boxFromCube.display();

    Box box2(5, 5, 5);
    box2.display();

    return 0;
}
