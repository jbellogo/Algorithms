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

typedef vector<TreeNode*> Path; 

 
 void print_path(Path path){
        for (int i = 0; i < path.size(); i++){

            cout << path[i]->val; 
            if (i < path.size()-1){
                cout << " -> ";
            }
        }
        cout << endl;
    }


 struct PathsState{
    
    Path closed; // max length closed path
    Path open;   // max length open path
    int closed_weight;        // weight of max length closed path
    int open_weight;          // weight of max length open path

    // Constructors 
    PathsState(TreeNode* leaf) : closed({}), open({leaf}), closed_weight(0), open_weight(leaf->val) {
        assert(leaf != nullptr);
    }

    PathsState() : closed({}), open({}), closed_weight(0), open_weight(0) {}

    // Debugging
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

        Path append_paths(Path p1, TreeNode* elem, Path p2){
           
            Path new_path = p1;
            new_path.push_back(elem);
            for(int i = 0; i < p2.size(); i++){
                new_path.push_back(p2[i]);
            }
            return new_path;
        }

        pair<int, Path> get_max_open_path(PathsState* left, TreeNode* intersection, PathsState* right){
            Path new_open = {};
            int new_open_weight = 0;
            if (left == nullptr && right == nullptr){
                // both are nullptr
                new_open = {intersection};
                new_open_weight = intersection->val;
            } else if (left == nullptr || right == nullptr){
                // one of them is nullptr
                PathsState* non_null_state = left == nullptr ? right : left;
                if (non_null_state->open_weight > 0){
                    new_open = non_null_state->open;
                    new_open_weight = non_null_state->open_weight;
                } 
                new_open.push_back(intersection);
                new_open_weight += intersection->val;

            } else {
                // both are non-null
                new_open = left->open_weight > right->open_weight ? left->open : right->open;
                new_open_weight = max(left->open_weight, right->open_weight);

                if (new_open_weight < 0) {
                    // restart the path.
                    new_open = {};
                    new_open_weight = 0;
                }
                // always add intersection to keep it 'open'
                new_open.push_back(intersection);
                new_open_weight += intersection->val;
            }
            return {new_open_weight, new_open};
        }



        pair<int, Path> get_max_closed_path(PathsState* left, TreeNode* intersection, PathsState* right){
            Path new_closed = {};
            int new_closed_weight = 0;

            if (left == nullptr && right == nullptr){
                return {0, {}};
            }
            if (left == nullptr || right == nullptr){
                cout << "one of them is nullptr" << endl;
                // one of them is nullptr
                PathsState* non_null_state = left == nullptr ? right : left;
                // Case 1: can choose from non_null state closed or open (without including intersection to become closed):
                if (non_null_state->closed.empty()){
                    // closed can be empty but open cannot be empty.
                    new_closed = non_null_state->open;
                    new_closed_weight = non_null_state->open_weight;
                } else if (non_null_state->closed_weight > non_null_state->open_weight){
                    new_closed = non_null_state->closed;
                    new_closed_weight = non_null_state->closed_weight;
                } else {
                    // both are non-empty and closed_weight < open_weight
                    new_closed = non_null_state->open;
                    new_closed_weight = non_null_state->open_weight;
                }
                return {new_closed_weight, new_closed};
            }
            // both are non-null


            // Case 1: new max-weight closed path is one the right or the left closed paths. 
            new_closed = (left->closed_weight > right->closed_weight) ? left->closed : right->closed;
            new_closed_weight = max(left->closed_weight, right->closed_weight);



            // Case 2: new max-weight closed path joins the left and right opens at intersection. 
            int joined_opens_weight = left->open_weight + right->open_weight + intersection->val;

            if (joined_opens_weight > new_closed_weight){
                // this is the only case when we can add the intersection and keep it closed to parent
                new_closed = append_paths(left->open, intersection, right->open);
                new_closed_weight = joined_opens_weight;
            }

            // Case 3: new max-weight closed path is one from right or left OPEN paths, becomes closed after this intersection

            int max_open = max(left->open_weight, right->open_weight); // these things cannot be initialized to zero because domain is all reals. 
            if (new_closed_weight <  max_open || new_closed.empty()){
                new_closed = (left->open_weight > right->open_weight) ? left->open : right->open;
                new_closed_weight = max_open;
            }
            return {new_closed_weight, new_closed};
        }


        PathsState* combine_states(PathsState* left, TreeNode *intersection, PathsState *right){
            pair<int, Path> open = get_max_open_path(left, intersection, right);
            pair<int, Path> closed = get_max_closed_path(left, intersection, right);

            PathsState* ps = new PathsState();
            ps->open_weight = open.first;
            ps->open = open.second;
            ps->closed_weight = closed.first;
            ps->closed = closed.second;
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
                // initialize the state of leafs as singleton open paths, empty closed path.
                PathsState * ps = new PathsState(root);
                return ps;
            } 

            PathsState* left_state = nullptr; //new PathsState();
            PathsState* right_state = nullptr; //new PathsState();

            if (right != nullptr && parents.find(right) == parents.end()){
                parents[right] = root;
                right_state = dfs_visit(right, parents);
            }
            if (left != nullptr && parents.find(left) == parents.end()){
                parents[left] = root;
                left_state = dfs_visit(left, parents);
            }

            return combine_states(left_state, root, right_state);
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


            cout << "----- maxPathsum -----" << endl;
            cout << "MAX CLOSED PATH: " << endl;
            print_path(state->closed);
            cout << "MAX OPEN PATH: " << endl;
            print_path(state->open);
            
            return max(state->closed_weight, state->open_weight);
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
    cout << "-------------------------------- test5 --------------------------------" << endl;
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(-1);
    int res = sol.maxPathSum(root);
    cout << "----------------------------- Max Path Sum: " << res << "-----------------------------" << endl;
    assert(res == 2);
}

void test6(Solution &sol){
    cout << "-------------------------------- test6 --------------------------------" << endl;
    TreeNode *root = new TreeNode(5);
    root->left = new TreeNode(-2);
    root->left->left = new TreeNode(1);
    int res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == 5);

    root->left->left->left = new TreeNode(2);
    res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == 6);
}

void test7(Solution &sol){
    cout << "-------------------------------- test7 --------------------------------" << endl;
    TreeNode *root = new TreeNode(-1);
    root->left = new TreeNode(1);
    root->right = new TreeNode(-1);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(-1);
    root->right->right = new TreeNode(-1);
    int res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == 3);
}


void test8(Solution &sol){
    // all negative
    // [-2,-1]
    cout << "-------------------------------- test8.1 --------------------------------" << endl;
    TreeNode *root = new TreeNode(-2);
    root->left = new TreeNode(-1);
    int res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == -1);

    cout << "-------------------------------- test8.2 --------------------------------" << endl;

    root = new TreeNode(-2);
    root->left = new TreeNode(-1);
    res = sol.maxPathSum(root);
    cout << "Max Path Sum: " << res << endl;
    assert(res == -1);
    
}



int main(){
    Solution sol;
    test0(sol);
    test1(sol);
    test2(sol);
    test3(sol);
    test4(sol);
    test5(sol);
    test6(sol);
    test7(sol);
    test8(sol);
}