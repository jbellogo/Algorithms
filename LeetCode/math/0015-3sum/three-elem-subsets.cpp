#include <iostream>
#include <vector>

using namespace std;

void print_vector(vector<int> &v){
    for (auto &x : v){
        cout << x << " ";
    }
    cout << endl;
}

class Solution {
    
public:
    // UNRELATED FUNCTIONS 
    // just for understanding and exploring the problem, in particular for the 3-elem-subsets.
    vector<int> get_permut(int n, int i1, int i2, int i3){
        vector<int> permut(n,0); //[1,1,1]
        permut[i1] = 1;
        permut[i2] = 1;
        permut[i3] = 1;
        return permut;
    }

    int three_elem_subsets(int n) {
        // It works //
        // returns the number of 3-elem-subsets of a set of size n
        int num_subsets = 0;

        // i3 is the third one index
        for (int i3 = 2; i3 < n; i3++){
            for (int i2 = 1; i2 < i3; i2++){
                for (int i1 = 0; i1 < i2; i1++){
                    vector<int> permut = get_permut(n, i1,i2,i3);
                    print_vector(permut);
                    num_subsets++;
                }
            }
        }
        return num_subsets;
    }
};

int main(){
    Solution sol;
    sol.three_elem_subsets(6);
}