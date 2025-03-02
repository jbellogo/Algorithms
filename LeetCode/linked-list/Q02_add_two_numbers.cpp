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


class Solution1 {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /*
        The two lists are already reversed, so we can just add the values together.
        The only issue is that the lists may be of different lengths, so they are aligned
        by their lengths to determine the position of the remainders of the additon and 
        the quotients are carried forward. 
        @NOTE: What makes it suboptimal is that get_len() is a O(n) operation. So our 
        solution is O(3n) for time complexity when we could just iterate through both at the time.
        */
        // determine the larger list. 
        int len1 = l1->get_len();
        int len2 = l2->get_len();

        ListNode *long_list = len1 > len2 ? l1 : l2;
        ListNode *short_list = len1 <= len2 ? l1 : l2;


        // create a new list to store the sum. 
        ListNode *added_list = new ListNode(); // head of the new list
        ListNode *added_list_traverse = added_list; // pointer to traverse the new list

        int carry_forward = 0;

        while(long_list != nullptr){
            int sum = long_list->val;
            sum += carry_forward; // this needs to be here before carry_forward is potentially reset to 0. 
            // Since the list are reversed, iterate through both simultaneously from start to end
            // While the smaller list is not exhausted, add the values together mod 10, carry forward the quotient
            if (short_list != nullptr) {
                sum += short_list->val;
                short_list = short_list-> next;
            } else {
                carry_forward = 0; // needs to be reset to 0 once short_list reaches nullptr
            }
            carry_forward = sum / 10;
            sum %= 10;
            added_list_traverse->val = sum;

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


class Solution2 {
    // Solution by Rahul Varma
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // How to do it without taking the length of the lists?
        ListNode *dummy_head = new ListNode(); // will be removed at end.
        ListNode *tail = dummy_head; // tail is a good name for this traversing pointer.

        int carry = 0;

        // While one of these conditions is true, we need to keep iterating. 
        // WLOG:
        // * if l1 is the only true, the tail array keeps copying off it. 
        // * If carry and l1 are true, the tail array keeps copying off l1 and applies the carry once 
        // * If only carry is true, we must add an additional final node to hold the carry.

        while (l1 != nullptr || l2 != nullptr || carry != 0){
            int digit1 = (l1==nullptr) ? 0 : l1->val;
            int digit2 = (l2==nullptr) ? 0 : l2->val;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            int digit = sum % 10;
            
            tail->next = new ListNode(digit);
            tail = tail->next;

            l1 = (l1==nullptr) ? nullptr : l1->next; 
            l2 = (l2==nullptr) ? nullptr : l2->next;
        }
        ListNode *head = dummy_head->next;
        delete dummy_head;
        return head;
    }
};


void test1(Solution2 &s){

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


void test2(Solution2 &s){
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


void test3(Solution2 &s){
    // test that additions which result in bigger number of digits are handled correctly. 

    vector<int> v1 = {0, 5};
    vector<int> v2 = {5, 5};
    vector<int> v3 = {5, 0, 1}; // expected addition result

    ListNode* l1 = get_linked_list_from_vector(v1);
    ListNode* l2 = get_linked_list_from_vector(v2);
    ListNode* result = s.addTwoNumbers(l1, l2);

    l1->print();
    l2->print();
    result->print();

    assert(get_vector_from_linked_list(result) == v3);
}


void test4(Solution2 &s){
    // test that additions which result in bigger number of digits are handled correctly. 

    vector<int> v1 = {9, 9, 9, 9, 9, 9, 9};
    vector<int> v2 = {9, 9, 9, 9};
    vector<int> v3 = {8, 9, 9, 9, 0, 0, 0, 1}; // expected addition result

    ListNode* l1 = get_linked_list_from_vector(v1);
    ListNode* l2 = get_linked_list_from_vector(v2);
    ListNode* result = s.addTwoNumbers(l1, l2);

    l1->print();
    l2->print();
    result->print();

    assert(get_vector_from_linked_list(result) == v3);
}


int main(){
    Solution2 s;
    cout << "test1" << endl;
    test1(s);
    cout << "test2" << endl;
    test2(s);
    cout << "test3" << endl;
    test3(s);
    cout << "test4" << endl;
    test4(s);
    return 0;
}
