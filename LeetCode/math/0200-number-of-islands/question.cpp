#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std; 

#include <chrono>
using namespace std::chrono;



class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int numRows = grid.size();
        int numCols = grid[0].size();
        queue<pair<int, int>> q ; // coordinates 
        

        int num_islands = 0;
        // find root for BFS
        for (int i = 0 ; i < numRows ; i++){
            for (int j = 0; j < numCols ; j++){
                if (grid[i][j] == '1') {
                    q.push(make_pair(i,j));
                    num_islands++;   // easier to see here than after the while loop

                    // BFS on binary tree begins
                    while (!q.empty()){
                        pair<int, int> coords = q.front();
                        int x = coords.first, y = coords.second;
                        // this guard is super necessary, otherwise we repeat visits to the same node, why? Not sure.
                        if (grid[x][y] == '0'){
                            q.pop();
                            continue;
                        }
                        grid[x][y] = '0'; // mark as visited, this itself is optimization as we wonto run the if check again
                        q.pop();

                        // right child (y+1)
                        if (y+1 < numCols && grid[x][y+1] == '1'){
                            q.push(make_pair(x,y+1));
                        }
                        // down child (x+1)
                        if (x+1 < numRows && grid[x+1][y] == '1'){
                            q.push(make_pair(x+1,y));
                        }
                        // left child (y-1)
                        if (y-1 >= 0 && grid[x][y-1] == '1'){
                            q.push(make_pair(x,y-1));
                        }
                        // up child (x-1)
                        if (x-1 >= 0 && grid[x-1][y] == '1'){
                            q.push(make_pair(x-1,y));
                        }
                    } 
                }
            }
        }
        return num_islands;
    }
};

void test1(Solution &sol){
    cout << "--------------- test1 ---------------" << endl;
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



void testBig(Solution &sol){
    cout << "--------------- testBig ---------------" << endl;
    ifstream file("big.in");
    vector<vector<char>> grid;
    string line;
    while (getline(file, line)){
        vector<char> row;
        for (char c : line){
            if (c == '0' || c == '1'){
                row.push_back(c);
            }
        }
        grid.push_back(row);
    }
    auto start = high_resolution_clock::now();
    int ans = sol.numIslands(grid);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
}

int main(){
    Solution sol;
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
    testBig(sol);
}

