#include <vector>
using namespace std;
#include <cassert>
#include <iostream>

// Binary Search

int binarySearchIterative(vector<int> &nums, int target){
    // returns the position at which target is located. if it is not present, returns -1
    int n = nums.size();
    int left = 0, right = n-1;
    int search_indx = (right-left)/2;
    while(nums[search_indx] != target){
        int current  = nums[search_indx];
        if (abs(right-left)<3){
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
    if (nums[search_indx] == target){
        return search_indx;
    } else if (nums[left] == target){
        return left;
    } else if (nums[right] == target){
        return right;
    } 
    return -1;
}

int binarySearchRecursive(vector<int> &nums, int target, int left, int right){
    int mid = (right+left)/2;
    cout << "left: " << left << " right: " << right << " mid: " << mid << " nums[mid]: " << nums[mid] << endl;

    // base cases
    if (nums[mid] == target) {
        return mid;
    } else if (nums[left] == target){
        return left;
    } else if (nums[right] == target){
        return right;
    } else if (abs(right-left)<3){
        return -1;
    }

    // recursive cases
    if (nums[mid] < target){
        // look to the right side. 
        return binarySearchRecursive(nums, target, mid, right);
    } else {
        return binarySearchRecursive(nums, target, left, mid);
    }
    
}

void test1(){

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Test 1: target in nums
    int target = 5;
    int result_iterative = binarySearchIterative(nums, target);
    int result_recursive = binarySearchRecursive(nums, target, 0, nums.size()-1);
    
    assert(result_iterative == 4);
    assert(result_recursive == 4);
    cout << "Test 1 passed!" << endl;
    // Test 2: target not in nums
    target = 11;
    result_iterative = binarySearchIterative(nums, target);
    result_recursive = binarySearchRecursive(nums, target, 0, nums.size()-1);
    assert(result_iterative == -1);
    assert(result_recursive == -1);
    cout << "Test 2 passed!" << endl;
    // Test 3: target is first element
    target = 0;
    result_iterative = binarySearchIterative(nums, target);
    result_recursive = binarySearchRecursive(nums, target, 0, nums.size()-1);
    assert(result_iterative == -1);
    assert(result_recursive == -1);
    cout << "Test 3 passed!" << endl;

    // Test 4: target is last element
    target = 10;
    result_iterative = binarySearchIterative(nums, target);
    result_recursive = binarySearchRecursive(nums, target, 0, nums.size()-1);
    assert(result_iterative == 9);
    assert(result_recursive == 9);
    cout << "Test 4 passed!" << endl;

    // Test 5: target is in the middle
    target = 6;
    result_iterative = binarySearchIterative(nums, target);
    result_recursive = binarySearchRecursive(nums, target, 0, nums.size()-1);
    assert(result_iterative == 5);
    assert(result_recursive == 5);
    cout << "Test 5 passed!" << endl;
    
}

int main(){
    test1();
    cout << "All tests passed!" << endl;
}