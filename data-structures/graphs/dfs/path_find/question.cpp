// Is there a path from node a to node b in G?
#include<vector>
#include<map>
#include<cassert>
#include<iostream>

using namespace std;

class Solution {
    public:

    bool vp_dfs_visit(vector<vector<int>> &adj, vector<int> &path, map<int,int> &parents, int source, int destination){
        for (auto &v : adj[source]){
            if (parents.find(v) != parents.end()){
                // if v has been visited before, ignore it. 
                continue;
            }
            parents[v] = source;
            if (v == destination){
                path.push_back(v);
                // print path
                return true;
            } else {
                vector<int> new_path = path; // this is inefficient, copying the path at each step, in djikstra, we can reconstruct the path from the parents map.
                new_path.push_back(v);
                return vp_dfs_visit(adj, new_path, parents, v, destination);
            }
        }
        return false;
    }
    
    bool validPath(int n, vector<vector<int>>&adj, int source, int destination){
        vector<int> path = {};
        map<int, int> parents = {{source, -1}};
        bool valid_path = vp_dfs_visit(adj, path, parents, source, destination);
        return valid_path;
    }
};


void test0(Solution &s){
    vector<vector<int>> adj = {{1,2},{3},{3},{1,2,4},{5},{}};
    int source = 0;
    int destination = 5;
    bool valid_path = s.validPath(6, adj, source, destination);
    cout << "valid_path: " << valid_path << endl;
}


