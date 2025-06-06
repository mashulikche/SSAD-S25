/*Implement a generic stack in C++ that can store elements of any data type. Use templates to achieve
generality and constructors for initialization. Extend the functionality through inheritance to customize the
stack for specific data types.
● Implement a class template named GenericStack that supports basic stack operations: push(), pop(), and peek().
● The push() method should insert an element at the top of the stack.
● The pop() method should remove and return the element at the top of the stack. If the stack is empty, it should
throw an exception or return a default value.
● The peek() method should return the element at the top of the stack without removing it. If the stack is empty, it
should throw an exception or return a default value.
● Include a constructor that initializes the stack's capacity. The stack should dynamically adjust its size as elements
are added.
● Ensure proper memory management to avoid leaks
 ● Create a subclass of GenericStack named StringStack that is specifically designed for handling strings.
● Override the push() method in StringStack to include a check that rejects empty strings (i.e., the method should
not allow pushing empty strings onto the stack).
● Add a new method concatTopTwo() in StringStack that pops the top two strings, concatenates them, and then
pushes the result back onto the stack. If there are not enough elements in the stack, throw an exception.
Instructions:
● Start by planning your implementation and sketching out the class structure.
● Implement the GenericStack class template, focusing on correctly handling generic data types with templates.
● After testing your GenericStack, proceed to implement the StringStack class, paying attention to how inheritance
can be used to extend and customize behavior.
● Include error handling for edge cases, such as popping from an empty stack or pushing invalid elements.
● Write a simple main function to demonstrate the functionality of your stack implementation, particularly
showcasing the features of the StringStack.*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <typename T>
class GenericStack {
private:
    vector<T> stack;
    size_t capacity;

public:
    GenericStack(size_t cap = 10) : capacity(cap) {
        stack.reserve(capacity);
    }

    void push(const T& element) {
        stack.push_back(element);
    }

    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty. Cannot pop.");
        }
        T topElement = stack.back();
        stack.pop_back();
        return topElement;
    }

    T peek() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty. Cannot peek.");
        }
        return stack.back();
    }

    bool isEmpty() const {
        return stack.empty();
    }

    size_t size() const {
        return stack.size();
    }
};

class StringStack : public GenericStack<string> {
public:

    StringStack(size_t cap = 10) : GenericStack<string>(cap) {}
    void push(const string& element) {
        if (element.empty()) {
            throw invalid_argument("Cannot push empty string onto the stack.");
        }
        GenericStack<string>::push(element);
    }

    void concatTopTwo() {
        if (size() < 2) {
            throw out_of_range("Not enough elements to concatenate.");
        }
        string first = pop();
        string second = pop();
        push(first + second);
    }
};

int main() {
    try {
        GenericStack<int> intStack;
        intStack.push(1);
        intStack.push(2);
        cout << "Top of int stack: " << intStack.peek() << endl;
        cout << "Popped from int stack: " << intStack.pop() << endl;

        StringStack stringStack;
        stringStack.push("Hello");
        stringStack.push("World");
        cout << "Top of string stack: " << stringStack.peek() << endl;

        stringStack.concatTopTwo();
        cout << "After concatenation, top of string stack: " << stringStack.peek() << endl;
        

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
