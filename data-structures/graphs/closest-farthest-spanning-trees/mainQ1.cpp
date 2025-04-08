// Djikstras algorithm using priority_queue inspired from geeksforgeeks
// Adaptation of prims is based on prim's implementation in geeksforgeeks

#include<bits/stdc++.h>
using namespace std;

// iPair ==> Integer Pair (small, big)
typedef pair<long long int, long long int> iPair;


// Directed graph w/ adjacency list representation
class Graph
{
	int V;

	list< iPair > *adj; 	
	// Such that we have adj[v] = [(u1, w(vu1)), (u2, w(vu2)),  ...] 
public:
	Graph(int V);

	void addEdge(int u, int v, int w);

	vector<long long int> djikstraSTPs(int r); // return by value

    void update_edge_weights(const vector<long long int>& dj_out);

    void getMaxMinSTWts(int r); // Adaptation of Prims to get MST and MaxST total weights
};


// METHOD IMPLEMENTATIONS:
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair > [V]; 
	// Allocate V many list<pairs>'s (V sets of neighbours, one for each vertex)
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w)); // make_pair(v,w) is edge representation
	adj[v].push_back(make_pair(u, w));
}

vector<long long int> Graph::djikstraSTPs(int r)
{
    // Min heap priority queue to hold 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    
    // Current shortest path distances initialized to +INFINITY
    vector<long long int> dist(V, LLONG_MAX);
 
    // STP distance from root is initialized to 0 
    pq.push(make_pair(0, r));  // priority, vtx
    dist[r] = 0;
 
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
 
        list<iPair >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            int v = (*i).first;
            long long int weight = (*i).second;
            // If there is shorter path to v through u.
            if (dist[v] > dist[u] + weight) {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    // / TESTING
    // printf("DJIKSTRA: Vertex Distance from Source\n");
    // for (int i = 0; i < V; ++i)
    //     printf("%d \t\t %lld\n", i, dist[i]);
    return dist;
}

void Graph::update_edge_weights(const vector<long long int>& dj_out) 
{
    // printf("UPDATE EDGE WEIGHTS");
    for (int u = 0; u<V;u++){
        list< iPair >::iterator e;
        for (e = adj[u].begin(); e != adj[u].end(); ++e) {
            int v = e->first;
            long long int weight = e->second;
            long long int newW = dj_out[v] < dj_out[u] ? dj_out[v] : dj_out[u]; // returns minimum
            e->second = newW;
            // cout << "w(" << u << v << "): " << e->second << endl;
        }
    }
}

void Graph::getMaxMinSTWts(int r){

    // MAX heap priority
    priority_queue< iPair > pqMax; 
    vector<long long int> keysMax(V, LLONG_MIN); // initialize to negative number st all positive weights will overwrite
    vector<bool> inMaxST(V, false);
    pqMax.push(make_pair(0, r));
    keysMax[r] = 0;

    // MIN heap priority
    priority_queue< iPair, vector <iPair> , greater<iPair> > pqMin;
    vector<long long int> keysMin(V, LLONG_MAX);
    vector<bool> inMinST(V, false);
    pqMin.push(make_pair(0, r));
    keysMin[r] = 0;

    long long int MAX_COUNT = 0;
    long long int MIN_COUNT = 0;

    while (!pqMin.empty())
    {
        ///////////////////////////
        int u = pqMin.top().second;
        pqMin.pop();
        if(inMinST[u] == true){continue;}
        inMinST[u] = true; // we will be adding this to the path
        MIN_COUNT += keysMin[u];
        list< iPair >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            long long int weight = (*i).second;
            if (inMinST[v] == false && keysMin[v] > weight)
            {
                keysMin[v] = weight;
                pqMin.push(make_pair(keysMin[v], v));
            }
        }
            ///////////////////////////
    }

    while(!pqMax.empty()){
        ///////////////////////////
        int u = pqMax.top().second;
        pqMax.pop();
        if(inMaxST[u] == true){continue;}
        inMaxST[u] = true;
        MAX_COUNT += keysMax[u];
        list< iPair >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            long long int weight = (*i).second;
            if (inMaxST[v] == false && keysMax[v] < weight)
            {
                keysMax[v] = weight;
                pqMax.push(make_pair(keysMax[v], v));
            }
        }
        ///////////////////////////
    }
    // printf("PRIMS\n");
    cout << MIN_COUNT << " " << MAX_COUNT << endl;
}

int main(){
    int n, m, r, u, v, w;
    cin >> n >> m >> r;
	Graph g(n);
    if (m == 0) {
        cout << "0 0" << endl;
        return 0;
    }
    while(cin >> u >> v >> w) {
		g.addEdge(u, v, w);
        --m;
        if (m == 0) {break;}
    };
	vector<long long int> dj_out = g.djikstraSTPs(r);
    // printf("MAX/MIN STW of original: ");
    // g.getMaxMinSTWts(r);
    g.update_edge_weights(dj_out);
    // printf("MAX/MIN STW of      new: ");
    g.getMaxMinSTWts(r);
    return 0;
};


