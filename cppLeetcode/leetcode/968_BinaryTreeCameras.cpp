/*
 968. Binary Tree Cameras
 
 Given a binary tree, we install cameras on the nodes of the tree.

 Each camera at a node can monitor its parent, itself, and its immediate children.

 Calculate the minimum number of cameras needed to monitor all nodes of the tree.

 
 
 
 Approach 1: Dynamic Programming
 Intuition

 Let's try to cover every node, starting from the top of the tree and working down. Every node considered must be covered by a camera at that node or some neighbor.

 Because cameras only care about local state, we can hope to leverage this fact for an efficient solution.
 Specifically, when deciding to place a camera at a node, we might have placed cameras to cover some subset of this node, its left child, and its right child already.

 Algorithm

 Let solve(node) be some information about how many cameras it takes to cover the subtree at this node in various states. There are essentially 3 states:

 [State 0] Strict subtree: All the nodes below this node are covered, but not this node.
 [State 1] Normal subtree: All the nodes below and including this node are covered, but there is no camera here.
 [State 2] Placed camera: All the nodes below and including this node are covered, and there is a camera here (which may cover nodes above this node).
 Once we frame the problem in this way, the answer falls out:

 To cover a strict subtree, the children of this node must be in state 1.
 To cover a normal subtree without placing a camera here, the children of this node must be in states 1 or 2, and at least one of those children must be in state 2.
 To cover the subtree when placing a camera here, the children can be in any state.

 
 
 */

#include <algorithm>
#include <vector>
#include <limits>
#include <functional>

using std::min_element;
using std::vector;


class MinCameraCover {

    //Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    /*
        968.Binary-Tree-Cameras
        本题粗看有点像house robber系列，考虑是否可以用ＤＰ来解，似乎应该设计三个状态：本身没有被cover(0),本身有camera(1)，本身没camera但是被邻近的camera给cover了(2)。
        基本的思路应该是，按照从上往下的顺序，后续节点的状态取决于前面的（若干个）节点状态。但是问题在于，依照从上往下的顺序的话，每个节点只能受父节点或者更高层的节点影响，
        显然是不合适的，因为它应该还应该受平行的兄弟节点的影响，而这个在线性的ＤＰ遍历中没法实现（因为你没法保证在考察这个node之前，它的兄弟node已经被更新过了）。

        于是我们反向考虑，如果从下往上走会怎么样？这样，每个节点的状态可以取决于它的两个子节点。这个方案似乎有戏。为什么呢？假设我们从下往上依次更新，考察node时它的两个子节点的状态是已知的：

        1.如果当前node的两个子节点只要有一个状态是0，那么该node必须设置为状态１，以保证两个子节点都被cover到。相应result++.

        2.如果当前node的两个子节点都是状态２，那么按照从简的原则，当前node就可以不必安排camera，故状态可以设置为0。状态是0了没有被cover怎么办？不用担心，靠后续node的父节点来兜着就行，当前不用操心。

        3.其他情况下，当前node都没有必要设置camera，并且当前node必然已经被某个子节点给cover了，所以我们设置node状态为2.

        有了以上的传递关系，我们再考虑边界条件。边界条件就是叶子节点（最底层）。直觉告诉我们，所有的叶子节点没有必要设置camera，只要把camera放在它的父节点即可，这样肯定不亏（父节点装一个camera可以管两个子节点）。
        事实上，这个贪心法的思想（将最底层节点设置状态为２）是整个递归传递(从下往上更新)的根基。因此只有double check这个贪心的思想是对的，这个算法才是可行的。

        最后需要注意的是，如果根节点最终设置状态为0了（此时程序结束），那么我还需要额外再在root上加一个camera以覆盖root。
    */
    // 0: uncovered
    // 1: with camera
    // 2: covered without camera
    int result;
public:
    int minCameraCover(TreeNode* root) 
    {
        result = 0;
        int temp = DFS(root);
        if (temp==0) result++;
        return result;
    }
    
    int DFS(TreeNode* node)
    {
        if (node==NULL) return 2;
        int left = DFS(node->left);
        int right = DFS(node->right);
        if (left==0 || right==0)
        {
            result++;
            return 1;
        }
        if (left==2 && right==2)
        {
            return 0;
        }
        return 2;
    }
    
    
public:

    int doit_greedy(TreeNode* root) {
        
        std::function<vector<int>(TreeNode*)> dfs = [&](TreeNode* p) -> vector<int>{
          
            if (!p) return {0, 0, INT_MAX/2-1};
            
            auto l = dfs(p->left);
            auto r = dfs(p->right);
            
            // 0 uncovered
            // 1 covered without camera
            // 2 covered with camera
            return {
                l[1] + r[1],
                std::min(l[2] + std::min(r[1], r[2]), r[2] + std::min(l[1], l[2])),
                1 + *std::min_element(begin(l), end(l)) + *std::min_element(begin(r), end(r))
            };
        };
        
        auto res = dfs(root);
        return std::min(res[1], res[2]);
    }
    
    void post_order(TreeNode* root, int &res)
    {
       if(root->left != NULL)
       {
           post_order(root->left,res);
       }
        
       if(root->right != NULL)
       {
           post_order(root->right,res);
       }
        
       if((root->left != NULL && root->left->val == 0) || (root->right != NULL && root->right->val == 0))
       {
           res++;
           root->val = 2;
           if(root->left!=NULL && root->left->val != 2)root->left->val = 1;
           if(root->right!=NULL && root->right->val != 2)root->right->val = 1;
       }
        
       else if((root->left!=NULL && root->left->val == 2) || (root->right!=NULL && root->right->val == 2))
       {
           if(root->val != 2)root->val = 1;
       }
    }
    
    int minCameraCover(TreeNode* root) {
        int res = 0;
        post_order(root,res);
        if(root->val == 0)
            res++;
        
        return res;
    }
};