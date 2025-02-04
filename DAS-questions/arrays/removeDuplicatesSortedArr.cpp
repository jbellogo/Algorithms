#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // nums is sorted in non-decreasing order
        // Approach: keep a second array and then overwrite nums with the contests of ans
        vector<int> ans;
        int current_element = nums[0];
        ans.push_back(current_element);
        for (int i = 1; i < nums.size(); i++){
            if (nums[i]!=current_element){
                ans.push_back(nums[i]);
                current_element = nums[i];
            } // else do nothing
        }
        // ans has unique elements, now overwrite them onto nums
        for (int i = 0 ; i < ans.size(); i++){
            nums[i] = ans[i];
        }
        return ans.size();
    }
};


int main() {
    Solution sol;
    vector<int> nums = {0,0,0,1,1,1,2,3,3,3,3,3,3,3,4,4,4}; // Input array
    vector<int> expectedNums = {0,1,2,3,4}; // The expected answer with correct length
    int k = sol.removeDuplicates(nums); // Calls your implementation
    assert(k == expectedNums.size());
    for (int i = 0; i < k; i++) {
        assert(nums[i] == expectedNums[i]);
    }

    

}
