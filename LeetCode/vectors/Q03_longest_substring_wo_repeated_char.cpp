#include <iostream>
#include <string>
#include <cassert>
using namespace std;

bool isInString(char c, string str){
    return str.find(c) != string::npos;
}

void print(vector <string> &v){
    cout << "CANDIDATES: ";
    for (string &s : v){
        cout << s << ", ";
    }
    cout << endl;
}

class Solution {
public:
    // @NOTE: This is a first attempt, it has a time complexity of O(n^3)
    int lengthOfLongestSubstringFirstAttempt(string s) {
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

    void lengthOfLongestSubstring_COMPREHENSIVE(string s){
        // Comprehensively computes and stores all candidates to eyeball the optimal one (O(n^2))
        vector<string> candidates;

        string curr_candidate = "";
        int curr_candidate_start = 0; // starting index of current candidate so that we can recover absolutepositions on s
        int i = 0;
        while (i < s.length()){
            // cout << "index: " << i << endl;
            int curr_candidate_repeated_index = curr_candidate.find(s[i]); 
            // this is the local index on curr_candidate string, 
            // how to translate it to a 'gloabl' index of s? // add starting point of curr_candidate on s. 
            
            if (curr_candidate_repeated_index == string::npos){
                // s[i] not found. Add it to current candidate
                curr_candidate+=s[i];
                i++;
            } else {
                // charachter is present in candidate at repeated_index. 
                // Save current_candidate
                candidates.push_back(curr_candidate);

                // Start anew candidate
                curr_candidate = "";
                i = curr_candidate_start + curr_candidate_repeated_index +1; 
                curr_candidate_start = i;
                // cout << "new index: " << i << endl;
            }
        }
        if (curr_candidate != ""){
            candidates.push_back(curr_candidate);
        }
        print(candidates);        
    }

    int lengthOfLongestSubstring(string s){

        string best_candidate = "";
        string curr_candidate = "";
        int curr_candidate_start = 0; // starting index of current candidate so that we can recover absolutepositions on s
        int i = 0;

        while (i < s.length()){
            // cout << "index: " << i << endl;
            int curr_candidate_repeated_index = curr_candidate.find(s[i]); 
            // this is the local index on curr_candidate string, 
            // how to translate it to a 'global' index of s? // add starting point of curr_candidate on s. 
            if (curr_candidate_repeated_index == string::npos){
                // s[i] not found. Add it to current candidate
                curr_candidate+=s[i];
                i++;
            } else {
                // charachter is present in candidate at repeated_index. 
                // Save current_candidate
                if (best_candidate.length() < curr_candidate.length()) {
                    best_candidate = curr_candidate;
                }

                // cout << "old candidate: "<< curr_candidate << endl;
                // Start anew candidate
                curr_candidate = "";
                i = curr_candidate_start + curr_candidate_repeated_index +1; 
                curr_candidate_start = i;
                // cout << "new index: " << i << endl;
            }
        }
        if (best_candidate.length() < curr_candidate.length()) {
            best_candidate = curr_candidate;
        }
        // cout << "candidate: " << best_candidate << endl;

        return best_candidate.length();        
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
    cout << "-------test 5" << endl;
    string s = "dvdf";
    sol.lengthOfLongestSubstring_COMPREHENSIVE(s);
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


// // void test9(Solution &sol){
// //     string s = "abdekhdejanedahkeb";
// //     sol.lengthOfLongestSubstring_COMPREHENSIVE(s);

// }

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
    // test9(sol);
    return 0;
}