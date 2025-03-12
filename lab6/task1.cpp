//Create a class template called Wrapper that wraps a single value of
//any type. Implement a member function called getValue() that
//        returns the wrapped value.
//● However, explicitly specialize this template for the char* type and
//provide a custom implementation for the getValue() function that
//returns the length of the string instead.
#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class Wrapper {
private:
    T value;

public:
    Wrapper(T val) : value(val) {}

    T getValue() const {
        return value;
    }
};
template <>
class Wrapper<const char*> {
private:
    const char* value;

public:
    Wrapper(const char* val) : value(val) {}
    int getValue() const {
        return strlen(value);
    }
};

int main() {
    Wrapper<int> intWrapper(52);
    cout << "Wrapped int value: " << intWrapper.getValue() << endl;

    Wrapper<const char*> strWrapper("I love C++");
    cout << "Length of wrapped string: " << strWrapper.getValue() << endl;

    return 0;
}
