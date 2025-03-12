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

    bool has(vector<vector<int>> &ans, vector<int> &u){
        // ans contains only sorted vectors. u is sorted also.
        for (auto &v : ans){
            // check if 1,2,3 is equal to 2,3,1
            if ( u == v) return true;
        }
        return false;
    }

    bool equal_set_of_vectors(vector<vector<int>> &v1, vector<vector<int>> &v2){
        if (v1.size() != v2.size()) return false;
        // check if v1 is a subset of v2
        for (auto &v : v1){
            if (!has(v2, v)) return false;
        }
        // check if v2 is a subset of v1
        for (auto &v : v2){
            if (!has(v1, v)) return false;
        }
        return true;
    }
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;


        // i < j < k will be ones indeces.
 for (int i = 0 ; i < n-2 ; i++){
            // add another guard
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            int j = i+1;
            int k = n-1;
            while ( j < k ){
                int sum = nums[i] + nums[j] + nums[k];
                if (sum > 0) {
                    k--;
                } else if (sum < 0){
                    j++;
                } else {
                    ans.push_back(vector<int>{nums[i], nums[j], nums[k]});
                    
                    // CHANGE THIS HERE!
                    j++;
                    while (nums[j] == nums[j-1] && j < k) j++;
                    while (k+1 < n && nums[k] == nums[k+1] && j < k) k--;


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
    assert(sol.has(ans, u1));
    assert(!sol.has(ans, u2));

    vector<vector<int>> ans2 = {{-2, 1, 1},{0,0,0},{-2,3,-1}};
    vector<int> u = {0,1,-1};
    assert(!sol.has(ans2, u));

}

void test_equal_set_of_vectors(Solution &sol){
    vector<vector<int>> ans1 = {{1,2,3},{3,5,1}};
    vector<vector<int>> ans2 = {{3,5,1}, {1,2,3}};
    assert(sol.equal_set_of_vectors(ans1, ans2));
}

void test1(Solution &sol){
    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> ans = sol.threeSum(nums);
    vector<vector<int>> expected = {{-1,-1,2}, {-1,0,1}};
    assert(sol.equal_set_of_vectors(ans, expected));
}

void test2(Solution &sol){
    vector<int> nums = {0,0,0,0};
    vector<vector<int>> ans = sol.threeSum(nums);
    vector<vector<int>> expected = {{0,0,0}};
    assert(sol.equal_set_of_vectors(ans, expected));
}

void test3(Solution &sol){
    cout << "------------test3------------" << endl;
    vector<int> nums = {3, -3, 0, 5, -2, 2, -5};
    vector<vector<int>> ans = sol.threeSum(nums);
    vector<vector<int>> expected = {{-3, 0, 3}, {-3, -2, 5}, {-2, 0, 2}, {-5, 0, 5}, {-5, 2, 3}};
    assert(sol.equal_set_of_vectors(ans, expected));
}

void test4(Solution &sol){
    vector<int> nums = {0,1,1};
    vector<vector<int>> ans = sol.threeSum(nums);
    vector<vector<int>> expected = {};
    assert(sol.equal_set_of_vectors(ans, expected));
}

void test5(Solution &sol){
    vector<int> nums = {-5,0,-2,3,-2,1,1,3,0,-5,3,3,0,-1};
    vector<vector<int>> ans = sol.threeSum(nums);
    vector<vector<int>> expected = {{-2,1,1},{0,0,0},{-2,-1,3},{-1,0,1}};
    assert(sol.equal_set_of_vectors(ans, expected));
}

void test6(Solution &sol){
    vector<int> nums = {0,0,0, -1, -1, -1, 1, 1, 1};
    vector<vector<int>> ans = sol.threeSum(nums);
    vector<vector<int>> expected = {{0,0,0}, {-1,0,1}};
    assert(sol.equal_set_of_vectors(ans, expected));
}

int main(){
    Solution sol;
    test_is_in_ans(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
}