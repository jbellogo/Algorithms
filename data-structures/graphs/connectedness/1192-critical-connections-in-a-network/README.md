# 1192 Critical connections in a network 

## Difficulty: HARD

There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:


Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
Example 2:

Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
 

Constraints:

2 <= n <= 105
n - 1 <= connections.length <= 105
0 <= ai, bi <= n - 1
ai != bi
There are no repeated connections.



# bruteforce improvement 

Ideas for increased efficiency:
1. Synthezise adjacency representation and leave-one-out logic into a O(n) time. 
We will start with a base adjencency list with all the edges. Then for each leave-one-out edge e=uv, we will ignore it's values if they match u or v