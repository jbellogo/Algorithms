
#include<vector>
#include<iostream>
#include<queue>
#include<cassert>
#include<map>

using namespace std;

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

        vector<int> Inefficient(TreeNode* root) {
            int lvl = 1;
            vector<TreeNode*> frontier;
            frontier.push_back(root);
            vector<int> rightmosts;

            while (!frontier.empty()){
                vector<TreeNode*> next = {};
                cout << "lvl: " << lvl << " frontier: ";
                for (auto &v : frontier){
                    if (v == nullptr){
                        continue;
                    }
                    // update answer
                    if (rightmosts.size() == lvl){
                        rightmosts[lvl-1] = v->val;
                    } else {
                        rightmosts.push_back(v->val);
                    }
                    TreeNode* left = v->left;
                    TreeNode* right = v->right;
                    for (auto &child : vector<TreeNode*>{left, right}){
                        if (child != nullptr){
                            next.push_back(child);
                        }
                    }
                }
                cout << endl;
                frontier = next;
                lvl++;
            }
            return rightmosts;
        }

        vector<int> rightSideView(TreeNode* root) {
            int lvl = 1;
            queue<TreeNode*>frontier;
            frontier.push(root);            
            vector<int> rightmosts;

            TreeNode * temp;

            while (!frontier.empty()){
                cout << "lvl: " << lvl << " frontier: ";
                // not using i, just want to control how I process all chilren at a time
                const int children_in_level = frontier.size(); // before adding new children 
                for (int i = 0; i < children_in_level; i++){
                    temp = frontier.front();
                    frontier.pop();
                    if (temp == nullptr){
                        continue;
                    }
                    // update answer
                    if (rightmosts.size() == lvl){
                        rightmosts[lvl-1] = temp->val;
                    } else {
                        rightmosts.push_back(temp->val);
                    }
                    TreeNode* left = temp->left;
                    TreeNode* right = temp->right;
                    for (auto &child : vector<TreeNode*>{left, right}){
                        if (child != nullptr){
                            frontier.push(child); // it's okay
                        }
                    }
                }
                cout << endl;
                lvl++;
            }
            return rightmosts;
        }

        

        vector<int> FirstAttempt(TreeNode* root) {
            queue<TreeNode *> q;
            q.push(root);
            vector<TreeNode *> bstree;
            int n = bstree.size();
            int level = 1; // as exponent
            int children_in_level = 1;
            vector<int> rightmost_vals;
            int candidate = -1;
            while (!q.empty()){
                TreeNode * node = q.front();
                q.pop();

                if (node != nullptr){
                    candidate = node->val;
                    if (rightmost_vals.size() == level){
                        rightmost_vals[level-1] = candidate;
                    } else {    
                        rightmost_vals.push_back(candidate);
                    }
                    // cannot keep the full tree structure as it causes an infinite loop
                    TreeNode * left = node->left;
                    TreeNode * right = node->right;
                    q.push(left);
                    q.push(right);
                }


                int val = node != nullptr ? node->val : -1;
                cout << "val: " << val << "  &&  level: " << level  << endl;
                if (children_in_level > 1){
                    children_in_level--;
                } else {
                    level++;
                    children_in_level = pow(2,level-1);
                }
            }
            return rightmost_vals;
        }
    
};

void print_vector(vector<int> &vec){
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

void test0(Solution &sol){
    cout << "------------test0------------" << endl;
    TreeNode * root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);
    vector<int> ans = sol.rightSideView(root);
    print_vector(ans);
    assert(ans == vector<int>({1, 3, 4}));
    // [1, 3, 4] answer
}

void test1(Solution &sol){
    cout << "------------test1------------" << endl;
    TreeNode * root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->left = new TreeNode(5);
    vector<int> ans = sol.rightSideView(root);
    print_vector(ans);
    assert(ans == vector<int>({1, 3, 4, 5}));
    // [1, 3, 4, 5] answer
}

void test2(Solution &sol){
    cout << "------------test2------------" << endl;
    TreeNode * root = nullptr;
    vector<int> ans = sol.rightSideView(root);
    print_vector(ans);
    assert(ans == vector<int>({}));
    // [] answer
}

void test3(Solution &sol){
    cout << "------------test3------------" << endl;
    TreeNode * root = new TreeNode(1);
    root->right = new TreeNode(3);
    vector<int> ans = sol.rightSideView(root);
    print_vector(ans);
    assert(ans == vector<int>({1, 3}));
    // [1, 3] answer
}

void test4(Solution &sol){
    cout << "------------test4------------" << endl;
    TreeNode * root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->left->right->left = new TreeNode(6);
    root->left->right->left->left = new TreeNode(7);
    root->left->right->left->right = new TreeNode(8);
    root->left->right->left->left->right = new TreeNode(9);
    root->left->right->left->left->right->right = new TreeNode(10);
    vector<int> ans = sol.rightSideView(root);
    print_vector(ans);
    assert(ans == vector<int>({1, 3, 5, 6, 8, 9, 10}));
    // [1, 3, 4, 6, 7, 8, 9, 10] answer
}


int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
}