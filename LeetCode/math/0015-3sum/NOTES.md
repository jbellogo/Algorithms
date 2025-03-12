## 3 Sum solution

## Attempt 1 (Innefficient):
A brute-force method involves generating all 3-element subsets of the given set and summing them to check for zero.


```cpp
void get_three_elem_subsets(int n) {
        // It works.
        vector<vector<int>> ans;

        // i3 is the third one index
        for (int i3 = 2; i3 < n; i3++){
            for (int i2 = 1; i2 < i3; i2++){
                for (int i1 = 0; i1 < i2; i1++){
                    vector<int> permut = get_permut(n, i1,i2,i3);
                    print_vector(permut);
                }
            }
        }
}
```

## Attempt 2 (Still innefficient):
To optimize, we can take inspiration from the 2Sum problem. By sorting the array first, we simplify the process of finding triplets that sum to zero.

1. Fix the first element (i).
2. Use two pointers: j (second element) and k (third element) st $i<j<k$ to traverse the remaining elements.
    * The trick is that we don't want to traverse all possible positions, instead, keep track of the sum = num[i]+nums[j]+nums[k] and use this to move j and k only in the directions which will mkake the sum closer to zero.
    * If the sum is too high, decrease k to lower it. 
    * If the sum is too low, increase j to raise it. This efficiently narrows down valid triplets without redundant checks.

3. If the sum of the three elements is greater than zero, decrease k (move the right pointer left) to reduce the sum.
4. If the sum is less than zero, increase j (move the left pointer right) to increase the sum.
5. Continue adjusting until all valid triplets are found.
6. This two-pointer approach significantly improves efficiency compared to the brute-force method.

```cpp
bool has(vector<vector<int>> &ans, vector<int> &u){
    // ans contains only sorted vectors and u is sorted also.
    for (auto &v : ans){
        if ( u == v) return true;
    }
    return false;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> ans;

    // i < j < k will be ones indices.
    for (int i = 0 ; i < n-2 ; i++){
        int j = i+1;
        int k = n-1;
        while ( j < k ){
            int sum = nums[i] + nums[j] + nums[k];
            if (sum > 0) {
                k--;
            } else if (sum < 0){
                j++;
            } else {
                vector<int> u = {nums[i], nums[j], nums[k]};
                sort(u.begin(), u.end());
                if (!has(ans, u)){ // INNEFICIENCY
                    ans.push_back(u);
                }
                j++;
                k--;
            }

        }

    }
    
    return ans;
}
```

Now the problem lies in the has function. It is too slow. It's purpose is to avoide adding duplicates to the answer, but since the nums array is sorted, we can take care of this right from the main for loop in threeSum.

If nums[i] + nums[j] + nums[k] = 0
and nums is sorted. How do we avoid duplicates? Well how could they happen?
Since we are coming left with j and right with k
nums  = [... -2,-2 ... 0,0,0,0 ... 2,2,2 ...]
              i        j         k
We don't need to increase all three until we find a new number, we can just do it for j.


```cpp

// ...
for (int i = 0 ; i < n-2 ; i++){
    // CHANGE IS HERE!
    if (i > 0 && nums[i] == nums[i-1]) {
        continue;
    }
    int j = i+1;
    int k = n-1;
    while ( j < k ){
        int sum = nums[i] + nums[j] + nums[k];
        if (sum > 0) {
            k--;
        } else if (sum < 0){
            j++;
        } else {
            ans.push_back(vector<int>{nums[i], nums[j], nums[k]});
            
            // CHANGE IS HERE!
            j++;
            while (nums[j] == nums[j-1] && j < k) j++;
            while (k+1 < n && nums[k] == nums[k+1] && j < k) k--;

        }

    }
}
// ...
```








