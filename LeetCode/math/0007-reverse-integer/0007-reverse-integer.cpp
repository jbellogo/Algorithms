#include <queue>
#include <iostream>
#include <cassert>

using namespace std;


class Solution {
public:
    // INNEFFICIENT 
    int reverse(int x) {

        // handle tricky edge case
        if (x == INT_MIN || x == INT_MAX) return 0;

        bool is_negative = x < 0;
        x = abs(x);
        int quotient = x;
        queue <int> q;

        while(quotient > 0){
            int remainder = quotient%10;
            // cout << "quotient: " << quotient << ", remainder: " << remainder << endl;
            q.push(remainder);
            quotient/=10;
        }
        int ans = 0;
        while (!q.empty()) {
            int x_rev = q.front();
            int power = q.size();
            // check overflow
            // basically trying to make checks before making computations
            if (power-1 >= 9 && x_rev > 2) return 0;
            int digit = x_rev * pow(10, power-1);

            if (ans >= INT_MAX - digit) return 0;
            // if (ans  -1 > INT_MAX - digit && is_negative) return 0;
            ans += digit;
            q.pop();
        }
        return is_negative ? -ans : ans;
        
    }
};

void test0(Solution &sol){
    int x = 123;
    int ans = sol.reverse(x);
    // cout << "actual: " << ans << ", expected: " << 321 << endl;
    assert(ans == 321);
}

void test1(Solution &sol){
    int x = -123;
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == -321);
}

void test2(Solution &sol){
    int x = INT_MIN;
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == 0);
}

void test3(Solution &sol){
    int x = INT_MAX;
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == 0);
}

void test4(Solution &sol){
    int x = 99999999;
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == x);
}

void test5(Solution &sol){
    int x = 10000003;
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == 30000001);
}

void test6(Solution &sol){
    // Overflow test
    int x = 1534236469; // this fits in 32 bit integer
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == 0); // this overflows 32 bit integer (max is 2147483647)
}

void test7(Solution &sol){
    int x = -2147483648;
    int ans = sol.reverse(x);
    cout << ans << endl;
    assert(ans == 0);
}




int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
    test7(sol);
}


