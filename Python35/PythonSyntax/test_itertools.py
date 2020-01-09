"""
itertools — Functions creating iterators for efficient looping

This module implements a number of iterator building blocks inspired by constructs from APL, Haskell, and SML. Each has been recast in a form suitable for Python.

The module standardizes a core set of fast, memory efficient tools that are useful by themselves or in combination.
Together, they form an “iterator algebra” making it possible to construct specialized tools succinctly and efficiently in pure Python.

For instance, SML provides a tabulation tool: tabulate(f) which produces a sequence f(0), f(1), .... The same effect can be achieved in Python by combining map() and count() to form map(f, count()).

These tools and their built-in counterparts also work well with the high-speed functions in the operator module.
For example, the multiplication operator can be mapped across two vectors to form an efficient dot-product: sum(map(operator.mul, vector1, vector2)).

"""

import itertools


def test_itertools_basic_infinite_iterator():

    for c in itertools.count(10):
        print(c)  # 10, 11, 12, 13, 14 ...

    for b in itertools.cycle('ABCD'):
        print(b)  # A, B, C, D, A, B, C, D, A, B, C ...

    for a in itertools.repeat(10, 3):
        print(a)  # 10, 10, 10


def test_itertools_basic_terminating_sequence():

    for a in itertools.accumulate([1, 2, 3, 4, 5, 6]):
        print(a)  # 1, 3, 6, 10, 15, 21

    for a in itertools.chain('ABC', 'DEF', 'GHI'):
        print(a)  # A B C D E F G H I

    for a in itertools.chain.from_iterable(['ABC', 'DEF', 'GHI']):
        print(a)  # A B C D E F G H I

    for a in itertools.compress('ABCDEF', [1, 0, 1, 1, 1, 1]):
        print(a)  # A, C, E, F

    for a in itertools.dropwhile(lambda x: x < 5, [1, 4, 6, 4, 1]):
        print(a)  # 6, 4, 1

    for a in itertools.filterfalse(lambda x: x % 2, range(10)):
        print(a)  # 0, 2, 4, 6, 8

    for k, v in itertools.groupby('xxxyyyzzzuuuuuxxx'):
        print(k, v)

    for k in itertools.islice('ABCDEFG', 2, None):
        print(k)  # C, D, E, F, G

    for k in itertools.starmap(pow, [(2, 5), (3, 2), (10, 3)]):
        print(k)  # 32, 9, 1000

    for k in itertools.takewhilw(lambda x: x < 5, [1, 4, 6, 4, 1]):
        print(k)  # 1, 4


def test_itertools_combination():

    # cartesian product, equivalent to a nested for-loop
    for a in itertools.product('ABCD', 2):
        print(a)  # AA AB AC AD BA BB BC BD CA CB CC CD DA DB DC DD

    # r-length tuples, all possible orderings, no repeated elements
    for b in itertools.permutations('ABCD', 2):
        print(b)  # AB AC AD BA BC BD CA CB CD DA DB DC

    # r-length tuples, in sorted order, no repeated elements
    for c in itertools.combinations('ABCD', 2):
        print(c)  # AB AC AD BC BD CD

    # r-length tuples, in sorted order, with repeated elements
    for d in itertools.combinations_with_replacement('ABCD', 2):
        print(d)  # AA AB AC AD BB BC BD CC CD DD


if __name__ == '__main__':

    test_itertools_basic_terminating_sequence()
