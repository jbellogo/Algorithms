
// A2Q2a
// Uses BFS to approximate maximum cuts.
// Algorithm is wrong as 2-approx , sometimes it underpredicts a cut with edges < E/2

#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

// Unweighted Directed graph w/ adjacency list representation
class Graph
{
public:

	int n;

    vector<int> ANS;

	vector< int > *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
	Graph(int n);

	void addEdge(int u, int v);

    void BFS(int k, vector<bool> &visited, vector<bool> &inSolSet);

	void MaxVtxCov();
};

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


void Graph::BFS(int k, vector<bool> &visited, vector<bool> &inSolSet)
// BFS adapted
{
    vector<int> frontier;
    frontier.push_back(k);
    bool even_iter = true;
    while (frontier.size() !=0){
        vector<int> next;
        // cout << "frontier: ";
        for (int i : frontier){
            // cout << i+1 << " ";
            if (even_iter){
                inSolSet[i] = true;
            }
            for (int v : adj[i]) {
                if (!visited[v]){
                    visited[v] = true;
                    next.push_back(v);
                }
            }
        }
        // cout << endl;
        frontier = next;
        even_iter = !even_iter;
    }
}


void Graph::MaxVtxCov()
{
    int r = 0; 
    // cout << "root: " << r+1 << endl; 
    vector<bool> visited(n, false);
    vector<bool> solset(n, false); // solution set.
    // Graph is connected!
    for (int i = 0; i < n; i++){
        if (!visited[r]) {
            visited[r] = true;
            BFS(r, visited, solset);
        }
    }
    for (int i = 0; i< n ; i++){
        if (solset[i]){
            ANS.push_back(i+1); // to rewrite into inpit format >0
        }
    }
    /// PRINT ANSWER
    int l = ANS.size();
    cout << l << endl;
    for (int i = 0; i< l-1 ; i++){
        cout << ANS[i] << " ";
    }
    cout << ANS[l-1] << endl;
}

int main(){
    int n, m, u, v;
    cin >> n >> m;
	Graph G(n);
    for (int j = 0; j < m; j++) {
        cin >> u >> v;
		G.addEdge(u-1, v-1);
    }
    G.MaxVtxCov();
    return 0;
};

