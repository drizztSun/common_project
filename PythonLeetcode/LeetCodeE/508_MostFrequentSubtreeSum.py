# 508. Most Frequent Subtree Sum

# Given the root of a tree, you are asked to find the most frequent subtree sum. 
# The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself).
# So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

# Examples 1
# Input:

#   5
#  /  \
# 2   -3
# return [2, -3, 4], since all the values happen only once, return all of them in any order.


# Examples 2
# Input:

#   5
#  /  \
# 2   -5
# return [2], since 2 happens twice, however -5 only occur once.
# Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class FrequentTreeSum(object):

    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if not root:
            return []

        from collections import Counter, defaultdict
        def search(node, record):

            left = search(node.left, record) if node.left else 0
            right = search(node.right, record) if node.right else 0

            record[left + right + node.val] += 1

            return left + right + node.val
        
        cnt = Counter()
        search(root, cnt)
        group = defaultdict(list)
        maxv = -float('inf')

        for c in cnt.keys():
            group[cnt[c]].append(c)
            maxv = max(maxv, cnt[c])                        
            
        return group[maxv]


    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if not root:
            return []
        def dfs(node):
            if not node:
                return 0
            res=dfs(node.left)+dfs(node.right)+node.val
            if res in counts:
                counts[res]+=1
            else:
                counts[res]=1
            return res

        counts={}
        dfs(root)
        ans=[]
        max_count=0

        for i,v in counts.items():

            if v>max_count:
                max_count=v
                ans=[i]

            elif v==max_count:
                ans.append(i)

        return ans


if __name__ == "__main__":

    root = TreeNode(5)
    root.left = TreeNode(2)
    root.right = TreeNode(-5)

    res = FrequentTreeSum().doit(root)


    root = TreeNode(5)
    root.left = TreeNode(2)
    root.right = TreeNode(-3)

    res = FrequentTreeSum().doit(root)

    pass


