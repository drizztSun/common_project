
class Treenode:
    def __init__(self, data):
        self._data = data
        self._left = None
        self._right = None 



def maketree():
    s = Treenode(6)
    s._left =  Treenode(3)
    s._right = Treenode(8)
    s._right._right = Treenode(9)
    s._left._right = Treenode(4)
    s._left._left = Treenode(1)

    return s

def preorder_travel(a): # return [...]
    if a == None:
        return []

    if a._left == None and a._right == None :       
        return [a._data]

    return [a._data] + preorder_travel(a._left) + preorder_travel(a._right) 

def inorder_travel(a):
    if a == None:
        return []

    if a._left == None and a._right == None :       
        return [a._data]

    return preorder_travel(a._left) + [a._data] + preorder_travel(a._right) 

def postorder_travel(a):
    if a == None:
        return []

    if a._left == None and a._right == None :       
        return [a._data]

    return  preorder_travel(a._left) + preorder_travel(a._right) + [a._data]


if __name__ == "__main__":
    maketree()
    a = preorder_travel(maketree())
    print(a)