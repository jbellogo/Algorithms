// Main implementation of prims algorithm inspired from geeksforgeeks

#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

// Directed graph w/ adjacency list representation
class Graph
{
	int V;

	list< pair<int, int> > *adj; 	
	// Such that we have adj[v] = [(u1, w(vu1)), [u2, w(vu2), ...] 
public:
	Graph(int V);

	void addEdge(int u, int v, int w);

	int kMinTreeWeight(int k);
};

// METHOD IMPLEMENTATIONS:
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair> [V]; 
	// Allocate V many list<iPair>'s (V sets of neighbours, one for each vertex)
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w)); // make_pair(v,w) is edge representation
	adj[v].push_back(make_pair(u, w));
}

// Uses prim's algorithm to caclulate the weight/size of all clusters
// of maximally connected edges of weight one.
// Put them in a MAX HEAP priority queue
int Graph::kMinTreeWeight(int k)
{
	// Create a MIN heap for prim's. Priority given to smaller weight edges.
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	int r = 0; // Let vtx 0 be the root

	// key[v] = w(uv) such that uv is in the MST
	vector<int> key(V, INF);

	// Vertex v in MST? (quicker than lookup through iteration)
	vector<bool> inMST(V, false);

	// Initialize max heap for prims
	pq.push(make_pair(0, r));
	key[r] = 0;

	// Size of current Consecutive Ones Cluster
	int CURR_CONSECUTIVE_ONES = 0;

	// MAX heap to store sizes of connected-ones-clusters "COCs" (pop max priority first)
    priority_queue<int> cocs; 

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if(inMST[u] == true){
			continue;
		}
	
		inMST[u] = true;

		if(key[u] == 1){ 
			CURR_CONSECUTIVE_ONES += 1;
		} else {
			if(CURR_CONSECUTIVE_ONES != 0) {
				cocs.push(CURR_CONSECUTIVE_ONES);
				CURR_CONSECUTIVE_ONES = 0;
			}
		}
		if(CURR_CONSECUTIVE_ONES >= k){
			return k;
		}

		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;
			if (inMST[v] == false && key[v] > weight)
			{
				key[v] = weight;
				pq.push(make_pair(key[v], v));
			}
		}

	}
	if (CURR_CONSECUTIVE_ONES != 0){
		cocs.push(CURR_CONSECUTIVE_ONES);
	}
	int ANS = 0;
	while(!cocs.empty()){
		int block_len = cocs.top();
		cocs.pop();
		if(block_len < k){
			ANS += block_len;
			ANS += 2;
			k -= block_len;
			k -=1;
		} else {
			ANS += k;
			k = 0;
		}
	}
	if(k != 0){
		ANS += 2*k;
	}
	return ANS;
}


int main(){
    int n, k, u, v, w;
    cin >> n >> k;
    int lim  = n*(n-1)/2;
	Graph g(n);
    while(cin >> u >> v >> w) {
		g.addEdge(u, v, w);
        --lim;
        if (lim == 0) {break;}
    };
	cout << g.kMinTreeWeight(k);
    return 0;
};
