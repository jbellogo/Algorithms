#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Solution {
public:
    string addBinaryINEFFICIENT(string a, string b) {
        cout << "REVERSING STRINGS" << endl;
        // reverse pointers
        int i = a.length() - 1;
        int j = b.length() -1;
        int carry = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || carry > 0){
            if(i >= 0){
                carry += (a[i] == '1') ? 1 : 0;;
            } 
            if(j >= 0){
                carry += (b[j] == '1') ? 1 : 0;
            } 

            int remainder = carry%2;
            carry/=2;

            ans  = to_string(remainder) + ans;
            cout << "ans: " << ans << endl;
            cout << "carry: " << carry << endl;
            i--;
            j--;
        }
        return ans;
    }

    string addBinary(string a, string b) {
        /* FINAL SOLUTION */
        int i = a.length() - 1;
        int j = b.length() -1;
        int carry = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || carry > 0){
            if(i >= 0){
                carry += (a[i] == '1') ? 1 : 0;;
            } 
            if(j >= 0){
                carry += (b[j] == '1') ? 1 : 0;
            } 

            int remainder = carry%2;
            carry/=2;

            ans  += remainder + '0';
            i--;
            j--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

};

void test0(Solution sol){
    string a = "11";
    string b = "1";
    string ans = sol.addBinary(a, b);
    cout << ans << endl;
    assert(ans == "100");
}

void test1(Solution sol){ 
    string a = "1010";
    string b = "1011";
    string ans = sol.addBinary(a, b);
    cout << ans << endl;
    assert(ans == "10101");
}

void test2(Solution sol){
    string a = "1111";
    string b = "1111";
    string ans = sol.addBinary(a, b);
    cout << ans << endl;
    assert(ans == "11110");
}
int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
    return 0;
}
    