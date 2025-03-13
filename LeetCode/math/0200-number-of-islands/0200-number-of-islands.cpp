#include <queue>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std; 


class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int numRows = grid.size();
        int numCols = grid[0].size();
        queue<pair<int, int>> q ; // coordinates 
        
        vector<vector<int>> visited(numRows, vector<int>(numCols, 0)); // starts from zero matrix ends up the same as grid

        ////////// For testing ////////////
        vector<vector<pair<int, int>>> islands;
        ////////////////////////////////

        int num_islands = 0;
        // find root for DFS
        pair<int, int> root;
        for (int i = 0 ; i < numRows ; i++){
            for (int j = 0; j < numCols ; j++){
                if (grid[i][j] == '1' && visited[i][j] == 0) {
                    cout << "starting BFS at ROOT: (" << i << "," << j << ")" << endl;
                    root = make_pair(i,j);
                    q.push(root);

                    //////// For testing ////////////
                    vector<pair<int, int>> island;
                    ////////////////////////////////

                    // BFS on binary tree begins
                    while (!q.empty()){
                        pair<int, int> coords = q.front();
                        int x = coords.first, y = coords.second;
                        visited[x][y] = 1;
                        //////// For testing ////////////
                        island.push_back(coords);
                        ////////////////////////////////

                        // cout << "adding x,y: " << x << "," << y << endl;
                        // right child (y+1)
                        if (y+1 < numCols && grid[x][y+1] == '1' && visited[x][y+1] == 0){
                            q.push(make_pair(x,y+1));
                        }
                        // down child (x+1)
                        if (x+1 < numRows && grid[x+1][y] == '1' && visited[x+1][y] == 0){
                            q.push(make_pair(x+1,y));
                        }
                        // left child (y-1)
                        if (y-1 >= 0 && grid[x][y-1] == '1' && visited[x][y-1] == 0){
                            q.push(make_pair(x,y-1));
                        }
                        // up child (x-1)
                        if (x-1 >= 0 && grid[x-1][y] == '1' && visited[x-1][y] == 0){
                            q.push(make_pair(x-1,y));
                        }

                        q.pop();
                    } 
                    num_islands++;   
                    /////// For testing ////////////
                    islands.push_back(island);
                    ////////////////////////////////
                }
            }
        }
        //////// For testing ////////////
        for (int i = 0; i < islands.size(); i++){
            cout << "Island " << i+1 << ": ";
            for (int j = 0; j < islands[i].size(); j++){
                cout << "(" << islands[i][j].first << "," << islands[i][j].second << ") ";
            }
            cout << endl;
        }
        ////////////////////////////////
        return num_islands;
    }
};

void test1(Solution &sol){
    vector<vector<char>> grid = {{'1','1','1','1','0'},
                                 {'1','1','0','1','0'},
                                 {'1','1','0','0','0'},
                                 {'0','0','0','0','0'}};
    int ans = sol.numIslands(grid);
    assert(ans == 1);
}

void test2(Solution &sol){
    cout << "--------------- test2 ---------------" << endl;
    vector<vector<char>> grid = {{'1','1','0','0','0'},
                                 {'1','1','0','0','0'},
                                 {'0','0','1','0','0'},
                                 {'0','0','0','1','1'}};
    int ans = sol.numIslands(grid);
    cout << "ans: " << ans << endl;
    assert(ans == 3);                            
}

void test3(Solution &sol){
    cout << "--------------- test3 ---------------" << endl;
    vector<vector<char>> grid = {{'1','1','1'},
                                 {'0','1','0'},
                                 {'1','1','1'}};
    int ans = sol.numIslands(grid);
    assert(ans == 1);
}

void test4(Solution &sol){
    cout << "--------------- test4 ---------------" << endl;
    vector<vector<char>> grid = {{'1','1','1','1','1'},
                                 {'1','1','1','1','1'},
                                 {'1','1','1','1','1'},
                                 {'1','1','1','1','1'}};
    int ans = sol.numIslands(grid);
    assert(ans == 1);
}

void test5(Solution &sol){
    cout << "--------------- test5 ---------------" << endl;
    vector<vector<char>> grid = {{'1','0','1','1','1'},
                                 {'1','0','1','0','1'},
                                 {'1','1','1','0','1'}};
    int ans = sol.numIslands(grid);
    assert(ans == 1);
}

void test6(Solution &sol){
    cout << "--------------- test6 ---------------" << endl;
    vector<vector<char>> grid = {{'1','0','1','0','1'},
                                 {'0','1','0','1','0'},
                                 {'1','0','1','0','1'}};
    int ans = sol.numIslands(grid);
    assert(ans == 8);
}

int main(){
    Solution sol;
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
}

