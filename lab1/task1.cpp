// task 1 : Write a program that accepts time period given in seconds and returns it
//in the following format: hours : minutes : seconds
#include <iostream>

using namespace std;

int main(){
   int n;
    cin >> n;
    cout << n / 3600 << ":" << n % 3600 / 60 << ":" << n % 60;
    return 0;
}
