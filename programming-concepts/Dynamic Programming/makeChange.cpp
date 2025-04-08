#include<vector>
#include<iostream>
#include<cassert>
#include<map>

using namespace std;


// Given a target amount and a set of coin denominations, how many ways can you make change?
// Approach it recursively, 

// HELPERS
void print_v(vector<int> &v){
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}


void print_change(vector<int> &coeffs, vector<int> &coins){
    int n = coeffs.size();
    for (int i = 0; i < n; i++){
        cout <<  coeffs[i] << " x ($" << coins[i] << ")";
        if (i < n-1){
            cout << " + ";
        } 
    }
    cout << endl;
}



struct ChangeSequence{
    // By default, a struct has public members
    map<int, int> change;
    // constructor
    ChangeSequence(vector<int> &denominations) {
        for (auto &denom : denominations){
            change[denom] = 0;
        }
    }

    void reset(){
        for (map<int, int>::iterator it = change.begin(); it != change.end(); it++){
            it->second = 0;
        }
    }

    void set_coin_num(int coin, int amount){
        // setting amount x coin
        change[coin] = amount;
    }
    void increment_coin(int coin){
        change[coin]++;
    }

    void print(){
        for (map<int, int>::iterator it = change.begin(); it != change.end(); it++){
            cout << "$" << it->first  << "x" << it->second << "  ";
        }
        cout << endl;
    }
}; 


class Solution {
public:


    int makeChange(int target, vector<int> &denominations){
        sort(denominations.begin(), denominations.end(), greater<>());
        int num_coins = denominations.size();
        vector<int> coeffiecients(num_coins, 0);
        map<pair<int, int>, int> memoizations = {}; // based on map<target, coin_idx>
        return makeChangeRecursive(denominations, target, 0, coeffiecients, memoizations);
    }

    int makeChangeRecursive(vector<int> &coins, int target, int coin_idx, vector<int> &coefficients, map<pair<int, int>, int> memz){
        // BASE case 1
        if (coin_idx >= coins.size()) {
            return 0;
        }

        int coin = coins[coin_idx]; // current denomination in consideration

        // BASE case 2
        // I like this second and condition as I don't want to be recursing once I get to the last denomination, there is no need, just check a remainder.
        if (target == 0 || (coin_idx == coins.size()-1 && target % coin ==0)){
            // cout << "exact change sequence found: ";
            coefficients[coin_idx] = target/coin;
            // print_change(coefficients, coins);
            return 1;
        }

        // Memoization check
        if (memz.find({target, coin_idx}) != memz.end()){
            // note instead of the interger pair, key, you could just make it a string concatenating the two values, useful say in python where dict keys must be strings.
            cout << " ---- MEMOIZED KEY FOUND!!!!" << endl;
            return memz[{target, coin_idx}];
        }


        // RECURSION
        int num_ways = 0; // you don't need to keep multipliers
        int current_coins = 0;

        while (current_coins*coin <= target) {        
            int remaining = target-current_coins*coin;
            // update coefficient sequence 
            vector<int> coefficients_copy = coefficients;// make copy of coeffs
            coefficients_copy[coin_idx] = current_coins;      

            num_ways += makeChangeRecursive(coins, remaining, coin_idx+1, coefficients_copy, memz);
            current_coins++;
        }
        memz[{target, coin_idx}] = num_ways;
        return num_ways;
    }

};

void test0(Solution &sol){
    vector<int> denominations = {1, 2, 5};
    int target = 5;
    int result = sol.makeChange(target, denominations);
    cout << "Result: " << result << endl;
    assert(result == 4);
}

void test1(Solution &sol){
    vector<int> denominations = {1, 2, 5};
    int target = 14;
    int result = sol.makeChange(target, denominations);
    cout << "Result: " << result << endl;
    assert(result == 16);
}

void test2(Solution &sol){
    vector<int> denominations = {1, 2, 5, 10, 20, 50};
    int target = 100;
    int result = sol.makeChange(target, denominations);
    cout << "Result: " << result << endl;
    assert(result == 4562);
}

int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
}