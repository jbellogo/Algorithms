// Time: 23:00 minutes

#include <stack>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:

    bool is_left_char(char c){
        return ((c == '(') || (c == '{') || (c == '['));
    }
    char left_version(char c){
        // takes right version char and returns matchin left
        if (c == ')') {
            return '(';
        } else if (c == ']'){
            return '[';
        } else if (c == '}'){
            return '{';
        }
        return 'e';

    }

    bool isValid(string s) {
        stack<char> left_brackets; // reset the stack
        for (char &c : s){
            // cout << "c: " << c << endl;
            if (is_left_char(c)){
                left_brackets.push(c);
            } else {
                if (left_brackets.empty()){
                    return false;
                } else if (left_brackets.top() != left_version(c)){
                    return false;
                } else {
                    left_brackets.pop();
                }
            } 
        }
        return left_brackets.empty();
        
    }
};


int main(){
    Solution sol;
    assert(sol.isValid("()") == true);
    assert(sol.isValid("()[]{}") == true);
    assert(sol.isValid("(]") == false);
    assert(sol.isValid("([)]") == false);
    assert(sol.isValid("{[]}") == true);
    assert(sol.isValid("]") == false);
    assert(sol.isValid("((") == false);
}
