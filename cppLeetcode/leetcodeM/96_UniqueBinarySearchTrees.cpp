/*
96. Unique Binary Search Trees

Given an integer n, return the number of structurally unique BST's (binary search trees) which has exactly n nodes of unique values from 1 to n.

 

Example 1:


Input: n = 3
Output: 5
Example 2:

Input: n = 1
Output: 1
 

Constraints:

1 <= n <= 19
*/
#include <vector>
#include <functional>

using std::vector;


class UniqueBST {

public:

    /*
        Approach 1: Dynamic Programming
        Intuition

        The problem can be solved in a dynamic programming way.

        Given a sorted sequence 1 ... n, to construct a Binary Search Tree (BST) out of the sequence, we could enumerate each number i in the sequence, and use the number as the root, then, 
        the subsequence 1 ... (i-1) on its left side would lay on the left branch of the root, and similarly the right subsequence (i+1) ... n lay on the right branch of the root. 
        
        We then can construct the subtree from the subsequence recursively. Through the above approach, we could be assured that the BST that we construct are all unique, since they start from unique roots.

        As we can see, the problem can be reduced into problems with smaller sizes, instead of recursively (also repeatedly) solve the subproblems, we can store the solution of subproblems and reuse them later, i.e. the dynamic programming way.
    */
    int doit_dp(int n) {
        
        vector<int> dp(n+1, -1);
        dp[0] = 1, dp[1] = 1;
        
        std::function<int(int)> dfs = [&](int t) {
        
            if (dp[t] != -1) return dp[t];
            
            int ans = 0;
            for (int i = 0; i < t; i++)
                ans += dfs(i) * dfs(t-i-1);
            dp[t] = ans; 
            return ans;
        };
        
        return dfs(n);
        
    }

    /*
        Approach 2: Mathematical Deduction
        Intuition

        Actually, as it turns out, the sequence of G(n)G(n) function results is known as Catalan number C_nC 
        n
        ​	
        . And one of the more convenient forms for calculation is defined as follows:

        C_0 = 1, \qquad C_{n+1} = \frac{2(2n+1)}{n+2}C_n \qquad \qquad (4)C 
        0
        ​	
        =1,C 
        n+1
        ​	
        = 
        n+2
        2(2n+1)
        ​	
        C 
        n
        ​	
        (4)

        We skip the proof here, which one can find following the above reference.

        Algorithm

        Given the formula (3), it becomes rather easy to calculate G_nG 
        n
        ​	
        which is actually C_nC 
        n
        ​	
        . Here are some examples:
        Complexity Analysis

        Time complexity : O(N), as one can see, there is one single loop in the algorithm.
        Space complexity : O(1), we use only one variable to store all the intermediate results and the final one.
    */
    int doit_math(int n) {
     
        long C = 1;
        
        for (int i = 0; i < n; i++) {
            C = C * 2 * (2 * i + 1) / (i + 2);
        }
        
        return C;
    }

};

/*
95. Unique Binary Search Trees II

Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly n nodes of unique values from 1 to n. Return the answer in any order.

 

Example 1:


Input: n = 3
Output: [[1,null,2,null,3],[1,null,3,2],[2,1,3],[3,1,null,null,2],[3,2,null,1]]
Example 2:

Input: n = 1
Output: [[1]]
*/

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
class UniqueBSTII {

    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        095.Unique-Binary-Search-Trees-II
        这道题如何构造DFS函数很有讲究。函数的参数应该是start和end，输出应该是一系列由start到end元素构成的BST。注意这样的BST不止一个，除了根节点可以在start~end之间任意选择外，左子树和右子树在下一轮递归中也会有很多解。
        所以在当前的返回值应该要穷举出所有这样的BST。

        考虑这样构造DFS函数

        vector<TreeNode*> generateTreesDFS(int start, int end)
        遍历每个可能的root(从start到end)，然后确定了左子树、右子树包含的元素。递归调用DFS分别生成一系列左子树和右子树。

        重点来了！然后对每一个根节点，需要所有的左子树、右子树都两两配对，构成一个完整的树。所以对每一个左右子树组合，都要不断实例化这个根节点，然后加入到结果数组中。

                    for (int i=start; i<=end; i++)
                    {
                        vector<TreeNode*> leftSubTree = generateTreesDFS(start, i - 1);
                        vector<TreeNode*> rightSubTree = generateTreesDFS(i + 1, end);             
                    
                        for (int j = 0; j < leftSubTree.size(); ++j) 
                            for (int k = 0; k < rightSubTree.size(); ++k) 
                            {
                                TreeNode *node = new TreeNode(i);
                                node->left = leftSubTree[j];
                                node->right = rightSubTree[k];
                                subTree.push_back(node);
                            }
                    }             
        另外需要注意的细节： 如果start>end，需要返回的是一个包含NULL的vector<TreeNode*>，而不是空数组。否则之后的二重循环就可能无法展开。
    */
    vector<TreeNode*> generateTrees(int n) 
    {
        if (n == 0) return {};
        return generateTreesDFS(1,n);
    }
    
    vector<TreeNode*> generateTreesDFS(int start, int end) 
    {
        vector<TreeNode*> subTree;
        
        if (start>end)
        {
            subTree.push_back(NULL);
        }
        else
        {
            for (int i=start; i<=end; i++)
            {
                vector<TreeNode*> leftSubTree = generateTreesDFS(start, i - 1);
                vector<TreeNode*> rightSubTree = generateTreesDFS(i + 1, end);
                
            
                for (int j = 0; j < leftSubTree.size(); ++j) 
                    for (int k = 0; k < rightSubTree.size(); ++k) 
                    {
                        TreeNode *node = new TreeNode(i);
                        node->left = (leftSubTree)[j];
                        node->right = (rightSubTree)[k];
                        subTree.push_back(node);
                    }
            }
        }
        
        return subTree;
    }

public:

    vector<TreeNode*> generateTrees(int n) {
        
        std::function<vector<TreeNode*>(int, int)> dfs = [&](int l, int r) -> vector<TreeNode*> {

            if (l > r) return vector<TreeNode*>{};

            if (l == r) return vector<TreeNode*>{new TreeNode(l)};

            vector<TreeNode*> ans;

            for (int i = l; i <= r; i++) {

                if (i == l) {
                    vector<TreeNode*> right = dfs(i+1, r);
                    for (auto c: right)
                        ans.push_back(new TreeNode(l, nullptr, c));
                } else if (i == r) {
                    vector<TreeNode*> left = dfs(l, r-1);
                    for (auto c: left)
                        ans.push_back(new TreeNode(r, c, nullptr));
                } else {
                    vector<TreeNode*> left = dfs(l, i-1);
                    vector<TreeNode*> right = dfs(i+1, r);
                    for (auto lc : left)
                        for (auto rc: right)
                            ans.push_back(new TreeNode(i, lc, rc));
                }
            }

            return ans;
        };

        return dfs(1, n);
    }
};

