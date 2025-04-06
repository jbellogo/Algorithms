
// A2Q2a
// Approach 2: BFS

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


// Unweighted Directed graph w/ adjacency list representation
class Graph
{
public:

	int n;

	vector< int > *adj;
	// Such that we have adj[v] = [u1, u2, ..., u_n] 
    vector<int> orderings; // keeps counts for easy topological max. 
    // a vertex has +1 for outgoing edges and -1 for incoming ones.
	Graph(int n);

    int semiArb(int k, vector<bool> &visited);

	void addEdge(int u, int v);

    int chose_root();

	int hasArb(); // semi-arborescence starting at k (not necessarily spanning)
};

// METHOD IMPLEMENTATIONS:
Graph::Graph(int n)
{
	this->n = n;
	adj = new vector<int> [n]; 
    this->orderings = vector<int>(n);
	// Allocate V many list<iPair>'s (V sets of neighbours, one for each vertex)
}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v);
    orderings[u] +=1;
    orderings[v] -=1;
}

int Graph::chose_root(){
    int maxOrd = INT_MIN;
    int maxIndx = 0;
    for (int i=0; i<n; i++){
        if (orderings[i] > maxOrd){
            maxIndx = i;
            maxOrd = orderings[i];
        }
    }
    return maxIndx;
}


int Graph::semiArb(int k, vector<bool> &visited)
// BFS adapted
{
    queue<int> queue;
    queue.push(k);
    int ans = 0;
    visited[k] = true;

    while(!queue.empty())
    {
        int u = queue.front();
        queue.pop();
        // printf("current %d vtx: ",u);

        for (auto itr = adj[u].begin();
                itr != adj[u].end(); itr++)
        {
            // cout << "->" << *itr;
            if (!visited[*itr])
            {
                ans += 1; 
                visited[*itr] = true;
                queue.push(*itr);
            }
        }
        // printf("\n");
    }
    // printf("  ans %d\n",ans);
    return ans;
}


int Graph::hasArb()
{
    // for (int i =0; i <n; i++){
    int r = chose_root();
    vector<bool> visited(n, false); // length-n vector initialized with false 
    // cout << "root: " << r << endl;
    int semi_arb = semiArb(r, visited); // replace 0 with i
    if (semi_arb == n-1){
        // cout << semi_arb << endl;
        return true;
    }
    // }
    return false;

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

