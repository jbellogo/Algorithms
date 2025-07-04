#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>
using namespace std;


class Solution {
public:
    string longestOddPalindrome(string s) {
        int n = s.length();
        unordered_map <char, int> max_palindrome; 
        // if (n<3 && s!="") return s[0];

        for (int i = 1; i < n-1; i++){
            // try to put i at the center of palindrome
            for (int j = 1; i+j< n && i-j > 0 ; j++){
                if (s[i+j] == s[i-j]) {

                }
            }
        }


        
    }
};