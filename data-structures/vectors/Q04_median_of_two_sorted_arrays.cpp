#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

void print(vector<int> & v){
    for (auto &elem: v){
        cout << elem << ", ";
    }
    cout << endl;
}

class Solution {
public:
    vector<int> mergeIntoSingleSorted(vector<int>& nums1, vector<int>& nums2) {
        vector<int>::iterator it1 = nums1.begin();
        vector<int>::iterator it2 = nums2.begin();
        vector<int> merged;
        int mn = nums1.size()+nums2.size();
        int target = (mn%2==0) ? (mn/2) : (mn/2 +1);

        while (it1 != nums1.end() || it2 != nums2.end() || merged.size() < target){
            int val1 = (it1 != nums1.end()) ? *it1 : INT_MAX;
            int val2 = (it2 != nums1.end()) ? *it2 : INT_MAX;

            if (val1 < val2) {
                merged.push_back(*it1);
                it1++;
            } else {
                merged.push_back(*it2);
                it2++;
            }
        }
        print(merged);
        return merged;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        /* The key now is stopping the algorithm earlier*/
        vector<int>::iterator it1 = nums1.begin();
        vector<int>::iterator it2 = nums2.begin();
        vector<int> merged;
        int mn = nums1.size()+nums2.size(); // m+n
        bool even = (mn%2==0) ? true : false; // parity of m+n
        int target = mn/2+1; // for both cases because we translating full length m+n to indices on m+n-1


        while (merged.size() < target){
            if (it1==nums1.end() && it2 ==nums2.end()) break;
            int val1 = (it1 != nums1.end()) ? *it1 : INT_MAX;  // Every time you think you handle edge cases like these, you must test.
            int val2 = (it2 != nums2.end()) ? *it2 : INT_MAX;


            if (val1 < val2) {
                merged.push_back(*it1);
                it1++;
            } else {
                merged.push_back(*it2);
                it2++;
            }
        }
        print(merged);
        double my_median;
        if (even){
            cout << "even" << endl;
            cout << "last two: " << merged.back() << ", " << merged[target-2] << endl;
            my_median = ((float)merged.back()+ (float)(merged[target-2]))/(float)2;
        } else {
            cout << "odd" << endl;
            my_median = (float)merged.back();
        }
        cout << "median: " << my_median << endl;
        return my_median;
    }
};

double EPSILON = 0.001;

void test1(Solution &s){
    vector<int> v1 = {4,6,8,12,17};
    vector<int> v2 = {1,9,13,23,25,60};
    assert(abs(12 - s.findMedianSortedArrays(v1, v2)) < EPSILON);

}


void test2(Solution &s){
    vector<int> v1 = {1,3};
    vector<int> v2 = {2};
    assert(abs(2 - s.findMedianSortedArrays(v1, v2)) < EPSILON);

}

void test3(Solution &s){
    vector<int> v1 = {1,2,3};
    vector<int> v2 = {8,9,12};
    double med = s.findMedianSortedArrays(v1, v2);
    cout << med;
    assert(abs(5.5 - med) < EPSILON);

}

void test4(Solution &s){
    cout << "---- test4 ----" << endl;
    vector<int> v1 = {0,0};
    vector<int> v2 = {0,0};
    double med = s.findMedianSortedArrays(v1, v2);
    cout << med;
    assert(abs(0 - med) < EPSILON);

}




int main(){
    Solution s;
    test1(s);
    test2(s);
    test3(s);
    test4(s);
}