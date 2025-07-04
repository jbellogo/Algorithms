package org.example;

import java.util.List;

public class Solution {

    public int[] getPrefixProducts(int [] nums) {
        int n = nums.length;
        // validation
        if (n == 0) {
            return new int[]{};
        } else if (n == 1){
            return new int[]{1};
        }
        int[] prefixProducts = new int[n];
        int prefixTotalProd = 1;
        prefixProducts[0] = 1;
        for (int i = 1 ; i < n ; i++){
            prefixTotalProd *= nums[i-1];
            prefixProducts[i] = prefixTotalProd;
        }
        return prefixProducts;
    }

    public int[] getSuffixProducts(int[] nums){
        int n = nums.length;
        // validation
        if (n == 0) {
            return new int[]{};
        } else if (n == 1){
            return new int[]{1};
        }
        int[] suffixProducts = new int[n];
        int suffixTotalProd = 1;
        suffixProducts[n-1] = 1;
        for (int i = n-2 ; i >= 0 ; i--){
            suffixTotalProd *= nums[i+1];
            suffixProducts[i] = suffixTotalProd;
        }
        return suffixProducts;
    }

    public int[] productExceptSelf(int[] nums) {
        int[] suffixProducts = getSuffixProducts(nums);
        int[] prefixProducts = getPrefixProducts(nums);
        int[] ans = new int[nums.length];
        for (int i = 0 ; i < nums.length ; i++){
            ans[i] = suffixProducts[i]*prefixProducts[i];
        }
        return ans;
    }
}

