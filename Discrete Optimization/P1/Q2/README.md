# Minimum Cost k-Edge Subtree

Consider a complete undirected graph $G = (V,E)$. Each edge $e \in E$ is assigned a cost
$c_e$ of either 1 or 2. Find a set $E' \subseteq E$ with $|E'| = k$ such that the edges in $E'$ form a
tree (that is, the graph $(V',E')$ must be connected and acyclic for some subset of vertices
$V' \subseteq V$) and the total cost $\sum_{e \in E'} c_e$ is minimized.

## Running time
The target running time should be $O(m)$, where $m = |E|$. The complexity
bound is in the arithmetic model, i.e. addition, subtraction, multiplication, division
comparison and assignment are $O(1)$.

## Input format
The first line of input contains two integers $n$ (1 ≤ $n$ ≤ 103) and $k$ (1 ≤ $k$ ≤ $n$ − 1).
Then, n(n − 1)/2 lines follow, each containing three integers u, v (0 ≤ u, v < n, u ̸= v), and
$c$ (c ∈ {1, 2}) indicating that the edge between $u$ and $v$ has cost $c$. There will be exactly one
edge given between every possible pair of vertices.

## Output format
Output a single integer indicating the total cost of the lowest cost set $E'$
as described above.

## Sample input/output
### Sample 1
> Input: 
> 
> 4 2
> 
> 0 3 1
> 
> 2 3 1
> 
> 0 1 2
> 
> 0 2 2
> 
> 1 2 2
> 
> 1 3 2
> 
> ---------
> Output: 
> 
> 2

### Sample 2
> Input: 
> 
> 4 2
> 
> 0 3 1
> 
> 2 3 2
> 
> 0 1 2
> 
> 0 2 2
> 
> 1 2 1
> 
> 1 3 2
> 
> ---------
> Output: 
> 
> 3