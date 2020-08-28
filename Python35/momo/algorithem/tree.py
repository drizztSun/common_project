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
    a, b, c,  = root, [], []
    while a :
        if a.left:
            b.append(a)
            a = a._left
        else:
            c.append(a.val)
            while not a.right and b:
                cur = b.pop()
                c.append(cur.val)

            cur = cur.right
                
    return c
        
        
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


def post_order_travel_1(self, root):
        stack, current, result = [], root, []
        while current or stack:
            if not current:
                current = stack.pop()
            result.append(current.val)
            if current.right:
                stack.append(current.right)
            current = current.left
        return result

def post1(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        stack, current, result = [], root, []
        while current or stack:

            if not current:
                current = stack.pop()

            result.append(current.val)

            if current.right:
                stack.append(current.right)

            current = current.left

        return result

def post_order_2(self, a):
    b, c = [a], []
    while b:
        n= b.pop()
        if n:
            c.append(n.val)
            b.append(n.right)
            b.append(n.left)
            return c

def post2(self, root):
    """
    :type root: TreeNode
    :rtype: List[int]
    """
    stack, res = [root], []

    while stack:
        n = stack.pop()
        if n :
            res.append(n.val)

            stack.append(n.right)
            stack.append(n.left)

    return res            
                


if __name__ == "__main__":
    maketree()
    a = preorder_travel(maketree())
    print(a)
    v = preorder_travel_no_recr(maketree())
    print(v)