#include<map>
#include<vector>
#include<cassert>
#include<iostream>

/* 
Given a list of strings, return the grouping into anagrams. 
in = ["opt", "top", "pot", "cat", "tac", "toe"]
Out =   [["opt", "top", "pot"],
         ["cat", "tac"], 
         [toe]]

*/

using namespace std; 

// What charachterizes anagrams is equal letter distributions, so:
typedef map<char, int> LetterDist; 
// {"p":1, "o":1, "t":1}

// I also want to keep two pieces of data about an anagram group:
// a. The LetterDist to determine if an outside element  belongs to it, ie to insert other permuations of thje word. 
// b. The  list of words ["opt", "top", "pot"]
typedef pair<LetterDist, vector<string>> AnagramGroup;


// Now we need something to hold the AnagramGroup, ... if its a 
typedef map<string, AnagramGroup> GroupMap; 

class Solution {
public:

    LetterDist getDistribution(string &s){
        LetterDist dist = {};
        for (auto& key : s){
            if (dist.find(key) == dist.end()){
                dist[key] = 1;
            } else {
                dist[key]++;
            }
        }
        return dist;
    }

    void updateGroup(GroupMap &g, string &s){
        // 1. Compute distribution
        LetterDist dist = getDistribution(s);
        // 2. Get the AnagramGroup key as the sorted string
        string key = s;
        sort(key.begin(), key.end());

        // Having this as a key search rather than iterating 
        // through a verctor to detremine where to put it takes this function from linear to constant time!!
        if (g.find(key) == g.end()){
            g[key] = {dist, vector<string>{s}};
        } else {
            g[key].second.push_back(s);
        }
    }

    vector<vector<string>> vectorize_group(GroupMap &g){
        vector<vector<string>> ans = {};
        GroupMap::iterator ita;
        for (ita = g.begin(); ita != g.end(); ita++){
            vector<string> group = (ita->second).second;
            ans.push_back(group);
        }
        return ans;
    }


    vector<vector<string>> getAnagrams(vector<string> &strs){
        GroupMap groups = {};
        for (auto &s : strs){
            updateGroup(groups, s);
        }
        return vectorize_group(groups);
    }
};

void print_vector(vector<vector<string>> &v){
    for (auto &v2 : v){
        cout << "[ ";
        for (auto &s : v2){
            cout << s << " ";
        }
        cout << "]" << endl;
    }
}

void test0(){
    vector<string> in = {"opt", "top", "pot", "cat", "tac", "toe"};
    Solution sol = Solution();
    vector<vector<string>> out = sol.getAnagrams(in);
    vector<vector<string>> expected = {{"cat", "tac"}, {"toe"}, {"opt", "top", "pot"}};
    print_vector(out);
    assert(out == expected);
}

void test1(){
    vector<string> in = {"bats", "tabs", "cat", "tac", "toe", "act", "dog", "god"};
    Solution sol = Solution();
    vector<vector<string>> out = sol.getAnagrams(in);
    vector<vector<string>> expected = {{"bats", "tabs"}, {"cat", "tac", "act"}, {"dog", "god"}, {"toe"}};
    assert(out == expected);
}

int main(){
    test0();
    test1();
}