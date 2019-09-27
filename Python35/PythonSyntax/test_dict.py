

def main():

    # genenrator
    tel = dict([('Jack', 12), ('Peter', 13), ('Tom', 14)])
    print(tel)

    tel1 = {k : v for k, v in [('Jack', 12), ('Peter', 13), ('Tom', 14)]}
    print(tel1)

    nums = {x : x**2 for x in range(6)}
    print(nums)

    # update
    tel = {'Jack': 12, 'Peter': 13}
    tel.update(Tom=14)
    print('Jack : ', tel['Jack'], 'Peter : ', tel['Peter'])
    print(tel)

    tel1 = {'Jack': 1, 'Peter': 2}
    tel.update(tel1)
    print(tel)


    # iter
    for i in iter(tel):
        print("item : ", i, tel[i])

    # iterate
    for key in tel.keys():
        print(tel[key])

    # len
    print("len = ", len(tel))

    # get
    tel['Tom']

    print("Tom : ", tel.get('Tom', 100))
    print("Jason : ", tel.get('Jason', 200))

    # set
    tel['Tom'] = 12

    # setdefault
    v = tel.setdefault("Tom", 100)
    tel.setdefault("Mary", 200)
    print(tel)

    # del
    del tel['Tom']
    print('tel ', tel)

    assert( 'Tom' not in tel)

    tel['Tom'] = 10
    assert( 'Tom' in tel)

    # pop
    print("Tom ", tel.pop('Tom', 200))
    print("Jeff ", tel.pop('Jeff', 300))

    # copy
    tel2 = tel.copy()
    print("tel ", tel)
    print("tel2 ", tel2)

    # items
    print("items = ", tel.items())
    for item in tel.items():
        print(item[0], '->', item[1])

    # keys
    print("keys = ", tel.keys())

    # values
    print("values = ", tel.values())

    # clear
    tel.clear()
    print(tel)

    # popitem
    while tel1:
        print("pop item ", tel1.popitem())

    

if __name__ == '__main__':

    # ['__class__', '__contains__', '__delattr__', '__delitem__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', 
    # '__getattribute__', '__getitem__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__iter__', '__le__', '__len__', 
    # '__lt__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__setitem__', '__sizeof__', 
    # '__str__', '__subclasshook__', 
    # 'clear', 'copy', 'fromkeys', 'get', 'items', 'keys', 'pop', 'popitem', 'setdefault', 'update', 'values']

    print(dir(dict))

    main()