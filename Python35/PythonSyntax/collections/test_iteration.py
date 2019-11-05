
# Interprator is going to check, __iter__, __next__, or __getitem__ in iterable objects

# *** Iterator Types
# Python supports a concept of iteration over containers. This is implemented using two distinct methods; these are used to allow user-defined classes to support iteration.
# Sequences, described below in more detail, always support the iteration methods.

# One method needs to be defined for container objects to provide iteration support:

# *** container.__iter__()
# Return an iterator object. The object is required to support the iterator protocol described below.
# If a container supports different types of iteration, additional methods can be provided to specifically request iterators for those iteration types.
# (An example of an object supporting multiple forms of iteration would be a tree structure which supports both breadth-first and depth-first traversal.)
# This method corresponds to the tp_iter slot of the type structure for Python objects in the Python/C API.

# The iterator objects themselves are required to support the following two methods, which together form the iterator protocol:

# *** iterator.__iter__()
# Return the iterator object itself. This is required to allow both containers and iterators to be used with the for and in statements.
# This method corresponds to the tp_iter slot of the type structure for Python objects in the Python/C API.

# *** iterator.__next__()
# Return the next item from the container. If there are no further items, raise the StopIteration exception.
# This method corresponds to the tp_iternext slot of the type structure for Python objects in the Python/C API.

# Python defines several iterator objects to support iteration over general and specific sequence types, dictionaries, and other more specialized forms.
# The specific types are not important beyond their implementation of the iterator protocol.

# Once an iterator’s __next__() method raises StopIteration, it must continue to do so on subsequent calls.
# Implementations that do not obey this property are deemed broken.



# *** next(iterator[, default])
# Retrieve the next item from the iterator by calling its __next__() method.
# If default is given, it is returned if the iterator is exhausted, otherwise StopIteration is raised.

# *** iter(object[, sentinel])
# Return an iterator object. The first argument is interpreted very differently depending on the presence of the second argument.
# Without a second argument, object must be a collection object which supports the iteration protocol (the __iter__() method), or it must support the sequence protocol (the __getitem__() method with integer arguments starting at 0).
# If it does not support either of those protocols, TypeError is raised. If the second argument, sentinel, is given, then object must be a callable object.
# The iterator created in this case will call object with no arguments for each call to its __next__() method; if the value returned is equal to sentinel, StopIteration will be raised, otherwise the value will be returned.

class Animal:
    def __init__(self, animal_list):
        self.animals_name = animal_list

    def __getitem__(self, index):
        if index == len(self.animals_name):
            raise StopIteration # without raise, it get dead-loop. for ...in ... can capture this exception.

        return self.animals_name[index]

    def __len__(self):
        return len(self.animals_name)


class PrimeNumber:
    def __init__(self, max_number):
        self._max_number = max_number

    def __iter__(self):
        self._num = 0
        return self

    def __next__(self):
        if self._num > self._max_number:
            raise StopIteration # without raise, it get dead-loop, for ...in ... can capture this exception.

        self._num += 1
        return self._num


class non_iter:
    pass


class ud_dict(dict):

    def __init__(self, **kwargs):

        super().__init__(**kwargs)

    def __getitem__(self, key):
        return super().__getitem__(key)

    def __setitem__(self, key, value):
        return super().__setitem__(key, value)

    def __delitem__(self, key):
        return super().__delitem__(key)

    def __iter__(self):
        return super().__iter__()

    def __next__(self):
        return super().__next__()


def test_iteration():

    print(dir(list))
    print(dir(dict))
    print(dir(set))

    list_func = dir(list)
    dict_func = dir(dict)
    set_func = dir(set)

    if '__iter__' in list_func and '__getitem__' in list_func:
        for c in [1, 2, 3, 4, 5]:
            print(c)

    if '__iter__' in dict_func and '__getitem__' in dict_func:
        items = { 'a': 20, 'b': 30, 'c': 40}
        for key in items:
            print(items[key])

    if '__iter__' in set_func and '__getitem__' not in set_func:
        items = set([1, 2, 3, 4, 5, 1, 2])
        for c in items:
            print(c)

    # iter and list
    for c in iter([1, 2, 3, 4, 5, 6]):
        print(c)

    iter_c = iter([1, 2, 3, 4, 5, 6])
    while True:
        try:
            print( next(iter_c))
        except StopIteration:
            break

    iter_c = iter([1, 2, 3, 4, 5, 6])


    # user-defined class with iter
    for c in PrimeNumber(5):
        print(c)
    else:
        print("success to iterate PrimeNumber")


    # user-defined class
    animals = Animal(['cat', 'dog', 'human'])
    for animal in animals:
        print(animal)
    else:
        print("success to iterate Animal")

    try:
        for c in non_iter():
            pass
    except TypeError as e:
        print(e)


    t = ud_dict(a=100, b=200, c=300)
    for c in t:
        print( t[c] )


class mylist(list):

    def __iter__(self):
        c = super().__iter__()
        return c

    def __next__(self):
        c = super().__next__()
        return c

def test_iteration_advanced():

    a = mylist()

    for c in a:
        print(c)

if __name__ == '__main__':

    test_iteration_advanced()

    test_iteration()