#include <map>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
 void print_path(vector<TreeNode*> path){
        for (int i = 0; i < path.size(); i++){

            cout << path[i]->val; 
            if (i < path.size()-1){
                cout << " -> ";
            }
        }
        cout << endl;
    }


 struct PathsState{

    // "max length closed path"
    vector<TreeNode*> closed = {}; 
    int closed_len = 0; 

    // "max length open path"
    vector<TreeNode*> open = {}; // pointer, value
    int open_len = 0; 

    void print_state(){
        cout << "CLOSED : ";
        print_path(this->closed);
        cout << "OPEN : ";
        print_path(this->open);
    }
};


class Solution {
    public:

        bool isLeaf(TreeNode *v){
            return (v != nullptr && v->left == nullptr && v->right == nullptr);
        }

        vector<TreeNode*> append_paths(vector<TreeNode*> p1, TreeNode* elem, vector<TreeNode*> p2){
           
            vector<TreeNode*> new_path = p1;
            new_path.push_back(elem);
            for(int i = 0; i < p2.size(); i++){
                new_path.push_back(p2[i]);
            }
            return new_path;
        }


        PathsState* combine_states(TreeNode *intersection, PathsState* left, PathsState *right){
            PathsState* ps = new PathsState();

            // update max_closed_path
            cout << "------- combine_states -------" << endl;
            cout << "Intersection: " << intersection->val << endl;
            if (left != nullptr && right == nullptr){
                ps->open = left->open;
                ps->open.push_back(intersection);
                ps->open_len = left->open_len + intersection->val;
                ps->closed = left->closed;
                ps->closed_len = left->closed_len;
            } else if (right != nullptr && left == nullptr){
                ps->open = right->open;
                ps->open.push_back(intersection);
                ps->open_len = right->open_len + intersection->val;
                ps->closed = right->closed;
                ps->closed_len = right->closed_len;
            } else if (right != nullptr && left != nullptr){
                cout << "  Neither are nullptr" << endl;
                // UPDATE MAX CLOSED PATH:            
                // if you have two local closed paths, compare them.
                if (left->closed_len >  right->closed_len){
                    ps->closed = left->closed;
                    ps->closed_len = left->closed_len;
                } else {
                    ps->closed = right->closed;
                    ps->closed_len = right->closed_len;
                }
                // Compare that to joining the two open paths:
                if (left->open_len + right->open_len + intersection->val > ps->closed_len){
                    cout << " - joining two open paths for new max_closed at intersections" << endl;
                    ps->closed = append_paths(left->open, intersection, right->open);
                    ps->closed_len = left->open_len + right->open_len + intersection->val;
                }    
                
                // UPDATE MAX OPEN PATH
                if (left->open_len >  right->open_len){
                    ps->open = left->open;
                    ps->open_len = left->closed_len;
                } else {
                    ps->open = right->open;
                    ps->open_len = right->open_len;
                }
                ps->open.push_back(intersection);
                ps->open_len++;
            }
            ps->print_state();
            cout << "--------------------------------" << endl;
            return ps;            
        }


        // Let s be node names 
        PathsState* dfs_visit(TreeNode *root, map<TreeNode*, TreeNode*> &parents){
            // Recursive 
            cout << "vertex : " << root->val << endl;
            TreeNode * left = root->left;
            TreeNode * right = root->right;
            // For all its descendants, compute this
            if (isLeaf(root)){
                // ps->max_closed_path.push_back({root, root->val});
                PathsState * ps = new PathsState();
                ps->open.push_back(root);
                ps->open_len += root->val;
                return ps;
            } 

            PathsState* left_state = nullptr;
            PathsState* right_state = nullptr;

            if (right != nullptr && parents.find(right) == parents.end()){
                parents[right] = root;
                right_state = dfs_visit(right, parents);
            }
            if (left != nullptr && parents.find(left) == parents.end()){
                parents[left] = root;
                left_state = dfs_visit(left, parents);
            }

            return combine_states(root, left_state, right_state);
        }



        int maxPathSum(TreeNode* root) {
            map<TreeNode*, TreeNode*> parents = {{root, nullptr}};
            // Used to determine connected components.
            if (root == nullptr){
                return 0;
            }
            if (root->left == nullptr && root->right == nullptr){
                return root->val;
            }
            PathsState *state = dfs_visit(root, parents);
            cout << "MAX CLOSED PATH: " << endl;
            print_path(state->closed);
            cout << "MAX OPEN PATH: " << endl;
            print_path(state->open);
            return state->closed_len < state->open_len ? state->open_len : state->closed_len;
        }
};


void test0(Solution &sol){
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1000);
    root->left->left = new TreeNode(4);
    int res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == 1012);
}

void test1(Solution &sol){
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    int res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == 6);
}

void test2(Solution &sol){
    TreeNode *root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    int res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == 42);
}

void test3(Solution &sol){
    TreeNode *root = new TreeNode(-3);
    cout << "Max Path Sum: " << sol.maxPathSum(root) << endl;
    assert(sol.maxPathSum(root) == -3);
}

void test4(Solution &sol){
    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(3);
    cout << "Max Path Sum: " << sol.maxPathSum(root) << endl;
    assert(sol.maxPathSum(root) == 4);
}

void test5(Solution &sol){
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(-1);
    cout << "Max Path Sum: " << sol.maxPathSum(root) << endl;
    assert(sol.maxPathSum(root) == 2);
}

int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
}