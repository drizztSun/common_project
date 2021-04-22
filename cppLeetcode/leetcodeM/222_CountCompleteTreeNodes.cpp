/*
222. Count Complete Tree Nodes

Given the root of a complete binary tree, return the number of the nodes in the tree.

According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible. 
It can have between 1 and 2h nodes inclusive at the last level h.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: 6
Example 2:

Input: root = []
Output: 0
Example 3:

Input: root = [1]
Output: 1
 

Constraints:

The number of nodes in the tree is in the range [0, 5 * 104].
0 <= Node.val <= 5 * 104
The tree is guaranteed to be complete.



*/
#include <cmath>
#include <functional>
#include <vector>

using std::vector;


class CountCompleteTreeNodes {


    //Definition for a binary tree node.
    struct TreeNode {
        
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };


    /*
        222.Count-Complete-Tree-Nodes
        解法1：二分搜索
        先写一个辅助函数bool hasK(TreeNode* root, int K)，表示判断在一个完全二叉树里面是否存在第k号节点。这里，对于完全二叉树节点的编号规则，是按照层级遍历的顺序（如题目的图例）。
        hasK函数的算法思想是：对于任何编号为K的节点，我们都可以写出它从下往上（直至root）的path（就是将K不断除以2）。然后将这个path逆向，起点变成从root开始从上往下遍历，就可以查看是否能抵达编号为K的节点。

        有了这个辅助函数，我们就可以利用二分搜索的思想，猜测二叉树里面是否存在编号为K的节点。如果存在，那么说明总节点数可以大于等于K；如果不存在，那么说明总节点数一定小于K。不断调整搜索范围直至收敛。

        解法2：
        需要观察得到如下的重要性质：对于一个完全二叉树，root的左子树和右子树里面，必然有一个是满二叉树。

        对于高度为h的满二叉树，其节点个数可以直接计算为2^h-1。所以我们对于root，先判断左右哪一个是满二叉树，然后再递归处理另外一部分就行了。比如 f(root) = 1 + pow(2,h)-1 + f(root->left)，其中h是右子树这棵满二叉树的高度。

        如何判断是否一棵满二叉树呢？只要递归计算它的左深度和有深度，查看两者是否相等就行了。

        这个总算法复杂度是logN*logN。可以这么考虑：每次计算满二叉树的高度需要o(logN)，不停二分递归处理非满二叉树又需要o(logN)次。
    
    */
    int countNodes(TreeNode* root) 
    {
        if (root==NULL) return 0;
        
        int ret = 1;        
        int h1 = findLeftDepth(root->left);
        int h2 = findRightDepth(root->left);
        int h3 = findLeftDepth(root->right);
        int h4 = findRightDepth(root->right);
        
        if (h1==h2)
        {
            ret += pow(2,h1)-1;
            return ret+countNodes(root->right);
        }           
        else 
        {
            ret += pow(2,h3)-1;
            return ret+countNodes(root->left);            
        }            
    }
    
    int findLeftDepth(TreeNode* node)
    {
        int count = 0;
        while (node!=NULL)
        {
            count++;
            node=node->left;
        }        
        return count;
    }
    
    int findRightDepth(TreeNode* node)
    {
        int count = 0;
        while (node!=NULL)
        {
            count++;
            node=node->right;
        }        
        return count;
    }

public:

    int countNodes(TreeNode* root) 
    {
        int h = 0;
        TreeNode* node = root;
        while (node!=NULL)
        {
            h++;
            node = node->left;            
        }
        int low = (1<<(h-1));
        int hi = (1<<h)-1;
        
        while (low<hi)
        {
            int mid = low+(hi-low+1)/2;
            if (hasK(root,mid))
                low = mid;
            else
                hi = mid-1;
        }
        return low;
    }
    
    bool hasK(TreeNode* root, int K)
    {
        vector<int>path;
        while (K>0)
        {
            path.push_back(K);
            K = K/2;
        }
        for (int i=path.size()-1; i>=0; i--)
        {
            if (root==NULL) return false;
            if (i==0) return true;
            if (path[i-1]==path[i]*2)
                root = root->left;
            else
                root = root->right;            
        }
        return true;
    }

public:

    // O(n)
    int doit_search_1(TreeNode* root) {

        std::function<int(TreeNode*)> build = [&](TreeNode* p) {
            if (!p) return 0;

            return build(p->left) + build(p->right) + 1;
        };

        return build(root);
    }

    // O(log(n) ^ 2)
    int doit_binary_search(TreeNode* root) {
        
        if (!root) return 0;
        
        int depth = 0;
        TreeNode *p = root->left;
        while (p) {
            depth++;
            p = p->left;
        }
        
        if (depth == 0) return 1;
        
        int base = std::pow(2, depth) - 1;
        
        auto search = [&](int val, int d, TreeNode* p) {
            
            int left = 0, right = base;
            
            while (d--) {
                int mid = left + (right - left) / 2;
                if (mid >= val) {
                    p = p->left;
                    right = mid;
                } else {
                    p = p->right;
                    left = mid + 1;
                }
            }
            return p != nullptr;
        };
        
        int left = 1, right = base;

        while (left <= right) {
        
            int mid = left + (right - left) / 2;
        
            if (search(mid, depth, root)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return base + left;
    }
};