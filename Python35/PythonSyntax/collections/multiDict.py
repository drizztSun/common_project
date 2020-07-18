from collections import defaultdict, OrderedDict, UserDict, Counter


def test_counter():

    cnt = Counter('this is the test for counter')
    print(cnt)

    cnt1 = Counter({'red': 4, 'blue': 2})
    print(cnt1)

    cnt2 = Counter(cats=4, dogs=8)
    print(cnt2)

    print(list(cnt.elements()))
    print(sorted(cnt.elements()))

    print(cnt.most_common(4))  # most 4 elements

    print(cnt)
    cnt.subtract(Counter(a=1, b=1, i=3, o=1))
    print(cnt)

    # Elements are counted from an iterable or added-in from another mapping (or counter). Like dict.update() but adds counts instead of replacing them.
    # Also, the iterable is expected to be a sequence of elements, not a sequence of (key, value) pairs.
    cnt.update(Counter(a=1, b=1, i=3, o=1))
    print(cnt)

    # +, - & |
    c1 = Counter(a=3, b=1)
    c2 = Counter(a=1, b=2)

    print(c1 + c2)  # add two counters together:  c[x] + d[x]
    print(c1 - c2)  # subtract (keeping only positive counts)
    print(c1 & c2)  # intersection:  min(c[x], d[x]) # doctest: +SKIP
    print(c1 | c2)  # union:  max(c[x], d[x])

    # Unary addition and subtraction are shortcuts for adding an empty counter or subtracting from an empty counter.
    c = Counter(a=2, b=-5)
    print(+c)
    print(-c)


def test_defaultdict():

    print(" --- default dict --- ")

    # Returns a new dictionary-like object. defaultdict is a subclass of the built-in dict class.
    # It overrides one method and adds one writable instance variable. The remaining functionality is the same as for the dict class and is not documented here.
    # The first argument provides the initial value for the default_factory attribute; it defaults to None. All remaining arguments are treated the same as if they were passed to the dict constructor, including keyword arguments.

    # New in version 2.5.
    # defaultdict objects support the following method in addition to the standard dict operations:

    # __missing__(key)
    # If the default_factory attribute is None, this raises a KeyError exception with the key as argument.
    # If default_factory is not None, it is called without arguments to provide a default value for the given key, this value is inserted in the dictionary for the key, and returned.
    # If calling default_factory raises an exception this exception is propagated unchanged.

    # This method is called by the __getitem__() method of the dict class when the requested key is not found; whatever it returns or raises is then returned or raised by __getitem__().
    # Note that __missing__() is not called for any operations besides __getitem__(). This means that get() will, like normal dictionaries, return None as a default rather than using default_factory.

    # defaultdict objects support the following instance variable:

    # default_factory
    # This attribute is used by the __missing__() method; it is initialized from the first argument to the constructor, if present, or to None, if absent.

    # defaultdict
    # Using list as the default_factory, it is easy to group a sequence of key-value pairs into a dictionary of lists:
    s = [('yellow', 1), ('blue', 2), ('yellow', 3), ('blue', 4), ('red', 1)]
    d = defaultdict(list)

    for i, k in s:
        d[i].append(k)

    print(sorted(d.items()))

    # defaultdict/int
    s = 'mississippi'
    d = defaultdict(int)

    for k in s:
        d[k] += 1

    print(sorted(d.items()))

    # default/function
    # def constant_factory(x):
    #    return lambda : x
    # d = defaultdict(constant_factory('<missing>')
    #d.update(name='Johen', action='ran')

    # defaultdict/set
    s = [('red', 1), ("blue", 2), ("red", 3),
         ('blue', 4), ('red', 1), ('blue', 4)]
    d = defaultdict(set)

    for k, v in s:
        d[k].add(v)

    print(sorted(d.items()))


def test_orderdict():

    print(" --- order dict ---")
    #  orderdict
    # Return an instance of a dict subclass, supporting the usual dict methods.
    # An OrderedDict is a dict that remembers the order that keys were first inserted.
    # If a new entry overwrites an existing entry, the original insertion position is left unchanged.
    # Deleting an entry and reinserting it will move it to the end.

    # OrderedDict.popitem(last=True)
    # The popitem() method for ordered dictionaries returns and removes a (key, value) pair. The pairs are returned in LIFO order if last is true or FIFO order if false.
    # In addition to the usual mapping methods, ordered dictionaries also support reverse iteration using reversed().

    c = OrderedDict()
    c['blue'] = 100
    c['yellow'] = 200
    c['red'] = 300

    c['black'] = 400
    print(c)

    print(c.popitem(False))  # FIFO
    print(c)

    print(c.popitem(True))  # LIFO
    print(c)

    c.move_to_end('yellow', True)  # move to the right
    print(c)

    c.move_to_end('yellow', False)  # move to the left
    print(c)

    d = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}
    # ordered by keys
    print(OrderedDict(sorted(d.items(), key=lambda t: t[0])))

    # ordered by values
    print(OrderedDict(sorted(d.items(), key=lambda t: t[1])))

    # ordered by length of the key string
    print(OrderedDict(sorted(d.items(), key=lambda t: len(t))))


# An ordered dictionary can be combined with the Counter class so that the counter remembers the order elements are first encountered:
class OrderedCounter(Counter, OrderedDict):
    'Counter that remembers the order elements are first encountered'

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, OrderedDict(self))

    def __reduce__(self):
        return self.__class__, (OrderedDict(self),)


# It is also straight-forward to create an ordered dictionary variant that remembers the order the keys were last
# inserted. If a new entry overwrites an existing entry, the original insertion position is changed and moved to the
# end:
class LastUpdatedOrderedDict(OrderedDict):
    """Store items in the order the keys were last added"""

    def __setitem__(self, key, value):
        if key in self:
            del self[key]
        OrderedDict.__setitem__(self, key, value)


# An OrderedDict would also be useful for implementing variants of functools.lru_cache():
class LRU(OrderedDict):
    """Limit size, evicting the least recently looked-up key when full"""

    def __init__(self, maxsize=128, *args, **kwds):
        self.maxsize = maxsize
        super().__init__(*args, **kwds)

    def __getitem__(self, key):
        value = super().__getitem__(key)
        self.move_to_end(key)
        return value

    def __setitem__(self, key, value):
        super().__setitem__(key, value)
        if len(self) > self.maxsize:
            oldest = next(iter(self))
            del self[oldest]


class myUserDict(UserDict):

    def __init__(self):
        super().__init__()
        self['a'] = 0
        self['b'] = 0


def test_userdict():

    # The class, UserDict acts as a wrapper around dictionary objects.
    # The need for this class has been partially supplanted by the ability to subclass directly from dict;
    # however, this class can be easier to work with because the underlying dictionary is accessible as an attribute.
    # class collections.UserDict([initialdata])

    # Class that simulates a dictionary. The instance’s contents are kept in a regular dictionary,
    # which is accessible via the data attribute of UserDict instances. If initialdata is provided,
    # data is initialized with its contents; note that a reference to initialdata will not be kept, allowing it be
    # used for other purposes.

    # In addition to supporting the methods and operations of mappings, UserDict instances provide the following
    # attribute:

    # data
    # A real dictionary used to store the contents of the UserDict class.

    m = myUserDict()
    m['a'] = 5
    m['b'] = 7

    print(m)

    return
    
    c = UserDict(dict=dict)

    c['blue'] = 100
    c['yellow'] = 200
    c['red'] = 300

    c['black'] = 400
    print(c)

    print(c.popitem(False))  # FIFO
    print(c)

    print(c.popitem(True))  # LIFO
    print(c)

    c.move_to_end('yellow', True)  # move to the right
    print(c)

    c.move_to_end('yellow', False)  # move to the left
    print(c)


if __name__ == "__main__":

    test_counter()

    test_defaultdict()

    test_orderdict()

    test_userdict()
