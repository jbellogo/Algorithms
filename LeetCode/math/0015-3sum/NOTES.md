# How to generate all 3 element subsets of a set?

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

