#include <iostream>
#include <list>
#include <set>
using namespace std;

#define MAX_LINE 3
#define LOG(x) cout << x << endl

struct Edge {
    public:
    int u, v;
};


int MCkSubTree(list<Edge> ones, int k) {
    list<set<int> > trees;
    int count = 0;
    for (auto const& e :ones) {
        // do something to e
        if (count >= k){
            break;
        };
        if (trees.empty()) {
            set<int> newset({e.u, e.v});
            trees.push_back(newset);
            continue;
        }
        for (list<set<int> >::iterator myset = trees.begin(); myset != trees.end(); ++myset){
            bool u_is_in = myset->find(e.u) != myset->end();
            bool v_is_in = myset->find(e.v) != myset->end();
            if (u_is_in && v_is_in){
                continue;
            } else if (u_is_in) {
                // const int v = e.v;
                myset->insert(e.v);
            } else if (v_is_in) {
                myset->insert(e.u);
            } else {
                set<int> newset({e.u, e.v});
                trees.push_back(newset);
            }
            if (myset->size() > count) {
                count = myset->size()-1;
            };
        }
        if (count > k){
            count = k;
        }
    };
    return 2*k-count;
};

int main(){
    int n, k, u, v, w;
    cin >> n >> k;
    int lim  = n*(n-1)/2;
    list<Edge> ones;
    while(cin >> u >> v >> w) {
        // cout << lim;
        /// do stuff 
        if (w == 1){
            Edge e({u, v});
            ones.push_back(e);
        }
        ///
        --lim;
        if (lim == 0) {break;}
    };
    cout << MCkSubTree(ones,k);
    return 0;
};