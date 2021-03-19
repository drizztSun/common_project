/*
 958. Check Completeness of a Binary Tree

 # Given a binary tree, determine if it is a complete binary tree.

 # Definition of a complete binary tree from Wikipedia:
 # In a complete binary tree every level, except possibly the last, is completely filled,
 # and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.


 # Example 1:

 # Input: [1,2,3,4,5,6]
 # Output: true
 # Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.

 # Example 2:

 # Input: [1,2,3,4,5,null,7]
 # Output: false
 # Explanation: The node with value 7 isn't as far left as possible.

 # Note:

 # The tree will have between 1 and 100 nodes.
 
 */

#include <vector>
#include <queue>

using std::queue;
using std::vector;

class IsCompleteTree {

    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    /*
        954.Check-Completeness-of-a-Binary-Tree
        解法1：
        查验是否一棵完全二叉树，有一个固定的技巧。我们将所有的节点按照从高到低，从左往右的顺序依次编号。例如第0层的编号是0，那么第一层的两个节点编号是1,2,那么第二层的四个节点（如果存在的话）编号就是3,4,5,6.其特点是: left index = parent index * 2 +1,right index = parent index * 2 +2.

        如果一棵完全二叉树按照上述规则编号的话，理论上等同于严格按照层级顺序来遍历所有节点，那么得到的节点编号是顺序的且是满枝的，并且不会超过总结点数。而其他任何非完全二叉树，按照上述规则编号，则必然会导致有某个节点的编号大于了总节点数目。

        解法2：
        有一个更直观易懂的方法。一棵完全二叉树最大的特点就是，如果我们做层级遍历，那么在遇到最后一个节点之前，所有的节点都是非空的。

        因此我们可以用队列做一个层级的遍历，也就是说，每遇到一个节点就将其左右子节点（即使子节点是空）加入队列中。
        层级遍历的特点就是从上到下，从左到右，因此当遇到队列中的队首元素是NULL的时候，那么意味着它应该就是整棵树最后的节点，队列中剩下的所有的节点必须都是NULL。这就是完全二叉树的充要条件。
    */
public:
    bool isCompleteTree(TreeNode* root) 
    {
        int nodeNums = countNodes(root);
        return DFS(root,0,nodeNums);
    }
    
    bool DFS(TreeNode* node, int index, int nodeNums)
    {
        if (!node) return true;
        if (index>=nodeNums) return false;
        return DFS(node->left,index*2+1,nodeNums)&&DFS(node->right,index*2+2,nodeNums);
    }
    
    int countNodes(TreeNode* node)
    {
        if (!node) return 0;
        else return 1+countNodes(node->left)+countNodes(node->right);
    }

public:
    bool isCompleteTree(TreeNode* root) 
    {
        queue<TreeNode*>q;
        q.push(root);
        while (q.front()!=NULL)
        {            
            q.push(q.front()->left);            
            q.push(q.front()->right);
            q.pop();
        }
        while (!q.empty())
        {
            if (q.front()!=NULL) return false;
            q.pop();
        }
        return true;   
    }

    bool doit1(TreeNode *root) {
        
        bool pre = true;
        queue<TreeNode*> nq;
        nq.push(root);
        
        while(!nq.empty()){
            TreeNode* node = nq.front();
            nq.pop();
            
            if(node == NULL){
                pre = false;
            }
            else{
                if(pre == false) return false;
                nq.push(node->left);
                nq.push(node->right);
            }
        }
        
        return true;
    }

public:
    
    // TLE, overflow, because 2 * v could be very big
    bool doit(TreeNode* root) {
        
        vector<std::pair<TreeNode*, int>> buf;
        buf.push_back({root, 1});
        int i = 0;
        
        while (i < buf.size()) {
            
            TreeNode *n = buf[i].first;
            int v = buf[i].second;
            i += 1;
            
            if (n) {
                buf.push_back({n->left, 2 * v});
                buf.push_back({n->right, 2 * v + 1});
            }
        }
        
        return buf.size() == buf.back().second;
    }
    
    // DFS
    bool isCompleteTree(TreeNode*& root, int i, int n) {
        
        if (!root)  return true;
        else if (i >= n) return false;
        return isCompleteTree(root->left, 2 * i + 1, n) && isCompleteTree(root->right, 2 * i + 2, n);
    }
    
    int countNodes(TreeNode*& root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    bool doit2(TreeNode* root) {
        
        return isCompleteTree( root, 0, countNodes(root));
    }
};