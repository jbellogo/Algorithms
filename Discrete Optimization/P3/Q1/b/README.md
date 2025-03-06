# Vertex Cover of graph with exactly one cycle

Given a graph which is a tree plus one edge, find a maximum cover: set of vertices $S$ such that no two vertices in $S$ are connected by an edge.

We use DFS, only including a vertex in the cover if none of its children are in the cover.

why not BFS? because children may have more than one parent in common, given that the graph is guaranteed to have exactly one cycle.




