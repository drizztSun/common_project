/*
662. Maximum Width of Binary Tree

Given a binary tree, write a function to get the maximum width of the given tree. The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

It is guaranteed that the answer will in the range of 32-bit signed integer.

Example 1:

Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:

Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:

Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:

Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).
 

Constraints:

The given binary tree will have between 1 and 3000 nodes.


*/
#include <queue>
#include <deque>

using std::deque;
using std::queue;

class WidthOfBinaryTree {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    /*
        662.Maximum-Width-of-Binary-Tree
        利用二叉树的这个性质：若一个节点的深度是level，在该层的序号是order，则其左子树的深度是level+1且在该层的序号是order*2，其右子树的深度是level+1且在该层的序号是order*2+1。

        我们可以用BFS的思想，对这棵树做层级遍历。那么每层的的第一个节点和最后一个节点的序号之差就代表了这一层的宽度。数据结构的使用上，deque比queue更方便一些。

        本题需要优化的第一个地方是：随着层级的深入，节点序号的数值也会膨胀，可以想象，当超过128层的时候，序号连long long都无法记录了。优化的方法是：如果某一层只有一个节点的话，我们可以把那个节点看做成根节点，并将其序号reset成为0. 这样它之后层级的节点序号就又变小了，同时也不影响最终结果。    
    */
    int widthOfBinaryTree(TreeNode* root) 
    {
        root->val = 0;
        deque<TreeNode*>q;
        q.push_back(root);
        int ans = 1;

        while (!q.empty())
        {
            int len = q.size();
            ans = std::max(ans, q.back()->val - q.front()->val + 1);

            int flag = (len == 1);

            while (len--)
            {            
                TreeNode* node = q.front();
                q.pop_front();

                if (flag==1) node->val = 0;
                
                if (node->left)
                {
                    node->left->val = node->val*2+1;
                    q.push_back(node->left);
                }
                if (node->right)
                {
                    node->right->val = node->val*2+2;
                    q.push_back(node->right);
                }
            }
        }
        return ans;
    }


public:
    /*
        I solved this problem before, but it looks like there is a new test case and my old solution threw the overflow.

        So, I converted it to BFS so I know the leftmost index of the level, and can compensate by making it "zero" (in other words, substracting left from every pos). It works because we process all nodes in the current level.

        Imagine two "vines" going 10,000 levels deep. A solution without compensation would fail (well, a big integer in Python helps).
    */
    
    int doit_bfs(TreeNode* root) {
        
        queue<std::pair<TreeNode*, long long>> buff;
        buff.push({root, 0});
        int ans = 0;
        
        while (!buff.empty()) {
            
            int size = buff.size();
            int minus = buff.front().second;
            int index = 0;
            
            while (size--) {
                
                auto cur = buff.front();
                buff.pop();
                
                TreeNode* node = cur.first;
                index = cur.second;
                
                if (node->left)
                    buff.push({node->left, 2 * (cur.second - minus)});
                
                if (node->right)
                    buff.push({node->right, 2 * (cur.second - minus) + 1});
            }
            
            ans = std::max(ans, index - minus + 1);
        }
        
        return ans;
    }
};