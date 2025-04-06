// SLOW SOLUTION
// O(n^3) time complexity
// Exceeds time limit on LeetCode

#include <vector>
#include <iostream>
#include <cassert>
#include <set>

using namespace std;

void print_vector(vector<int> &v){
    for (auto &i : v){
        cout << i << " ";
    }
    cout << endl;
}

class Solution {
    
public:

    bool set_equal(vector<int> &u, vector<int> &v){
        sort(u.begin(), u.end());
        sort(v.begin(), v.end());
        return u == v;
    }

    bool is_in_ans(vector<vector<int>> &ans, vector<int> &u){
        // check if they are eual up to permutation to avoid adding duplicates (almost like IsInSet?)
        for (auto &v : ans){
            // check if 1,2,3 is equal to 2,3,1
            if (set_equal(u, v)) return true;
        }
        return false;
    }


    
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;

        // i3 is the third one index
        for (int i3 = 2; i3 < n; i3++){
            for (int i2 = 1; i2 < i3; i2++){
                for (int i1 = 0; i1 < i2; i1++){
                    if (nums[i1]+nums[i2]+nums[i3] == 0){
                        vector<int> u = {nums[i1], nums[i2], nums[i3]};
                        if (!is_in_ans(ans, u)){
                            ans.push_back(u);
                        }
                    }
                }
            }
        }
        return ans;
    }
};


void test_is_in_ans(Solution &sol){
    vector<vector<int>> ans = {{1,2,3},{3,5,1}};
    vector<int> u1 = {1,2,3};
    vector<int> u2 = {1,2,4};
    assert(sol.is_in_ans(ans, u1));
    assert(!sol.is_in_ans(ans, u2));

    vector<vector<int>> ans2 = {{-2, 1, 1},{0,0,0},{-2,3,-1}};
    vector<int> u = {0,1,-1};
    assert(!sol.is_in_ans(ans2, u));

}

void test1(Solution &sol){
    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> ans = sol.threeSum(nums);
    cout << "------ans: " << endl;
    assert(ans == vector<vector<int>>({{-1,0,1},{-1,-1,2}})); // only holds in this particualr order without having to convert to set
}

void test2(Solution &sol){
    vector<int> nums = {0,0,0,0};
    vector<vector<int>> ans = sol.threeSum(nums);
    assert(ans == vector<vector<int>>({{0,0,0}}));
}

void test3(Solution &sol){
    vector<int> nums = {3, -3, 0, 5, -2, 2, -5};
    vector<vector<int>> ans = sol.threeSum(nums);
    assert(ans == vector<vector<int>>({{-3, 0, 3}, {-3, -2, 5}, {-2, 0, 2}, {-5, 0, 5}, {-5, 2, 3}}));
}

void test4(Solution &sol){
    vector<int> nums = {0,1,1};
    vector<vector<int>> ans = sol.threeSum(nums);
    assert(ans == vector<vector<int>>({}));
}

void test5(Solution &sol){
    vector<int> nums = {-5,0,-2,3,-2,1,1,3,0,-5,3,3,0,-1};
    vector<vector<int>> ans = sol.threeSum(nums);
    cout << "------ans: " << endl;
    for (auto &v : ans){
        print_vector(v);
    }
    assert(ans == vector<vector<int>>({{-2,1,1},{0,0,0},{-2,-1,3},{-1,0,1}}));
}

int main(){
    Solution sol;
    test_is_in_ans(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
}