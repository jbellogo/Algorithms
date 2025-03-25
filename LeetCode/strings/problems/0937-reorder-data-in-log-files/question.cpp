#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>


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

    vector<string> recover_logs(SameTypeLogs &letter_logs, SameTypeLogs &digit_logs){
        vector<string> ans = {};
        // add letter logs first
        for (int i = 0; i < letter_logs.size(); i++){
            ans.push_back(letter_logs[i].first + " " + letter_logs[i].second);
        }
        for (int i = 0 ; i < digit_logs.size(); i ++){
            ans.push_back(digit_logs[i].first + " " + digit_logs[i].second);
        }
        return ans;
    }



    vector<string> reorderLogFiles(vector<string>& logs) {
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

        // recover the original logs
        vector<string> ans = recover_logs(letter_logs, digit_logs);
        return ans;

    }
};

void print_reg_vec(vector<string> &v){
    for (int i = 0; i < v.size(); i++){
        cout << v[i];
        if (i < v.size()-1) {
            cout << " -> ";
        }
    }
}

void test0(){
    // is default string comparison in lexicographical order?
    vector<string> v = {"dig1 8 1 5 1","let12 art can","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"};
    Solution sol = Solution();
    vector<string> ans = sol.reorderLogFiles(v);
    print_reg_vec(ans);
    vector<string> expected = {"let1 art can", "let12 art can", "let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"};

    assert(ans == expected); 
}

void test1(){
    vector<string> v = {"a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"};
    Solution sol = Solution();
    vector<string> expected = {"g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"};
    vector<string> ans = sol.reorderLogFiles(v);
    assert(ans == expected);
}

int main(){
    test0();
    test1();
}