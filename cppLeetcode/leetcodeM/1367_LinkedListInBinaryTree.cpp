/*
1367. Linked List in Binary Tree

Given a binary tree root and a linked list with head as the first node. 

Return True if all the elements in the linked list starting from the head correspond to some downward path connected in the binary tree otherwise return False.

In this context downward path means a path that starts at some node and goes downwards.

 

Example 1:



Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Explanation: Nodes in blue form a subpath in the binary Tree.  
Example 2:



Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: true
Example 3:

Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
Output: false
Explanation: There is no path in the binary tree that contains all the elements of the linked list from head.
 

Constraints:

The number of nodes in the tree will be in the range [1, 2500].
The number of nodes in the list will be in the range [1, 100].
1 <= Node.val <= 100 for each node in the linked list and binary tree.
*/
#include <vector>
#include <functional>

using std::vector;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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
class ListNode;
class TreeNode;


class LinkedListInBinaryTree {

    /*
    
        1367.Linked-List-in-Binary-Tree
        解法1：递归
        此题的递归解法和572.Subtree-of-Another-Tree一样。对于当前的两个节点，考察isSame(head,root)，如果不成立的话就递归处理isSubPath(head, root->left)||isSubPath(head, root->right)

        解法2：KMP
        对于任意一条从root到leaf的支链，我们都可以看做是一个序列，可以用KMP来高效地搜索head所代表的模式串。不同的支链之间，我们用DFS来切换。

        具体的做法是，定义全局变量dp[i]来表示从root开始的第i个（深度的）树节点，与linked list的“互相关后缀数组”，即dp[i]表示最大的长度k，使得截止第i个树节点的后缀序列，恰好等于链表的前缀序列。
        我们注意到，对于树的不同的支链，如果它们共享一个深度为i的树节点，那么对它们而言，dp[i]都是一样的。对于在不同分支的dp[i]，则彼此互不依赖。所以如果我们采用DFS，对于dp的更新不影响各条支路的搜索结果。

        我们设计dfs(node, i)来计算当前树节点是node、并且深度为i时的dp[i]。根据KMP的算法，我们知道dp[i]仅依赖于dp[i-1]和模式串的后缀数组。如果当前节点计算得到的dp[i]==linkedList.size()，那么返回true；否则探索dfs(node->left, i+1) || dfs(node->right, i+1)
    
    */
    bool isSubPath(ListNode* head, TreeNode* root) 
    {
        if (head == NULL) return true;
        if (root == NULL) return false;

        if (isSame(head, root))
            return true;
        else
            return isSubPath(head,root->left)||isSubPath(head,root->right);
    }

    bool isSame(ListNode* head, TreeNode* root)
    {
        if (head == NULL) return true;
        if (root == NULL) return false;

        if (head->val != root->val)
            return false;
        return isSame(head->next, root->left)||isSame(head->next, root->right);
    }

public:

    vector<int> suf;
    vector<int> list;
    int dp[2500];

    bool isSubPath(ListNode* head, TreeNode* root) 
    {
        suf = preprocess(head);
        return dfs(root, 0);
    }

    bool dfs(TreeNode* node, int i)
    {
        if (node==NULL) return false;
        
        if (i==0) 
        {
            dp[i] = (list[0] == node->val);
        }
        else
        {
            int j = dp[i-1];
            while (j>0 && list[j] != node->val)
                j = suf[j-1];

            dp[i] = j + (list[j] == node->val);
        }
        
        if (dp[i] == list.size()) 
            return true;
        else
            return dfs(node->left, i+1) || dfs(node->right, i+1);
    }

    vector<int> preprocess(ListNode* head)
    {
        while (head!=NULL)
        {
            list.push_back(head->val);
            head = head->next;
        }

        int n = list.size();
        vector<int>dp(n);
        
        for (int i=1; i<n; i++)
        {
            int j = dp[i-1];
            while (j>0 && list[j]!=list[i])
                 j = dp[j-1];
            dp[i] = j+(list[j]==list[i]);
        }

        return dp;
    }

public:

    bool isSubPath(ListNode* head, TreeNode* root) {
        
        vector<int> target;
        while (head) {
            target.push_back(head->val);
            head = head->next;
        }
        
        int k = target.size();
        vector<int> path;
        
        std::function<bool(TreeNode*)> dfs = [&](TreeNode* p) {

            if (path.size() >= k) {
                int i = 0;
                for (auto it1=rbegin(path), it2=rbegin(target); i != k && *it1 == *it2; it1++, it2++) i++;
                
                if (i == k) return true;
            }
            
            if (!p) return false;
            
            path.push_back(p->val);
            bool r = dfs(p->left) || dfs(p->right);
            path.pop_back();
            return r;
        };
        
        return dfs(root);   
    }

    bool isSubPath_KMP(ListNode* head, TreeNode* root) {
        
        vector<int> linkvalues;
        while(head) {
            linkvalues.push_back(head->val);
            head = head->next;
        }
        
        vector<int> pattern(linkvalues.size(), 0);
        for (int i = 1; i < linkvalues.size(); i++) {
            int j = pattern[i-1];
            while (j > 0 && linkvalues[i] != linkvalues[j]) {
                j = pattern[j-1];
            }    
            pattern[i] = j + linkvalues[i] == linkvalues[j];
        }
        
        std::function<bool(TreeNode*, int)> dfs = [&](TreeNode* p, int i) {
            
            if (i == pattern.size()) return true;
            
            if (!p) return false;
            
            if (p->val != linkvalues[i]) {
                
                if (i > 0) {
                    int j = pattern[i-1];
                    while (j > 0 && p->val != linkvalues[j]) {
                        j = pattern[j-1];
                    }
                    i = j + p->val == linkvalues[j];                    
                }

            } else {
                i++;
            }
            
            return dfs(p->left, i) || dfs(p->right, i);
        };
        
        return dfs(root, 0);
    }
};