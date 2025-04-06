#include<bits/stdc++.h>
using namespace std;


typedef pair<int, vector<int>> myVec; // (weight, vector)

class Matroid 
{
    int n,m;
    priority_queue<myVec> elements;  // first element in pair is weight by default

public:
    Matroid(int n, int m);

    void addElem(myVec v);

    bool is_zero_vector(vector<int> v);

    bool is_independent(vector<vector<int>> S, vector<int> v);

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

bool Matroid::is_independent(vector<vector<int>> S, vector<int> v) {   // MAKE VECTOR V CONSTANT?????
    // 
    // Checks to see if the introduction of v into INDEPENDENT set S is independent. 
    int l = S.size(); 
    cout << "---- INDEPENDENT? size of A: "<< l  << endl;
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
    if (l==0) {return true;}

    // if for all m, all sums are zero -> independent. 
    for (int i = 0; i<l; i++){
        // compute the vector = v + sum from v[i] to v[j]
        vector<int> currVsums = v; // starts with vector 
        for (int x =0; x< m;x++){
            currVsums[x] += (currVsums[x] + S[i][x])%2; // starting sum
        }
        // to V1 I want to add V1+V2, V1+V3, V1+4, ...
        for (int j = i; j<l; j++){
            // i =0, j=1 < 1-> FALSE
            for (int e = 0; e<m; e++){
                // check the sum!!
                currVsums[e] = (currVsums[e]+ S[j][e])%2 ;
                cout << e << "-th entry from v[" << i << "] to v[" << j << "] is now:" << currVsums[e] << endl;
                if (is_zero_vector(currVsums)){
                    cout << "NO! can't add" << endl << endl;
                    return false;
                }
                // update it

            }
            cout << endl;
            // if (is_zero_vector(currVsums)){
            //     cout << "NO! can't add" << endl << endl;
            //     return false;
            // }

        }
    }
    cout << "YES! can add" << endl << endl;
    return true ;
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
    vector <vector<int>> A;
    int MWIS = 0 ; // Max weight of independent set. 
    
	while (!elements.empty())
	{
		vector<int> v = elements.top().second;
        int w = elements.top().first;
		elements.pop();
        if (is_independent(A, v)){
            A.push_back(v); 
            MWIS +=w;
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





