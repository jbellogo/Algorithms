// Main implementation of prims algorithm inspired from geeksforgeeks
// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl

#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

// Directed graph w/ adjacency list representation
// Class definition. Abstracted from method implementeations for readability
class Graph
{
	int V; // No. of vertices
	list< pair<int, int> > *adj; 	
	// ptr to a list(<v,w>) 
	// adj is a ptr to ONE adjacency list for ONE vertex v (the first one)
	// we don't have to say give me list<list<iPair>> because, 
	// we know the outside list will have length = V so we can optimize
	// we have adj[v] = [(u1, w(vu1)), [u2, w(vu2), ...] 

public:
	Graph(int V); // Constructor

	// function to add an edge to graph
	void addEdge(int u, int v, int w);

	// Print MST weight using Prim's algorithm
	int kMinTreeWeight(int k);
};

// METHOD IMPLEMENTATIONS:
///// Constructor
Graph::Graph(int V)
{
	this->V = V; // belonging to THIS object... it's like self in python
	adj = new list<iPair> [V]; 
	// Allocate V many list<iPair>'s and, 
	// return the address to the first list<iPair>
}
//// Don't need destructor with "delete [] adj"?

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w)); // like a tuple (v,w)
	adj[v].push_back(make_pair(u, w));
}

// Uses prim's algorithm to caclulate the number of maximally connected edges of weight one
int Graph::kMinTreeWeight(int k)
{
	// Create a min heap
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	int src = 0; // Taking vertex 0 as source

	// Create a vector for keys and initialize all
	vector<int> key(V, INF);

	// To keep track of vertices included in MST
	vector<bool> inMST(V, false);

	// Insert source itself in priority queue and initialize
	pq.push(make_pair(0, src));
	key[src] = 0;

	// Things for Q2
	int CURR_CONSECUTIVE_ONES = 0;

	// priority queue to store sizes of connected-ones-clusters "COCs" in descending order
    priority_queue<int> cocs; 

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();

		if(inMST[u] == true){
			continue;
		}
	
		inMST[u] = true;

		///////////////

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
		///////////////

		// 'i' is used to get all adjacent vertices of a vertex
		list< pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;
			// If v is not in MST and weight of (u,v) is smaller
			// than current key of v
			if (inMST[v] == false && key[v] > weight)
			{
				// Updating key of v
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
