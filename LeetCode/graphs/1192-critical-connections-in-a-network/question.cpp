// Problem 1192 
#include <vector>
#include <map>
#include <queue>
#include <iostream>

using namespace std;

typedef pair<int, int> Edge;

class Solution {
    public:
        void get_cycle(queue<Edge> &edge_list, map<int, int> &parents, int v){
            while (edge_list.front().first != v){
                edge_list.pop();
            }
            while (!edge_list.empty()){
                auto [v, u] = edge_list.front();
                cout << "(" << v << " -> " << u << ")";
                edge_list.pop();
            }
            cout << endl;
        }
 
        void dfs_visit(vector<vector<int>> &adj, int root, map<int, int> &parents, queue<Edge> &cycles){
            cout << "root: " << root << endl;
            for (auto &v : adj[root]){
                // (root,v) is an Edge.
                if (parents[root] != v) {
                    cycles.push({root, v});
                }
                if (parents.find(v) == parents.end()){
                    parents[v] = root;
                    dfs_visit(adj, v, parents, cycles);
                } else {
                    // cout << "root: " << root << ", v: " << v << endl;
                    // we have found a cycle?! 
                    cout << "Found first cycle: ";
                    get_cycle(cycles, parents, v);
                    break;
                }
            }

        }

        void criticalConnections(int n, vector<vector<int>>& connections) {
            // 1. Convert to adjacency list
            vector<vector<int>> adj(n);
            map<int, int> parents = {{0, -1}};
            queue<Edge> cycles;

            for (auto &edge : connections){
                adj[edge[0]].push_back(edge[1]);
                adj[edge[1]].push_back(edge[0]);            
            }

            // 2. Run Dfs
            dfs_visit(adj, 0, parents, cycles);
            
        }
    };


    void test0(){
        vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
        int n = 4;
        Solution sol;
        sol.criticalConnections(n, connections);
    }

    int main(){
        test0();
    }
    