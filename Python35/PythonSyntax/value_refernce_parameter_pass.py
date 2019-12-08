

def reassign(l):
    print(id(l))
    l = [0, 1]  # change the para(pass-by-ref) to be ref to [0, 1]
    print(id(l))


def append(l):
    print(id(l))
    l.append(2)  # call append on para(pass-by-ref)


def add(a, b):
    print(id(a), id(b))
    return a + b


if __name__ == '__main__':

    # pass-by-value ??? still pass-by-ref
    a, b = 1, 2
    print(id(a), id(b))
    print(add(a, b))  # pass-by-value, a, b int, from stack,

    # pass-by-ref
    l = [0]
    print(id(l))
    reassign(l)  # pass-by-ref
    print(l)

    append(l)  # pass-by-ref
    print(l)

    # Pass-by-object-reference
    # Python is different. As we know, in Python, “Object references are passed by value”.

    # A function receives a reference to (and will access) the same object in memory as used by the caller.
    # However, it does not receive the box that the caller is storing this object in;
    # as in pass-by-value, the function provides its own box and creates a new variable for itself.
    # Let’s try appending again:

    la = [0]
    lb = [0]
    lc = la
    print(id(la), id(lb), id(lc))
    lb.append(1)
    lc.append(2)
    print(la)
    print(lb)
    print(lc)
    print(id(la), id(lb), id(lc))
