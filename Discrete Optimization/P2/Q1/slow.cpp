#include<bits/stdc++.h>
using namespace std;


typedef pair<int, vector<int>> myVec; // (weight, vector)

class Matroid 
{
    int n,m;

    int lenA = 0;

    priority_queue<myVec> elements;  // first element in pair is weight by default

    vector<vector<int>>  A; // contains vector linear combinations [v1, v2, v1+v2] etc.

public:
    Matroid(int n, int m);

    void addElem(myVec v);

    bool is_zero_vector(vector<int> v);

    bool is_pairwise_independent(vector<int> v); // is A U {v} still independent?

    void add_vector_combinations(vector<int> v);

    int mwis();
};

Matroid::Matroid(int n, int m){
    this->n = n;
    this->m = m;
}
void Matroid::addElem(myVec v){
    // cout << "\nadding row: w=" << v.first << " v: ";
    // for (auto i: v.second) {
    //     std::cout << i << ' '; 
    // }
    // cout << endl;
    elements.push(v);
}

// vector<vector<int>> get_subsets(int n){
//     vector <vector<int>> subsets;
//     for (int i = 0; i < n ;i++){
//         for (int j = 0; j < n ; j++){   
//         }
//     }
// }

bool Matroid::is_pairwise_independent(vector<int> v) {   // compares v added to A
    // 
    // Checks to see if the introduction of v into INDEPENDENT set S is independent. 
    cout << "---- INDEPENDENT? size of A: "<< lenA << endl;
    cout << "vector to add:";
    for (auto i : v){
        cout << " " << i << " ";
    }
    cout << endl;

    bool hasOnes = false;
    for (auto i : v){
        if (i==1) {hasOnes =  true;}
    }
    if (!hasOnes) {return false;}
    if (lenA == 0) {return true;}

    for (int i = 0; i<lenA; i++){
        // compute pairwise sum vector
        int ones = 0;
        for (int e = 0; e<m; e++){
            ones += (A[i][e]+v[e])%2;
        }
        if (ones == 0){
            cout << "NO! can't add" << endl << endl;
            return false;
        }
    }
    cout << "YES! can add" << endl << endl;
    return true ;
}

void Matroid::add_vector_combinations(vector<int> v){
    int oldLen = lenA;
    A.push_back(v); // keep smallests here
    lenA++;
    for (int i=0; i < oldLen; i++) {
        // cout << "adding v" << i << " < " << oldLen << endl;
        vector<int> currComb(m,0);
        for (int j = 0; j< m; j++){
            currComb[j] = (A[i][j]+v[j])%2;
        }
        B.push_back(currComb);
        lenA++;
    }
}



bool Matroid::is_zero_vector(vector<int> v){
    for (int e = 0; e<m; e++){
        if (v[e] == 1){
            return false;
        }
    }
    return true;
}


//     ///
//     for (int i =0; i<m; i++){
//         // dimension
//         int curr_sum = 0;
//         // cout << i << "-th row: ";
//         for (auto itrv : S){
//             cout << " + " << itrv[i];
//             curr_sum += itrv[i];
//             curr_sum %= 2;
//         }
//         // cout << endl << i << "-th row sums to: " << curr_sum << endl << endl;
//         if (curr_sum == 1) {
//             return true;
//         }
//     }
//     return false;
// }

int Matroid::mwis() {
    int MWIS = 0 ; // Max weight of independent set. 
    int MCID = 0;
    
	while (!elements.empty())
	{
		vector<int> v = elements.top().second;
        int w = elements.top().first;
		elements.pop();
        if (is_pairwise_independent(v)){ // when v is added to A?
            add_vector_combinations(v);
            MWIS +=w;
            MCID ++;
        }
        if (MCID == n){
            break;
        }
    //    } else {
    //     A.pop_back();
    //    }
    }
    return MWIS;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<int>* V = new vector<int> [n];
	Matroid M(n,m);
    for(int i = 0; i <n; i++) {
        // vector index
        int w;
        cin >> w;
        for(int j = 0; j <m; j++) {
            // element index
            int x;
            cin >> x;
            V[i].push_back(x);
        }
        M.addElem(make_pair(w, V[i]));
    };
    cout << M.mwis() << endl;

    return 0;

}





