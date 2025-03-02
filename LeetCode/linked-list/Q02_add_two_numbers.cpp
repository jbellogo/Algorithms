#include <stack>
#include <cassert>
#include <iostream>
#include "linked_list.h"

// This problem is interesting because there is no type that can handle a 100 digit number
// So we cant just convert the list onto a stack and them into a number to add with the + operator.
// That defeats the whole purpose of the question.
// Instead, we will determine how the lists align baed on their lengths, and add values 
// in along this alignment. Might padd the shorter list with leading 0's, at least implicitly. 



using namespace std;
using namespace LinkedList;


class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // determine the larger list. 
        int len1 = l1->get_len();
        int len2 = l2->get_len();

        ListNode *long_list = len1 > len2 ? l1 : l2;
        ListNode *short_list = len1 <= len2 ? l1 : l2;

        // determine the offset between the two lists. 

        // create a new list to store the sum. 
        ListNode *added_list = new ListNode(); // head of the new list
        ListNode *added_list_traverse = added_list; // pointer to the last node of the new list
        int carry_forward = 0;

        while(long_list != nullptr){
            // cout << "offset: " << offset << endl;
            // cout << "long_list: " << long_list->val << endl;
            int sum = long_list->val; // should keep prior quotient (lists are already reversed)
            // addition will be made while offset is greater than 0 (recall the lists are reversed)
            sum += carry_forward;
            if (short_list != nullptr) {
                // cout << "short_list: " << short_list->val << endl;
                sum += short_list->val;
                carry_forward = sum / 10;
                sum %= 10;
                short_list = short_list-> next;
            } else {
                carry_forward = 0; // needs to be reset to 0 once short_list reaches nullptr
            }
            added_list_traverse->val = sum;
            // cout << "added_list: " << current_added_list->val << endl;
            if (long_list->next != nullptr){
                added_list_traverse->next = new ListNode();
                added_list_traverse = added_list_traverse->next;
            } else if (long_list->next == nullptr && carry_forward > 0){
                added_list_traverse->next = new ListNode(carry_forward);
            }
            long_list = long_list->next;


        }
        return added_list;      
    }
};


void test1(){
    Solution s;

    vector<int> v1 = {2, 4, 3};
    vector<int> v2 = {5, 6, 4};
    vector<int> v3 = {7, 0, 8}; // expected addition result

    ListNode* l1 = get_linked_list_from_vector(v1);
    ListNode* l2 = get_linked_list_from_vector(v2);
    ListNode* result = s.addTwoNumbers(l1, l2);

    l1->print();
    l2->print();
    result->print();

    assert(get_vector_from_linked_list(result) == v3);
}


void test2(){
    Solution s;
    // 34916+465=35381

    vector<int> v1 = {6, 1, 9, 4, 3};
    vector<int> v2 = {5, 6, 4};
    vector<int> v3 = {1, 8, 3, 5, 3}; // expected addition result

    ListNode* l1 = get_linked_list_from_vector(v1);
    ListNode* l2 = get_linked_list_from_vector(v2);
    ListNode* result = s.addTwoNumbers(l1, l2);

    l1->print();
    l2->print();
    result->print();

    assert(get_vector_from_linked_list(result) == v3);
}


void test3(){
    // test that additions which result in bigger number of digits are handled correctly. 
    Solution s;

    vector<int> v1 = {0, 5};
    vector<int> v2 = {5, 5};
    vector<int> v3 = {5, 0, 1}; // expected addition result

    ListNode* l1 = get_linked_list_from_vector(v1);
    ListNode* l2 = get_linked_list_from_vector(v2);
    ListNode* result = s.addTwoNumbers(l1, l2);

    l1->print();
    l2->print();
    cout << "result: ";
    result->print();
    cout << endl;

    assert(get_vector_from_linked_list(result) == v3);
}


void test4(){
    // test that additions which result in bigger number of digits are handled correctly. 
    Solution s;

    vector<int> v1 = {9, 9, 9, 9, 9, 9, 9};
    vector<int> v2 = {9, 9, 9, 9};
    vector<int> v3 = {8, 9, 9, 9, 0, 0, 0, 1}; // expected addition result

    ListNode* l1 = get_linked_list_from_vector(v1);
    ListNode* l2 = get_linked_list_from_vector(v2);
    ListNode* result = s.addTwoNumbers(l1, l2);

    l1->print();
    l2->print();
    cout << "result: ";
    result->print();
    cout << endl;

    assert(get_vector_from_linked_list(result) == v3);
}


int main(){
    test1();
    test2();
    test3();
    test4();
    return 0;
}
