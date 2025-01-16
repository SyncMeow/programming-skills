#include <iostream>
using namespace std;

void swap(int *a, int *b) {
    *a = (*a)^(*b);
    *b = (*a)^(*b);
    *a = (*a)^(*b);
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int min = INT32_MAX, idx = -1;
        for (int j = i; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                idx = j;
            }
        }
        if (i != idx) swap(arr+i, arr+idx);
    }
}

int main() {
    int arr[] = {1, 3, 7, 19, 8, 28, 23, 16, 4, 5};
    selectionSort(arr, 10);
    for (auto i: arr) cout << i << " ";
    cout << endl;
    return 0;
}