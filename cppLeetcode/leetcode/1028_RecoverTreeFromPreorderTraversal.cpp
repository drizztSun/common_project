/*
 # 1028. Recover a Tree From Preorder Traversal

 # We run a preorder depth first search on the root of a binary tree.

 # At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

 # If a node has only one child, that child is guaranteed to be the left child.

 # Given the output S of this traversal, recover the tree and return its root.


 # Example 1:

 # Input: "1-2--3--4-5--6--7"
 # Output: [1,2,5,3,4,6,7]

 # Example 2:

 # Input: "1-2--3---4-5--6---7"
 # Output: [1,2,5,3,null,6,null,4,null,7]

 # Example 3:
 # Input: "1-401--349---90--88"
 # Output: [1,401,null,349,88,90]

 # Definition for a binary tree node.
 */

#include <string>
#include <unordered_map>
#include <vector>

using std::vector;
using std::string;
using std::unordered_map;



class RecoverFromPreorder {
    
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} 
    };

    /*
        1028.Recover-a-Tree-From-Preorder-Traversal
        我们知道，用树的先序遍历可以唯一地重构出这棵树来。这在297.Serialize and Deserialize Binary Tree中曾经提到过。但在那道题里面，先序遍历的序列化需要包括所有的空节点。在本题所给出的先序遍历里，并没有指明空节点，但是提供了另一个信息：每个节点的深度。那我们可以利用这个条件来实现相似的重构。

        首先我们先预处理一下字符串，使得其变成一个节点数组nodes，每个节点元素包含了value和depth两个信息。

        我们设计递归函数DFS(cur)，表示构造以nodes[cur]为根的子树。先序遍历的最大特点是，任何子树序列的第一个元素cur一定是该子树的root。然后，通常情况下，第二个元素cur+1就是左子树的根。但是也有可能root的左节点是空，这样的话第二元素就不是左子树的根（因为空节点不会计入序列）。那么如何判断呢？就看它们的深度信息就可以了：

        TreeNode* root = new TreeNode(nodes[cur].value);
        if (nodes[cur].depth+1 == nodes[cur+1].depth)
        root->left = DFS(cur+1);
        那么如何知道root的右节点在什么位置呢？只要查看一下左子树有多大即可，假设是leftNum这么多：

        if (nodes[cur].depth+1 == nodes[cur+leftNum+1].depth)
        root->right = DFS(cur+leftNum+1);
        怎么知道左子树的大小leftNum是多少呢？可以再把左子树扫一遍。不过这样的时间复杂度就是o(N^2)了。比较高效的算法就是在构造左子树的时候，顺便把左子树的大小给算出来。所以我们设计TreeNode* DFS(int cur, int& num)，其中num返回的是以cur为根的子树的大小。显然有

        num = leftNum+rightNum+1;
        其中leftNum和rightNum又都是继续递归的产物。

        那么递归算法的边界条件是什么？其实不用特地写边界条件。当遍历到叶子节点的时候，两个if语句的条件就保证递归不下去了。
    */
    vector<std::pair<int,int>>nodes;
public:
    TreeNode* recoverFromPreorder(string S) 
    {        
        for (int i=0; i<S.size(); i++)
        {
            int j = i;
            while (j<S.size() && S[j]=='-')
                j++;
            int depth = j-i;
            i = j;
            while (j<S.size() && isdigit(S[j]))
                j++;
            int val = stoi(S.substr(i, j-i));
            nodes.push_back({val, std::max(0,depth)});
            i = j-1;
        }
        int num = 0;
        return DFS(0, num);
    }

    TreeNode* DFS(int cur, int& num)
    {
        TreeNode* root = new TreeNode(nodes[cur].first);
        int leftNum = 0, rightNum = 0;
        if (cur+1 < nodes.size() && nodes[cur+1].second == nodes[cur].second+1)
        {
            TreeNode* left = DFS(cur+1, leftNum);
            root->left = left;
        }        
        if (cur+leftNum+1 < nodes.size() && nodes[cur+leftNum+1].second == nodes[cur].second+1)
        {
            TreeNode* right = DFS(cur+leftNum+1, rightNum);
            root->right = right;
        }
        num = leftNum+rightNum+1;
        return root;
    }
    
public:
    
    TreeNode* doit(string S) {
    
        unordered_map<int, vector<TreeNode*>> buf;
        
        int i = 0;
        
        while (i < S.length()) {
            
            int j = i;
            while (j < S.length() && S[j] == '-') {
                j++;
            }
            
            int depth = j - i;
            i = j;
            
            int c = 0;
            while (j < S.length() && S[i] >= '0' && S[i] <= '9') {
                c = c * 10 + (S[i] - '0');
                i++;
            }
            
            TreeNode* n = new TreeNode(c);
            
            if (buf.count(depth -1) > 0)
                if (buf[depth-1].back()->left == nullptr) {
                    buf[depth-1].back()->left = n;
                }
                else {
                    buf[depth-1].back()->right = n;
                }
            buf[depth].push_back(n);
        }
        
        return buf[0].front();
    }
};