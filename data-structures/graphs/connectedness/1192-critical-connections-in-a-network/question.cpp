// Problem 1192 
#include <vector>
#include <map>
#include <iostream>
#include <cassert>
#include <set>


using namespace std;

typedef set<int> Edge;

bool edge_comparison(Edge &e1, Edge &e2){
    // order matters, it essentially returns a variant of if edge1 < edge2 
    int e1v = *e1.begin(), e1u = *(++e1.begin());
    int e2v = *e2.begin(), e2u = *(++e2.begin()); 
    int e2min = (e2v < e2u) ? e2v : e2u;
}

class Solution {
    public:

        void print_vertex_path(vector<int> &ans){
            for (int i = 0; i < ans.size(); i++){
                cout << ans[i];
                if (i < ans.size()-1){
                    cout << " -> ";
                }
            }
            cout << endl;
        }

        void print_edge_path(vector<Edge> &path){
            for (int i = 0 ; i < path.size(); i++){
                set<int>::iterator it = path[i].begin();
                int v  = *it; 
                advance(it, 1);
                int u = *it;
                cout << "(" << u << ", " << v << ")";
            }
            cout << endl;
        }


        vector<int> my_vec_copy(vector<int> &path){
            vector<int> ans = {};
            for (auto &e : path){
                ans.push_back(e);
            }
            return ans;
        }
 
        void dfs_visit_print_cycles(
            int root, 
            vector<vector<int>> &adj, 
            vector<int> &parents, 
            vector<int> &ranks,
            vector<int> &current_path, 
            vector<vector<int>> &cycles,
            int RANK){
            // exclude edge uv
            // cout << "------------- root: " << root  << " -------------"<< endl;
            for (auto &v : adj[root]){ 
                if (parents[root] == v){
                    continue;
                }
                if (parents[v] == -1){
                    // UPDATE STATE

                    // - parents
                    parents[v] = root;

                    // - current_path
                    vector<int> new_path = my_vec_copy(current_path); // you need to copy the current path before mutating it.  
                    new_path.push_back(v);

                    // - ranks 
                    ranks[v] = RANK;
                    RANK++;

                    dfs_visit_print_cycles(v, adj, parents, ranks, new_path, cycles, RANK);

                } else if (ranks[v] < ranks[root]){
                    // cycle embedded in current path, need to remove left padding to obtain it.
                    // copy current path from v to end, and that is a cycle!
                    vector<int> cycle = {};
                    bool start = false;
                    // cout << "- CURRENT_PATH: ";
                    // print_path(current_path);
                    int prev = root;
                    for (auto &u: current_path){
                        if (!start && u == v){
                            cycle.push_back(u);
                            start = true;
                            prev = u;
                        } else if (start){
                            cycle.push_back(u);
                            prev = u;
                        }
                    }
                    cycles.push_back(cycle);
                    // print cycle path
                    cout << "- CYCLE_PATH ";
                    print_vertex_path(cycle);

                    // current_path remains unmutated as it should;
                }
            }
        }

        void dfs_visit(int root, vector<vector<int>> &adj,  vector<int> &parents, 
            vector<int> &ranks, vector<int> &current_path, vector<Edge> &cyclic_edges, int RANK){

            for (auto &v : adj[root]){ 
                if (parents[root] == v){
                    continue;
                }
                if (parents[v] == -1){
                    // v doesn't have a parent

                    // UPDATE STATE

                    // - parents
                    parents[v] = root;

                    // - current_path
                    vector<int> new_path = my_vec_copy(current_path); // you need to copy the current path. 
                    new_path.push_back(v);
                    // - ranks 
                    ranks[v] = RANK;
                    RANK++;

                    dfs_visit(v, adj, parents, ranks, new_path, cyclic_edges, RANK);

                } else if (ranks[v] < ranks[root]){
                    bool start = false;
                    int prev = root;
                    for (auto &u: current_path){
                        if (!start && u == v){
                            cyclic_edges.push_back({prev,u});
                            start = true;
                            prev = u;
                        } else if (start){
                            cyclic_edges.push_back({prev,u});
                            prev = u;
                        }
                    }
                }
            }
        }

        vector<vector<int>> my_set_differnce(vector<Edge> &set1, vector<Edge> &set2){
            // SET1 is bigger
            // how is it differnt from the algos lib implementation? 
            // Takes in two vectors of len 2 SETS of ints (representing edges) 
            // Returns vector of len 2 VECTORS of ints (representing edges) 
            vector<set<int>>::iterator it1 = set1.begin();
            vector<set<int>>::iterator it2 = set2.begin();
            // sets are ordered, they contain elements 1 to n. 
            // {1,9}, {9,8}, 

            vector<vector<int>> ans;
            while (it1!= set1.end() && it2 != set2.end()){
                if (*it1 < *it2){
                    set<int> edge = *it1;
                    ans.push_back(vector<int>{*edge.begin(), *(++edge.begin())});
                    it1++;
                } else if (*it1 > *it2){
                    it2++;
                } else {
                    it1++;
                    it2++;
                }
            }
            return ans;


        }




        vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
            int m = connections.size();
            vector<Edge> edges;

            vector<vector<int>> ans;

            // base adj-representation
            vector<vector<int>> adj(n);
            for (int i = 0; i < m; i++){
                int v = connections[i][0], u = connections[i][1];
                adj[v].push_back(u);
                adj[u].push_back(v);   
                edges.push_back({u,v});             
            }

            // SETUP
            int root = 0, RANK = 0;
            vector<int> parents(n, -1);
            parents[0] = -2; // needs to be differntiated from -1
            vector<int> ranks(n, -1);
            vector<int> current_path = {0}; 
            // vector<vector<int>> cycles = {};
            vector<Edge> cyclic_edges = {};

            // DFS
            dfs_visit(root, adj, parents, ranks, current_path, cyclic_edges, RANK); // you don't need to keep explicit cycles, next optimization step!!
            // compute set differnce 

            cout << "cyclic_edges: ";
            print_edge_path(cyclic_edges);  
            cout << "edges: ";
            print_edge_path(edges);

            vector<vector<int>> critical_edges = my_set_differnce(edges, cyclic_edges);

           
            return critical_edges;         
        }
    };


void print_edges(vector<vector<int>> &edges){
    for (auto &e: edges){
        cout << "("<< e[0] << ", " << e[1] << ")";
    }
    cout << endl;
}

void test0(Solution &sol){
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    int n = 4; 
    vector<vector<int>> ans = sol.criticalConnections(n, connections);
    print_edges(ans);
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
    print_edges(ans);
    // assert(ans == vector<vector<int>>({{1,3}}));
}

int main(){
    Solution sol;
    test0(sol);
    test1(sol);
}
