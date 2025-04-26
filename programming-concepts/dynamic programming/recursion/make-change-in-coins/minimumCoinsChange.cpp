// Similar to makeChange.cpp, but instead of counting the number of ways to make change, 
//we want to find the minimum number of coins needed to make change for a target amount.
// It is a notable problem becase a Greedy algorithm does not work here, we also don't want to check all possible combinations, directly. 
// We can use Dynamic Programming (via Recursion) and memoization to solve this problem.


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


class ChangeSequence{

    int n; // number of coins
    vector<vector<int>> complete_sequences;
    vector<int> curr_coeffs; // coefficients st dot-product := curr_coeffs * denoms = target
    vector<int> coins; // coin denominations

    // for keeping track of min sequence
    int curr_seq_num_coins;

    int min_seq_num_coins;
    vector<int> min_seq_coeffs;

public:
    // constructor
    ChangeSequence(vector<int> &denominations) {
        curr_seq_num_coins = 0;
        min_seq_num_coins = INT_MAX;
        n = denominations.size();
        coins = denominations;
        curr_coeffs = vector<int>(n, 0);
        min_seq_coeffs = vector<int>(n, 0);
    }

    void reset(){
        curr_coeffs = vector<int>(n, 0);
        int curr_seq_num_coins = 0;

    }

    void complete(){
        // completes current sequence, called when sequence weight reaches target.
        // since we can explore all paths that react teh target explicitly, we can keep track of the min sequence.
        vector<int> cpy = curr_coeffs;
        complete_sequences.push_back(cpy);
        // // check if new min
        if (min_seq_num_coins > curr_seq_num_coins){
            min_seq_num_coins = curr_seq_num_coins;
            min_seq_coeffs = curr_coeffs;
        }
    }

    void set(int coin_indx, int count){
        curr_coeffs[coin_indx] = count;
        curr_seq_num_coins+=count;
    }


    void print(bool min_seq = false){
        // prints the current coefficients
        if (min_seq){
            cout << "MIN CHANGE SEQUENCE: ";
            for (int i = 0; i < n; i++){
                cout <<  min_seq_coeffs[i] << " ($" << coins[i] << ")";
                if (i < n-1){
                    cout << " + ";
                } 
            }
            cout << " number of coins: " << min_seq_num_coins;
            cout << endl;    
        } else {
            for (int i = 0; i < n; i++){
                cout <<  curr_coeffs[i] << " ($" << coins[i] << ")";
                if (i < n-1){
                    cout << " + ";
                } 
            }
            cout << " number of coins: " << curr_seq_num_coins;
            cout << endl;    
        }
    }

    int get_min_num_coins(){
        print(true);
        return min_seq_num_coins;
    }

}; 



class Solution {
public:


    int minChange(int target, vector<int> &denominations){
        sort(denominations.begin(), denominations.end(), greater<>());
        ChangeSequence change(denominations);
        return minChangeRecursive(denominations, target, 0, change);
    }

    int minChangeRecursive(vector<int> &coins, int target, int coin_idx, ChangeSequence &change){
        // BASE 
        if (coin_idx >= coins.size()) {
            return 0;
        }
        int coin = coins[coin_idx]; // current denomination in consideration
        if (target == 0 || (coin_idx == coins.size()-1 && target % coin ==0)){
            cout << "exact change sequence found: "; 
            // you can just save the count here something like min_count = max(min_count, curr_count); curr_count = 0;
            change.set(coin_idx, target/coin);
            change.print();
            change.complete();
            return change.get_min_num_coins();
        }


        // RECURSION
        int current_coins = 0;
        int global_min = INT_MAX;

        while (current_coins*coin <= target) {        
            int remaining = target-current_coins*coin;

            // update coefficient sequence 
            ChangeSequence change_copy(change);// make copy of coeffs, default copy constructor
            change_copy.set(coin_idx, current_coins);
            /// 

            int min_down_this_path = minChangeRecursive(coins, remaining, coin_idx+1, change_copy); //
            if (min_down_this_path < global_min){
                global_min = min_down_this_path;
            }

            current_coins++;
        }
        return global_min;
    }

};

void test0(Solution &sol){
    vector<int> denominations = {1, 2, 5};
    int target = 5;
    int result = sol.minChange(target, denominations);
    cout << "Result: " << result << endl;
    assert(result == 1);
}

void test1(Solution &sol){
    vector<int> denominations = {1, 2, 5};
    int target = 14;
    int result = sol.minChange(target, denominations);
    cout << "Result: " << result << endl;
    assert(result == 4);
}

void test2(Solution &sol){
    vector<int> denominations = {1, 3, 4};
    int target = 6;
    int result = sol.minChange(target, denominations);
    cout << "Result: " << result << endl;
    assert(result == 2);
}


void test3(Solution &sol){
    vector<int> denominations = {1, 2, 5, 10, 20, 50};
    int target = 100;
    int result = sol.minChange(target, denominations);
    cout << "Result: " << result << endl;
}

int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
}