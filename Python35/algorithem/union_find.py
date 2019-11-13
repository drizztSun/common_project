
# disjoint_set
# union-find

def find(a):
    if a.parent != a:
        a.parent = find(a.parent)
    return a.parent


def union(a, b):
    a_parent, b_parent = find(a), find(b)
    if a_parent != b_parent:
        a.parent = b


def test_union_find():

    pass


if __name__ == '__main__':
    
    test_union_find()
