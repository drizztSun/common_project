/*
 
 # 1019. Next Greater Node In Linked List

 # We are given a linked list with head as the first node.  Let's number the nodes in the list: node_1, node_2, node_3, ... etc.

 # Each node may have a next larger value: for node_i, next_larger(node_i) is the node_j.val such that j > i, node_j.val > node_i.val, and j is the smallest possible choice.
 # If such a j does not exist, the next larger value is 0.

 # Return an array of integers answer, where answer[i] = next_larger(node_{i+1}).

 # Note that in the example inputs (not outputs) below, arrays such as [2,1,5] represent the serialization of a linked list with a head node value of 2,
 # second node value of 1, and third node value of 5.


 # Example 1:

 # Input: [2,1,5]
 # Output: [5,5,0]

 # Example 2:

 # Input: [2,7,4,3,5]
 # Output: [7,0,5,5,0]

 # Example 3:

 # Input: [1,7,5,1,9,2,5,1]
 # Output: [7,9,9,9,0,5,0,0]

 
 
 */

#include <vector>
#include <stack>

using std::stack;
using std::vector;



class NextLargerNodes {

    // Definition for singly-linked list.
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    
    /*
        1019.Next-Greater-Node-In-Linked-List
        本题和Next Greater Element并没有本质的区别。我们维护一个单调递减的栈，当如果新元素大于栈顶元素时，栈顶元素退栈，并且可以知道栈顶元素的next greater element就是新元素。

        需要注意的是，ret的结果并不是顺次更新的。所以栈的类型应该设计成pair，需要包括元素的数值和索引，这样方便将结果存入对应的ret[i]中。
    */
    vector<int> nextLargerNodes(ListNode* head) 
    {
        vector<int>ret;
        stack<std::pair<int,int>>Stack;
        ListNode* p = head;
        int i = 0;

        while (p!=NULL)
        {
            while (!Stack.empty() && Stack.top().first < p->val)
            {
                ret[Stack.top().second] = p->val;
                Stack.pop();
            }
            ret.push_back({0});
            Stack.push({p->val, i});
            i++;
            p = p->next;
        }

        return ret;
    }


public:
    
    vector<int> doit(ListNode* head) {
        
        vector<int> ans;
        vector<std::pair<int, int>> buf;
        
        while (head) {
            
            ans.push_back(0);
            
            while (!buf.empty() && buf.back().first < head->val) {
                auto top = buf.back();
                buf.pop_back();
                ans[top.second] = head->val;
            }
            
            buf.push_back({head->val, ans.size() - 1});
            head = head->next;
        }
    
        return ans;
    }
};
