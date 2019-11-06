from copy import deepcopy


def test_dict_basic():

    # genenrator
    tel = dict([('Jack', 12), ('Peter', 13), ('Tom', 14)])
    print(tel)

    tel1 = {k : v for k, v in [('Jack', 12), ('Peter', 13), ('Tom', 14)]}
    print(tel1)

    nums = {x : x**2 for x in range(6)}
    print(nums)

    # *** access ***
    print( "Peter: ", tel['Peter'])

    print("Tom : ", tel.get('Tom', 100))
    print("Jason : ", tel.get('Jason', 200)) # if key not in dict, it will return default-value

    # getdefault
    print( 'Jack : ', tel.get('Jack'))
    print( 'Lucy : ', tel.get('Lucy', 'default-value')) # if key not in dict, it will return default-value

    # *** add  and change***
    # update
    tel = {'Jack': 12, 'Peter': 13}
    tel.update(Tom=14)
    print('Jack : ', tel['Jack'], 'Peter : ', tel['Peter'])
    print(tel)

    tel1 = {'Jack': 1, 'Peter': 2}
    tel.update(tel1)
    print(tel)

    # []
    tel['Mozart'] = 100
    tel['Chopin'] = 110

    # setdefault
    v = tel.setdefault("Tom", 100) # if key in dict, do nothing and return value
    tel.setdefault("Mary", 200)
    print( tel.setdefault('Dav', 1000)) # if key not in dict, it will add key, and then return default-value

    # *** iter ***
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


    # len
    print("len = ", len(tel))

    # *** delete ***
    # del
    del tel['Tom']
    print('tel ', tel)

    assert( 'Tom' not in tel)

    tel['Tom'] = 10
    assert( 'Tom' in tel)

    # pop
    print("Tom ", tel.pop('Tom', 200)) # if key in dict, remove key-value and return value
    print("Jeff ", tel.pop('Jeff', 300)) # if key not in dict, return default-value.

    # popitem
    while tel1:
        print( "pop item ", tel1.popitem()) # remove last one in the dict 

    # *** copy ***
    # copy 
    tel2 = tel.copy()
    print("tel: ", tel)
    print("tel2: ", tel2)

    # deepcopy
    tel3 = deepcopy(tel)
    print("tel: ", tel),
    print("tel3: ", tel3)

    # *** keys and values ***
    # keys
    print("keys = ", tel.keys())

    # values
    print("values = ", tel.values())


    # *** zero clear ***
    # clear
    tel.clear()
    print(tel)


# user-defined dict
class mydict(dict):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def __getitem__(self, key):  # like mydict[key], 'get' doesn't go through this

        if key == 'default':
            return 2000

        return super().__getitem__(key)

    def __setitem__(self, key, val): # like mydict[key] = value, 'setdefault' doesn't go through this

        return super().__setitem__(key, val)

    def __delitem__(self, key): # del mydict[key]

        return super().__delitem__(key)


    def __contains__(self, key):

        return super().__contains__(key)

    def __iter__(self): # like for c in iter()

        for c in super().__iter__():
            yield c


    def __getattribute__(self, name): # object.name

        return super().__getattribute__(name)

    def __setattr__(self, name, value): # object.name = value

        return super().__setattr__(name, value)

    def __delattr__(self, name): # del object.name

        return super().__delattr__(name)


    def __len__(self): # len(object)

        return super().__len__()

    def __iter__(self):
        return super().__iter__()

    def __next__(self):
        return super().__next__()

    
def test_user_defined():
    
    a = mydict([('a', 10), ('b', 20), ('c', 30)])

    print( a['default'])

    print( a['a'])

    a['b'] = 100

    print( a.get('a'))

    a.setdefault('a', 200)

    for c in a:
        print(a[c])

    del a['a']

    a.new_attr = 'new_attr'

    print( a.new_attr)

    del a.new_attr



if __name__ == '__main__':

    # ['__class__', '__contains__', '__delattr__', '__delitem__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__',
    # '__getattribute__', '__getitem__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__iter__', '__le__', '__len__', 
    # '__lt__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__setitem__', '__sizeof__', 
    # '__str__', '__subclasshook__',
    # 'clear', 'copy', 'fromkeys', 'get', 'items', 'keys', 'pop', 'popitem', 'setdefault', 'update', 'values']

    print(dir(dict))

    test_user_defined()