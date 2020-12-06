"""
1104. Path In Zigzag Labelled Binary Tree

In an infinite binary tree where every node has two children, the nodes are labelled in row order.

In the odd numbered rows (ie., the first, third, fifth,...), the labelling is left to right, while in the even numbered rows (second, fourth, sixth,...), the labelling is right to left.



Given the label of a node in this tree, return the labels in the path from the root of the tree to the node with that label.



Example 1:

Input: label = 14
Output: [1,3,4,14]
Example 2:

Input: label = 26
Output: [1,2,6,10,26]


Constraints:

1 <= label <= 10^6

"""


class PathInZigZagTree:

    def doit_binary(self, label: int) -> list:
        import math
        c = int(math.log2(label))
        ans = [label]

        while c > 0:
            label //= 2
            label = (1 << c) - 1 - label + (1 << (c-1))
            c -= 1
            ans.append(label)

        return ans[::-1]


if __name__ == '__main__':

    PathInZigZagTree().doit_binary(14)

    PathInZigZagTree().doit_binary(26)
