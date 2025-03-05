#include <iostream>
#include <string>
#include <cassert>
#include <unordered_map>
using namespace std;

void print(vector<pair<char, int>> &candidates){
    for (auto it : candidates)
        cout <<  "  - "<< it.first << " " << it.second << endl;
}

void print_v(vector<string> &candidates){
    for (auto it : candidates)
        cout <<  "  - "<< it << endl;
}

class Solution {
public:
    void OddPalindromes(string s) {
        int n = s.length();
        vector<pair<char, int>> candidates;
        // to keep the list of candidates small, only numbers at candidates of length > 3 are stored. 
        // A PROBLEM I RAN INTO: 
        //     Two centers of palindromes can have the same charachter.  ie "bab__bbabb". 
        //     Need to keep actual palidnrome candidates. 
        //     Kept in tuples of (center, pal_length). To optimize memory and save max recovery, 
        //     keep only palindrome of max_length.

        for (int i = 1; i < n-1; i++){
            // try to put i at the center of palindrome
            char center = s[i];
            int pal_length = 1;

            for (int j = 1; 0 <= i-j && i+j <= n-1 ; j++){
                char left = s[i-j];
                char right = s[i+j];
                if (left == right) {
                    cout <<  " left: " << left << " center: " << center << " right: " << right << endl;
                    pal_length += 2;
                } else {
                    break;
                }
            }
            if (pal_length > 1){
                candidates.push_back(make_pair(center, pal_length));
            }
        }
        print(candidates);        
    }
    void EvenPalindromes(string s) {
        // looking for repeating pairs of charachters to start my center
        int n = s.length();
        vector<pair<char, int>> candidates;

        for (int l = 0; l < n-1; l++){
            int r = l+1;
            // try to put i at the center of palindrome
            if (s[l] != s[r]) continue;
            int pal_length = 2;
            for (int j = 1; 0 <= l-j && r+j <= n-1 ; j++){
                char left = s[l-j];
                char right = s[r+j];
                if (left == right) {
                    cout <<  " left: " << left << " right: " << right << endl;
                    pal_length += 2;
                } else {
                    break;
                }
            }
            if (pal_length > 1){
                candidates.push_back(make_pair(s[l], pal_length));
            }
        }
        print(candidates);        
    }


    void allPalindromes(string s){
        int n = s.length();
        vector<string> odd_candidates;
        vector<string> even_candidates;


        for (int i = 0; i < n-1; i++){
            // ODD palindromes
            char center = s[i];
            int width = 0;

            for (int j = 1; 0 <= i-j && i+j <= n-1 ; j++){
                char left = s[i-j];
                char right = s[i+j];
                if (left == right) {
                    // cout <<  " left: " << left << " center: " << center << " right: " << right << endl;
                    width ++;
                } else {
                    break;
                }
            }
            if (width > 0){
                string odd_candidate = s.substr(i-width, 2*width+1);  // substr(start, length)
                // cout << "i-width: " << i-width << " i: " << i << " i+width: " << i+width << endl;
                // cout << "odd_candidate: " << odd_candidate << endl;

                odd_candidates.push_back(odd_candidate);
            }

            // EVEN palindromes 
            int l = i;
            int r = i+1;
            if (s[l] != s[r]) continue;
            width = 0;
            for (int j = 1; 0 <= l-j && r+j <= n-1 ; j++){
                char left = s[l-j];
                char right = s[r+j];
                if (left == right) {
                    width = j;
                } else {
                    break;
                }
            }
            if (width > 0){
                // cout << "start: " << l-width << " length: " << width*2+2 << endl;
                string even_candidate = s.substr(l-width, width*2+2);
                // cout << "even_candidate: " << even_candidate << endl;
                even_candidates.push_back(even_candidate);
            }
        }
        cout << "odd candidates: " << endl;
        print_v(odd_candidates);     
        cout << "even candidates: " << endl;
        print_v(even_candidates);   
    }



    string longestPalindrome(string s) {
        int n = s.length();
        string candidate = "";

        for (int i = 0; i < n; i++){
            // ODD palindromes
            char center = s[i];
            int width = 0;

            for (int j = 1; 0 <= i-j && i+j <= n-1 ; j++){
                char left = s[i-j];
                char right = s[i+j];
                if (left == right) {
                    width ++;
                } else {
                    break;
                }
            }
            if (width > 0){
                string odd_candidate = s.substr(i-width, 2*width+1); 
                if (odd_candidate.length() > candidate.length()){
                    candidate = odd_candidate;
                }
            }

            // EVEN palindromes 
            int l = i;
            int r = i+1;
            if (s[l] != s[r]) continue;
            width = 0;
            for (int j = 1; 0 <= l-j && r+j <= n-1 ; j++){
                char left = s[l-j];
                char right = s[r+j];
                if (left == right) {
                    width = j;
                } else {
                    break;
                }
            }
            string even_candidate = s.substr(l-width, width*2+2);
            if (even_candidate.length() > candidate.length()){
                candidate = even_candidate;
            }
        }
        cout << "candidate: " << candidate << endl;
        cout << "length(): " << candidate.length() << endl;
        if (candidate.length() == 0 && n > 0) return s.substr(0, 1);
        return candidate;
    }


};


void test1(Solution &sol){
    cout << "---------------------test1------------------------" << endl;
    string s = "babefchijalajmxmjalaj";
    string res = sol.longestPalindrome(s);
    assert(res == "jalajmxmjalaj");
}

void test2(Solution &sol){
    cout << "---------------------test2------------------------" << endl;
    string s = "abbadededlejm";
    string res = sol.longestPalindrome(s);
    assert(res == "deded");
}

void test3(Solution &sol){
    cout << "---------------------test3------------------------" << endl;
    string s = "a";
    string res = sol.longestPalindrome(s);
    assert(res == "a");
}

void test4(Solution &sol){
    cout << "---------------------test4------------------------" << endl;
    string s = "babad";
    string res = sol.longestPalindrome(s);
    assert(res == "bab");
}

void test5(Solution &sol){
    cout << "---------------------test5------------------------" << endl;
    string s = "cbbd";
    string res = sol.longestPalindrome(s);
    assert(res == "bb");
}

void test6(Solution &sol){
    cout << "---------------------test6------------------------" << endl;
    string s = "acdefghijk";
    string res = sol.longestPalindrome(s);
    assert(res == "a");
}




int main(){
    Solution sol;
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
}