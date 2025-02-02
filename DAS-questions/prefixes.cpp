// Leetcode 14
// Very optimal solution!!!!


// Write a function to find the longest common prefix string amongst an array of strings.

// If there is no common prefix, return an empty string "".
 
// Example 1:
// Input: strs = ["flower","flow","flight"]
// Output: "fl"

// Example 2:
// Input: strs = ["dog","racecar","car"]
// Output: ""
 
// Constraints:

// 1 <= strs.length <= 200
// 0 <= strs[i].length <= 200
// strs[i] consists of only lowercase English letters if it is non-empty.


#include <string>
#include <limits.h>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:

    int find_min_size(vector<string>& strs){
        int min_size = INT_MAX;
        for (string &str : strs){
            if (str.size() < min_size){
                min_size = str.size();
            }
        }
        return min_size;
    }

    string longestCommonPrefix(vector<string>& strs) {
        int min_size = find_min_size(strs);
        // chech charachter by character
        string common_prefix = "";
        for (int indx = 0; indx < min_size; indx++){
            char current_char = '\0';
            bool current_char_is_prefix = true;
            for (string &word : strs){
                if (current_char == '\0'){
                    current_char = word[indx];
                } else if (current_char != word[indx]){
                    current_char_is_prefix = false;
                    break;
                }
            }
            if (current_char_is_prefix){
                common_prefix += current_char;
            }
            else{
                return common_prefix;
            }
        }
        return common_prefix;
    }
};


int main(){
    Solution sol;
    vector<string> strs{"flower","flow","flight"};
    assert("fl" == sol.longestCommonPrefix(strs));
    vector<string> strs2{"dog","racecar","car"};
    assert("" == sol.longestCommonPrefix(strs2));
    vector<string> strs3{""};
    assert("" == sol.longestCommonPrefix(strs3));
    vector<string> strs4{"archaeology", "archery", "archival", "archivist"};
    assert("arch" == sol.longestCommonPrefix(strs4));
    return 0;
}