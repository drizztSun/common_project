class Treenode:
    def __init__(self, data):
        self.val = data
        self.left = None
        self.right = None


def maketree():
    s = Treenode(6)
    s.left = Treenode(3)
    s.right = Treenode(8)
    s.right.right = Treenode(9)
    s.left.right = Treenode(4)
    s.left.left = Treenode(1)

    return s


def preorder_travel(a):  # return [...]
    if a is None:
        return []

    if a.left is None and a.right is None:
        return [a.val]

    return [a.val] + preorder_travel(a.left) + preorder_travel(a.right)


def inorder_travel(a):
    if a == None:
        return []

    if a.left == None and a.right == None:
        return [a.val]

    return inorder_travel(a.left) + [a.val] + inorder_travel(a.right)


def postorder_travel(a):
    if a == None:
        return []

    if a.left == None and a.right == None:
        return [a.val]

    return postorder_travel(a.left) + postorder_travel(a.right) + [a.val]


def preorder_travel_no_recr(root):
    res = []
    right_buffer = []

    while right_buffer or root:
        if not root:
            root = right_buffer.pop()

        res.append(root.val)
        if root.right:
            right_buffer.append(root.right)
        root = root.left
    return res


def inorder_travel_(self, root):

    res = []
    buff = []

    while root or buff:
        if not root:
            root = buff.pop()
            res.append(root.val)
            root = root._right
        else:
            buff.append(root)
            root = root._left
    return res


def inorder_travel_2(self, root):
    """
    :type root: TreeNode
    :rtype: List[int]
    """
    cur, buff, res = root, [], []

    while cur:

        if cur.left:
            buff.append(cur)
            cur = cur.left
        else:
            res.append(cur.val)
            while not cur.right and buff:
                cur = buff.pop()
                res.append(cur.val)

            cur = cur.right
            
    return res


def postorderTraversal(self, root):
    """
    :type root: TreeNode
    :rtype: List[int]
    """
    cur, buff, res = root, [], []

    while cur or buff:
        while cur:
            res = [cur.val] + res
            buff.append(cur.left)
            cur = cur.right

        cur = buff.pop()
    return res

def maxval(root):
    if not root:
        return 0
    max_left = maxval(root.left)
    max_right = maxval(root.right)
    return max(root.val, max_left, max_right)

if __name__ == "__main__":
    maketree()
    a = preorder_travel(maketree())
    print(a)
    v = preorder_travel_no_recr(maketree())
    print(v)
    res = maxval(maketree())
    print(res)