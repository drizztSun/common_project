/*
236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [1,2], p = 1, q = 2
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the tree.


*/
#include <vector>
#include <functional>

using std::vector;


/*
235. Lowest Common Ancestor of a Binary Search Tree

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
Output: 6
Explanation: The LCA of nodes 2 and 8 is 6.
Example 2:


Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
Output: 2
Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
Example 3:

Input: root = [2,1], p = 2, q = 1
Output: 2
 

Constraints:

The number of nodes in the tree is in the range [2, 105].
-109 <= Node.val <= 109
All Node.val are unique.
p != q
p and q will exist in the BST.
*/
class LowestCommonAncestor {
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

public:
    TreeNode* doit_recursive(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        if (p->val > q->val) std::swap(p, q);
     
        std::function<TreeNode* (TreeNode*)> search = [&](TreeNode* node) -> TreeNode* {
            
            if (!node) return nullptr;
            
            if (node->val >= p->val && node->val <= q->val)
                return node;
            
            if (node->val < p->val)
                return search(node->right);
            
            else if (node->val > q->val)
                return search(node->left);
            else
                return nullptr;
        };
  
        return search(root);
    }

    TreeNode* doit_itertate(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        int smaller = std::min(p->val, q->val), bigger = std::max(p->val, q->val);
        
        while (root) {
          
            if (root->val >= smaller && root->val <= bigger) 
                break;
            else if (root->val < smaller) 
                root = root->right;
            else if (root->val > bigger)
                root = root->left;
        };
        
        return root;
    }
};



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class LowestCommonAncestor {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    /*
        
        235.Lowest-Common-Ancestor-of-a-Binary-Search-Tree
        从根节点开始考察，如果p,q都比root小，则root移动至其左子树；否则，root移动至其右子树。直到发现p,q在root节点的两侧，则root是最低共同节点。

        236.Lowest Common Ancestor of a Binary Tree
        解法1：找到各自完全的路径
        和235不同，没有任何线索提示这两个节点的位置关系。所以只好用DFS搜索出抵达这两个节点的路径。通过路径的比较，找出共同的一段path，即可得出最低的公共节点。

        DFS函数会一路向下层搜索直到发现节点p，然后在返回的过程中将路径所经过的所有节点存在数组P中。

            bool DFS(TreeNode* node, TreeNode* p, vector<TreeNode*>&P)
            {
                if (node==NULL)
                    return false;        
                
                if (node==p || DFS(node->left, p, P) || DFS(node->right, p, P))
                {
                    P.push_back(node);
                    return true;
                }
                else
                    return false;
                
            }
        得到数组P和Q之后，只要从后往前比较两个数组，追踪它们相同的路径截止到哪一位为止就行了。

        解法2：递归调用
        因为p,q保证是在这棵树里面，所以我们可以这样定义lowestCommonAncestor(node,p,q)，返回的是p或者q或者两者的LCA。

        1.如果node是NULL或者p或者q，那么我们就返回node，表示我们定位到了p/q。

        2.分别递归调用left=lowestCommonAncestor(node->left,p,q); right=lowestCommonAncestor(node->right,p,q).如果left和right都非空，那么必然说明一个分支含有p，另一个分支含有q，故node一定就是LCA。
        如果left非空而right为空，说明我们在左边定位到了p或者q或者是p,q的LCA，不管如何，都返回left。同理，如果right非空而left为空，说明我们在右边定位到了p或q或者是pq的LCA。如果两者都为空，那么就自然返回空。    
    */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        vector<TreeNode*>P;
        vector<TreeNode*>Q;
        bool temp;
        temp = DFS(root,p,P);
        temp = DFS(root,q,Q);
        
        TreeNode* result;
        int i=P.size()-1;
        int j=Q.size()-1;
        while (i>=0 && j>=0 && P[i]==Q[j])
        {
            result=P[i];
            i--;
            j--;
        }
        return result;
    }
    
    bool DFS(TreeNode* root, TreeNode* r, vector<TreeNode*>& R)
    {
        if (root==NULL) return false;
        if (root==r || DFS(root->left,r,R) || DFS(root->right,r,R)) 
        {
            R.push_back(root);
            return true;
        }
        else
            return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if (root==NULL || root==p || root==q)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);
        if (left && right)
            return root;
        else if (!left && right)
            return right;
        else if (left && !right)
            return left;
        else
            return NULL;
    }


public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        TreeNode* ans = nullptr;

        std::function<bool(TreeNode*)> search = [&](TreeNode* node) {
            
            if (!node) return false;
            
            bool isTarget = node == p || node == q;
            bool l = search(node->left), r = search(node->right);
            
            if (l && r || ((l || r) && isTarget))
                ans = node;
            
            return l || r || isTarget;
        };
        
        search(root);
        return ans;
    }
};