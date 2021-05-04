/*
272. Closest Binary Search Tree Value II

Given the root of a binary search tree, a target value, and an integer k, return the k values in the BST that are closest to the target. You may return the answer in any order.

You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

Example 1:


Input: root = [4,2,5,1,3], target = 3.714286, k = 2
Output: [4,3]
Example 2:

Input: root = [1], target = 0.000000, k = 1
Output: [1]
 

Constraints:

The number of nodes in the tree is n.
1 <= k <= n <= 104.
0 <= Node.val <= 109
-109 <= target <= 109
 

Follow up: Assume that the BST is balanced. Could you solve it in less than O(n) runtime (where n = total nodes)?
*/

#include <functional>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <stack>

using std::stack;
using std::multimap;
using std::priority_queue;
using std::queue;
using std::vector;

class ClosestKValues {

    /*
        272.Closest-Binary-Search-Tree-Value-II
        构造一个队列。按中序遍历递归这个数组，不断将访问的节点加入这个队列。当加入的元素与target的差距大于队首元素与target的差距，即可停止。
    */

public:
    vector<int> closestKValues(TreeNode* root, double target, int k) 
    {
        queue<int>q;
        
        DFS(root,q,target,k);
        
        vector<int>result;
        while (!q.empty())
        {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
    
    void DFS(TreeNode* root, queue<int>&q, double target, int k)
    {
        if (root==NULL) return;
        
        DFS(root->left, q, target, k);
        
        if (q.size()<k)
        {
            q.push(root->val);
            DFS(root->right,q,target,k);
        }
        else
        {
            if (abs(q.front()-target)>abs(root->val-target))
            {
                q.push(root->val);
                q.pop();
                DFS(root->right,q,target,k);
            }
        }
    }

public:

    /*
        Approach 2: Recursive Inorder + Heap, O(N log k) time
        img Figure 2. Heap.

        Algorithm

        Instantiate the heap with "less close element first" strategy so that the heap contains the elements that are closest to the target.

        Use inorder traversal to traverse the tree following the direction Left -> Node -> Right.

        Push all elements into heap during the traversal, keeping the heap size less than or equal to kk.
        As a result, the heap contains kk elements that are closest to target. Convert it into a list and return.

        Implementation


        Optimisations

        One could optimize the solution by adding the stop condition. Inorder traversal pops the elements in the sorted order. Hence once the distance of the current element to the target becomes greater than the distance of the first element in a heap, one could stop the computations. The overall worst-case time complexity would be still \mathcal{O}(N \log k)O(Nlogk), but the average time could be improved to \mathcal{O}(H \log k)O(Hlogk), where HH is a tree height.

        Complexity Analysis

        Time complexity: O(Nlogk) to push N elements into the heap of the size kk.

        Space complexity: O(k+H) to keep the heap of k elements and the recursion stack of the tree height.
    */
    vector<int> doit_heap(TreeNode* root, double target, int k) {

        std::multimap<double, int> buf;

        std::function<void(TreeNode*)> inorder = [&](TreeNode* p) {

            if (!p) return;

            inorder(p->left);

            buf.emplace(abs(p->val - target), p->val);

            if (buf.size()>k)
                buf.erase(prev(buf.end()));


            inorder(p->right);
        };

        inorder(root);
        
        vector<int> ans;
        for (auto it : buf) {
            ans.push_back(it.second);
        }

        return ans;
    }

    /*
        The idea is to keep a size K max-heap, which contains the k closest element of the binary search tree. In order to calculate the difference between value and target, 
        we keep a pair<int, double> as the priority_queue's element. p.first ------> the value in the binary search tree, p.second -------->target. difference = abs(p.first - p.second).
        But this solution is O(N + K), because it needs to depth-first-search all values in the binary search tree, which takes O(N); and the time to store all k closest elements into the result vector is O(K).
    */

   struct compare {
        bool operator() (const std::pair<int, double>& l, const std::pair<int, double>& r) {
            return abs (l.first - l.second) < abs (r.first - r.second);
        }
    };

    vector<int> closestKValues(TreeNode* root, double target, int k) {
        priority_queue<std::pair<int, double>, vector<std::pair<int, double>>, compare> Q;
        dfs(root, Q, target, k);
        //push all Q into the result vector
        vector<int> res;
        while (!Q.empty()) {
            res.push_back(Q.top().first);
            Q.pop();
        }
        return res;
    }
    
    void dfs(TreeNode* root, priority_queue<std::pair<int, double>, vector<std::pair<int, double>>, compare>& Q, double target, int k) {
        if (root == NULL) return;
        Q.push({root->val, target});
        if (Q.size() > k)
            Q.pop();
        dfs(root->left, Q, target, k);
        dfs(root->right, Q, target, k);
    }

public:

    vector<int> closestKValues(TreeNode* root, double target, int k) {
        deque<int> res;
        // find up to k values, that smaller than(or equal to) target
        find_k_smallerEq(root, target, k, res);
        deque<int> resBigger;
        find_k_bigger(root, target, k, resBigger);
        for (auto v : resBigger) {
            res.push_back(v);
        }
        while (res.size() > k) {
            if (abs(res.front() - target) >= abs(res.back() - target)) {
                res.pop_front();
            }else {
                res.pop_back();
            }
        }
        return vector<int>(res.begin(), res.end());
    }

    void find_k_smallerEq(TreeNode* root, double target, const int k, deque<int>& res) {
        if (not root || res.size() >= k)
            return;
        if (root->val > target) {
            find_k_smallerEq(root->left, target, k, res);
            return;
        }
        find_k_smallerEq(root->right, target, k, res);
        if (res.size() < k)
            res.push_front(root->val);
        find_k_smallerEq(root->left, target, k, res);
    }
    
    void find_k_bigger(TreeNode* root, double target, const int k, deque<int>& res) {
        if (not root || res.size() >= k) {
            return;
        }
        if (root->val <= target) {
            find_k_bigger(root->right, target, k, res);
            return;
        }
        find_k_bigger(root->left, target, k, res);
        if (res.size() < k)
            res.push_back(root->val);
        find_k_bigger(root->right, target, k, res);
    }

public:

    // stack that moves lower and higher on the BST
    stack <TreeNode*> hi, lo;
    vector<int> closestKValues(TreeNode * root, double target, int k) {
        // write your code here
        // first find the closest TreeNode
        TreeNode* pivot = findTarget(root, target);
        initStacks(root, pivot);
        vector<int> ret;
        ret.push_back(pivot->val);
        moveHigher();
        moveLower();
        
        while (ret.size() < k){
            if (lo.empty() && hi.empty()){
                break;
            }
            if (lo.empty() || (!hi.empty() && abs(hi.top()->val - target) < abs(lo.top()->val - target))){
                ret.push_back(hi.top()->val);
                moveHigher();
            }
            else{
                ret.push_back(lo.top()->val);
                moveLower();
            }
        }
        return ret;
    }
    // pushing the root to closest TreeNode path onto a stack
    void initStacks(TreeNode* root, TreeNode* closest){
        while (root){
            hi.push(root);
            lo.push(root);
            if (root == closest){
                return;
            }
            if (root->val < closest->val){
                root = root->right;
            }
            else{
                root = root->left;
            }
        }
    }
    
    TreeNode* findTarget(TreeNode* root, double target){
        TreeNode* closest = root;
        while (root){
            if (abs(closest->val - target) > abs(root->val - target)){
                closest = root;   
            }
            if (root->val > target){
                root = root->left;
            }
            else{
                root = root->right;
            }
        }
        return closest;
    }
    // move to larger elements using hi stack
    void moveHigher(){
        TreeNode* t = hi.top();
        if (t->right){
            t = t->right;
            while (t){
                hi.push(t);
                t = t->left;    
            }
        }
        else{
           while (!hi.empty() && hi.top()->val <= t->val){
               hi.pop();
           } 
        }
    }
    // move to lower elements using lo stack
    void moveLower(){
        TreeNode* t = lo.top();
        if (t->left){
            t = t->left;
            while (t){
                lo.push(t);
                t = t->right;    
            }
        }
        else{
           while (!lo.empty() && lo.top()->val >= t->val){
               lo.pop();
           }
        }
    }
};