#include <map>
#include <iostream>

using namespace std;    


class Solution {
public:
    int climbStairs(int n) {
        map<int, int> memoizations = {};
        return climbStairsRecursive(n, memoizations);
    }

    int climbStairsRecursive(int n, map<int, int> &memz){

        // base
        if (n<0){
            return 0;
        } else if (n == 0){
            return 1;
        }
        // memoization optimization
        if (memz.find(n) == memz.end()){
            memz[n] = climbStairsRecursive(n-2, memz) + climbStairsRecursive(n-1, memz);
        }
        // take 2 steps in this iteration or 1 step in this iteration and add them up.
        return memz[n];
    }

    int climbStairsIterative(int n){
        // This is efficient in time, but not in space.
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

    int climbStairsOptimized(int n){
        // Efficient in time, but not in space. Save the array allocation space.
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