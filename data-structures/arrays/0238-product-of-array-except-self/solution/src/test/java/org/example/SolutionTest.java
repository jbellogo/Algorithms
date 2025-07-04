package org.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;
import java.util.Arrays;

class SolutionTest {
    @Test
    void testGetPrefixProducts1(){
        Solution sol = new Solution();
        int [] input = new int[]{1,2,3,4};
        // Prefix
        int[] actual = sol.getPrefixProducts(input);
        int[] expected = {1,1,2,6};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetPrefixProducts2(){
        Solution sol = new Solution();
        int[] actual = sol.getPrefixProducts(new int[]{});
        int[] expected = {};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetPrefixProducts3(){
        Solution sol = new Solution();
        int[] actual = sol.getPrefixProducts(new int[]{10});
        int[] expected = {1};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetPrefixProducts4(){
        Solution sol = new Solution();
        int[] actual = sol.getPrefixProducts(new int[]{10, 3, 5, -3, 6, 2});
        int[] expected = {1, 10, 30, 150, -450, -2700};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetPrefixProducts5(){
        Solution sol = new Solution();
        int[] actual = sol.getPrefixProducts(new int[]{-1,1,0,-3,3});
        int[] expected = {1, -1, -1, 0, 0};
        assertArrayEquals(expected, actual);
    }

    // Suffix tests
    @Test
    void testGetSuffixProducts1(){
        Solution sol = new Solution();
        int [] input = new int[]{1,2,3,4};
        int[] actual = sol.getSuffixProducts(input);
        int[] expected = {24,12,4,1};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetSuffixProducts2(){
        Solution sol = new Solution();
        int[] actual = sol.getSuffixProducts(new int[]{});
        int[] expected = {};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetSuffixProducts3(){
        Solution sol = new Solution();
        int[] actual = sol.getSuffixProducts(new int[]{10});
        int[] expected = {1};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetSuffixProducts4(){
        Solution sol = new Solution();
        int[] actual = sol.getSuffixProducts(new int[]{10, 3, 5, -3, 6, 2});
        int[] expected = {-540, -180, -36, 12, 2, 1};
        assertArrayEquals(expected, actual);
    }

    @Test
    void testGetSuffixProducts5(){
        Solution sol = new Solution();
        int[] actual = sol.getSuffixProducts(new int[]{-1,1,0,-3,3});
        int[] expected = {0, 0, -9, 3, 1};
        assertArrayEquals(expected, actual);
    }

    // Test productExceptSelf
    @Test
    void testProductExceptSelf1(){
        Solution sol = new Solution();
        int[] actual = sol.productExceptSelf(new int[]{-1,1,0,-3,3});
        int[] expected = {0, 0, 9, 0, 0};
        assertArrayEquals(expected, actual);
    }
    @Test
    void testProductExceptSelf2(){
        Solution sol = new Solution();
        int[] actual = sol.productExceptSelf(new int[]{1,2,3,4});
        int[] expected = {24, 12, 8, 6};
        assertArrayEquals(expected, actual);
    }

}