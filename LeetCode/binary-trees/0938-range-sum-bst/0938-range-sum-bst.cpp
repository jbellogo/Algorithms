
#include <queue>
#include <iostream>
#include <cassert>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        queue<TreeNode*> q; // queue node addresses. 
        q.push(root);
        int sum = 0;
        while (!q.empty()) {
            TreeNode* current = q.front();
            if (current != nullptr) {
                TreeNode* left = current->left;
                TreeNode* right = current->right;

                int val = current->val;
                // cout << "checking node: " << val << endl;
                if (low <= val && val <= high){
                    // check both children
                    q.push(left);
                    q.push(right);
                    sum += val;
                } else if (val < low){
                    // only check the right child
                    q.push(right);
                } else if (val > high){
                    // check the left child
                    q.push(left);
                }
            }
            q.pop(); 
        }
        return sum;
        
    }
};

void test1(Solution& sol){
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->right = new TreeNode(18);
    int sum = sol.rangeSumBST(root, 7, 15);
    assert(sum == 32);   
    sum = sol.rangeSumBST(root, 10, 15);
    assert(sum == 25);
    sum = sol.rangeSumBST(root, 20, 30);
    assert(sum == 0);
    sum = sol.rangeSumBST(root, 1, 2);
    assert(sum == 0);
    sum = sol.rangeSumBST(root, 5, 40);
    assert(sum == 55);

}

void test2(Solution& sol){
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->left->left->left = new TreeNode(1);
    root->left->right->left = new TreeNode(6);

    root->right = new TreeNode(15);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(18);

    int sum = sol.rangeSumBST(root, 6, 10);
    assert(sum == 23);
    int sum2 = sol.rangeSumBST(root, 1, 6);
    assert(sum2 == 22);

}

int main(){
    Solution sol;
    test1(sol);
}
