#include <stack>
#include <cmath>
#include <cassert>
#include <iostream>

// Note: this solution is inelegant and inefficient.

using namespace std;

int get_len(int x){
    // Number of digits // length of the decimal expansion of x.
    int quotient = x/10;
    int len = 1;
    while (quotient!=0){
        len++;
        quotient/=10;
    }
    return len;
}


class Solution {
    stack<int> mystack;

public:

    bool isPalindrome(int x) {
        if (x < 0) return false;
        int lenx = get_len(x);  // O(x) linear in x
        // Then another loop 
        for (int i =1; i <= lenx; i++){
            int remainder = x%10;
            x/=10;
            if (i<= lenx/2){
                mystack.push(remainder);
            } else {
                // Need to deal with odd length palindromes. Skip the middle digit.
                if (lenx%2 == 1 && i == lenx/2+1){
                    continue;
                } 
                if (mystack.top() != remainder){
                    return false;
                }
                mystack.pop();

            }
        }
        return true;
    }
};


int main(){
    
    assert(get_len(10) == 2);
    assert(get_len(1234324) == 7);
    assert(get_len(12324) == 5);
    assert(get_len(0) == 1);

    Solution sol;
    assert(sol.isPalindrome(12321));
    assert(!sol.isPalindrome(12323));
    assert(!sol.isPalindrome(122321));
    assert(sol.isPalindrome(12299221));

}