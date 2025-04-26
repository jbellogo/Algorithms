#include <string>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;



class Solution {

public:

    void print_arr(vector<string> &v){
        for (int i = 0; i< v.size(); i++){
            cout << v[i] << endl;
        }
    }

    vector<string> split_str(string s) {
        /* 
        Python str.split(',') method for giggles
        */
        vector<string> split_string;
        string word = ""; // Double quotes for strings

        for (int i =0; i < s.length(); i++){
            char c = s[i];
            if (c != ' '){
                word+=c; // add char to a string
                if (i==s.length()-1){
                    split_string.push_back(word);
                }
            } else if (word != ""){
                split_string.push_back(word);
                word = "";
            }
        }
        print_arr(split_string);
        return split_string;
    }

    int lengthOfLastWordINTIAL(string s) {
        // all fo these variables declared will add to space complexity. 
        vector<string> split_string;
        string word = ""; // Double quotes for strings

        for (int i =0; i < s.length(); i++){
            char c = s[i];
            if (c != ' '){
                word+=c; // add char to a string
                if (i==s.length()-1){
                    split_string.push_back(word);
                }
            } else if (word!=""){
                split_string.push_back(word);
                word="";
            }
        }
        int last_indx = split_string.size()-1;
        return split_string[last_indx].length();
    }

    int lengthOfLastWordOptimized(string s) {
        int last_word_len = 0;
        int n = s.length();

        // NOTE: see how these two loops still make up n steps when added, not even 2n
        // Need to deal with right padded whitespaces
        int last_char_indx = n-1; // last non-trivial char index
        while (last_char_indx >= 0 && s[last_char_indx] == ' '){
            last_char_indx--;
        }

        for (int i = last_char_indx; i >= 0; i--){
            if (s[i] == ' '){
                break;
            } else {
                last_word_len++;
            }
        }
        // this covers the two edge cases: s = "" and s = "SingularWord"
        return last_word_len; 
    }

};


void test_0_edges(Solution& sol){
    string str = "";
    assert(sol.lengthOfLastWordOptimized(str) == 0);

    str = "TonyRomo";
    assert(sol.lengthOfLastWordOptimized(str) == 8);

    str = " TonyRomo ";
    assert(sol.lengthOfLastWordOptimized(str) == 8);


}


void test_1(Solution& sol){
    string str = "Hello Mr. Postman!";
    // sol.split_str(str);
    assert(sol.lengthOfLastWordOptimized(str) == 8);
}

void test_2(Solution& sol){
    string str = "   fly me   to   the moon  ";
    // sol.split_str(str);
    // sol.lengthOfLastWord(str);
    assert(sol.lengthOfLastWordOptimized(str)==4);
}



int main(){
    Solution sol;
    test_0_edges(sol);
    test_1(sol);
    test_2(sol);
    
}