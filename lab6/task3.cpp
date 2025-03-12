//1.Implement a map Function
//- The map function takes a vector and a callback function as its parameters.
//- The callback function performs an operation on each element of the vector
//- It returns a new vector containing the results of applying the callback function
//        to each element in the original vector.
//2.Implement a filter Function
//- The filter function takes a vector and a callback function as its parameters.
//- The callback function for filter should be a predicate (returning a boolean
//value) that decides whether an element in the vector should be included in
//the result.
//- The filter function should return a new vector containing only those
//elements of the original vector for which the callback function returns true
//3. Test Your Functions
//- Demonstrate the use of your map and filter functions with at least two
//different lambda expressions for each function.
//- For map, you might use a lambda that squares each number.
//- For filter, you could use a lambda that filters out even numbers
#include <iostream>
#include <vector>

using namespace std;

vector<int> customMap(const vector<int>& vec, int (*func)(int)) {
    vector<int> result;
    for (int elem : vec) {
        result.push_back(func(elem));
    }
    return result;
}

vector<int> customFilter(const vector<int>& vec, bool (*pred)(int)) {
    vector<int> result;
    for (int elem : vec) {
        if (pred(elem)) {
            result.push_back(elem);
        }
    }
    return result;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};

    auto squared = customMap(nums, [](int x) { return x * x; });

    cout << "Squared: ";
    for (const auto& num : squared) {
        cout << num << " ";
    }
    cout << endl;

    auto odds = customFilter(nums, [](int x) { return x % 2 != 0; });

    cout << "Odd numbers: ";
    for (const auto& num : odds) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}