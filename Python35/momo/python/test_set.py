def test_set():
    set1 = {1, 2, 3, 4, 5}
    print(type(set1))
    print(set1)#could be{1, 2, 3, 4, 5} could be not

    set2 = set([1, 1, 2, 3, 3, 5, 5, 4, 2])
    print(set2)

    set2.add(90)
    print(set2)

    set2.remove(90)
    print(set2)

    try:
        set2.remove('a;djklfs')
    except KeyError:
        print('key error if element not exist, phew, you used try!')
    set2.discard('kaudhflue')#NOTE: **this will not raise error**
    print(set2)

    set3 = set('apple')
    print(set3)

    set4 = set(['apple', 'pear', 'pear', 'peely', 'xbox', 'k', 'k', 'lsudfliudhlficauuhfkiu'])
    print(set4)

    if 'apple' in set4:
        print('apple is in set4')

    if 'hello'not in set4:
        print('hello is not in EARA#3333w98yri8$%328rhcwiuehrki$@%@#cqoyniwjfr(I ment set4)')

    seta = set([1, 2, 3, 4, 5, 6])
    setb = set([1, 3, 8, 9, 0, -5])

    print(seta - setb)#seta.difference(setb)
    print(setb - seta)#setb.difference(seta)
    print(seta & setb)#seta.intersection(setb)
    print(seta | setb)#seta.union(setb)
    print(seta ^ setb)#seta.symmetric_difference(setb)

    set3 = set([1, 2, 3, 4, 5])
    set4 = set([1, 2, 3, 4, 5, 6, 7, 8, 9, 0])

    print(set3.isdisjoint(set4))
    print(set3.issubset(set4))
    print(set4.issuperset(set3))

    set5 = set3.copy()
    print(set5 == set3)

    set3.update(set4)
    print(set3)

    set6 = set([1, 2, 3])
    set7 = set([2, 3, 4])

    set6.intersection_update(set7)#set &= other & ...Update the set, keeping only elements found in it and all others.
    print(set6)


    setc = set([4, 5, 6])
    setd  = set([5, 6, 7])

    setc.difference_update(setd)#set -= other | ... Update the set, removing elements found in others.
    print(setc)

    setx = set([6, 7, 8])
    sety = set([7, 8, 9])

    setx.symmetric_difference_update(sety)#set ^= other Update the set, keeping only elements found in either set, but not in both.
    print(setx)
if __name__ == '__main__':

    test_set()