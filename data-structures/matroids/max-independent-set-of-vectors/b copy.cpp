#include<bits/stdc++.h>
using namespace std;


typedef pair<long long, vector<int>> myVec; // (weight, vector)

class Matroid 
{
    int n,m;

    int lenA = 0;

    priority_queue<myVec> elements;  // first element in pair is weight by default. For Greedy

    vector <vector<int>> A; // for independence Row reduction check

public:
    Matroid(int n, int m);

    void addElem(myVec v);

    bool is_zero_vector(vector<int> v);

    bool is_A_independent();

    void swapRowsA(int i, int j);

    long long mwis();
};

Matroid::Matroid(int n, int m){
    this->n = n;
    this->m = m;
}
void Matroid::addElem(myVec v){
    elements.push(v);
}

void Matroid::swapRowsA(int i, int j){
    for (int x = 0; x<m; x++){
        int dummy = A[i][x];
        A[i][x] = A[j][x];
        A[j][x] = dummy;
    }
}

bool Matroid::is_A_independent() {   
    // checks if A is independent. 
    // ROW REDUCE A mod 2
    int lenA = A.size();
    if (lenA == 1) {
        for (auto i : A[0]){
            if (i==1){return true;}
        }
        return false;
    }
    // for every row:    
    for (int i=0; i<lenA; i++){
        ///////////////////  get a leading one.
        int lead = i; // initialized by n but bounded by m
        while(true){
            if (lead >= m){return false;} // make sure it doesn't give you any problems
            // try swaping rows
            for (int j = lead+1; j < lenA; j++){
                // cout << "Attempt to swap (i, j)= (" << i << ", " << j << ")" << endl;
                if (A[i][lead] == 1){break;}
                swapRowsA(i, j);
            }
            /////////////////// if there is no ones in column lead increase the lead. 
            if (A[i][lead]==0){
                lead++;
            } else {break;}
        //////////////////
        }
        //// make everything under lead zero.
        for (int j = i+1; j<lenA; j++){
            // cout << "A[" << j << "][" << lead << "]" << endl; 
            if (A[j][lead] != 0) {
                // set Aj = Aj+ Ai
                for (int x=0; x < m; x++){
                    A[j][x] = (A[j][x] + A[i][x])%2;
                }
            }
        }
    }
    // /// PRINT THE REDUCED MATRIX HERE IF NEEDED? 
    // cout << "A size: " << lenA<< endl;
    // for (int i =0; i<lenA; i++){
    //     for (int j=0; j<m; j++){
    //         cout << A[i][j];
    //     }
    //     cout << endl;
    // }
    
    for (int i = lenA-1; i >=0;i--){
        for (int j=m-1;j>=0;j--){
            if (A[i][j]==1){  // I think zero lines will be at the end so just A[lenA-1][j] should do
                // cout << "YES, adding vector!";
                return true;
            }
        }
    }
    return false;
}



long long Matroid::mwis() {
    long long MWIS = 0 ; // Max weight of independent set. 
	while (!elements.empty())
	{
		vector<int> v = elements.top().second;
        long long w = elements.top().first;
		elements.pop();
        if (A.size() >= m){break;}
        A.push_back(v);
        if (is_A_independent()){ // when v is added to A?
            MWIS +=w;
        } else {
        A.pop_back();
       }
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
        long long w;
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





