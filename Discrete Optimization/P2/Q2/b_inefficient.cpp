
// A2Q2a

#include<bits/stdc++.h>
using namespace std;


// Unweighted Directed graph w/ adjacency list representation
class Graph
{
    int n;
public:

	vector< int > *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
    vector<int> parent; // keeps counts for easy topological max. 

	Graph(int n);

    int CYCLES = 0;

    int DFS_visit(int k, int ans);

	void addEdge(int u, int v);

	bool hasArb();
};

// METHOD IMPLEMENTATIONS:
Graph::Graph(int n)
{
	this->n = n;
	adj = new vector<int> [n]; 
    this->parent = vector<int>(n, -1); // -1 if no parent, -2 if root, else index of parent. 
}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v);
}

int Graph::DFS_visit(int k, int ans){
    for (auto v : adj[k]){
        if (parent[v] == -1){
            // Not visited
            // cout << v << " ";
            parent[v] = k;
            ans = DFS_visit(v, ans+1);
        } 
   }
    return ans;
}
        // else if (parent[v] == -2)
        // {
        //     // // This is the magic step
        //     // if (v != current_root){
        //     //     // v corresponds to a root in an connected component arborescence.
        //     //     parent[v] = k;
        //     // } else {
        //     //     // we have found a cycle. remove v's arborescne root status?
        //     // }
        //     parent[v] = k; // to pass t4,5
        //     // if (explored_acyclic_edges == V-1) // MAYBE IF WE ADD THIS FLAg counting the explored edges
        //     //     FINISHED == true; // and stop it the function at a higher-level
        //     // NOW IT FAILS t1
        //     // NEED to consider t1, t4, t5 all at once
        // }
 

bool Graph::hasArb(){
    // cout << "DFS:" << endl;
    for (int r = 0; r<n; r++){
        parent = vector<int>(n, -1); // -1 if no parent, -2 if root, else index of parent. 
        parent[r] = -2; // set as root of arborescence
        // cout << "-----DFS-RECURSIVE for root: "<< r << endl;
        int semiArbLen = DFS_visit(r, 0); // current root will not change during recurrence
        // cout << endl << "reachable vertices: " << semiArbLen << endl << endl;
        if (semiArbLen == n-1){
            return true;
        }
    }
    return false;
}


// int Graph::hasArb()
// {
//     DFS();
//     int numberRoots = 0;
//     for (int r = 0; r<n; r++){
//         if (parent[r] == -2){
//             // cout << "v: " << r << ", parent: " << parent[r] << endl; 
//             numberRoots++;
//         }
//     }
//     cout << "ROOTS: " << numberRoots << endl;
//     return numberRoots==1;
// }

int main(){
    int n, m, u, v;
    cin >> n >> m;
	Graph g(n);
    for (int j = 0; j < m; j++) {
        cin >> u >> v;
		g.addEdge(u, v);
    };
    bool boolAns = g.hasArb();
    string ans = boolAns ? "yes" : "no";
	cout << ans << endl;
    return 0;
};

