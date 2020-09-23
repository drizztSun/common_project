from collections import Counter


def test_counter():

    # build
    a = Counter()
    b = Counter("aaabbbcccdddeeffg")
    c = Counter([1, 2, 3, 4, 'a', 'b', 'c'])

    print(b, c)

    if 'j' not in b:
        print('j does not exist in b')
    if b.get('j') is None:
        print('same as above')

    # functions

    a = Counter(a=10, b=3, f=2)
    print(list(a.elements()))

    print(Counter('aaabbbcccdef').most_common(3))

    b = Counter(a=20, b=10, c=5)
    c = Counter(a=10, b=5, c=2)
    b.subtract(c)
    print(b)

    d = Counter(a=1, b=2, c=3, d=4)
    print(sum(d.values()))

    d.clear()
    print(d)

    # convert
    e = Counter(a=5, b=6, c=8, d=10)
    print(list(e))
    print(tuple(e))
    print(dict(e))
    print(set(e))
    print(e.values())

    # create
    print(Counter(dict(a=1, b=1, c=2)))

    # operations
    f = Counter()
    return


if __name__ == "__main__":
    test_counter()
