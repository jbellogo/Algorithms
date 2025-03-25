#include <string>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;


class Solution {
public:

    string convert(string s, int numRows) {
        int mod = (numRows == 1) ? 1 : numRows * 2 - 2;
        vector<string> rows(numRows, "");
        cout << "mod: " << mod << ", numRows: " << numRows << endl;
        for (int i = 0; i < s.length() ; i++) {
            int remainder = i % mod;
            int row_index = (remainder >= numRows) ? (mod - remainder) : remainder;
            cout << "remainder: " << remainder << ", char: " << s[i] << ", row_index: " << row_index << endl;
            rows[row_index]+= s[i]; // add the charachter to the row it belongs to. 
        } 

        // append zigzag rows for final answer
        string ans = "";
        for (string &str : rows){
            cout << str << endl;
            ans+=str;
        }
        return ans;
    }
};

void test0(Solution &sol){
    string s = "PAYPALISHIRING";
    int numRows = 3;
    string ans = sol.convert(s, numRows);
    cout << ans << endl;
    assert(ans == "PAHNAPLSIIGYIR");
}

void test1(Solution &sol){
    string s = "PAYPALISHIRING";
    int numRows = 4;
    string ans = sol.convert(s, numRows);
    cout << ans << endl;
    assert(ans == "PINALSIGYAHRPI");
}

void test2(Solution &sol){
    string s = "A";
    int numRows = 1;
    string ans = sol.convert(s, numRows);
    assert(ans == "A");
}

void test3(Solution &sol){
    string s = "AB";
    int numRows = 1;
    string ans = sol.convert(s, numRows);
    assert(ans == "AB");
}

void test4(Solution &sol){
    string s = "ABCD";
    int numRows = 2;
    string ans = sol.convert(s, numRows);
    cout << ans << endl;
    assert(ans == "ACBD");
}

int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
}