/*Understand and apply smart pointers in C++ (unique_ptr, shared_ptr, weak_ptr) to manage resources
automatically and solve common memory management problems.
● Create class Box: The class should have integer value with a constructor and a destructor.
● Understanding unique_ptr: Implement a function create_unique() that dynamically allocates a Box with a given
value and returns int which is the value inside Box. Demonstrate transferring ownership of the unique_ptr to
another unique_ptr and the automatic deallocation of resources.
● Exploring shared_ptr: Implement a function create_shared_boxes() that creates two shared_ptr<Box> pointing
to different Box instances and demonstrates shared ownership. Show how the reference count changes when
new shared_ptr instances are created or destroyed.
● Working with weak_ptr: Extend the Box class usage by introducing a weak_ptr<Box>. Demonstrate how to
check if a weak_ptr points to an object (i.e., if the object is still alive) and how to convert a weak_ptr to a
shared_ptr to access the object. Explain the use case of weak_ptr to solve the problem of circular references.
 Instructions:
● Implement each part of the task sequentially, testing your understanding of how each smart pointer
type works and their respective use cases.
● Pay attention to the mechanics of ownership transfer, especially how unique_ptr cannot be copied but
can be moved.
● For shared_ptr, observe how the reference count mechanism prevents premature deallocation and
how it automatically cleans up when no more shared_ptr instances point to the object.
● Use weak_ptr to access resources without taking ownership and demonstrate how it helps in managing
circular references by breaking dependency cycles.*/
#include <iostream>
#include <memory>

using namespace std;

class Box {
public:
    int value;

    Box(int val) : value(val) {
        cout << "Box created with value: " << value << endl;
    }

    ~Box() {
        cout << "Box with value " << value << " destroyed." << endl;
    }
};

unique_ptr<Box> create_unique(int value) {
    unique_ptr<Box> boxPtr = make_unique<Box>(value);
    return boxPtr; 
}

void demonstrate_unique_ptr() {
    unique_ptr<Box> box1 = create_unique(5);
    cout << "Value in unique_ptr: " << box1->value << endl;

    unique_ptr<Box> box2 = move(box1);
    if (box1) {
        cout << "box1 is still valid." << endl;
    } else {
        cout << "box1 is now null after transfer." << endl;
    }
    cout << "Value in transferred unique_ptr: " << box2->value << endl;
} 

void create_shared_boxes() {
    shared_ptr<Box> box1 = make_shared<Box>(10);
    shared_ptr<Box> box2 = make_shared<Box>(20);

    cout << "Box1 value: " << box1->value << ", Reference count: " << box1.use_count() << endl;
    cout << "Box2 value: " << box2->value << ", Reference count: " << box2.use_count() << endl;

    shared_ptr<Box> box3 = box1;
    cout << "Box1 value: " << box1->value << ", Reference count after sharing: " << box1.use_count() << endl;

}

void demonstrate_weak_ptr() {
    shared_ptr<Box> sharedBox = make_shared<Box>(30);
    weak_ptr<Box> weakBox = sharedBox; 

    cout << "Shared Box value: " << sharedBox->value << endl;
    cout << "Weak Box expired: " << weakBox.expired() << endl;

    if (auto lockedBox = weakBox.lock()) {
        cout << "Weak Box value: " << lockedBox->value << endl;
    } else {
        cout << "Weak Box is expired." << endl;
    }

    sharedBox.reset();
    cout << "Shared Box reset." << endl;

    if (weakBox.expired()) {
        cout << "Weak Box expired after shared Box reset." << endl;
    }
}

int main() {
    cout << "Demonstrating unique_ptr:" << endl;
    demonstrate_unique_ptr();

    cout << "\nDemonstrating shared_ptr:" << endl;
    create_shared_boxes();

    cout << "\nDemonstrating weak_ptr:" << endl;
    demonstrate_weak_ptr();

    return 0;
}