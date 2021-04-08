/*
572. Subtree of Another Tree

Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. 
A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
 

Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.

*/
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class SubtreeOfAnotherTree {


    using ll = long long;


    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        572.Subtree-of-Another-Tree
        解法1： 递归
        判断s是否含有子树是t，先考虑s是否本身就是t：如果是的话直接返回true，如果不是的话就需要考察 isSubtree(s->left,t)||isSubtree(s->right,t)，注意相应的前提是左右子树非NULL。

        对于判断两个数是否相等的函数 isSameTree(s,t)，就很好写了。

        解法2： KMP
        我们将每棵树按照先序遍历转化为数组S和T，就可以映射为一个unique的序列。注意，对于任何的叶子节点，序列里也要包含它的两个空叶子（可以设计为INT_MAX）.

        于是这道题就变成了在序列S里找一段和T一样的window。这就可以用到KMP算法。尽管这里的“目标串”和“模式串”都是数组而不是字符串，但并不妨碍KMP算法的实现：依旧是先计算模式串的自相关后缀数组，再计算S和T之间的互相关后缀数组。

        解法3： UID
        参考652.Find-Duplicate-Subtrees的解法。先对s树的所有子树进行编号(包括key和ID），在已有的key2Id数据库的基础上，再对t树的所有子树用同样的法则进行编号。如果t树根节点的编号在数据库里出现了2次或以上，那么就说明t树必然在s树里出现过（因为t树里面不可能出现两个结构相同的、以t为根节点子树）。
    */
    
    // 解法1： 递归
    bool isSubtree(TreeNode* s, TreeNode* t) 
    {
        if (s==NULL||t==NULL)
            return (s==t);
        if (isSame(s,t))
            return true;
        else
            return isSubtree(s->left,t) || isSubtree(s->right,t);
    }
    
    bool isSame(TreeNode* a, TreeNode* b)
    {
        if (a==NULL || b==NULL) return a==b;
        if (a->val!=b->val) return false;
        return isSame(a->left,b->left) && isSame(a->right,b->right);
    }
    // -- end --- //

    // 解法2： KMP
    bool isSubtree(TreeNode* s, TreeNode* t) 
    {
        vector<int>S, T;
        convert(s, S);
        convert(t, T);
        vector<int>suf = preprocess(T);
        int n = S.size();
        vector<int>dp(n,0);
        dp[0] = (T[0]==S[0]);
        for (int i=1; i<n; i++)
        {
            int j = dp[i-1];
            while (j>0 && T[j]!=S[i])
                j = suf[j-1];
            dp[i] = j+(T[j]==S[i]);
            if (dp[i] == T.size())
                return true;
        }
        return false;
    }

    void convert(TreeNode* node, vector<int>&arr)
    {
        if (node==NULL)
        {
            arr.push_back(INT_MAX);
            return;
        }
        arr.push_back(node->val);
        convert(node->left, arr);
        convert(node->right, arr);
    }

    vector<int> preprocess(vector<int>& P)
    {
        int n = P.size();
        vector<int>dp(n,0);
        for (int i=1; i<n; i++)
        {
            int j = dp[i-1];
            while (j>0 && P[j]!=P[i])
                j = dp[j-1];
            dp[i] = j+(P[j]==P[i]);
        }
        return dp;
    }

public:

    // 解法3： UID
    unordered_map<ll, int>key2Id;
    unordered_map<ll, int>key2Count;
    unordered_map<ll, int>Id2key;

    bool isSubtree(TreeNode* s, TreeNode* t) 
    {
        getId(s);
        int ID = getId(t);
        for (auto x: key2Id)
        {
            if (x.second==ID)
                return key2Count[x.first] > 1;
        }
        return false;
    }
    
    ll getId(TreeNode* node)
    {
        if (node==NULL) return 0;        
        ll key = (getId(node->left)<<32) + (getId(node->right)<<16) + node->val;        
        key2Count[key]+=1;
        if (key2Id.find(key)==key2Id.end())
        {
            key2Id[key] = key2Id.size()+1;                        
        }        
        return key2Id[key];
    }

public:

    bool doit_KMP(TreeNode* s, TreeNode* t) {

        vector<int> S, T;
        convert(s, S);
        convert(t, T);

        vector<int> pattern(T.size(), 0);
        int j = 0;
        for (int i = 1; i < T.size(); i++) {
            int j = pattern[i-1];
            while (j > 0 && T[j] != T[i]) {
                j = pattern[j-1];
            }
            pattern[i] = j + (T[i] == T[j]);
        }

        int j = 0;
        for (int i = 0; i < S.size(); i++) {

            while (j > 0 && S[i] != T[j]) {
                j = pattern[j-1];
            }

            if (S[i] == T[j])
                j++;

            if (j == T.size())
                return true;
        }

        return false;
    }
};