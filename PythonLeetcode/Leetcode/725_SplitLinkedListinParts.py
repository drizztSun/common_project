# 725. Split Linked List in Parts

# Given a (singly) linked list with head node root, write a function to split the linked list into k consecutive linked list "parts".

# The length of each part should be as equal as possible: no two parts should have a size differing by more than 1. This may lead to some parts being null.

# The parts should be in order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal parts occurring later.

# Return a List of ListNode's representing the linked list parts that are formed.

# Examples 1->2->3->4, k = 5 // 5 equal parts [ [1], [2], [3], [4], null ]
# Example 1:
# Input: 
# root = [1, 2, 3], k = 5
# Output: [[1],[2],[3],[],[]]
# Explanation:
# The input and each element of the output are ListNodes, not arrays.
# For example, the input root has root.val = 1, root.next.val = 2, \root.next.next.val = 3, and root.next.next.next = null.
# The first element output[0] has output[0].val = 1, output[0].next = null.
# The last element output[4] is null, but it's string representation as a ListNode is [].
# Example 2:
# Input: 
# root = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], k = 3
# Output: [[1, 2, 3, 4], [5, 6, 7], [8, 9, 10]]
# Explanation:
# The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class SplitListToParts:

    def doit(self, root: 'ListNode', k: 'int') -> 'List[ListNode]':

        total, node = 0, root
        while node:
            total += 1
            node = node.next

        nums = [total // k] * k
        for i in range(total % k):
            nums[i] += 1

        node, ans, i, prevNode = root, [root], 0, None
        
        while node:
            
            if nums[i] == 0:
                prevNode.next = None
                ans.append(node)
                i += 1
            
            nums[i] -= 1
            prevNode = node
            node = node.next
        
        if i != k:
            ans.extend([None] * (k - i - 1))

        return ans

    def not_the_answer(self, root: 'ListNode', k: 'int') -> 'List[ListNode]':

        int2linker = map()
        node = root
        
        while node:
            
            if root.val - 1 not in int2linker:
                int2linker[root.val] = int2linker.get(root.val, []).append((node, node))
            else:
                tmp = int2linker[root.val-1].pop()
                tmp[1].next = node
                tmp[1] = node
                int2linker[root.val] = int2linker.get(root.val, []).append(tmp)

            node = node.next

        ans = []
        for value in int2linker.values():
            for c in value: 
                ans.append(c[0])

        return ans       


if __name__ == "__main__":

    res = SplitListToParts().doit()
