#include <string>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;



// Main concept here is iterating trhough string sentences of space seaprated words,
// without the magic split() from python.



class Solution {

public:

    void print_arr(vector<string> &v){
        for (int i = 0; i< v.size(); i++){
            cout << v[i] << endl;
        }
    }

    vector<string> split_str(string s) {
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

    int lengthOfLastWord(string s) {
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
};


void test_1(Solution& sol){
    string str = "Hello Mr. Postman!";
    sol.split_str(str);
    assert(sol.lengthOfLastWord(str) == 8);
}

void test_2(Solution& sol){
    string str = "   fly me   to   the moon  ";
    sol.split_str(str);
    sol.lengthOfLastWord(str);
    assert(sol.lengthOfLastWord(str)==4);
}

int main(){
    Solution sol;
    test_1(sol);
    test_2(sol);
    
}