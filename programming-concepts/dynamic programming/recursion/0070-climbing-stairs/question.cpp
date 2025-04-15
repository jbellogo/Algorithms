#include <map>
#include <iostream>

using namespace std;    


class Solution {
public:

    // Solution 1: Recursive with memoization
    // Without memoization, this is O(2^n) time complexity.
    // With memoization, this is O(n) time complexity.
    int climbStairs1Recursive(int n, map<int, int> &memz){
        // base
        if (n<0){
            return 0; // Did we overshoot the top?
        } else if (n == 0){
            return 1; // Did we reach the top exactly?
        }
        // memoization optimization
        if (memz.find(n) == memz.end()){
            memz[n] = climbStairs1Recursive(n-2, memz) + climbStairs1Recursive(n-1, memz);
        }
        return memz[n];
    }

    int climbStairs1(int n) {
        map<int, int> memoizations = {}; // map in order to store non sequential integer keys
        return climbStairs1Recursive(n, memoizations);
    }

    // Solution 2: Iterative
    // Efficient in time O(n), but not in space O(n) to allocate the array.
    int climbStairs2Iterative(int n){
        if (n <= 2) return n;
        // ITERATIVE
        vector<int> dp(n, 0);
        dp[0] = 1;
        dp[1] = 2;
        for (int i = 2 ; i < n; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n-1];
    }

    // Solution 3: Optimized
    // Efficient in time and space, by saving the array allocation space.
    int climbStairs3Optimized(int n){
        if (n <= 2) return n;

        int last  = 1;
        int second_last = 2;
        int curr = second_last + last;

        for (int i = 3; i <= n; i++){
            curr =  last+second_last;
            second_last = last;
            last = curr;
        }
        return curr;
    }



};