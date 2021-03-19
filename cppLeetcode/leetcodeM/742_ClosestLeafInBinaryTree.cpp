/*
742. Closest Leaf in a Binary Tree

Given a binary tree where every node has a unique value, and a target key k, find the value of the nearest leaf node to target k in the tree.

Here, nearest to a leaf means the least number of edges travelled on the binary tree to reach any leaf of the tree. Also, a node is called a leaf if it has no children.

In the following examples, the input tree is represented in flattened form row by row. The actual root tree given will be a TreeNode object.

Example 1:

Input:
root = [1, 3, 2], k = 1
Diagram of binary tree:
          1
         / \
        3   2

Output: 2 (or 3)

Explanation: Either 2 or 3 is the nearest leaf node to the target of 1.
Example 2:

Input:
root = [1], k = 1
Output: 1

Explanation: The nearest leaf node is the root node itself.
Example 3:

Input:
root = [1,2,3,4,null,null,null,5,null,6], k = 2
Diagram of binary tree:
             1
            / \
           2   3
          /
         4
        /
       5
      /
     6

Output: 3
Explanation: The leaf node with value 3 (and not the leaf node with value 6) is nearest to the node with value 2.
Note:
root represents a binary tree with at least 1 node and at most 1000 nodes.
Every node has a unique node.val in range [1, 1000].
There exists some node in the given binary tree for which node.val == k.
*/

#include <functional>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class ClosestLeaf {


    /*
        742.Closest-Leaf-in-a-Binary-Tree
        一般解决关于二叉树的问题，90%都可以用DFS解决。此题也不例外，但需要仔细考虑设计。

        首先要明确，从节点k到最近叶子节点的路径，有两种可能：第一种只有一种情况，即从k节点本身开始直接往下走之外；第二种就是可能先向上走，然后经过一个拐点，再从另一端的子树往下。所以这个“拐点”就和路径就是一一对应的关系。我们的目的就是考察所有的节点，找出以其为拐点、“从节点k到最近叶子节点”的路径的最短长度，

        对于节点node，我们首先要知道node到节点k之间的距离，这需要一个递归函数 DFS_find_k。如果节点k在node的左子树，那么我们就要考虑沿着node的右子树往下、到达叶子节点的最短路径，这又需要一个递归函数 DFS_find_closest_leaf. 于是 DFS_find_k(node->left)+2+DFS_find_closest_leaf(node->right) 就是整条路径的长度。反之，如果节点k在node的右子树，那么 DFS_find_closest_leaf(node->right)+2+DFS_find_k(node->left) 就是整条路径的长度。注意，两个长度只可能有一个有效。

        从上可知，我们可以提前做一次整棵树的DFS_find_closest_leaf搜索，记录下所有节点对应的 Dist_to_Leaf[node]，顺带把ClosetLeaf[node]也记录下来，因为结果需要输出的是这个叶子节点的val。然后再过一遍DFS_find_k，对于经过的每一个节点，我们都可以算出如上所述的路径长度。然后再在全局变量中取最小。

        注意：慎用INT_MAX，因为在你不知情的情况下很可能会对INT_MAX做了运算，而INT_MAX+1反而成了最小值。
    */
    unordered_map<TreeNode*,int>Dist2Leaf;
    unordered_map<TreeNode*,int>ClosestLeaf;
    int dist=INT_MAX;
    int result;
public:
    int findClosestLeaf(TreeNode* root, int k) 
    {
        int temp;
        temp = DFS_find_closest_leaf(root);
        temp = DFS_find_k(root,k);
        return result;
    }
    
    int DFS_find_closest_leaf(TreeNode* root)
    {
        if (root==NULL) 
            return INT_MAX;
        
        if (root->left==NULL && root->right==NULL)
        {
            Dist2Leaf[root]=0;
            ClosestLeaf[root]=root->val;
            return 0;
        }
        
        int L=DFS_find_closest_leaf(root->left);
        int R=DFS_find_closest_leaf(root->right);
        
        if (L>R)
        {
            Dist2Leaf[root]=R+1;
            ClosestLeaf[root]=ClosestLeaf[root->right];            
        }
        else
        {
            Dist2Leaf[root]=L+1;
            ClosestLeaf[root]=ClosestLeaf[root->left];            
        }        
        
        return Dist2Leaf[root];
    }
    
    int DFS_find_k(TreeNode* root, int k)
    {
        if (root==NULL) 
            return -1;
        
        if (root->val==k)
        {
            if (dist > Dist2Leaf[root])
            {
                dist = Dist2Leaf[root];
                result = ClosestLeaf[root];
            }
            return 0;
        }
        
        int L=DFS_find_k(root->left,k);
        if (L!=-1)
        {
            if (root->right!=NULL && dist > L+2+Dist2Leaf[root->right])
            {
                dist = L+2+Dist2Leaf[root->right];
                result = ClosestLeaf[root->right];                    
            }
            return L+1;
        }
        
        int R=DFS_find_k(root->right,k);
        if (R!=-1)
        {
            if (root->left!=NULL && dist > R+2+Dist2Leaf[root->left])
            {
                dist = L+2+Dist2Leaf[root->left];
                result = ClosestLeaf[root->left];                    
            }
            return R+1;
        }
        
        return -1;
    }
public:

    int doit_(TreeNode* root, int k) {

        vector<int> paths;
        TreeNode *target = NULL;

        std::function<bool(TreeNode*)> findpath = [&](TreeNode* p) -> bool {
            if (!p) return false;

            paths.push_back(p->val);

            if (p->val == k) {
                target = p;
                return true;
            }

            if (findpath(p->left) || findpath(p->right)) return true;

            paths.pop_back();
            return false;
        };

        findpath(root);

        if (!target->left && !target->right) return target->val;
        
        unordered_map<int, int> buf;
        for (int i = paths.size()-1; i >= 0; i--) 
            buf[paths[i]] = paths.size() - i - 1;
        
        int ans = INT_MAX, minlen = INT_MAX;

        std::function<std::pair<int, int>(TreeNode*)> search = [&](TreeNode* p) -> std::pair<int, int> {

            if (!p->left && !p->right) return {1, p->val};

            int ret = INT_MAX, val = p->val;
            if (p->left) {
                auto it = search(p->left);
                if (it.first < ret) {
                    ret = it.first, val = it.second;
                }
                if (buf.count(p->val) && minlen > ret + buf[p->val]) {
                    minlen = ret + buf[p->val];   
                    ans = val;
                }
            }

            if (p->right) {
                auto it = search(p->right);
                if (it.first < ret) {
                    ret = it.first, val = it.second;
                }
                if (buf.count(p->val) && minlen > ret + buf[p->val]) {
                    minlen = ret + buf[p->val];    
                    ans = val;
                }
            }

            return {ret+1, val};
        };    

        search(root);
        return ans;
    }
};