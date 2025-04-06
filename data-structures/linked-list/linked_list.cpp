// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// This file contains the implementation of the linked list namespace.
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



#include "linked_list.h"
#include <iostream>
#include <vector>

using namespace std;

namespace LinkedList {
// Definition for singly-linked list.
        
void ListNode::print() {
    // Prints all linked list values starting from this node
    ListNode* current = this;
    while (current != nullptr) {
        std::cout << current->val;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

int ListNode::get_len() {
    // Returns the length of the linked list starting from this node
    int len = 0;
    ListNode *traverse = this;
    while(traverse != nullptr) {
        len++;
        traverse = traverse->next;
    }
    return len;
}


ListNode* get_linked_list_from_vector(std::vector<int> v){
    // Creates a linked list from a vector of integers, returns the head of the list
    ListNode* head = new ListNode();
    ListNode* traverse = head;
    for (int i = 0; i < v.size(); i++){
        traverse->val = v[i];
        if (i != v.size()-1){
            traverse->next = new ListNode();
        } else {
            traverse->next = nullptr;
        }
        traverse = traverse->next;
    }
    return head;
}

std::vector<int> get_vector_from_linked_list(ListNode* head){
    // Creates a vector of integers from a linked list, returns the vector
    std::vector<int> v;
    ListNode* current = head;
    while (current != nullptr) {
        v.push_back(current->val);
        current = current->next;
    }
    return v;
}



};

