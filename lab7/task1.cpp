#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class CircularBuffer {
private:
    vector<T> buffer;
    size_t capacity;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;

public:
    CircularBuffer(size_t size) : capacity(size) {
        buffer.resize(size);
    }

    void push(const T& value) {
        if (count == capacity) {
            throw overflow_error("Buffer is full");
        }
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        count++;
    }

    T pop() {
        if (count == 0) {
            throw underflow_error("Buffer is empty");
        }
        T value = buffer[head];
        head = (head + 1) % capacity;
        count--;
        return value;
    }

    bool empty() const {
        return count == 0;
    }

    size_t size() const {
        return count;
    }

    class Iterator {
    private:
        CircularBuffer& buffer;
        size_t index;
        size_t steps;

    public:
        Iterator(CircularBuffer& buf, size_t idx, size_t s = 0)
                : buffer(buf), index(idx), steps(s) {}

        T& operator*() {
            return buffer.buffer[index];
        }

        Iterator& operator++() {
            index = (index + 1) % buffer.capacity;
            steps++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return index == other.index && steps == other.steps;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };

    Iterator begin() {
        return Iterator(*this, head);
    }
    
    Iterator end() {
        return Iterator(*this, head, count);
    }
};

int main() {
    CircularBuffer<int> cb(5);

    cb.push(1);
    cb.push(2);
    cb.push(3);
    cb.push(4);
    cb.push(5);

    cout << "Popped: " << cb.pop() << endl;

    cb.push(6);

    cout << "Buffer contents: ";
    for (auto it = cb.begin(); it != cb.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}