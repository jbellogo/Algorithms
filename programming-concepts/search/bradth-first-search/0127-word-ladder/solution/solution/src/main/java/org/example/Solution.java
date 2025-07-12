package org.example;
// This is for submission

import java.util.*;

class Solution {

    private Map<String, List<String>> adj = new HashMap<>();

    private void addEdge(String v1, String v2){
        if (!adj.containsKey(v1)) {
            adj.put(v1, new LinkedList<>()); // List is abstract, cannot be instantiated
        }
        if (!adj.containsKey(v2)){
            adj.put(v2, new LinkedList<>());
        }
        adj.get(v1).add(v2);
        adj.get(v2).add(v1);
    }


    private int shortestUVPath(String start, String end){
        // uses BFS
        Queue<String> frontier = new LinkedList<>();
        frontier.add(start);

        Map<String, String> parents = new HashMap<>();
        parents.put(start, null);

        Map<String, Integer> shortestDistancesFromU = new HashMap<>();
        for (String key : adj.keySet()) {
            shortestDistancesFromU.put(key, Integer.MAX_VALUE); // -1 for unvisited vertices
        }
        shortestDistancesFromU.put(start, 0);

        while(!frontier.isEmpty()){
            String u = frontier.remove();

            for (String v : adj.get(u)){
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
        List<String> shortestPathReversed = new LinkedList<>();
        shortestPathReversed.add(end);
        String current_node = parents.get(end);
        while(!Objects.equals(current_node, start)){
            shortestPathReversed.add(current_node);
            current_node =  parents.get(current_node);
        }
        shortestPathReversed.add(start);
        return shortestPathReversed.size();
    }


    private boolean differBySingleLetter(String w1, String w2){
        if (w1.length() != w2.length()) return false;
        boolean firstDifference = false;
        for (int i = 0; i < w1.length(); i++){
            // they are not equal -> only one difference allowed
            if (w1.charAt(i) != w2.charAt(i)){
                if (!firstDifference){
                    firstDifference = true; // If it's the first diff, cool, keep going
                } else {
                    return false;
                }
            }
            // if they are the same keep going
        }
        // if no first diff -> words are the same.
        return firstDifference;
    }

    private void createGraph(List<String> words){
        for (int i = 0 ; i < words.size() ; i++){
            for (int j = i+1 ; j < words.size() ; j++){
                String w1 = words.get(i);
                String w2 = words.get(j);
                if (differBySingleLetter(w1, w2)){
                    addEdge(w1, w2);
                }
            }
        }
    }

    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        List<String> words = new ArrayList<>(wordList); // make a modifiable copy
        if (!words.contains(beginWord)){
            words.add(beginWord);
        }
        createGraph(words);
        return shortestUVPath(beginWord, endWord);
    }
}
