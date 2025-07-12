package org.example;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {


    public static boolean differBySingleLetter(String w1, String w2){
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

    public static Graph<String> createGraph(List<String> words){
        Graph<String> g = new Graph<>();
        for (int i = 0 ; i < words.size() ; i++){
            for (int j = i+1 ; j < words.size() ; j++){
                String w1 = words.get(i);
                String w2 = words.get(j);
                if (differBySingleLetter(w1, w2)){
                    g.addEdge(w1, w2);
                }
            }
        }
        return g;
    }

    public int ladderLength(String beginWord, String endWord, List<String> wordList) {
        List<String> copyList = new ArrayList<>(wordList); // make a modifiable copy
        if (!copyList.contains(beginWord)){
            copyList.add(beginWord);
        }
        Graph<String> g = createGraph(copyList);
        List<String> ans = g.shortestUVPath(beginWord, endWord);
        System.out.println(ans);
        return ans.size();
    }


        public static void main(String[] args) {
        List<String> words = Arrays.asList("hit", "hot", "dot", "dog", "lot", "log", "cog", "kog");
        Graph<String> g = createGraph(words);
        g.printGraph();
        List<String> ans = g.shortestUVPath("hit", "kog");
        System.out.println(ans);
    }
}