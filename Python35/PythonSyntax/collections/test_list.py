

def slice():

    a = [0, 1, 2, 3, 4, 5, 6]

    print(a)

    print("a[:] = ", a)

    print("a[1:] = ", a[1:])

    print("a[:5] = ", a[:5])

    print("a[1:5] = ", a[1:5])

    print("a[::2] = ", a[::2])

    print("a[1::2] = ", a[1::2])

    print("a[:5:2] = ", a[:5:2])

    print("a[1:5:2] = ", a[1:5:2])

    print("a[-1:] = ", a[-1:])
    
    print("a[:-1] = ", a[:-1])

    print("a[-5: -1] = ", a[-5:-1])

    print("a[-1:-5] = ", a[-1: -5])


    # reverse sequence
    print("a[::-1] = ", a[::-1])

    print("a[-1 : -5: -1] = ", a[-1:-5:-1])


def main():

    a = [ i for i in range(10)]

    # iter
    for c in a:
        print(c)

    # append
    a.append(10)
    print(a)

    # insert
    a.insert(4, 100)
    print(a)

    # extend
    a.extend([11, 12, 13])
    print(a)

    # index
    print("2 index", a.index(2))

    # pop
    c = a.pop()
    print(a, ' pop out ', c)

    # remove
    a.append(2)
    print("before remove : ", a)
    a.remove(2)
    print("after remove : ", a)

    # count
    a.extend([3, 3, 3])
    print("2 has ", a.count(2))
    print("3 has ", a.count(3))

    # reverse
    a.reverse()
    print("revese : ", a)

    # sort
    a.sort()
    print(a)
    
    a.sort(reverse=True)
    print(a)

    a.sort(key = lambda x : x)
    print(a)

    # copy
    b = a.copy()
    print(a)
    print(b)

    # clear
    a.clear()

if __name__ == "__main__":

    # ['__add__', '__class__', '__contains__', '__delattr__', '__delitem__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', 
    # '__getattribute__', '__getitem__', '__gt__', '__hash__', '__iadd__', '__imul__', '__init__', '__init_subclass__', '__iter__', 
    # '__le__', '__len__', '__lt__', '__mul__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__reversed__', 
    # '__rmul__', '__setattr__', '__setitem__', '__sizeof__', '__str__', '__subclasshook__', 
    # 'append', 'clear', 'copy', 'count', 'extend', 'index', 'insert', 'pop', 'remove', 'reverse', 'sort']

    print(dir(list))

    main()

    slice()