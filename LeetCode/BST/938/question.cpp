
#include <queue>
#include <iostream>


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
        while (!q.empty()) {
            TreeNode* current = q.front();
            TreeNode* left = current->left;
            TreeNode* right = current->right;

            int val = current->val;
            cout << "checking node: " << val << endl;
            if (current != nullptr) {
                if (low <= val <= high){
                    // check both children
                    
                    q.push(left);
                    q.push(right);
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
        
    }
};

void test1(Solution& sol){
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(7);
    root->right->right = new TreeNode(18);
    sol.rangeSumBST(root, 7, 15);

   
}

int main(){
    Solution sol;
    test1(sol);
}
