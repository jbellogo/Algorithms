// bubble sort 
#include<vector>

using namespace std;

class Solution {
    // In increasing order, from smallest to largest.
    void bubbleSort(vector<int> &arr){
        bool isSorted = false;
        int lastUnsorted = arr.size()-1;
        while(!isSorted) {
            isSorted = true;
            for (int i = 0; i < lastUnsorted; i++){
                if (arr[i] > arr[i+1]){
                    swap(arr, i, i+1);
                    isSorted = false;
                }

            }
            lastUnsorted--; // maximums are guaranteed to get sorted one by one after each iteration
        }


    }

    void swap(vector<int> &a, int i, int j){
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
};


