// task 2: Write your own function for swapping values of two integers using:
//a) passing by pointer
//b) passing by reference
#include <iostream>

using namespace std;

void swapByPointer(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapByReference(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int main(){
    int x, y;
    cin >> x >> y;
    int x1, y1;//for using 2 functions
    x1 = x;
    y1 = y;
    swapByPointer(&x, &y);
    swapByReference(x1, y1);
    cout << "swapping by pointer: " << x << " " << y << endl;
    cout << "swapping by refence: " << x1 << " " << y1;
    return 0;
}