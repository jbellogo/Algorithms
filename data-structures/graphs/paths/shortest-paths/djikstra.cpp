#include<vector>
#include<cassert>
#include<queue>
#include<iostream>

using namespace std;

// this can be as complicated as you want
// struct Node {
//     int index;
// };

typedef pair<int, int> iPair;

// Weighted Graph
class Graph {
private:
    int n;
    vector<vector<pair<int, int>>> adj; 
    // ej. adj[0] = [{1,10}, {2,20}] means vtx 0 has an edge with vtx 1 of weight 10 

public:
    Graph(int vertices){
        n = vertices;
        adj.resize(vertices);
    }

    void addEdge(int u, int v, int weight = 1){
        assert(u < n && v < n); // valid indeces
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    void BFS(int root) {
        // Visit the graph
        cout << "starting from root: " << root << endl;
        queue<int> frontier;
        frontier.push(root);
    
        vector<int> parents(n,-1);
        parents[root] = -2; // needs to be differentiated

        int level = 0;
        vector<int> levels(n, 0);
        
        while(!frontier.empty()){
            level++;
            // This is loop is not stricctly necessary, just helps you deal with children at one level at a time.
            for(int i = 0 ; i < frontier.size() ; i++){   
                int u = frontier.front();
                frontier.pop();
                for (auto &vw : adj[u]){
                    int v = vw.first;
                    int w = vw.second;
                    // if you haven't visited, visit it. 
                    if (parents[v] == -1){
                        cout << " - visiting node: " << v << " at level: " << level << endl;
                        parents[v] = u;
                        levels[v] = level;
                        frontier.push(v);
                    }
                }
            }
        }
    }

    vector<int> djikstra(int r) {
        
        // COMPUTES SHORTEST PATH DISTANCES FROM r to all other vertices.
            
        // Min heap priority queue to hold 
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
        // Note, to avoid having to implement your own comparator, use greater<iPair>, 
        // it will compare the first elements of the template T, which in this case is the first of the iPair. 
        // @IMPORTANT: So we need to reverse orders and store WEIGHTS FIRST and u vertices second
        
        // Current shortest path distances initialized to +INFINITY
        vector<int> dist(n, INT_MAX);
    
        // STP distance from root is initialized to 0 
        pq.push(make_pair(0, r));  // (weight, vtx)
        dist[r] = 0;
    
        while (!pq.empty()) {

            int u = pq.top().second; // second is the vtx, first is the weight (enables us to use default comparator)
            pq.pop();

            for (auto &[v, w] : adj[u]) {
                // If there is shorter path to v through u.
                if (dist[v] > dist[u] + w) {
                    // Updating distance of v
                    dist[v] = dist[u] + w;
                    pq.push(make_pair(dist[v], v)); 
                    // we are no longer storing the weights but the shortest paths in pq, we prioritize shortest paths over biggger single edges... wow 
                }
            }
        }
        // / TESTING
        cout << "DJIKSTRA:" << endl;
        printf("Vertex | Distance from Source\n");
        for (int i = 0; i < n; ++i)
            printf("\t%d \t|\t %d\n", i, dist[i]);
        return dist;
    }



};


void testBFS(){
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.BFS(0);
}


void test0(){
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.djikstra(0);
}


int main(){
    test0();
}