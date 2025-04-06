#include<vector>
#include<iostream>
#include<cassert>

using namespace std;

typedef pair<int, int> Coordinates;

class Solution {
    
    public:

    int countPaths(vector<vector<int>> &grid, int n, Coordinates position = {0,0}){
        int count = 0;  
        // this count = 0essentially means you are counting paths 'below,' 
        // or stemming from the current state through your children, then you pass the count up to your parent.
        int x = position.first, y = position.second;

        // base cases:
        // 1. if you are at the end of the grid and on a safe cell
        if (x == n-1 && y == n-1 && grid[x][y] == 0) return 1;
    
        // 2. if starting position is lava or if you are trapped with lava on both sides
        if (grid[x][y] == 1 || (x + 1 < n && grid[x+1][y] == 1) && (y + 1 < n && grid[x][y+1] == 1)) return 0;

        // recursive cases:
        // 1. move down
        if ( x + 1 < n && grid[x+1][y] == 0){
            count += countPaths(grid, n, {x+1,y});
        } 
        // 2. move right
        if ( y + 1 < n && grid[x][y+1] == 0){
            count += countPaths(grid, n, {x,y+1});
        }
    
        return count;
        
    }
};

void test0(Solution &s){
    vector<vector<int>> grid = {{0, 0, 1, 0, 0},
                                {0, 1, 0, 0, 0},
                                {0, 1, 0, 0, 0},
                                {0, 1, 0, 0, 0},
                                {0, 1, 0, 0, 0}};
    int n = grid.size();
    int count = s.countPaths(grid, n);
    cout << "count: " << count << endl;
    assert(count == 0); 
}

void test1(Solution &s){
    vector<vector<int>> grid = {{0, 0, 0},
                                {0, 0, 0},
                                {0, 0, 0}};
    int n = grid.size();
    int count = s.countPaths(grid, n);
    cout << "count: " << count << endl;
    assert(count == 6);
}

void test2(Solution &s){
    vector<vector<int>> grid = {{0, 1, 0},
                                {0, 0, 0},
                                {0, 0, 0}};
    int n = grid.size();
    int count = s.countPaths(grid, n);
    cout << "count: " << count << endl;
    assert(count == 3);
}

void test3(Solution &s){
    vector<vector<int>> grid = {{0, 1, 0},
                                {0, 1, 0},
                                {0, 0, 0}};
    int n = grid.size();
    int count = s.countPaths(grid, n);
    assert(count == 1);
}
int main(){
    Solution s;
    test0(s);
    test1(s);
    test2(s);
    test3(s);
    return 0;
}