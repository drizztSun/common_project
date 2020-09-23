class Treenode:
    def __init__(self, data):
        self._data = data
        self._left = None
        self._right = None


def maketree():
    s = Treenode(6)
    s._left = Treenode(3)
    s._right = Treenode(8)
    s._right._right = Treenode(9)
    s._left._right = Treenode(4)
    s._left._left = Treenode(1)

    return s


def preorder_travel(a):  # return [...]
    if a is None:
        return []

    if a._left is None and a._right is None:
        return [a._data]

    return [a._data] + preorder_travel(a._left) + preorder_travel(a._right)


def inorder_travel(a):
    if a == None:
        return []

    if a._left == None and a._right == None:
        return [a._data]

    return inorder_travel(a._left) + [a._data] + inorder_travel(a._right)


def postorder_travel(a):
    if a == None:
        return []

    if a._left == None and a._right == None:
        return [a._data]

    return postorder_travel(a._left) + postorder_travel(a._right) + [a._data]


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

if __name__ == "__main__":
    maketree()
    a = preorder_travel(maketree())
    print(a)
    v = preorder_travel_no_recr(maketree())
    print(v)