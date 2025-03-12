//Implement a class template called Dictionary that stores pairs of keys and
//        values that can be of different types. It should have the following member
//functions:
//● get(K key) returns the value for the given key
//● put(K key, V value) inserts the pair (key, value) to the dictionary
//● remove(K key) removes the pair with the given key
//● size() returns the number of elements in the dictionary
//Finally, write a main function that demonstrates how your solution works.
//Write partial specialization for the previous class template (Dictionary)
//that will be used only when the value type is int, i.e. <K, int>.
//In case of this specialization, member function get(K key) should return
//the absolute value of the value with the given key instead of value itself.
//Moreover, member function size() should not return the number of
//        elements in the dictionary but sum of all values in the dictionary.
#include <iostream>
#include <unordered_map>
#include <cmath> 

using namespace std;

template <typename K, typename V>
class Dictionary {
private:
    unordered_map<K, V> data;

public:
    
    V get(K key) {
        return data.at(key); 
    }

    void put(K key, V value) {
        data[key] = value;
    }
    
    void remove(K key) {
        data.erase(key);
    }

    size_t size() {
        return data.size();
    }
};

template <typename K>
class Dictionary<K, int> {
private:

    unordered_map<K, int> data;

public:
    
    int get(K key) {
        return abs(data.at(key)); 
    }

    void put(K key, int value) {
        data[key] = value;
    }

    void remove(K key) {
        data.erase(key);
    }

    int size() {
        int sum = 0;
        for (const auto& pair : data) {
            sum += pair.second;
        }
        return sum;
    }
};

int main() {
    
    Dictionary<string, double> myDict;
    myDict.put("pi", 3.14);
    myDict.put("e", 2.71);
    cout << "Value for 'pi': " << myDict.get("pi") << endl;
    cout << "Dictionary size: " << myDict.size() << endl;

    Dictionary<string, int> intDict;
    intDict.put("a", -5);
    intDict.put("b", 3);
    intDict.put("c", 10);

    cout << "Absolute value for 'a': " << intDict.get("a") << endl;
    cout << "Sum of values in intDict: " << intDict.size() << endl;

    return 0;
}
