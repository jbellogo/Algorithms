#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        int mod = numRows * 2 - 2;
        vector<string> rows(numRows, "");
        for (int i = 0; i < s.length() ; i++) {
            int remainder = i % mod;
            int row_index = (remainder >= numRows) ? (numRows - remainder) : remainder;
        } 
        
    }
};