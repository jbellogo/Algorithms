#include <iostream>
#include <vector>

using namespace std;

// This was my initial attempt at the problem. 
// It does not give all 3 element subsets of nums!!
// Works by shifting ones 
// here are the 12/20 permutations it does compute for n = 6
// third one
// 1 1 1 0 0 0 
// 1 1 0 1 0 0 
// 1 1 0 0 1 0 
// 1 1 0 0 0 1 
// second one  
// 1 1 0 0 0 1 
// 1 0 1 0 0 1 
// 1 0 0 1 0 1 
// 1 0 0 0 1 1 
// first one
// 1 0 0 0 1 1 
// 0 1 0 0 1 1 
// 0 0 1 0 1 1 
// 0 0 0 1 1 1 

void print_vector(vector<int> &v){
    for (auto &x : v){
        cout << x << " ";
    }
    cout << endl;
}

class Solution {
    
public:
    vector<int> get_initial_permut(int n){
        vector<int> permut(3,1); //[1,1,1]
        for (int i = 3; i < n; i++){
            permut.push_back(0);
        }
        return permut;
    }

    bool subset_adds_up(vector<int> &nums, int loc1, int loc2, int loc3){
        return (nums[loc1] + nums[loc2] + nums[loc3] == 0);
    }


    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> permut = get_initial_permut(n);

        int first_one_pos = 0;
        int second_one_pos = 1;
        int third_one_pos = 2;

        cout << "third one" << endl;
        while(third_one_pos < n){
            print_vector(permut);
            if (subset_adds_up(nums, first_one_pos, second_one_pos, third_one_pos)){
                ans.push_back(vector<int>({nums[first_one_pos], nums[second_one_pos], nums[third_one_pos]}));
            }
            if (third_one_pos == n-1){
                break; // don't want to set it to zero
            }
            permut[third_one_pos] = 0;
            third_one_pos++;
            permut[third_one_pos] = 1;
        }
        cout << "second one" << endl;
        while(second_one_pos < n-1){
            print_vector(permut);
            if (subset_adds_up(nums, first_one_pos, second_one_pos, third_one_pos)){
                ans.push_back(vector<int>({nums[first_one_pos], nums[second_one_pos], nums[third_one_pos]}));
            }
            if (second_one_pos == n-2){
                break;
            }
            permut[second_one_pos] = 0;
            second_one_pos++;
            permut[second_one_pos] = 1;
        }
        cout << "first one" << endl;
        while(first_one_pos < n-2){
            print_vector(permut);
            if (subset_adds_up(nums, first_one_pos, second_one_pos, third_one_pos)){
                ans.push_back(vector<int>({nums[first_one_pos], nums[second_one_pos], nums[third_one_pos]}));
            }
            if (first_one_pos == n-3){
                break;
            }
            permut[first_one_pos] = 0;
            first_one_pos++;
            permut[first_one_pos] = 1;
        }
        return ans;
    }
};
