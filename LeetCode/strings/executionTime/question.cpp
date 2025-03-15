#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMinimumOperations' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY executionTime
 *  2. INTEGER x
 *  3. INTEGER y
 */

bool all_negative(vector<int> &executionTime){
    for (int i = 0; i < executionTime.size(); i++){
        if (executionTime[i] > 0){
            return false;
        }
    }
    return true;
}

int getMinimumOperations(vector<int> executionTime, int x, int y) {
    // lets go with a greedy approach.
    int ops = 0;
    
    while (!all_negative(executionTime)) {
        // Find maximum element index
        // ONE operation
        int max_idx = 0;
        for (int i = 1; i < executionTime.size(); i++) {
            if (executionTime[i] > executionTime[max_idx]) {
                max_idx = i;
            }
        }
        
        // Apply operations
        for (int i = 0; i < executionTime.size(); i++) {
            // if (executionTime[i] > 0) { // to avoid issues with the negative values
            if (i == max_idx) {
                executionTime[i] -= x;
            } else {
                executionTime[i] -= y;
            }
            // }
        }
        ops++;
    }
    return ops;
}

void test1(){
    vector<int> executionTime = {3,4,1,7,6};
    int x = 4;
    int y = 2;
    int ans = getMinimumOperations(executionTime, x, y);
    assert(ans == 3);
}

int main()
{
    test1();
}


int get_max_index(vector<int> &vec){
    int max_idx = 0;
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] > vec[max_idx]) {
            max_idx = i;
        }
    }
    return max_idx;
}
