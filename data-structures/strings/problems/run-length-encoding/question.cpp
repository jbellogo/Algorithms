#include<vector>
#include<string>
#include<iostream>
#include<cassert>

using namespace std;

class Solution {
public:
    string getRunLengthEncoding(string s){
        // I want to be able to access the next charachter, so indeces  might do, indeces are simpler than iterators, keep it simple son. 
        int count = 1; 
        string ans = "";
        // if (s.length()==0) return ans; already covered 
        for (int i = 0; i < s.length(); i++){
            char current = s[i];
            if (i +1 < s.length()){
                char next = s[i+1];
                // if they are equal increase the count, else restart it and save the (char, count) state to ans
                if (current == next){
                    count++;
                } else {
                    ans += (count + '0'); // adding the count as a charachter
                    ans += current; // adding the char        
                    count = 1; // restarting count and next, different letter. 
                }
            } else {
                // there is no next one => save what we have and break.
                ans += (count + '0'); // adding the count as a charachter
                ans += current; // adding the char
                break;
            }
        }
        return ans;
    }
};

void test0(Solution &sol){
    string ans = sol.getRunLengthEncoding("aaaabbbbcazxe");
    cout << ans << endl;
    assert(ans == "4a4b1c1a1z1x1e");
}

int main(){
    Solution sol;
    test0(sol);
}