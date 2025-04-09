// @TODO add more tests later and the set of sets to print unique combinations


#include<vector>
#include<iostream>
#include<map>

using namespace std;



typedef pair<string, int> IceCream; // <flavor, price>


// Lessons:
// I started using a hashmab of string-int key-value pairs..
// but then I realized I also need a third metric, their enumeration/index for binarySearch so I switched a vector of IceCream instances
typedef vector<IceCream> Menu;

// THIS NEEDS TO BE OUTSIDE OF THE CLASS
// a comparator for a hashmap is between the key-value 'pairs', which incidentally are a pair type.
bool iceCreamComparator(const IceCream &A, const IceCream &B) {
    return A.second < B.second;
}

// THIS CAUSES REPEATED COMBINATIONS, SAME FLAVOURS TWICE MIRRORED, USE A SET INSTEAD
void print_choices(vector<pair<int, int>> &v, vector<IceCream> &menu){
    // takes v := vector if a,b index pairs AND menu
    cout << "CHOICES: ";
    for (auto &[a,b]: v){
        string flavour_a = menu[a].first;
        string flavour_b = menu[b].first; 
        cout << "(" << flavour_a << ", " << flavour_b << ") ";
    }
    cout << endl;
}

// // Huh, not as easy as I thought, maybe a set of sets?
// void print_choices_sets(set<set<int>> &v, vector<IceCream> &menu){
//     // takes v := vector if a,b index pairs AND menu
//     cout << "CHOICES: ";
//     for (set<set<int>>::iterator it = v.begin(); it != v.end(); it++){
//         int a = *it->begin();
//         int b = *it->end();
//         string flavour_a = menu[a].first;
//         string flavour_b = menu[b].first; 
//         cout << "(" << flavour_a << ", " << flavour_b << ") ";
//     }
//     cout << endl;
// }


class Solution{

public:

    pair<bool, int> binarySearch(Menu &menu, int complement, int forbidden_index){
        // Important: a match in our serach (b_flavor, b_price) consists of TWO things 
        //      1) price == complement AND 
        //      2) b_flavour != forbidden_index 
        int left = 0, right = menu.size()-1;
        while(right-left > 1){
            cout << "left: " << left << " right: " << right << endl;
            int mid = (right+left)/2;
            // current ice cream in consideration
            string flavor = menu[mid].first;
            int price = menu[mid].second;
            if (price < complement){
                left = mid;
            } else if (price > complement){
                right = mid;
            } else if (mid != forbidden_index){
                if (price == complement){
                    // we found our second ice cream! return its index
                    return {true, mid};
                } else if (menu[left].second == complement){
                    return {true, left};
                } else if (menu[right].second == complement){
                    return {true, right};
                }
            }
        }
        return {false, -1};
    } 


    void findChoices(Menu &menu, int money){
        vector<pair<int, int>> choices = {}; // keeps <index_a, index_b> of all desired combinations

        // 1. Sort menu in ascending order based on price ice cream prices
        sort(menu.begin(), menu.end(), iceCreamComparator);


        for (int a = 0; a < menu.size(); a++){
            string flavor_a = menu[a].first;
            int price_a = menu[a].second;
            // binary search
            int complement = money-price_a;
            pair<bool, int> bsResult = binarySearch(menu, complement, a); // don't explicitly compute b for simplicity
            bool matchFound = bsResult.first;
            if (matchFound){
                int b = bsResult.second; 
                choices.push_back({a,b}); // you could just do a vector of index pairs... better.
            }
        }
        print_choices(choices, menu);
    } 

};

void test0(Solution &s){
    Menu menu = {
        {"chocolate", 5},
        {"vanilla", 10},
        {"strawberry", 15},
        {"mint", 20},
        {"lemon", 25}
    };
    int money = 15;
    s.findChoices(menu, money);
}

void test1(Solution &s){
    Menu menu = {
        {"chocolate", 5},
        {"vanilla", 10},
        {"strawberry", 11},
        {"mint", 4},
        {"lemon", 7},
        {"orange", 8}
    };
    int money = 15;
    s.findChoices(menu, money); // THIS IS FAILING!!!!s huh?
}



int main(){
    Solution s = Solution();
    test0(s);
    test1(s);
}