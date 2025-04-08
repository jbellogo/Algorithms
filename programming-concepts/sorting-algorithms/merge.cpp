#include <vector>
#include <iostream>
#include <cassert>


using namespace std;

class Solution{
public:
	void mergeSort(vector<int> &arr){
		recursiveMergeSort(arr, 0, arr.size()-1);
	}

	void recursiveMergeSort(vector<int> &arr, int leftStart, int rightEnd){
		// base
		if (leftStart >= rightEnd){
			return;
		}
		int mid = (leftStart + rightEnd)/2;
		recursiveMergeSort(arr, leftStart, mid);  // sort the left
		recursiveMergeSort(arr, mid+1, rightEnd); // sort the right
		mergeHalves(arr, leftStart, mid, rightEnd);
	}

	void mergeHalves(vector<int> &arr, int leftStart, int mid, int rightEnd){
		// merge in place on arr
		// treat two halves as iteration through two pointers
		int n1 = mid + 1 - leftStart;
		int n2 = rightEnd - mid;

        // Create temp vectors
        vector<int> L(n1), R(n2);


        // Populate temp vectors with copies of the two sorte halves to merge.
        for (int i = 0; i < n1; i++){
            L[i] = arr[leftStart + i]; // leftStart offset 
        }
        for (int i = 0; i < n2; i++){
            R[i] = arr[mid + 1 + i]; // rightStart offset 
        }


        // merge the two vectors onto arr
        int i = 0, j = 0;
		int k = leftStart;
        while (i < n1 && j < n2){
			cout << "k: " << k << " i: " << i << " j: " << j << endl;
                // both L[i] and R[j] avaliable
			if (L[i] < R[j]){
				arr[k] = L[i];
				i++;
			} else {
				arr[k] = R[j];
				j++;
			}
            k++;
        }

        // copy remaining elements of L[] if any
        while (i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }

        // copy remaining elements of R[] if any
        while (j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    }
};

void print_v(vector<int> & arr){
    for (int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
}

void test0(Solution &sol){
	vector<int> arr = {1, 2, 3, 4, 5};
	sol.mergeSort(arr);
    print_v(arr);
	assert(arr == vector<int>({1, 2, 3, 4, 5}));
}

int main(){
    Solution sol;
    test0(sol);
}