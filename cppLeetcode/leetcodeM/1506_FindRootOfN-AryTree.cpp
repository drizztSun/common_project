/*
1506. Find Root of N-Ary Tree


You are given all the nodes of an N-ary tree as an array of Node objects, where each node has a unique value.

Return the root of the N-ary tree.

Custom testing:

An N-ary tree can be serialized as represented in its level order traversal where each group of children is separated by the null value (see examples).



For example, the above tree is serialized as [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14].

The testing will be done in the following way:

The input data should be provided as a serialization of the tree.
The driver code will construct the tree from the serialized input data and put each Node object into an array in an arbitrary order.
The driver code will pass the array to findRoot, and your function should find and return the root Node object in the array.
The driver code will take the returned Node object and serialize it. If the serialized value and the input data are the same, the test passes.
 

Example 1:



Input: tree = [1,null,3,2,4,null,5,6]
Output: [1,null,3,2,4,null,5,6]
Explanation: The tree from the input data is shown above.
The driver code creates the tree and gives findRoot the Node objects in an arbitrary order.
For example, the passed array could be [Node(5),Node(4),Node(3),Node(6),Node(2),Node(1)] or [Node(2),Node(6),Node(1),Node(3),Node(5),Node(4)].
The findRoot function should return the root Node(1), and the driver code will serialize it and compare with the input data.
The input data and serialized Node(1) are the same, so the test passes.
Example 2:



Input: tree = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
Output: [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 

Constraints:

The total number of nodes is between [1, 5 * 104].
Each node has a unique value.
 

Follow up:

Could you solve this problem in constant space complexity with a linear time algorithm?
*/

/*
// Definition for a Node.
    class Node {
    public:
        int val;
        vector<Node*> children;
        Node() {}
        Node(int _val) {
            val = _val;
        }
        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
    };
*/
#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;


class Solution {
    

    /*
        1506.Find-Root-of-N-Ary-Tree
        解法1：
        我们从每个节点的子节点开始递归访问所有后续节点并做标记。最终唯一没有被标记访问过的，就是根节点。

        解法2
        我们把数组里的每个节点和每个节点的所有子节点都访问一次，我们会发现只有根节点被访问了一次，其余的节点都访问了两次（作为数组的节点元素访问一次，作为子节点访问一次）。

        显然，我们只要在上述的遍历过程中，把所有的val都亦或起来，得到的就是根节点的val值。再扫一遍就可以根据val把根节点挑出来。
    */


    unordered_set<Node*>Set;

    class Node {
    public:
        int val;
        vector<Node*> children;
        Node() {}
        Node(int _val) {
            val = _val;
        }
        Node(int _val, vector<Node*> _children) {
            val = _val;
            children = _children;
        }
    };

public:

    Node* doit_(vector<Node*> tree) 
    {
        int n = tree.size();
        for (auto node: tree)
        {
            if (Set.find(node)!=Set.end())
                continue;
            for (auto child: node->children)
                dfs(child);
        }
        for (auto node: tree)
        {
            if (Set.find(node)==Set.end())
                return node;
        }
        return NULL;
    }
    
    void dfs(Node* node)
    {
        if (Set.find(node)!=Set.end())
            return;
        Set.insert(node);
        for (auto child: node->children)
            dfs(child);
    }

    Node * doit_hashtable(vector<Node*> tree) {
        
        unordered_set<int> seen;

        for (Node* c : tree) {
            for (auto child : c->children) {
                seen.insert(child->val);
            }
        }

        for (auto c: tree)
            if (seen.count(c->val) == 0)
                return c;
        
        return nullptr;
    } 


    Node* doit_bit(vector<Node*> tree) 
    {
        int ret = 0;
        for (auto cur: tree)
        {
            ret ^= cur->val;
            for (auto next: cur->children)
                ret ^= next->val;
        }
        
        for (auto cur: tree)
        {
            if (cur->val == ret)
                return cur;
        }
        
        return NULL;
        
    }
};