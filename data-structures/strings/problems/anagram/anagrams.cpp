// given two strings, how many charachters do we need to remove from either of them to make them anagrams? 
// "call" "llacs" 'remove s from secon' ans = 1;

#include<string>
#include<map>
#include<iostream>
#include<cassert>

using namespace std;

// Assumptions:

// ROADMAP
// 1. Get frequency dicts 
// 2. iterate through the keys of both at the same time,
//    adding the different between dict1[key]-dict1[key] to our final answer. 
//    sort keys in both first so that we have some partial ordering
// ACTUally before optimizing things, lets just do it in O(n^2) time
// ... ACTUALLY just make both dictionaries have the same keys of the union of the two words!!! just keep a zero if the key doesnt exist then wehn you sort they will align!!!!!
// "tonys" {s:1, o:1, t: 1, n: 1,  y: 1}
// "yoyos" {s:1, o:2, t: 0, n: 0,  y: 2}

// the answer becomes clear 1 + 1+ 1 + 1 = 4



class Solution {
public:
    int numberLetters(string &a, string&b){
        // 1. Record the charachter frequency in each of them in a map 
        map<char, int> freqs_a  = {}, freqs_b = {};
        //    traversing strings 
        string::iterator ita = a.begin(), itb = b.begin();
        while(ita != a.end() || itb != b.end()){
            if (ita != a.end()){
                char key = *ita;
                if (freqs_a.find(key) == freqs_a.end()){
                    // add key! 
                    freqs_a[key] = 1;
                } else {
                    freqs_a[key]++;
                }
                // ADD THIS TO MAKE BOTH SETS OF KEYS ALIGN:
                if (freqs_b.find(key) == freqs_b.end()){
                    freqs_b[key] = 0;
                }
                ita++;
            } 
            if (itb != b.end()){
                char key = *itb;
                if (freqs_b.find(key) == freqs_b.end()){
                    freqs_b[key] = 1;
                } else {
                    freqs_b[key]++;
                }
                if (freqs_a.find(key) == freqs_a.end()){
                    freqs_a[key] = 0;
                }
                itb++;
            } 

        }
    
        // 2. iterate thorugh both keys in the freq_maps at a time 
        map<char, int>::iterator keys_it = freqs_a.begin(); // both have the same set of keys, so one iterator will do. 
        int ans = 0;
        while (keys_it != freqs_a.end()){
            auto &[key, a_count] = *keys_it;
            int b_count = freqs_b[key];
            cout << "key: " << key << " a_count: " << a_count << " b_count: " << b_count << endl;
            ans+= abs(b_count-a_count);
            keys_it++;
        }
        return ans;
    }
};


void test1(Solution &s){
    string a = "tonys";
    string b = "yoyos";
    int ans = s.numberLetters(a, b);
    cout << "ans: " << ans << endl;
    assert(ans == 4);

}


int main(){
    Solution s;
    test1(s);
    return 0;
}
