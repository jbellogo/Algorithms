package org.example;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class MainTest {

    @Test
    void differBySingleLetterTest1() {
        Main sol = new Main();
        assertFalse(sol.differBySingleLetter("cat", "motocicleta"));
        assertFalse(sol.differBySingleLetter("cat", "tac"));

        assertTrue(sol.differBySingleLetter("cat", "rat"));
        assertTrue(sol.differBySingleLetter("abcdefgH", "abcdefgX"));
        assertTrue(sol.differBySingleLetter("hit", "hot"));
        assertTrue(sol.differBySingleLetter("hot", "dot"));
        assertTrue(sol.differBySingleLetter("hot", "lot"));
        assertTrue(sol.differBySingleLetter("log", "lot"));
        assertTrue(sol.differBySingleLetter("log", "cog"));
        assertTrue(sol.differBySingleLetter("dog", "cog"));
        assertTrue(sol.differBySingleLetter("dog", "dot"));
    }

    @Test
    void ladderLengthTest1(){
        Main sol = new Main();
        List<String> words = new ArrayList<>(Arrays.asList("hot","dot","dog","lot","log","cog"));
        int ans = sol.ladderLength("hit", "cog", words);
        assertEquals(5, ans);
    }


}