# Connected cells
This is a matrix connectivity problem where we need to find the largest connected region of 1s in a binary matrix (containing only 0s and 1s). 

# Ideas:
1. It Reduces to depth first search, just like an adjacency matrix can represent a graph.
2. When dealing with matrix questions, use (row, col) as opposed to (x,y) for the indeces.


### Problem Definition: 
Given a matrix filled with 0s and 1s, find the size of the largest region where 1s are connected to each other.

### Connection Rules: 
Two 1s are considered connected if they are adjacent to each other in any of 8 possible directions:

- 4 cardinal directions (up, down, left, right)
- 4 diagonal directions (top-left, top-right, bottom-left, bottom-right)


## DFS Components:
### dfs_wrapper: 
Lets iterate through x and y in the dfs_wrapper (quadratic time) 
considering (i,j) as a root to start our recursive search for the maximally connected component reachable from it. 

### dfs_recursive:
 We check its nbrs (8 possible 2 horizontal, 2 vertical, and 4 diagonal) and recurse on the first one that is one. 

