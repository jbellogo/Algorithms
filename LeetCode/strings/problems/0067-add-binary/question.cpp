#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        // reverse pointers
        int iA = a.length() - 1;
        int iB = b.length() -1;
        int carry = 0;
        string ans = "";
        while (iA >= 0 || iB >=0 || carry > 0){
            // cout << " ----------- " << endl;
            int amount = carry;
            // cout << "carry: " << carry << endl;

            if(iA >= 0){
                int val_a = a[iA] == '1' ? 1 : 0;
                amount += val_a;
                // cout << "a amount: " << a[iA] << endl;
            } 
            if(iB >= 0){
                int val_b = b[iB] == '1' ? 1 : 0;
                amount += val_b;
                // cout << "b amount: " << b[iB] << endl;
            } 
            // cout << "a + b + carry: " << amount << endl;

            carry = amount/2; 
            int remainder = amount%2;

            ans  = to_string(remainder) + ans;
            // cout << "remainder: " << remainder << endl;
            // cout << "ans: " << ans << endl;

            iA--;
            iB--;
        }
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
    