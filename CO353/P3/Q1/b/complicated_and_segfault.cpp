
// A2Q2a

#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;
typedef priority_queue< iPair, vector <iPair> , greater<iPair> > Nbrs;

// Unweighted Directed graph w/ adjacency list representation
class Graph
{
public:

	int n;
    int ANS =0;

    vector<iPair> edges; 

    vector<int> degrees; 

	Nbrs *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
	Graph(int n);

	void addEdge(int u, int v);
    void constructOrderedAdj();

    void DFS_visit(int k, vector<bool> &visited, bool include_nxt_frontier);

	void DFS(); // semi-arborescence starting at k (not necessarily spanning)

    int get_ans();

};

int Graph::get_ans(){
    return ANS;
}
// METHOD IMPLEMENTATIONS:
Graph::Graph(int n)
{
	this->n = n;
    this->degrees = vector<int>(n, 0);
	adj = new Nbrs [n]; 
}

void Graph::addEdge(int u, int v)
{
    edges.push_back(make_pair(u, v));
    degrees[u]++;
    degrees[v]++;

}

void Graph::constructOrderedAdj(){
    // THSI IS O(n*log n)
    cout << "HERE?" << endl;
    for (auto e : edges){
        int u = e.first;
        int v = e.second;
        cout << u << " "<< v << endl; 
        adj[u].push(make_pair(degrees[v], v));
        adj[v].push(make_pair(degrees[u], u));
    }
    cout << "YES IT IS THERE ^^^" << endl;

}


void Graph::DFS_visit(int k, vector<bool> &visited, bool include_nxt_frontier)
// BFS adapted
{
    visited[k] = true;
    if (include_nxt_frontier) {
        ANS ++;
        include_nxt_frontier = false;
    } else {
        include_nxt_frontier = true;
    }

    while(!adj[k].empty())
    {
        int v = adj[k].top().second; // v is neighbour, first is degree.
        adj[k].pop();
        if (!visited[v]){
            DFS_visit(v, visited, include_nxt_frontier);
        }
    }
}


void Graph::DFS()
{
    // for (int i =0; i <n; i++){
    // int r = chose_root(); // it can just be 0 WLOG
    int r = adj[0].top().second; // make sure you pick a starting vertex that will be included in the solution set
    ANS++;
    cout << "visited vec?" << endl;
    vector<bool> visited(n, false);
    // Graph is connected!
    visited[r] = true;
    cout << "DFS" << endl;

    DFS_visit(r, visited, false);

}

int main(){
    int n, u, v;
    cin >> n;
	Graph G(n);
    for (int j = 0; j < n; j++) {
        cin >> u >> v;
		G.addEdge(u, v);
    }
    G.constructOrderedAdj();
    G.DFS();
	cout << G.get_ans() << endl;
    return 0;
};

