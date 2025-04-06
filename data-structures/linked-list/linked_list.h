#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <vector>

namespace LinkedList {

    struct ListNode {
        int val;
        ListNode* next;
        
        // Constructor declaration
        ListNode(int x = 0) : val(x), next(nullptr) {}
        
        // Member function declaration
        void print();
        int get_len();
    };

    ListNode* get_linked_list_from_vector(std::vector<int> v);

    std::vector<int> get_vector_from_linked_list(ListNode* head);

}

#endif // LINKED_LIST_H
