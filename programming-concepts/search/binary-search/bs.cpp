#include <vector>
using namespace std;
#include <cassert>
#include <iostream>

// Binary Search

int binarySearch(vector<int> &nums, int target){
    // returns the position at which target is located. if it is not present, returns -1
    int n = nums.size();
    int left = 0, right = n-1;
    int search_indx = n/2;
    while(nums[search_indx]!= target){
        int current  = nums[search_indx];
        if (abs(right-left)<2){
            break;
        }
        if (current < target){
            // look to the right
            left = search_indx;
        } else if (current > target){
            // look to the left
            right = search_indx;
        } else {
            return search_indx;
        }
        search_indx = (right+left)/2;
    }
    return -1;
}

void test1(){
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target = 5;
    int result = binarySearch(nums, target);
    assert(result == 4);
}

int main(){
    test1();
    cout << "All tests passed!" << endl;
}