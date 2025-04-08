// Problem 1192 
#include <vector>
#include <map>
#include <iostream>
#include <cassert>


using namespace std;


class Solution {
    public:
 
        void dfs_visit(int root, vector<vector<int>> &adj, map<int, int> &parents){
            for (auto &v : adj[root]){                
                if (parents.find(v) == parents.end()){
                    // v doesn't have a parent
                    parents[v] = root;
                    dfs_visit(v, adj, parents);
                } 
            }
        }

        bool isDisconnected(vector<vector<int>>&adj, int n){
            map<int, int> parents = {{ 0, -1}};
            int root = 0;
            dfs_visit(root, adj, parents);
            // check if all elements have parents after starting a dfs from 0
            for (int i = 0 ; i < n; i++){
                if (parents.find(i) == parents.end()){
                    return true;
                }
            }
            return false;
        }

        vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
            int m = connections.size();

            vector<vector<int>> ans;

            // leave one out edges
            for (int loo_indx = 0; loo_indx < m; loo_indx++){
                // 1. Construct adj representation without edge at loo_indx; @SORUCE of inefficiency
                // int v = connections[loo_indx][0], u = connections[loo_indx][1];
                vector<vector<int>> adj(n);
                for (int i = 0; i < m; i++){
                    if (i != loo_indx){
                        int v = connections[i][0], u = connections[i][1];
                        adj[v].push_back(u);
                        adj[u].push_back(v);                
                    }
                }
                // 2. Run DFS to check connectedness of resulting adj
                bool isCritical = isDisconnected(adj, n);
                if (isCritical){
                    ans.push_back(connections[loo_indx]);
                }
            }   
            return ans;         
        }
    };

    void print_ans(vector<vector<int>> &ans){
        for (int i = 0; i < ans.size(); i++){
            int v = ans[i][0], u = ans[i][1]; // edge
            cout << "(" << u << ", " << v << ")";
        }
        cout << endl;
    }


    void test0(Solution &sol){
        vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
        int n = 4; 
        vector<vector<int>> ans = sol.criticalConnections(n, connections);
        print_ans(ans);
        assert(ans == vector<vector<int>>({{1,3}}));
    }

    void test1(Solution &sol){
        vector<vector<int>> connections = {
            {7,9}, {0,1}, {1,2}, {8,6},
            {5, 6}, {0,4}, {2,4}, {1,3},
            {4, 5}, {6,7}, {7,8}, {0,2}, 
            {0, 3}, {3,4}
        };
        int n = 10; 
        vector<vector<int>> ans = sol.criticalConnections(n, connections);
        print_ans(ans);
        // assert(ans == vector<vector<int>>({{1,3}}));
    }

    int main(){
        Solution sol;
        test0(sol);
        test1(sol);
    }
    