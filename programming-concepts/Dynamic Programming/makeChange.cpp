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

    void print(){
        for (map<int, int>::iterator it = change.begin(); it != change.end(); i++){
            cout << "$" << it->first  << " x " << it->second << " ";
        }
        cout << endl;
    }
}; 




class Solution {
public:


    int makeChange(int target, vector<int> &denominations){
        sort(denominations.begin(), denominations.end(), greater<>());
        vector<ChangeSeq> change_sequences; 
        ChangeSeq currSeq = {};
        return makeChangeRecursive(target, denominations, change_sequences, currSeq);
    }

    int makeChangeRecursive(int target, vector<int> &denominations, vector<ChangeSeq> &change_sequences, ChangeSeq&currSeq){
        if (denominations.size() == 0){
            return 0;
        }
        int count = 0;
        int curr_denom = denominations[0]; // current denomination in consideration
        int bound = target/curr_denom;
        cout << "target: " << target << " denominations: ";
        print_v(denominations);
        cout << "curr_denom: " << curr_denom << endl;
        cout << "bound: " << bound << endl;




        if (target == 0 || (denominations.size() == 1 && target%curr_denom == 0)){
            cout << "exact change sequence found" << endl;
            print_change(currSeq, denominations);
            change_sequences.push_back(currSeq);
            currSeq = {};
            return 1;
        } else if (denominations.size() == 1){
            return 0;
        }
        cout << "attempting to make change" << endl;
        for (int num_coins = 0; num_coins <= bound; num_coins++){
            // base case 
            if (curr_denom*num_coins == target){
                count++;
            }
            int left_over = target-curr_denom*num_coins;
            denominations.erase(denominations.begin());
            count+=makeChangeRecursive(left_over, denominations);
        }
        return count;
    }

};

void test0(Solution &sol){
    vector<int> denominations = {1, 2, 5};
    int target = 5;
    int result = sol.makeChange(target, denominations);
    cout << "Result: " << result << endl;
}

int main(){
    Solution sol;
    test0(sol);
}