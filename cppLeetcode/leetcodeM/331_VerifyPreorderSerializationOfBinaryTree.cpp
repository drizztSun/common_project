/*
331. Verify Preorder Serialization of a Binary Tree

One way to serialize a binary tree is to use preorder traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as '#'.


For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.

Given a string of comma-separated values preorder, return true if it is a correct preorder traversal serialization of a binary tree.

It is guaranteed that each comma-separated value in the string must be either an integer or a character '#' representing null pointer.

You may assume that the input format is always valid.

For example, it could never contain two consecutive commas, such as "1,,3".
 

Example 1:

Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
Example 2:

Input: preorder = "1,#"
Output: false
Example 3:

Input: preorder = "9,#,#,1"
Output: false
 

Constraints:

1 <= preorder.length <= 104
preoder consist of integers in the range [0, 100] and '#' separated by commas ','.
 

Follow up: Find an algorithm without reconstructing the tree.

*/
#include <vector>
#include <string>

using std::vector;
using std::string;


class isValidSerialization {

    /*
        331.Verify-Preorder-Serialization-of-a-Binary-Tree
        此题用到了这么一个性质：对于满二叉树，所有节点的入度和出度之差为0.

        关于入度和出度，我们知道，根节点的净值是-2（两个出度），非叶子节点的净值是-1（一个入度两个出度），叶子节点的净值是1（一个入度零个出度）。在对先序遍历的过程中，我们只能区分叶子和非叶子节点，但是无法再细分是否是根节点。
        不过因为根节点只有一个，所以我们如果把根节点也当做一般的非叶子节点来处理的话，遍历所有节点之后的总净值应该是1。也就是说，如果我们按先序遍历所有节点，遇到非#节点就减一，遇到#节点就加一，最终的结果必须是1。

        此外还有另外一个判定条件。在先序遍历的过程中，总有一些子二叉树是没有被完全遍历完的，也就是说，对于这些子二叉树，已经遍历的非叶子节点总比已经遍历的叶子节点多。所以按照上述的规则，遍历的过程中(不包括最后一个节点)，总净值不能大于0。
        注意，一旦把最后一个节点遍历完毕，根据上一个结论，总净值必须是1。
    */
    bool isValidSerialization(string preorder) 
    {

        int count=0;
        for (int i=0; i<preorder.size(); i++)
        {
            if (preorder[i]!=',' && preorder[i]!='#')
            {
                while (i<preorder.size() && preorder[i]!=',')
                    i++;
                count--;
            }
            else if (preorder[i]=='#')
            {
                count++;
                i++;
            }
            
            if (i<preorder.size()-1 && count>0) return false;
        }
        
        if (count!=1) return false;
        return true;
    }


public:

    /*
        Approach 1: Iteration
        Intuition

        Let's start from the simplest but not optimal solution to discuss the idea.

        Binary tree could be considered as a number of slots to fulfill. At the start there is just one slot available for a number or null node. Both number and null node take one slot to be placed. 
        For the null node the story ends up here, whereas the number will add into the tree two slots for the child nodes. Each child node could be, again, a number or a null.

        The idea is straightforward : take the nodes one by one from preorder traversal, and compute the number of available slots. 
        If at the end all available slots are used up, the preorder traversal represents the valid serialization.

        In the beginning there is one available slot.

        Each number or null consumes one slot.

        Null node adds no slots, whereas each number adds two slots for the child nodes.

        fig

        Algorithm

        Initiate the number of available slots: slots = 1.

        Split preorder traversal by comma, and iterate over the resulting array. At each step :

        Both a number or a null node take one slot : slots = slot - 1.

        If the number of available slots is negative, the preorder traversal is invalid, return False.

        Non-empty node node != '#' creates two more available slots: slots = slots + 2.

        Preorder traversal is valid if all available slots are used up : return slots == 0.

        Implementation


        Complexity Analysis

        Time complexity : O(N) to iterate over the string of length N.

        Space complexity : O(N) to keep split array in memory.
    */
    
    bool doit_(string preorder) {
        
        // number of available slots
        int slots = 1;

        int i = 0;
        preorder.push_back(',');
        vector<string> nodes;
        while (i < preorder.size()) {
            int j = preorder.find(',', i);
            nodes.push_back(preorder.substr(i, j-i));
            i = j+1;
        }

        for(auto node : nodes) {
            // one node takes one slot
            --slots;

            // no more slots available
            if (slots < 0) return false;

            // non-empty node creates two children slots
            if (!(node == "#")) slots += 2;
        }

        // all slots should be used up
        return slots == 0;
    }

    bool doit_(string preorder) {
        // number of available slots
        int slots = 1;

        int n = preorder.length();
        for(int i = 0; i < n; ++i) {
            if (preorder[i] == ',') {
                // one node takes one slot
                --slots;

                // no more slots available
                if (slots < 0) return false;

                // non-empty node creates two children slots
                if (preorder[i-1] != '#') slots += 2;
            }
        }

        // the last node
        slots = (preorder[n-1] == '#') ? slots - 1 : slots + 1;
        // all slots should be used up
        return slots == 0;
    }
};