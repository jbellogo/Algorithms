#include<bits/stdc++.h>
using namespace std;

typedef pair<long long int, pair<long long int, long long int>> Range; // weight of a rage is its length (w, (a,b)) and w = b-a


class RangesSet 
{
    // first element in pair is weight for comparison. MIN HEAP implementation
    priority_queue<Range, vector<Range>, greater<Range>> ranges;  

public:
    // RangesSet();

    void addElem(long long int a, long long int b);

    bool isIndependent(vector <pair<long long int, long long int>> R, pair<long long int, long long int> r);

    int maxWIS();
};

void RangesSet::addElem(long long int a, long long int b){
    int w = b-a;
    // prioritize earlier intervals. 
    Range r = make_pair(w, make_pair(a,b));
    ranges.push(r); // automatically keeps MIN FIRST
}

bool RangesSet::isIndependent(vector <pair<long long int, long long int>> R, pair<long long int, long long int> r) {
    // Checks if R U {r} is independent given that R is independent. 
    // R will be constructed in max_wis()
    int l = R.size(); 
    long long int aIn =  r.first;
    long long int bIn = r.second;
    for (int i = 0; i<l; i++){
        long long int aCurr = R[i].first;
        long long int bCurr =  R[i].second;
        if (!(bIn <= aCurr)  && !(bCurr <= aIn )) {
            // not independnt
            return false;
        }
    }
    return true;
}


int RangesSet::maxWIS() {
    vector <pair<long long int, long long int>> R; // we don't care about the weights here. 
    int MWIS = 0 ; // Max weight of independent set. 
    
	while (!ranges.empty())
	{
		pair<long long int, long long int> currRange = ranges.top().second;
        // int w = ranges.top().first; // this doesn't matter, just to keep priority queue. 
		ranges.pop(); // THIS IS UNSURE SINCE NOT A MATROID
        if (isIndependent(R, currRange)){
            R.push_back(currRange); 
            MWIS ++;
        }
    }
    return MWIS;
}

int main(){
    int n;
    cin >> n;
	RangesSet A;
    for(int i = 0; i <n; i++) {
        long long int a, b;
        cin >> a >> b;
        A.addElem(a,b);
    }
    cout << A.maxWIS() << endl;
    return 0;

}





