//Write a program that accepts a number of elements (N) of the array of
//integers and then N elements. After user inserts the array, your program
//should remove all duplicates from it. You should solve this task using:
//a) arrays
//b) vectors
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void removeDuplicates(vector<int>& vec) {
   sort(vec.begin(), vec.end());
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
}

int main() {
    int N;
    cin >> N;
    vector<int> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    removeDuplicates(vec);
    for (const int& num : vec) {
        cout << num << " ";
    }
    return 0;
}
