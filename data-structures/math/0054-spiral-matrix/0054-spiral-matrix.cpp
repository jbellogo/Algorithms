#include <vector>
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int numRows = matrix.size();
        int numCols = matrix[0].size();

        int rightBound = numCols; // the bound when going right // Decrease it to reduce the boundary --
        int downBound = numRows; // --
        int leftBound = 0; // ++
        int upBound = 1; // ++
        int row = 0, col = 0; 
        vector<int> ans;
        string direction = "right";
        ans.push_back(matrix[row][col]);
        while (true) {

            // // how do we stop? if you turn and see a boundary in front of you are done.
            // cout << "matrix[" << row << "][" << col << "]: " << matrix[row][col] << endl;
            // cout << " direction: " << direction << endl;
            // cout << " rightBound: " << rightBound << " downBound: " << downBound << " leftBound: " << leftBound << " upBound: " << upBound << endl;


            if (direction == "right") {
                // GOING RIGHT 
                // boundary in front?
                if (col + 1 >= rightBound) {
                    // TURN DOWN
                    direction = "down";
                    rightBound--;
                    // boundary ahead?
                    if (row+1 >= downBound) {
                        break;
                    }
                    continue; // avoid duplicates
                } else {
                    col++; // mantain course RIGHT
                }
            } else if (direction == "down") 
            { 
                // GOING DOWN 
                // boundary ahead?
                if (row+1 >= downBound){
                    // TURN LEFT
                    direction = "left";
                    downBound--;
                    // boundary ahead?
                    if (col-1 < leftBound) {
                        break;
                    }
                    continue;
                } else {
                    row++; // mantain course DOWN
                }
            } else if (direction == "left") 
            {
                // GOING LEFT
                // boundary ahead?
                if (col-1 < leftBound){
                    // TURN UP
                    direction = "up";
                    leftBound++;
                    // boundary ahead?
                    if (row-1 < upBound){
                        break;
                    }
                    continue;
                } else {
                    col--; // mantain course LEFT
                }
            } else if (direction == "up")
            {
                // GOING UP
                // boundary ahead?
                if (row-1 < upBound){
                    // TURN RIGHT
                    direction = "right";
                    upBound++;
                    if (col + 1 >= rightBound){
                        break;
                    }
                    continue;
                } else {
                    row--; // mantain course UP
                }
            }
            ans.push_back(matrix[row][col]);

            

        }
        return ans;
    }
};

void test0(){
    Solution sol;
    vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
    vector<int> ans = sol.spiralOrder(matrix);
    assert(ans == vector<int>({1,2,3,6,9,8,7,4,5}));
}

void test1(){
    Solution sol;
    vector<vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    vector<int> ans = sol.spiralOrder(matrix);
    assert(ans == vector<int>({1,2,3,4,8,12,11,10,9,5,6,7}));
}

void test2(){
    Solution sol;
    vector<vector<int>> matrix = {{1,2,3},{4,5,6}};
    vector<int> ans = sol.spiralOrder(matrix);
    assert(ans == vector<int>({1,2,3,6,5,4}));
}

void test3(){
    Solution sol;
    vector<vector<int>> matrix = {{1},{2},{3},{4},{5},{6},{7},{8},{9},{10}};
    vector<int> ans = sol.spiralOrder(matrix);
    assert(ans == vector<int>({1,2,3,4,5,6,7,8,9,10}));
}

void test4(){
    Solution sol;
    vector<vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
    vector<int> ans = sol.spiralOrder(matrix);
    assert(ans == vector<int>({1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10}));
}

int main(){
    test0();
    test1();
    test2();
    test3();
    test4();
}