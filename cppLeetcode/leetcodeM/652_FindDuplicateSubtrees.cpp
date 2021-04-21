/*
652. Find Duplicate Subtrees


Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

 

Example 1:


Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
Example 2:


Input: root = [2,1,1]
Output: [[1]]
Example 3:


Input: root = [2,2,2,3,null,3,null]
Output: [[2,3],[3]]
 

Constraints:

The number of the nodes in the tree will be in the range [1, 10^4]
-200 <= Node.val <= 200

*/
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <queue>

using std::queue;
using std::string;
using std::unordered_map;
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



 
class FindDuplicateSubtrees {

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /*
        652.Find-Duplicate-Subtrees
        解法1
        结合LeetCode 449，任何一颗二叉树都可以序列化成一个带有唯一特征的字符串。我们dfs整棵树，对于每个节点都作为子树进行序列化，利用序列化的字符串作为key创建Hash表，归类所有key相同的子树。

        解法2
        此题有o(N)的巧妙解法。

        任意两棵子树结构相同的充要条件是：node->val相同、左子树结构相同、右子树结构相同。我们将所有结构相同的子树都用同一个ID来表示，
        那么任意两棵子树结构相同的充要条件变成：node->val相同、左子树ID相同、右子树ID相同。这三个条件又可以序列化成为一个key，于是对于两棵子树（节点），相同的key <=> 相同的三个条件 <=> 相同的子树 <=> 相同的ID。

        对于一棵子树，它的key = node->val + getId(node->left) + getId(node->right). 
        同时我们再利用一个映射key2Id将高维的key转化为一个整数ID：如果已经出现过这个key，返回已经对应的ID，否则就生成一个新ID。最终getId(node)返回的就是key2Id[key]，这会返回给上一级供node的父节点用来生成父节点的ID。

        根据key的出现次数统计key2Count.如果对于某个节点，发现key2Count[key]==2，就在答案中记录该节点。
    */
    unordered_map<string,vector<TreeNode*>>Map;

    using ll = long long;

public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) 
    {
        DFS(root);
        vector<TreeNode*>results;
        for (auto a:Map)
        {
            if (a.second.size()>1)
                results.push_back(a.second[0]);
        }
        return results;        
    }
    
    void DFS(TreeNode* node)
    {
        if (node==NULL)
            return;
        Map[serialize(node)].push_back(node);
        DFS(node->left);
        DFS(node->right);        
    }
    
    string serialize(TreeNode* node)
    {        
        queue<TreeNode*>q;
        q.push(node);
        string result;
        
        while (!q.empty())
        {            
            if (q.front()==NULL)
            {
                q.pop();
                result+="#,";                
            }
            else
            {
                result+=std::to_string(q.front()->val);
                result+=",";
                q.push(q.front()->left);
                q.push(q.front()->right);
                q.pop();                
            }
        }
        return result;
    }

public:

    vector<TreeNode*>rets;
    unordered_map<ll, int>key2Id;
    unordered_map<ll, int>key2count;

    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) 
    {
        getId(root);
        return rets;        
    }
    
    ll getId(TreeNode* node)
    {
        if (node==NULL) return 0;
        
        ll key = (getId(node->left)<<32) + (getId(node->right)<<16) + node->val;
        key2count[key]+=1;
        if (key2count[key]==1)
        {
            key2Id[key] = key2Id.size()+1;
        }
        else if (key2count[key]==2)
        {
            rets.push_back(node);            
        }
        
        return key2Id[key];
    }

public:

    /*
        Approach #1: Depth-First Search [Accepted]
        Intuition

        We can serialize each subtree. For example, the tree

        1
        / \
        2   3
            / \
        4   5
        can be represented as the serialization 1,2,#,#,3,4,#,#,5,#,#, which is a unique representation of the tree.

        Algorithm

        Perform a depth-first search, where the recursive function returns the serialization of the tree. At each node, record the result in a map, and analyze the map after to determine duplicate subtrees.


        Complexity Analysis

        Time Complexity: O(N^2)O(N 
        2
        ), where NN is the number of nodes in the tree. We visit each node once, but each creation of serial may take O(N)O(N) work.

        Space Complexity: O(N^2)O(N 
        2
        ), the size of count.
    */
    
    vector<TreeNode*> doit_(TreeNode* root) {

        unordered_map<string, int> buff;
        vector<TreeNode*> ans;
        std::function<string(TreeNode*)> lookup = [&](TreeNode* node) -> string {

            if (!node) return "";

            string uid = std::to_string(node->val) + "," + lookup(node->left) + "," + lookup(node->right);

            buff[uid]++;
            if (buff[uid] == 2) {
                ans.push_back(node);
            }
            return uid;
        };

        lookup(root);
        return ans;
    }

    /*
        Approach #2: Unique Identifier [Accepted]
        Intuition

        Suppose we have a unique identifier for subtrees: two subtrees are the same if and only if they have the same id.

        Then, for a node with left child id of x and right child id of y, (node.val, x, y) uniquely determines the tree.

        Algorithm

        If we have seen the triple (node.val, x, y) before, we can use the identifier we've remembered. Otherwise, we'll create a new one.

        Complexity Analysis

        Time Complexity: O(N), where NN is the number of nodes in the tree. We visit each node once.
        Space Complexity: O(N). Every structure we use is using O(1)O(1) storage per node.
    */
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        using ll = long long;
        
        unordered_map<ll, int> keyid;
        unordered_map<ll, int> cnt;
        vector<TreeNode*> nodes;
        
        std::function<long long(TreeNode*)> dfs = [&](TreeNode* p) {
            
            if (!p) return 0;
            
            ll key = (dfs(p->left) << 32) + (dfs(p->right) << 16) + p->val;
            
            cnt[key]++; 
            if (cnt[key] == 1) {
                keyid[key] = keyid.size() + 1;
            } else if (cnt[key] == 2) {
                nodes.push_back(p);
            }
            
            return keyid[key];
        }; 
        
        dfs(root);
        
        return nodes;
    }
};