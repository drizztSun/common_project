/*

297. Serialize and Deserialize Binary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

 

Example 1:


Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
Example 2:

Input: root = []
Output: []
Example 3:

Input: root = [1]
Output: [1]
Example 4:

Input: root = [1,2]
Output: [1,2]
 

Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000

*/
#include <string>
#include <queue>
#include <vector>

using std::vector;
using std::queue;
using std::string;


    /*
        297.Serialize-and-Deserialize-Binary-Tree
        解法1：

        编码
        本题按照leetcode介绍的编码方式。

        构建队列，按照BFS逐层遍历二叉树，遇到非NULL节点就记录数值，遇到NULL就记录'#'，每个节点之间用','分开。遍历到队首的非NULL节点，其两个子节点都会加入队列；对于队首的NULL节点，则跳过不加入元素。

        整个编码过程和BFS遍历过程没有太大区别。

        解码
        解码的时候，先将整个编码字符串根据,分隔,构建一个指针数组，每个数组元素对应一个节点指针，这和编码过程中的队列类似。

        设置初始指针i=0表示当前父节点,j=1表示当前子节点。

        对于父节点q[i],对应的两个子节点必为q[j]和q[j+1]，此时只要将q[i]的left和right分别指向它们(即j和j+1)即完成了父子关系的构建． 注意此时如果q[i]为空,根据编码原则说明q里面并没有子节点被记录，故继续i++直到找到非NULL的节点，作为j和j+1的父节点。

        技巧：

        把数字转化为字符串 to_string(num) 会自动处理负号
        把字符串转化为数字 stoi(str) 也会自动处理负号

        解法2：
        
        编码可以用preorder遍历的方法递归得到，代码非常简洁：

            string serialize(TreeNode* root) 
            {
                if (root==NULL) return "#";
                return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);        
            }
        得到的一定是唯一的序列字符串。

        解码的时候首先将各个节点通过逗号的间隔抽取出来。重建的时候也是要设计递归。

            TreeNode* DFS(vector<string>&q, int a)
            {
                if (q[a]=="#") return NULL;
                TreeNode* root = new TreeNode(stoi(q[a]));
                TreeNode* left = DFS(q,a+1);
                int leftSize = getSize(left);
                TreeNode* right = DFS(q,a+1+leftSize);        
                root->left = left;
                root->right = right;
                return root;
            }
        需要额外一个getSize函数来计算这个子树共有多少个元素。或者在DFS的返回值里添加一个信息，表示该子树下的节点总数。

        解法3：

        在解法2的基础上，有一个技巧可以避免额外调用getSize. 我们将所有节点都放入一个队列之中。每次的DFS其实都是从该队列中弹出首元素作为子树的根；然后构建左子树；再构建右子树。
        当我们试图构建右子树的时候，其实队列中的首元素就已经是右子树的根了。
    */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Codec {



public:

 // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        queue<TreeNode*>q;
        q.push(root);
        string ret;
        while (!q.empty())
        {
            TreeNode* node = q.front();
            q.pop();
            if (node!=NULL)
            {
                ret+=std::to_string(node->val)+",";
                q.push(node->left);
                q.push(node->right);
            }
            else
                ret+="#,";
        }
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        vector<TreeNode*>nodes;
        for (int i=0; i<data.size(); i++)
        {
            int j = i;
            while (j<data.size() && data[j]!=',')
                j++;
            string str = data.substr(i,j-i);
            if (str=="#")
                nodes.push_back(NULL);
            else
                nodes.push_back(new TreeNode(stoi(str)));
            i = j;
        }

        int i = 0,  j = 1;
        while (j<nodes.size())
        {
            if (nodes[i]!=NULL)
            {
                nodes[i]->left = nodes[j];
                nodes[i]->right = nodes[j+1];
                j+=2;
            }
            i++;
        }
        return nodes[0];
    }
};

class Codec2 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        if (root==NULL) return "#";
        else return std::to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        vector<TreeNode*>nodes;
        for (int i=0; i<data.size(); i++)
        {
            int j = i;
            while (j<data.size() && data[j]!=',')
                j++;
            string str = data.substr(i,j-i);
            if (str=="#")
                nodes.push_back(NULL);
            else
                nodes.push_back(new TreeNode(stoi(str)));
            i = j;
        }

        return DFS(nodes, 0);
    }

    TreeNode* DFS(vector<TreeNode*>&nodes, int cur)
    {
        if (nodes[cur]==NULL) return NULL;

        TreeNode* left = DFS(nodes, cur+1);
        int leftSize = getNum(left);
        TreeNode* right = DFS(nodes, cur+leftSize+1);
        nodes[cur] -> left = left;
        nodes[cur] -> right = right;
        return nodes[cur];
    }

    int getNum(TreeNode* node)
    {
        if (node==NULL) return 1;
        else return getNum(node->left)+getNum(node->right)+1;
    }
};


class Codec3 {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) 
    {
        if (root==NULL) return "#";
        return to_string(root->val)+","+serialize(root->left)+","+serialize(root->right);        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) 
    {
        queue<string>q;
        for (int i=0; i<data.size(); i++)
        {
            int j=i;
            while (j<data.size() && data[j]!=',')
                j++;
            q.push(data.substr(i,j-i));
            i=j;
        }
        return DFS(q);
    }
    
    TreeNode* DFS(queue<string>&q)
    {
        string cur = q.front();
        q.pop();
        
        if (cur=="#") return NULL;
        TreeNode* root = new TreeNode(stoi(cur));
        
        TreeNode* left = DFS(q);        
        TreeNode* right = DFS(q);
        root->left = left;
        root->right = right;
        return root;
    }
};