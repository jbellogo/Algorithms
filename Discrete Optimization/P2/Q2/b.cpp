
// A2Q2a
// Approach 1: DFS

#include <iostream>
#include <vector>

using namespace std;


// Unweighted Directed graph w/ adjacency list representation
class Graph
{
    int n;
public:

	vector< int > *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
    vector<int> parent;

	Graph(int n);

    int CYCLES = 0;

    void DFS_visit(int k, int current_root);

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

void Graph::DFS_visit(int k, int current_root){
    for (auto v : adj[k])
    {
        if (parent[v] == -1){ // v is unexplored
            // Not visited
            // cout << v << " ";
            parent[v] = k;
            DFS_visit(v, current_root);
        } 
        else if (parent[v] == -2) // v is a semi-arborescence root
        {
            // This is the magic step
            parent[v] = k; // connect arborescence or possibly cycles 
            if (v == current_root){
                // we have found a cycle. keep track of disjoint cycles. 
                CYCLES +=1; // this is actually disjoint cycles. not total cycles.. which is what we want. IS IT?
            } 
        }
    }
}
 

bool Graph::hasArb(){
    // cout << "DFS:" << endl;
    for (int r = 0; r<n; r++){
        if (parent[r] == -1){
            parent[r] = -2; // set as root of arborescence
            // cout << "-----DFS-RECURSIVE for root: "<< r << endl;
            DFS_visit(r, r); // current root will not change during recurrence
        }
        // cout << endl << "reachable vertices: " << semiArbLen << endl << endl;
    }
    int maxArbLen=0;
    for (int v=0; v < n; v++){
        if (parent[v] == -2){
            maxArbLen += 1;
        }
    }
    // cout << "roots: " << maxArbLen << endl;
    // cout << "cycles: " << CYCLES << endl;
    return (maxArbLen + CYCLES == 1) or maxArbLen==1;
}



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

