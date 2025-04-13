#include <string>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
public:
    string mergeAlternatelySECONDARY(string word1, string word2) {
        string::iterator it1 = word1.begin();
        string::iterator it2 = word2.begin();

        string ans = "";

        while (it1 != word1.end() || it2 != word2.end()){
            char c1 = (it1 != word1.end()) ? *it1 : '';  // unformtunateley this is elegant but is adding something we don't want to strings.
            char c2 = (it2 != word2.end()) ? *it2 : '';

            ans+=c1;
            ans+=c2;

            it1 = (it1 == word1.end()) ? it1 : it1+1;
            it2 = (it2 == word2.end()) ? it2 : it2+1;
        }
        return ans;        
    }

    string mergeAlternately(string word1, string word2) {
        string::iterator it1 = word1.begin();
        string::iterator it2 = word2.begin();

        string ans = "";

        while (it1 != word1.end() || it2 != word2.end()){
            if (it1 != word1.end()){
                char c1 =  *it1;
                ans += c1;
                it1++;
            }
            if (it2 != word2.end()){
                char c2 =  *it2;
                ans += c2;
                it2++;
            }
            
        }
        return ans;
    }

};


void test1(){
    Solution sol;
    string word1 = "abc";
    string word2 = "pqr";
    string ans = sol.mergeAlternately(word1, word2);
    assert(ans == "apbqcr");
}

void test2(){
    Solution sol;
    string word1 = "ab";
    string word2 = "c";
    cout << "word1: " << word1 << " word2: " << word2 << endl;
    string ans = sol.mergeAlternately(word1, word2);
    cout << "ans: " << ans << endl;
    assert(ans == "acb");
}

void test3(){
    Solution sol;
    string word1 = "adedjedkehndkehndedb";
    string word2 = "kkkk";
    string ans = sol.mergeAlternately(word1, word2);
    assert(ans == "akdkekdkjedkehndkehndedb");
}
int main(){
    test1();
    test2();
    test3();
}