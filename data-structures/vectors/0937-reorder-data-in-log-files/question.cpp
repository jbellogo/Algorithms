#include <vector>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

typedef vector<pair<string, string>> SameTypeLogs; // vector<<identifier, content>>

void print_vec(SameTypeLogs &v){
    for (int i = 0 ; i < v.size() ; i++){
        cout << "(" << v[i].first << ", " << v[i].second << ")";
        if (i < v.size()-1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

class Solution {
public:
    vector<string> breakdown_str(string &s){
        // returns <type, string> or s.split(' ')[0], s.split(' ')[-1] in python.
       bool indentifier_complete = false;
       string type = "null"; // one of {"digit", "letter"}
       string identifier = "";
       string content = "";
        for (int i = 0; i < s.length(); i++){
            if (!indentifier_complete){
                if (s[i] != ' '){
                    identifier+=s[i];
                } else {
                    indentifier_complete = true;
                }
            } else {
                content +=s[i];
                if (type == "null" && s[i] != ' '){
                    if (48 <= s[i] && s[i]<= 57){
                        type = "digit";
                    } else {
                        type = "letter";
                    }
                }
            }
       }
       return {type, identifier, content}; // array of 3 strings
    }

    void insert_sorted(SameTypeLogs &letter_logs, string identifier, string content){
        // letter_logs is sorted as per specs.
        // update letter_logs in_place with identifier+content.
        // sorting rule is: 
        //      "sorted lexicographically by their contents. 
        //      "If their contents are the same, then sort them lexicographically by their identifiers.
        pair<string,string> new_elem = { identifier, content };
        if (letter_logs.empty() || letter_logs[letter_logs.size()-1].second < content){
            // @TODO test the second OR condition works.
            letter_logs.push_back(new_elem);
        } else {
            for (int i = 0; i < letter_logs.size(); i++){
                // try sorting by content
                string curr_identifier = letter_logs[i].first;
                string curr_content = letter_logs[i].second;
                if (content < curr_content){
                    letter_logs.insert(letter_logs.begin() + i, new_elem);
                    break;
                } else if (content == curr_content){
                    if (identifier <= curr_identifier){
                        letter_logs.insert(letter_logs.begin() + i, new_elem);
                    } else {
                        letter_logs.insert(letter_logs.begin() + i + 1, new_elem);
                    }
                    break;
                }
                // else keep going
            }
        }


    }



    void reorderLogFiles(vector<string>& logs) {
        SameTypeLogs digit_logs = {};
        SameTypeLogs letter_logs = {};
        for (int i = 0; i < logs.size() ; i ++){
            vector<string> breakdown = breakdown_str(logs[i]);
            string type = breakdown[0], identifier = breakdown[1], content = breakdown[2];
            if (type == "letter"){
                insert_sorted(letter_logs, identifier, content);
            } else if (type == "digit"){
                digit_logs.push_back({identifier, content});
            }
        }
        print_vec(digit_logs);
        print_vec(letter_logs);

        vector<strings> ans = letter_logs + digit_logs;

    }
};


void test0(){
    // is default string comparison in lexicographical order?
    vector<string> v = {"dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"};
    Solution sol = Solution();
    sol.reorderLogFiles(v);
}


int main(){
    test0();
}