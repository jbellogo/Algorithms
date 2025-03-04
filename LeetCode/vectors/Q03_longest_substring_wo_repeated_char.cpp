#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool isInString(char c, string str){
    return str.find(c) != string::npos;
}

class Solution {
public:
    // @NOTE: This is a first attempt, it has a time complexity of O(n^3)
    int lengthOfLongestSubstring(string s) {
        string longest_nonrepeating = ""; 
        int longest_nonrepeating_length = 0;

        string current_nonrepeating;

        for (int i =0; i<s.length(); i++){
            current_nonrepeating = "";
            // @NICE: It needs to be O(n^2) because we need to check the max nonrepeating seqeunce starting at every possible index i
            for (int j=i ; j< s.length(); j++){
                cout << "string: <" << s[j] << ">, " << "nonrepeating: <" << current_nonrepeating << ">" << endl;
                if (isInString(s[j], current_nonrepeating)){
                    current_nonrepeating = s[j];
                } else {
                    current_nonrepeating += s[j];
                }
                
                if (current_nonrepeating.length() > longest_nonrepeating_length){
                    longest_nonrepeating = current_nonrepeating;
                    longest_nonrepeating_length = current_nonrepeating.length();
                }

            }
        }
        if (longest_nonrepeating_length == 0){
            longest_nonrepeating = current_nonrepeating;
            longest_nonrepeating_length = current_nonrepeating.length();
        }
        cout << longest_nonrepeating << endl;
        return longest_nonrepeating_length;
    }
};

void test1(Solution &sol){
    string s = "abcabcbb";
    int res = sol.lengthOfLongestSubstring(s);
    assert(res == 3);
}


void test2(Solution &sol){
    string s = "bbbbb";
    int res = sol.lengthOfLongestSubstring(s);
    assert(res == 1);
}

void test3(Solution &sol){
    string s = "pwwkew";
    int res = sol.lengthOfLongestSubstring(s);
    assert(res == 3);
}

void test4(Solution &sol){
    string s = " ";
    int res = sol.lengthOfLongestSubstring(s);
    assert(res == 1);
}

void test5(Solution &sol){
    string s = "dvdf";
    int res = sol.lengthOfLongestSubstring(s);
    assert(res == 3);
}


void test6(Solution &sol){
    cout << "--------------------------------test6" << endl;
    string s = " abdek_hd5&^ejanedahkebdhjwedbekw ";
    int res = sol.lengthOfLongestSubstring(s);
    cout << res << endl;
    assert(res == 11);
}

void test7(Solution &sol){
    // should be "khdejan"
    cout << "--------------------------------test7" << endl;
    string s = "abdekhdejanedahkebdhjwedbekw ";
    int res = sol.lengthOfLongestSubstring(s);
    cout << res << endl;
    assert(res == 7);
}

void test8(Solution &sol){
    cout << "--------------------------------test8" << endl;
    string s = "au";
    int res = sol.lengthOfLongestSubstring(s);
    cout << res << endl;
    assert(res == 2);
}



int main(){
    Solution sol;
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
    test7(sol);
    test8(sol);
    return 0;
}