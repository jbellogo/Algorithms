// given a matrix of zeros and ones, determine size of the biggest region of 1s, 
// which may be connected vertically, horizontally, or diagonally. 

/*
Idea: 
    - Reduces to depth first search, 
        - dfs_wrapper: Lets iterate through x and y in the dfs_wrapper (quadratic time) 
          considering (i,j) as a root to start our recursive search for the maximally connected component reachable from it. 
        - dfs_recursive: We check its nbrs (8 possible 2 horizontal, 2 vertical, and 4 diagonal) and recurse on the first one that is one. 
*/

#include<vector>
#include<iostream>
#include<cassert>

using namespace std;

class Solution{
    vector<pair<int, int>> TRANSLATIONS = {{-1, -1}, {-1, 0}, {-1, 1},
                                           { 0, -1},          { 0, 1},
                                           { 1, -1}, { 1, 0}, { 1, 1}};
public:
    // return the size of the maximally connected region here. 
    int getRegionSizeRecursive(vector<vector<int>> &matrix, int rowStart, int colStart, int numRows, int numCols) {
        if (matrix[rowStart][colStart] == 0){
            return 0;
        }
        int regionSize = 1; // this node is 1 := unvisited
        matrix[rowStart][colStart] = 0; // mark this 'node' as visited
     
        // DFS STEP: for the current 'node' (i,j), check all its 'children' (all around) to see if you find another 'unvisited vertex' (with a matrix val of 1); 
        for (auto [row_tsl, col_tsl] : TRANSLATIONS){
            // translated indeces 
            int row_prime = rowStart + row_tsl;
            int col_prime = colStart + col_tsl;
            // determine if child at (row_prime, col_prime) is a valid and unvisited nbr
            if (0 <= row_prime && row_prime < numRows && 0 <= col_prime && col_prime < numCols && matrix[row_prime][col_prime] == 1){
                regionSize += getRegionSizeRecursive(matrix, row_prime, col_prime, numRows, numCols);
            }
        }
        return regionSize;
    }


    int getBiggestRegionDFS(vector<vector<int>> &matrix, int numRows, int numCols){
        int max_region_size = 0;
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numCols; col++){
                // iterate through all possible roots finding maximally connected components from them, exactl like dfs
                if (matrix[row][col] == 1){
                    // if 'unexplored'
                    int region_size = getRegionSizeRecursive(matrix, row, col, numRows, numCols);
                    cout << "region_size: " << region_size << endl; // print every island size!!
                    max_region_size = max(max_region_size, region_size); // very clever
                }
            }

        }
        return max_region_size;
    }
};


void test0(Solution &sol){
    vector<vector<int>> matrix = {
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1}
    };
    int ans = sol.getBiggestRegionDFS(matrix, 5, 5);
    cout << "ans: " << ans << endl;
    assert(ans == 5);
}


void test1(Solution &sol){
    vector<vector<int>> matrix = {
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1},    
        {1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1}
    };
    int ans = sol.getBiggestRegionDFS(matrix, 5, 5);
    cout << "ans: " << ans << endl;
    assert(ans == 9);
}

void test2(Solution &sol){
    vector<vector<int>> matrix = {
        {1, 1, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1},    
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1}
    };
    int ans = sol.getBiggestRegionDFS(matrix, 5, 5);
    cout << "ans: " << ans << endl;
    assert(ans == 13);
}



int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
}

