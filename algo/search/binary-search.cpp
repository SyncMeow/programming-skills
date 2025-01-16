#include <iostream>
using namespace std;

int binarySearch(int arr[], int n, int target) {
    int l = 0, r = n-1;
    while(l <= r) {
        int mid = l + (r-l)/2;
        if (target < arr[mid]) r = mid-1;
        else if (target == arr[mid]) return mid;
        else l = mid+1;
    }
    return -1;
}

int main() {
    int arr[] = {1, 3, 4, 7, 15, 19, 21, 22, 23, 28, 41, 45, 151};
    int target = -1;

    int idx = binarySearch(arr, sizeof(arr)/ sizeof(int), target);

    cout << idx << endl;
    return 0;
}