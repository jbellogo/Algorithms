# Maximum Weight Independent Set of Vectors

## Problem
Given a set of vectors in m-dimensional space over the field of integers modulo 2, where addition and multiplication are performed modulo 2, find a linearly independent subset of the vectors that maximizes the total sum of the weights of the vectors.

## Insight 
The problem can be formulated as a matroid. And a key result of matroids is that a greedy algorithm provides an optimal solution. The greedy algorithm is as follows:
1. Sort the vectors by their weights in descending order.
2. Iterate through the sorted vectors and add them to the subset if they result in a linearly independent set, else discard them.
3. Return the sum of the weights of the vectors in the subset.

## Input
First line: n number of vectors, m dimension of vectors. We have n vectors in m-dimensional space over the field of integers modulo 2, where addition and multiplication are performed modulo 2.
Next n lines: each line contains 1+m integers, the first integer is the weight of the vector, the rest are the elements of the vector.

## Output
A single integer, the maximum sum of the weights of the vectors in a linearly independent subset of the vectors.

## Running time
The running time is $O(n^3 * m)$ because we need to sort the vectors by their weights.

## Sample Input/Output
### Sample 1
> Input:
> 
> 7 5
> 
> 1 1 0 0 0 0 
> 
> 2 0 1 0 0 0
> 
> 3 0 0 0 0 1
> 
> 4 1 0 0 0 1
> 
> 5 0 1 0 0 1
> 
> 6 1 1 0 0 0
> 
> 7 1 1 0 0 1
> 
> ---------
> Output: 
> 
> 18