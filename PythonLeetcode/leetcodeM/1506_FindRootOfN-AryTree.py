"""
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
"""


"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children if children is not None else []
"""

class RootOfNAry:

    """
        Algorithm

        Given the above intuition, there are several ways to implement the idea.

        Here we give one approach which has a space complexity of \mathcal{O}(N)O(N) (where NN is the length of the input list).

        We can use a Hashset (named as seen) to keep track of all the child nodes that we visit, then at the end the root would not be in this set. We could find out the root node with two iterations as follows:

        As the first iteration, we traverse the elements in the input list. For each element, we put its child nodes into the hashset seen. Since the value of each node is unique, we could either put the node itself or simply its value into the hashset.

        Then, we visit the list once again. This time, we have all the child nodes in the hashset. Once we come across any node that is NOT in the hashset, then this is the root node that we are looking for.


        Complexity Analysis

        Let NN be the length of the input list, which is also the number of nodes in the N-ary tree.

        Time Complexity: \mathcal{O}(N)O(N)

        In the first iteration, we visit each node as well as its child nodes. For the non-root node, it would be visited twice exactly. While for the root node, it would be visited exactly once. Therefore, the time complexity for this part is \mathcal{O}(N + N - 1) = \mathcal{O}(N)O(N+N−1)=O(N).

        As to the second iteration, in the worst case, we would run through the entire list to find the root node. Hence the time complexity for this part is \mathcal{O}(N)O(N).

        To sum up, the overall time complexity of the algorithm is \mathcal{O}(N) + \mathcal{O}(N) = \mathcal{O}(N)O(N)+O(N)=O(N).

        Space Complexity: \mathcal{O}(N)O(N)

        We used a hashset to keep track of all the child nodes. Therefore, the number of elements contained in the set would be (N-1)(N−1) exactly.

        As a result, the space complexity of the algorithm is \mathcal{O}(N)O(N).
    """
    def doit_(self, tree: list) -> 'Node':
        # set that contains all the child nodes.
        seen = set()

        # add all the child nodes into the set
        for node in tree:
            for child in node.children:
                # we could either add the value or the node itself.
                seen.add(child.val)

        # find the node that is not in the child node set.
        for node in tree:
            if node.val not in seen:
                return node

    """
        The rational is that the values of non-root nodes are cancelled out during the above addition and deduction operations, i.e. the value of a non-root node is added once as a parent node but deducted as a child node.

        For this idea to work, an important condition is that the values of all nodes are unique, as specified in the problem.

        Still, we could find the root node with two iterations:

        In the first iteration, we traverse each node in the list, we add the value of the node to the value_sum. Moreover, we deduct the value of its child nodes from the value_sum.

        At the end of the first iteration, the value_sum would become the value of the root node, as we discussed before.

        Once we know the value of the root node, i.e. value_sum, we can run a second iteration on the list to find out the root node.

        Here are some sample implementations which are inspired from the post of Anonymouso in the discussion forum.


        Here are two characteristics about the XOR operator:

        A XOR A = 0
        0 XOR A = A
        As one can see, these characteristics can serve as the same cancelling-out effect as the addition and deduction operations.

        Given a list of [ABA] where the root node is B, we can perform an accumulated XOR operation on each element to obtain the value of root node, i.e. A XOR B XOR A = B.

        Complexity Analysis

        Let NN be the length of the input list, which is also the number of nodes in the N-ary tree.

        Time Complexity: \mathcal{O}(N)O(N)

        In the first iteration, we visit each node as well as its child nodes. Therefore, the time complexity for this part is \mathcal{O}(2 * N) = \mathcal{O}(N)O(2∗N)=O(N).

        As to the second iteration, in the worst case, we would run through the entire list to find the root node. Hence the time complexity for this part is \mathcal{O}(N)O(N).

        To sum up, the overall time complexity of the algorithm is \mathcal{O}(N) + \mathcal{O}(N) = \mathcal{O}(N)O(N)+O(N)=O(N).

        Space Complexity: \mathcal{O}(1)O(1)

        We used a variable (value_sum) which is of constant-space, regardless of the input.
    """

    def doit_(self, tree: list) -> 'Node':
        
        value_sum = 0

        for node in tree:
            # the value is added as a parent node
            value_sum ^= node.val
            for child in node.children:
                # the value is deducted as a child node.
                value_sum ^= child.val

        # the value of the root node is `value_sum`
        for node in tree:
            if node.val == value_sum:
                return node
                
    

                