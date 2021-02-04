/*
 
 979. Distribute Coins in Binary Tree
 
 
 Given the root of a binary tree with N nodes, each node in the tree has node.val coins, and there are N coins total.

 In one move, we may choose two adjacent nodes and move one coin from one node to another.
 (The move may be from parent to child, or from child to parent.)

 Return the number of moves required to make every node have exactly one coin.
 
 */

#include <algorithm>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class DistributeCoins {
    
public:
    /*
     Approach 1: Depth First Search
     Intuition

     If the leaf of a tree has 0 coins (an excess of -1 from what it needs), then we should push a coin from its parent onto the leaf. If it has say, 4 coins (an excess of 3), then we should push 3 coins off the leaf. In total, the number of moves from that leaf to or from its parent is excess = Math.abs(num_coins - 1). Afterwards, we never have to consider this leaf again in the rest of our calculation.

     Algorithm

     We can use the above fact to build our answer. Let dfs(node) be the excess number of coins in the subtree at or below this node: namely, the number of coins in the subtree, minus the number of nodes in the subtree. Then, the number of moves we make from this node to and from its children is abs(dfs(node.left)) + abs(dfs(node.right)). After, we have an excess of node.val + dfs(node.left) + dfs(node.right) - 1 coins at this node.

     Complexity Analysis

     Time Complexity: O(N), where NN is the number of nodes in the tree.
     Space Complexity: O(H), where HH is the height of the tree.
     */
    
    int doit(TreeNode* root) {
        
        int ans = 0;
        
        std::function<int(TreeNode*)> search = [&](TreeNode* node) {
          
            if (node == nullptr) return 0;
            
            int left = search(node->left), right = search(node->right);
            
            ans += abs(left) + abs(right);
            
            return left + right + node->val - 1;
        };
        
        search(root);
        
        return ans;
    }
};