#include <vector>
#include <iostream>
#include <cassert>
#include <stack>

using namespace std;


class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        stack<int> s;
        vector<int> ans;
        int remainder = 1;
        int quotient = 0;

        for (int i = digits.size()-1; i >= 0; i--) {
            if (remainder > 0){
                // If there is a remainder to be added this round, push (digits[i]+rem)%10 to stack
                int new_int = digits[i]+remainder;
                remainder = new_int%10;
                quotient = new_int/10;
                // cout << "----- INFO" << endl;
                // cout << "digits[i]: "<< digits[i] <<endl;
                // cout << "remainder: "<< remainder <<endl;
                // cout << "quotient: "<< quotient <<endl;
                s.push(remainder);
            } else {
                s.push(digits[i]);
                quotient = 0;
            }
            remainder = quotient;
        }

        // If there is still a remainder:
        if (remainder > 0){
            s.push(remainder);
        } 

        // update array with stack. 
        while(!s.empty()){
            ans.push_back(s.top());
            s.pop();
        }

        return ans;
    }
};

void v_print(vector<int>& v){
    for (auto &c : v){
        cout << c;
    }
    cout << endl;

}


void test1(){
    Solution s;

    vector<int> v = {1,2,3,4,5};
    vector<int> ans = {1,2,3,4,6};
    vector <int> out = s.plusOne(v);

    v_print(out);
    v_print(ans);
    assert(out == ans);
}


void test2(){
    Solution s;

    vector<int> v = {9,9,9,9,9,9};
    vector<int> ans = {1,0,0,0,0,0,0};
    vector <int> out = s.plusOne(v);

    v_print(out);
    v_print(ans);
    assert(out == ans);
}


void test3(){
    Solution s;

    vector<int> v = {1,2,9,3,8,4,9,9,9};
    vector<int> ans = {1,2,9,3,8,5,0,0,0};
    vector <int> out = s.plusOne(v);

    v_print(out);
    v_print(ans);
    assert(out == ans);
}


void test4(){
    Solution s;

    vector<int> v = {9};
    vector<int> ans = {1,0};
    vector <int> out = s.plusOne(v);

    v_print(out);
    v_print(ans);
    assert(out == ans);
}






int main(){
    test1();
    test2();
    test3();
    test4();
    return 0;
}