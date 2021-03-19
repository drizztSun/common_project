/*
437. Path Sum III


You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

*/

#include <functional>
#include <unordered_map>

using std::unordered_map;


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
class PathSumIII {
    
    /*
        437.Path-Sum-III
        方法1
        此题是112,113的follow up。不要求path一定是从root到leaf。

        在这种情况下，每个节点都有可能是path的起点。所以需要遍历树的所有节点，对每个节点都寻找pathSum(node,sum)。

        另外，(root->val==sum)并不意味着path的终点，如果子树还有和为零的路径，也合题意。所以遇到这种情况，还要进一步加上左右子树路径和为0的子问题。

            int pathSumNum(TreeNode* node, int sum)
            {
                if (node==NULL) return 0;
                if (node->val==sum) return 1+pathSumNum(node->left,0)+pathSumNum(node->right,0);
                return pathSumNum(node->left,sum-node->val)+pathSumNum(node->right,sum-node->val);
            }
        方法2
        突破点:任何一条从A点到B点的,和为sum的路径,可以等效为从root到B的路径和,减去root到A的路径和.

        所以我们考察B点时,将此时从root到B的路径和curSum,减去target,查看这个差值是否存在一个Hash表中.这个Hash表存储的是从root到任何B以前的点的路径和.因此更新结果的计数器只需要count+=Map[curSum-target]

        注意,这个DFS需要回溯.即向下递归时需要想Hash表中添加Map[curSum]+=1,而向上返回时需要删除这个记录即Map[curSum]-=1

        此外,需要注意的边界条件是:在最初始需要设置Map[0]=1,即什么都不拿的话也算target==1的一种方法.上述的DFS依赖于这个边界条件.
    
    */

public:
    int count=0;
   
    int pathSum(TreeNode* root, int sum) 
    {
        GoThrough(root,sum);
        return count;
    }
    
    void GoThrough(TreeNode *root,int sum)
    {
        if (root==NULL) return;
        
        GoThrough(root->left,sum);        
        GoThrough(root->right,sum);
        count+= pathSumNum(root,sum);        
    }
    
    int pathSumNum(TreeNode* node, int sum)
    {
        if (node==NULL) return 0;
        if (node->val==sum) 
            return 1+pathSumNum(node->left,0)+pathSumNum(node->right,0);
        else
            return pathSumNum(node->left,sum-node->val)+pathSumNum(node->right,sum-node->val);
    }

public:
    unordered_map<int,int>Map;
    int count = 0;

    int pathSum(TreeNode* root, int sum) 
    {
        if (root==NULL) return 0;
        Map[0]=1;
        DFS(root,0,sum);
        return count;
    }
    
    void DFS(TreeNode* node, int curSum, int target)
    {
        if (node==NULL) return;
        
        curSum+=node->val;        
        count+= Map[curSum-target];
        
        Map[curSum]+=1;               
        DFS(node->left,curSum,target);
        DFS(node->right,curSum,target);        
        Map[curSum]-=1;
                
        return;                    
    }

public:
    
    int doit_(TreeNode* root, int sum) {

        if (!root) return 0;
        
        unordered_map<int, int> presums;
        presums.emplace(0, 1);
        int ans = 0;
        
        std::function<void(TreeNode*, int)> dfs = [&](TreeNode* p, int total) {

            total += p->val;

            if (presums.count(total-sum) > 0) 
                ans += presums[total-sum];

            presums[total]++;
            
            if (p->left)
                dfs(p->left, total);

            if (p->right)
                dfs(p->right, total);

            presums[total]--;
        };
        
        dfs(root, 0);
        return ans;
    }
};