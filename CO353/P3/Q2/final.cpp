
// A3Q2

#include<bits/stdc++.h>
using namespace std;

// Unweighted undirected graph w/ adjacency list representation
class Graph
{
public:

	int n;
    int m;

    vector<bool> ANS; // initialized with zeroes. 
    vector<int> S; // Solution set

    int ANS_CUT = 0; // vertices adjacent to ANS vector set

	vector< int > *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
	Graph(int n, int m);

	void addEdge(int u, int v);

	void MaxCutApprox();

    int getSharedEdges(int v);

    void printANS();
};

// METHOD IMPLEMENTATIONS:
Graph::Graph(int n, int m)
{
	this->n = n;
    this->m = m;
    ANS = vector<bool> (n, false);
	adj = new vector<int> [n]; 
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int Graph::getSharedEdges(int v){
    int shared_edges = 0;
    // cout << "S : "; 
    // for (int u = 0; u < n; u++){
    //     if (ANS[u]){
    //         cout << u+1 << " ";
    //     }
    // }
    // cout << endl;
    // cout << "Incident edges of S with v = " << v+1 << endl;
    for (int i : adj[v]){
        if (ANS[i] == true){
            shared_edges++;
        }
    }
    // cout << endl << endl;
    return shared_edges;
}

void Graph::printANS(){
    /// PRINT ANSWER
    cout << S.size() << endl;
    for (int i : S){        
        cout << i+1 << " ";
    }
    cout << endl;
}


void Graph::MaxCutApprox()
{
    // Uses local search greedy. 
    for (int v = 0; v < n; v++){
        // cout << "CURRENT CUT SIZE = " << ANS_CUT << endl;
        if (2*ANS_CUT >= m) {
            break;
        }
        if (!ANS[v]){       
            int deg = adj[v].size();  // PROBABLY shold make sure adjacency list items match 1-1 with edges
            int CUT = getSharedEdges(v);  // THIS computation is different based on ANS[v]. 
            if (CUT*2<deg){
                // add it
                ANS[v] = true;
                S.push_back(v);
                // cout << "adding to cut" << ANS_CUT << " += " << deg << "-" << CUT << endl; 
                ANS_CUT += deg - 2*CUT;
            }
        }
    }

}


int main(){
    int n, m, u, v;
    cin >> n >> m;
	Graph G(n, m);
    for (int j = 0; j < m; j++) {
        cin >> u >> v;
		G.addEdge(u-1, v-1);
    }
    G.MaxCutApprox();
    G.printANS();
    return 0;
};

