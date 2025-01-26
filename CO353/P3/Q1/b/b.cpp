
// A2Q2a

#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

// Unweighted Directed graph w/ adjacency list representation
class Graph
{
public:

	int n;

    int ANS =0;

	vector< int > *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
	Graph(int n);

	void addEdge(int u, int v);

    bool DFS_visit(int k, vector<bool> &visited, vector<bool> &inSolSet);

	void DFS();

    int get_ans();

    int find_leaf();
};

int Graph::get_ans(){
    return ANS;
}
// METHOD IMPLEMENTATIONS:
Graph::Graph(int n)
{
	this->n = n;
	adj = new vector<int> [n]; 
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}


bool Graph::DFS_visit(int k, vector<bool> &visited, vector<bool> &inSolSet)
// BFS adapted
{
    bool hasChildrenInAnswerSet = false;
    visited[k] = true;
    for (int v : adj[k]) 
    {
        if (!visited[v]){
            hasChildrenInAnswerSet |= DFS_visit(v, visited, inSolSet);
        } else {
            hasChildrenInAnswerSet |= inSolSet[v];
        }
    }
    // cout <<  k  << " has children in solset? " << hasChildrenInAnswerSet << endl;
    if (hasChildrenInAnswerSet == false){
        ANS++;
        // if all its children have 0s, include it
        inSolSet[k] = true;
    }
    return (!hasChildrenInAnswerSet);

}

int Graph::find_leaf(){
    for (int i=0; i<n; i++){
        // cout << i << " has #nbrs: " <<  adj[i].size() << endl;
        if (adj[i].size() == 1) {
            return i;
        }
    }
    return 0; // if G has no leaves then it is a pure cycle so any starting point will do. 
}


void Graph::DFS()
{
    int r = find_leaf(); // adj[0].top().second; // make sure you pick a starting vertex that will be included in the solution set
    // cout << "root: " << r << endl; 
    vector<bool> visited(n, false);
    vector<bool> solset(n, false); // solution set.
    // Graph is connected!
    visited[r] = true;
    DFS_visit(r, visited, solset);

}

int main(){
    int n, u, v;
    cin >> n;
	Graph G(n);
    for (int j = 0; j < n; j++) {
        cin >> u >> v;
		G.addEdge(u-1, v-1);
    }
     G.DFS();
	cout << G.get_ans() << endl;
    return 0;
};

