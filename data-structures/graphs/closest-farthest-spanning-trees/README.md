# Difficulty: Extra Hard

From CO 353

# Closest and Farthest Spanning Trees.

You are given a connected undirected graph $G = (V,E)$ where each edge $e \in E$ is assigned
an integer weight $w_e$. A root vertex $r \in V$ is also given. We denote the shortest-path distance
in $G$ (with respect to the weights $w_e$) from $r$ to a vertex $v$ by $d_v$. The shortest-path distance
in $G$ from $r$ to an edge $e$ between vertices $u$ and $v$ is defined as $d_e := \min\{d_u, d_v\}$.

For a spanning tree $T$ of $G$, we say that the *closeness* of $T$ to $r$ is the sum of $d_e$ for all edges
e ∈ T. Find the minimum and maximum closeness values among all spanning trees of G.

## Running time
The target running time should be $O(m \log n)$, where $|V| = n$ and $|E| = m$.
The complexity bound is in the arithmetic model, i.e. addition, subtraction, multiplication,
division, comparison, and assignment are $O(1)$.

## Input format 
The first line of input contains three integers:
* $n$ (1 ≤ $n$ ≤ 105)
* $m$ (0 ≤ $m$ ≤ min{105, $n$ · ($n$ − 1)/2}), 
* $r$ (0 ≤ $r$ < $n$).

Then, $m$ lines follow, each containing three integers $u$, $v$ (0 ≤ $u$ < $v$ < $n$), and $w$ (0 ≤ $w$ ≤ 109) indicating the graph has an edge between $u$ and $v$ of weight $w$.

## Output forma
One line containing two integers, indicating the closeness of the closest spanning tree and the farthest spanning tree.


## Sample input/output.
### Sample 1
> Input:
> 
> 4 6 3
> 
> 0 2 4
> 
> 1 3 10
> 
> 0 3 7
> 
> 2 3 7
> 
> 0 1 5
> 
> 1 2 5
> 
> ---------
> Output:
> 
> 0 14


### Sample 2
> Input: 
> 
> 5 6 4
> 
> 3 4 3
> 
> 0 4 4
> 
> 1 2 1
> 
> 0 3 0
> 
> 1 4 8
> 
> 1 3 6
> 
> ---------
> Output:
> 
> 8 14