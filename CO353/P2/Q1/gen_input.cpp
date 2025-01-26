#include<bits/stdc++.h>

using namespace std;


int main(){
    cout << 30 << " " << 30 << endl;
    for (int i=0; i < 30; i++){
        cout << 1000000 << " ";
        for (int j=0; j<30; j++){
            if (i==j){
                cout << 1 << " ";
            } else {
                cout << 0 << " ";
            }
        }
        cout << endl;
    }

}