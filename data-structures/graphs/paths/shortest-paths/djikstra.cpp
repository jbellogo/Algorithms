#include<vector>
#include<cassert>
#include<queue>

using namespace std;

// this can be as complicated as you want

// struct Node {
//     int index;
// };


// BFS(r, Adj):
// 	level = {r : null}
// 	parent = {s : null}
// 	i = 1
// 	frontier = [s];
// 	while (frontier):
// 		next = [];
// 		for u in frontier:
// 			for v in Adj[u]:
// 				if v not in level:
// 					level[v] = i;
// 					parent[v] = u;
// 					next.append(v);
// 		frontier = next;
// 		i++;


void BFS(int root, vector<vector<int>> &adj) {
	queue<int>q;
	q.push(root);
	
	while(!q.empty()){
        // children at this level/rank		
		for(int i = 0 ; i<q.size() ; i++){
			int temp = q.front();
			q.pop();
		
			if(temp->right){
				q.push(temp->right);	
			}
		
			if(temp->left){
				q.push(temp->left);
			}
		
	}
		
}



class Graph {
private:
    int n;
    vector<vector<int>> adj; // stick to integer nodes for now

    Graph(int vertices){
        n = vertices;
        adj.resize(vertices);
    }

    void addEdge(int u, int v){
        assert(u < n && v < n); // valid indeces
        adj[u].push_back(v);
        adj[v].push_back(u);
    }



};