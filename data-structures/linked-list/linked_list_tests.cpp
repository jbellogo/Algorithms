#include "linked_list.h"
#include <vector>

using namespace std;
using namespace LinkedList;

void test0(){
    // Test 0: Create a linked list from a vector of integers
    vector<int> v = {1, 2, 3, 4, 5};
    ListNode* head = get_linked_list_from_vector(v);
    head->print();
}

int main(){
    test0();
    return 0;
}
