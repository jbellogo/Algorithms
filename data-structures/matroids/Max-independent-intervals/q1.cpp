#include<bits/stdc++.h>
using namespace std;

typedef pair<long long int, long long int> Range; 

class Compare
{
    public:
    bool operator()(Range R1, Range R2){
        long long int b1 = R1.second;
        long long int b2 =  R2.second;
        return b1 >= b2; // prioritize ealier end
    }
};

class RangesSet 
{
    // first element in pair is weight for comparison. MIN HEAP implementation
    // make a priority queue of priority queues.for each same weight. 
    priority_queue<Range, vector<Range>, Compare> ranges;  
    long long int endpointR =  LLONG_MIN;


public:
    void addElem(long long int a, long long int b);

    bool isIndependent( long long int rEnd);

    int maxWIS();
};

void RangesSet::addElem(long long int a, long long int b){
    // prioritize earlier intervals. 
    Range r = make_pair(a,b);
    ranges.push(r); // automatically keeps MIN FIRST
}



bool RangesSet::isIndependent(long long int rStart) {
    return (rStart >=  endpointR);
}


int RangesSet::maxWIS() {
    int MWIS = 0 ; // Max weight of independent set.     
	while (!ranges.empty())
	{
		pair<long long int, long long int> currRange = ranges.top();
		ranges.pop(); // THIS IS UNSURE SINCE NOT A MATROID
        long long int rStart = currRange.first; 
        if (isIndependent(rStart)){
            long long int b = currRange.second;
            // // cout << a << ", " << b << " ... w = " << b-a << endl;
            if (b > endpointR){
                endpointR = b;
            }
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





