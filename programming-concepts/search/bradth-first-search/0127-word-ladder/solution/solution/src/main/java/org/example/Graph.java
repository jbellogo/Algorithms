package org.example;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;

// non-directed graph implementation
// Generic type parameters for nodes supporting any type and or class.
// @TODO test this class
public class Graph<T> {

    private Map<T,List<T>> adj = new HashMap<>();

    public void addEdge(T v1, T v2){
        if (!adj.containsKey(v1)) {
            adj.put(v1, new LinkedList<>()); // List is abstract, cannot be instantiated
        }
        if (!adj.containsKey(v2)){
            adj.put(v2, new LinkedList<>());
        }
        adj.get(v1).add(v2);
        adj.get(v2).add(v1);
    }

    public void printGraph(){
        for (T key : adj.keySet()) {
            System.out.print(key + ": ");
            System.out.println(adj.get(key));
        }
    }

    public List<T> shortestUVPath(T start, T end){
        // uses BFS
        Queue<T> frontier = new LinkedList<>();
        frontier.add(start);

        Map<T, T> parents = new HashMap<>();
        parents.put(start, null);

        Map<T, Integer> shortestDistancesFromU = new HashMap<>();
        for (T key : adj.keySet()) {
            shortestDistancesFromU.put(key, Integer.MAX_VALUE); // -1 for unvisited vertices
        }
        shortestDistancesFromU.put(start, 0);

        while(!frontier.isEmpty()){
            T u = frontier.remove();

            for (T v : adj.get(u)){
                int distanceThroughU = shortestDistancesFromU.get(u)+1;
                if (!parents.containsKey(v)){
                    // visit for the first time,
                    parents.put(v, u);
                    shortestDistancesFromU.put(v, distanceThroughU);
                    frontier.add(v); // only enqueue unvisited vertices
                }
                // Do this every time to update shortest paths
                if (distanceThroughU < shortestDistancesFromU.get(v)){
                    shortestDistancesFromU.put(v, distanceThroughU);
                    parents.put(v, u);
                }
            }
        }

        List<T> shortestPathReversed = new LinkedList<>();
        shortestPathReversed.add(end);
        T current_node = parents.get(end);
        while(current_node != start){
            shortestPathReversed.add(current_node);
            current_node =  parents.get(current_node);
        }
        shortestPathReversed.add(start);
        return shortestPathReversed.reversed();
    }
}
