// Classic set up for binary search 
// to achieve O(log n) we cannot iterate through the array,  that would be O(n), 
// so search domain in halg at each iteration. 

// SPECS:
// Given a sorted array of distinct integers and a target value, 
// return the index if the target is found. If not, 
// return the index where it would be if it were inserted in order.
// You must write an algorithm with O(log n) runtime complexity.
#include <vector>
#include <cassert>
#include <iostream>
using namespace std;


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        // nums is sorted.
        int high_bound = nums.size();
        int low_bound = 0;
        int search_indx = nums.size()/2;
        cout << endl;
        cout << "TARGET: " << target << endl;
        while (true){
            cout << "low_bound: " << low_bound << ", search_index: " << search_indx;
            cout << ", high_bound: "<< high_bound <<  endl; 

            if (high_bound - low_bound <= 2){
                // Get specific.
                // Necessary to not stay in a permanent loop.
                // You could clean it up but this is the math/proof way of seing there are 4 possible intervals between 3 bounds.
                if (target <= nums[low_bound]){
                    search_indx = low_bound;
                } else if (target <= nums[search_indx]){
                    break;
                } else if (target <= nums[high_bound]){
                    search_indx = high_bound;
                } else {
                    search_indx = high_bound;
                }
                break;
            }
            if (target == nums[search_indx]){
                return search_indx;
            } else if (target < nums[search_indx]){
                high_bound = search_indx;
            } else {
                low_bound = search_indx;
            }
            search_indx = (high_bound+low_bound)/2; // NEEDS TO BE average, not difference!!

           
        }
        cout << search_indx << endl;
        return search_indx; // gotta test this
    }
};


int main(){
    vector<int> nums = {1,3,5,6};
    Solution s;
    assert(s.searchInsert(nums, 5) == 2);
    assert(s.searchInsert(nums, 2) == 1);
    assert(s.searchInsert(nums, 7) == 4);
    assert(s.searchInsert(nums, 0) == 0);
    assert(s.searchInsert(nums, 4) == 2);





}
