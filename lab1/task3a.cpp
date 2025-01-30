//Write a program that accepts a number of elements (N) of the array of
//integers and then N elements. After user inserts the array, your program
//should remove all duplicates from it. You should solve this task using:
//a) arrays
//b) vectors
#include <iostream>

using namespace std;
void removeDuplicates ( int arr[], int& n){
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            if (arr[i] = arr[j]){
                for (int k =j; k < n - 1; k++){
                    arr[k] = arr[k + 1];
                }
                n--;
                j--;
            }
        }
    }
}
int main(){
     int n;
     cin >> n;
     int arr[n];
     for (int i = 0; i < n; i++){
         cin >> arr[i];
     }
    removeDuplicates(arr, n);
     for (int i = 0; i < n; i++){
         cout << arr[i] << " ";
     }
}