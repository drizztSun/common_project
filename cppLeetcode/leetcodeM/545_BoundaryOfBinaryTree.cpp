/*
545. Boundary of Binary Tree

The boundary of a binary tree is the concatenation of the root, the left boundary, the leaves ordered from left-to-right, and the reverse order of the right boundary.

The left boundary is the set of nodes defined by the following:

1. The root node's left child is in the left boundary. If the root does not have a left child, then the left boundary is empty.
2. If a node in the left boundary and has a left child, then the left child is in the left boundary.
3. If a node is in the left boundary, has no left child, but has a right child, then the right child is in the left boundary.

The leftmost leaf is not in the left boundary.
The right boundary is similar to the left boundary, except it is the right side of the root's right subtree. Again, the leaf is not part of the right boundary, and the right boundary is empty if the root does not have a right child.

The leaves are nodes that do not have any children. For this problem, the root is not a leaf.

Given the root of a binary tree, return the values of its boundary.

 

Example 1:


Input: root = [1,null,2,3,4]
Output: [1,3,4,2]
Explanation:
- The left boundary is empty because the root does not have a left child.
- The right boundary follows the path starting from the root's right child 2 -> 4.
  4 is a leaf, so the right boundary is [2].
- The leaves from left to right are [3,4].
Concatenating everything results in [1] + [] + [3,4] + [2] = [1,3,4,2].
Example 2:


Input: root = [1,2,3,4,5,6,null,null,null,7,8,9,10]
Output: [1,2,4,7,8,9,10,6,3]
Explanation:
- The left boundary follows the path starting from the root's left child 2 -> 4.
  4 is a leaf, so the left boundary is [2].
- The right boundary follows the path starting from the root's right child 3 -> 6 -> 10.
  10 is a leaf, so the right boundary is [3,6], and in reverse order is [6,3].
- The leaves from left to right are [4,7,8,9,10].
Concatenating everything results in [1] + [2] + [4,7,8,9,10] + [6,3] = [1,2,4,7,8,9,10,6,3].
 

Constraints:

The number of nodes in the tree is in the range [1, 104].
-1000 <= Node.val <= 1000

*/
#include <vector>
#include <algorithm>
#include <functional>

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
class BoundaryOfBinaryTree {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        545.Boundary-of-Binary-Tree
        需要分别写子函数遍历左边界、底部叶子节点、右边界。

        对于左边界，注意题目要求，当根节点没有左子树时，左边界就只是根。所以，遍历左边界的函数其实可以从root->left开始。同理，遍历右边界的函数可以从root->right开始。左边界、右边界求完后，都要各自pop_back()，为叶子节点数组腾出重复的节点位置。

        另外，遍历底部叶子节点，需要注意仅有根节点的情况，这时不算有叶子节点。

        最终结果就是：根 + 左边界（弹出最后一个）+ 所有叶子节点（不包括根）+ 右边界的反序（弹出最后一个）。
    */
    vector<int> boundaryOfBinaryTree(TreeNode* root) 
    {
        vector<int>results;
        if (root==NULL) return results;
        
        results.push_back(root->val);
        
        vector<int>Left;
        if (root->left!=NULL)
        {
            GoLeft(root->left,Left);
            Left.pop_back();
        }
        
        vector<int>Bottom;
        if (root->left!=NULL || root->right!=NULL)
            GoBottom(root,Bottom);
        
        vector<int>Right;
        if (root->right!=NULL)
        {
            GoRight(root->right,Right);
            Right.pop_back();
        }
        reverse(Right.begin(),Right.end());
        
        for (int i=0; i<Left.size(); i++)
            results.push_back(Left[i]);

        for (int i=0; i<Bottom.size(); i++)
            results.push_back(Bottom[i]);
        
        for (int i=0; i<Right.size(); i++)
            results.push_back(Right[i]);    
        
        return results;
    }
    
    void GoLeft(TreeNode* root, vector<int>& Left)
    {
        if (root==NULL) return;
        
        Left.push_back(root->val);
        if (root->left!=NULL)
            GoLeft(root->left,Left);
        else if (root->right!=NULL)
            GoLeft(root->right,Left);
    }
    
    void GoRight(TreeNode* root, vector<int>& Right)
    {
        if (root==NULL) return;
        
        Right.push_back(root->val);
        if (root->right!=NULL)
            GoRight(root->right,Right);
        else if (root->left!=NULL)
            GoRight(root->left,Right);
    }    
    
    void GoBottom(TreeNode* root, vector<int>& Bottom)
    {
        if (root==NULL) return;
        if (root->left==NULL && root->right==NULL)
        {
            Bottom.push_back(root->val);
        }
        else
        {
            GoBottom(root->left,Bottom);
            GoBottom(root->right,Bottom);
        }
    }


public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {

        if (!root) return {};

        vector<int> ans;

        std::function<void(TreeNode*, bool, bool)> dfs = [&](TreeNode* p, bool edge, bool right) {

            if (!p) return;

            if ((!p->left && !p->right) || edge)
                ans.push_back(p->val);

            if (right) {
                if (p->right)
                    dfs(p->right, edge, right);
                if (p->left)
                    dfs(p->left, edge && !p->right, right);
            } else {
                if (p->left)
                    dfs(p->left, edge, right);
                if (p->right)
                    dfs(p->right, edge && !p->left, right);
            }
        };

        dfs(root->left, true, false);
        int n = ans.size();
        dfs(root->right, true, true);

        std::reverse(begin(ans)+n, end(ans));
        ans.insert(begin(ans), root->val);
        return ans;
    }

    /*
        Approach #2 Using PreOrder Traversal [Accepted]
        Algorithm

        Before we dive into this approach, let's look at the preorder traversal of a simple Binary Tree as shown below:

        Preorder Traversal

        From the above figure, we can observe that our problem statement is very similar to the Preorder traversal. Actually, the order of traversal is the same(except for the right boundary nodes, for which it is the reverse), but we need to selectively include the nodes in the return result list. Thus, we need to include only those nodes in the result, which are either on the left boundary, the leaves or the right boundary.

        In order to distinguish between the various kinds of nodes, we make use of a flagflag as follows:

        Flag=0: Root Node.

        Flag=1: Left Boundary Node.

        Flag=2: Right Boundary Node.

        Flag=3: Others(Middle Node).

        We make use of three lists \text{left\_boundary}left_boundary, \text{right\_boundary}right_boundary, \text{leaves}leaves to store the appropriate nodes and append the three lists at the end.

        We go for the normal preorder traversal, but while calling the recursive function for preorder traversal using the left child or the right child of the current node, we also pass the flagflag information indicating the type of node that the current child behaves like.

        For obtaining the flag information about the left child of the current node, we make use of the function leftChildFlag(node, flag). In the case of a left child, the following cases are possible, as can be verified by looking at the figure above:

        The current node is a left boundary node: In this case, the left child will always be a left boundary node. e.g. relationship between E & J in the above figure.

        The current node is a root node: In this case, the left child will always be a left boundary node. e.g. relationship between A & B in the above figure.

        The current node is a right boundary node: In this case, if the right child of the current node doesn't exist, the left child always acts as the right boundary node. e.g. G & N. But, if the right child exists, the left child always acts as the middle node. e.g. C & F.

        Similarly, for obtaining the flag information about the right child of the current node, we make use of the function rightChildFlag(node, flag). In the case of a right child, the following cases are possible, as can be verified by looking at the figure above:

        The current node is a right boundary node: In this case, the right child will always be a right boundary node. e.g. relationship between C & G in the above figure.

        The current node is a root node: In this case, the right child will always be a left boundary node. e.g. relationship between A & C in the above figure.

        The current node is a left boundary node: In this case, if the left child of the current node doesn't exist, the right child always acts as the left boundary node. e.g. B & E. But, if the left child exists, the left child always acts as the middle node.

        Making use of the above information, we set the flagflag appropriately, which is used to determine the list in which the current node has to be appended.


        Complexity Analysis

        Time complexity : O(n) One complete traversal of the tree is done.

        Space complexity : O(n) The recursive stack can grow upto a depth of nn. Further, \text{left\_boundary}left_boundary, \text{right\_boundary}right_boundary and \text{leaves}leaves combined together can be of size nn.
        */

        

};