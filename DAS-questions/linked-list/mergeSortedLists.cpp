// 21 Merge two sorted, linked lists

// @TODO Inefficient

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

 void print_list(ListNode* lst){
    ListNode*iter = lst;
    cout << iter->val;
    while (iter->next != nullptr){
        cout << ", "<< iter->next->val;
        iter = iter->next;
    }
    cout << endl;
}


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        //mutate list2 in place
        if (list1 == nullptr){
            return list2;
        } else if (list2 == nullptr){
            return list1;
        }
        ListNode* mergedList = nullptr;
        ListNode* prior = nullptr;


        if (list1->val <= list2->val) {
            mergedList = new ListNode(list1->val, list2);
            // on less from list 1 to add
            list1 = list1->next;
            prior = mergedList;
        } else {
            mergedList = list2;
        }

        while (list1 != nullptr){ 
            int val1 = list1->val;
            // insert a new node with val1 into list2
            cout << endl;
            cout << "ATTEMPTING TO ADD LIST1 ITEM: " << val1 << endl;
            cout << "lst2 = ";
            print_list(mergedList);




            while (list2 != nullptr){
                cout <<  "val2 = " << list2->val << endl;
                // int val2 = list2->val;
                if (val1 <= list2->val){
                    // ISSUE IS HERE
                    ListNode* intermediate_node1 = new ListNode(val1, list2);
                    cout << "prior is null?: "<< (prior == nullptr) << endl;
                    if (prior != nullptr){
                        prior->next = intermediate_node1;
                        prior = prior->next;
                        break;
                    }
                }
                // if (list2->next != nullptr) {
                //     if (val1 <= list2->next->val){
                //         // Insert intermediate node
                //         ListNode* intermediate_node = new ListNode(val1, list2->next);
                //         list2->next = intermediate_node;
                //         break;
                //     }

                // } else {
                
                if (list2->next == nullptr){
                    // Insert back node
                    ListNode* terminal_node = new ListNode(val1);
                    list2->next = terminal_node;
                    break;
                }
                // else don't insert it at this position, keep loop going.
                prior = list2;

                list2 = list2->next;
            }
            list1 = list1->next;


        }
        return mergedList;
    }
};




void test_0(){

    // TEST #0
    // List 1
    ListNode* L1n3 = new ListNode(9); // last node, pointing to nullptr
    ListNode* L1n2 = new ListNode(5, L1n3);
    ListNode* L1 = new ListNode(3, L1n2); // First node
    // List 2
    ListNode* L2n3 = new ListNode(6); // last node, pointing to nullptr
    ListNode* L2n2 = new ListNode(3, L2n3);
    ListNode* L2 = new ListNode(1, L2n2); // First node

    print_list(L1);
    print_list(L2);

    Solution sol;
    ListNode* ans  = sol.mergeTwoLists(L1, L2);

    vector<int> ans_vec = {1,3,3,5,6,9};
    int index = 0;
    while (ans != nullptr){
        // cout << ans->val << endl;
        assert(ans->val == ans_vec[index]);
        index++;
        ans = ans->next;
    }
}

void test_1(){
    /////////////////////////////////////////////////////////
    // TEST #2
    // List 1
    ListNode* L1T2 = new ListNode(0); // [0]
    ListNode* L2T2 = nullptr; // []
    Solution sol;
    ListNode* ans2  = sol.mergeTwoLists(L1T2, L2T2);
    assert(ans2->val == 0);
    assert(ans2->next == nullptr);
}

void test_2(){
    ListNode* L1 = new ListNode(0); // [0]
    ListNode* L2 = nullptr; // []
    Solution sol;
    ListNode* ans  = sol.mergeTwoLists(L1, L2);
    assert(ans->next == nullptr);
    assert(ans->val == 0);

}
void test_3(){

    /////////////////////////////////////////////////////////
    // TEST #3
    ListNode* L1T3 = nullptr; // [] List 1
    ListNode* L2T3 = nullptr; // [] List 2
    Solution sol;
    ListNode* ans3  = sol.mergeTwoLists(L1T3, L2T3);
    vector<int> ans3_vec = {};
    assert(ans3 == nullptr);    

}
void test_4(){

    /////////////////////////////////////////////////////////
    // TEST #4
    ListNode* L1 = new ListNode(2); // [2] List 1
    ListNode* L2 = new ListNode(1); // [1] List 2
    Solution sol;
    ListNode* ans  = sol.mergeTwoLists(L1, L2);
    vector<int> ans4_vec = {1,2};
    int index = 0;

    while (ans != nullptr){
        // cout << ans->val << " =? " << ans4_vec[index]<< endl;
        assert(ans->val == ans4_vec[index]);
        index++;
        ans = ans->next;
    }

}
void test_5(){
    /////////////////////////////////////////////////////////
    // TEST #5
   // List 1
    ListNode* L1T5n3 = new ListNode(4); // last node, pointing to nullptr
    ListNode* L1T5n2 = new ListNode(2, L1T5n3);
    ListNode* L1T5 = new ListNode(1, L1T5n2); // First node
    // List 2
    ListNode* L2T5n3 = new ListNode(4); // last node, pointing to nullptr
    ListNode* L2T5n2 = new ListNode(3, L2T5n3);
    ListNode* L2T5 = new ListNode(1, L2T5n2); // First node

    print_list(L1T5);
    print_list(L2T5);
    Solution sol;
    ListNode* ans  = sol.mergeTwoLists(L1T5, L2T5);
    int index=0;
    vector<int> ans5_vec = {1,1,2,3,4,4};
    index = 0;
    while (ans != nullptr){
        // cout << ans->val << endl;
        assert(ans->val == ans5_vec[index]);
        index++;
        ans = ans->next;
    }

}

void test_6(){
    /////////////////////////////////////////////////////////
    // TEST # 6
   // List 1
    ListNode* L1T6n2 = new ListNode(3); // last node, pointing to nullptr
    ListNode* L1T6 = new ListNode(-9, L1T6n2);
    // List 2
    ListNode* L2T6n2 = new ListNode(7); // last node, pointing to nullptr
    ListNode* L2T6 = new ListNode(5, L2T6n2);

    print_list(L1T6);
    print_list(L2T6);

    Solution sol;
    ListNode* ans  = sol.mergeTwoLists(L1T6, L2T6);

    vector<int> ans6_vec = {-9,3,5,7};
    int index = 0;
    cout << "ans : ";
    print_list(ans);
    while (ans != nullptr){
        assert(ans->val == ans6_vec[index]);
        index++;
        ans = ans->next;
    }


   
}

void test_7(){
    // TEST # 7
    // List 1
    // L1 = {-10,-10,-9,-4,1,6,6};


    ListNode* L1T7n7 = new ListNode(6); // last node, pointing to nullptr
    ListNode* L1T7n6 = new ListNode(6, L1T7n7);
    ListNode* L1T7n5 = new ListNode(1, L1T7n6); // last node, pointing to nullptr
    ListNode* L1T7n4 = new ListNode(-4, L1T7n5);
    ListNode* L1T7n3 = new ListNode(-9, L1T7n4); // last node, pointing to nullptr
    ListNode* L1T7n2 = new ListNode(-10, L1T7n3);
    ListNode* L1T7 = new ListNode(-10, L1T7n2); // last node, pointing to nullptr

    // List 2 
    // L2 : [-7]
    ListNode* L2T7 = new ListNode(-7); // last node, pointing to nullptr
    Solution sol;
    ListNode* ans  = sol.mergeTwoLists(L1T7, L2T7);

    vector<int> ans7_vec = {-10,-10,-9,-7,-4,1,6,6};
    int index = 0;
   
    cout << "ANSWER : ";
    print_list(ans);
    while (ans != nullptr){
        assert(ans->val == ans7_vec[index]);
        index++;
        ans = ans->next;
    }
}


int main() {
    test_0();
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
}




