import os

import operator

import itertools

import functools


def test_Intertools():


    """
    # Infinite iterators:
    """
    # count
    for n in count(10, 2):
        print(n)
        if n == 20:
            break

    # cycle
    c = 0
    for n in itertools.cycle('ABCD'):
        if n == 'D':
            c += 1
            if c == 3:
                break


    # repeat
    for n in repeat(10, 3):
        print(n)

        

    """
    # Iterators terminating on the shortest input sequence:
    """
    # accumulate
    print(list(itertools.accumulate([1, 2, 3, 4, 5])))

    print(list(itertools.accumulate([1, 2, 3, 4, 5], operator.mul)))


    # chain

    print(list(itertools.chain("ABC", "DEF")))

    print(list(itertools.chain.from_iterable(["ABC", "DEF"])))

    # compress
    print(list(itertools.compress('ABCDEFG', [1,0,1,0,1,0,1])))



    # dropwhile
    print(list(itertools.dropwhile(lambda x : x < 5, [1, 4, 6, 4, 1]))) # 6, 4, 1

    # takewhile
    print(list(itertools.takewhile(lambda x : x < 5, [1, 4, 6, 4, 1]))) # 1, 4


    # filterfalse
    print(list(itertools.filterfalse(lambda x : x % 2, range(10))))

    # islice
    # islice iterable, start, end, step
    print(list(itertools.islice('ABCDEFG', 2, None))) # ['C', 'D', 'E', 'F', 'G']
    
    print(list(itertools.islice('ABCDEFG', 2, 4))) # ['C', 'D']

    print(list(itertools.islice('ABCDEFG', 2, 6, 2))) # ['C', 'E']


    # starmap
    print(list(itertools.starmap(pow, [(2, 5), (3, 2), (10, 3)])))


    # zip_longest
    print(list(itertools.zip_longest('ABCD', 'xy', fillvalue='-'))) # [('A', 'x'), ('B', 'y'), ('C', '-'), ('D', '-')]


    """
    # Combinatoric iterators:
    """

    # combinations
    print(list(itertools.combinations(range(4), 3)))    # [(0, 1, 2), (0, 1, 3), (0, 2, 3), (1, 2, 3)]
    
    print(list(itertools.combinations('ABCD', 2))) # [('A', 'B'), ('A', 'C'), ('A', 'D'), ('B', 'C'), ('B', 'D'), ('C', 'D')]

    # combinations_with_replacement
    print(list(itertools.combinations_with_replacement(range(4), 3))) # [(0, 0, 0), (0, 0, 1), (0, 0, 2), (0, 0, 3), (0, 1, 1), (0, 1, 2), (0, 1, 3), (0, 2, 2), (0, 2, 3), (0, 3, 3), (1, 1, 1), (1, 1, 2), (1, 1, 3), (1, 2, 2), (1, 2, 3), (1, 3, 3), (2, 2, 2), (2, 2, 3), (2, 3, 3), (3, 3, 3)]
    
    print(list(itertools.combinations_with_replacement('ABCD', 2))) # [('A', 'A'), ('A', 'B'), ('A', 'C'), ('A', 'D'), ('B', 'B'), ('B', 'C'), ('B', 'D'), ('C', 'C'), ('C', 'D'), ('D', 'D')]

    # permutation
    print(list(itertools.permutations('ABCD', 2))) # [('A', 'B'), ('A', 'C'), ('A', 'D'), ('B', 'A'), ('B', 'C'), ('B', 'D'), ('C', 'A'), ('C', 'B'), ('C', 'D'), ('D', 'A'), ('D', 'B'), ('D', 'C')]

    print(list(itertools.permutations(range(3)))) # [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]
    
    # product
    print(list(itertools.product("ABCD", "xy"))) #[('A', 'x'), ('A', 'y'), ('B', 'x'), ('B', 'y'), ('C', 'x'), ('C', 'y'), ('D', 'x'), ('D', 'y')]

    pass



###
# Test functools
#
###

@lru_cache(maxsize=32)
def test_functools():

    res = functools.cmp_to_key()
    
    pass


###
# Test operator
#
###
# operator.lt(a, b)
# operator.le(a, b)
# operator.eq(a, b)
# operator.ne(a, b)
# operator.ge(a, b)¶
# operator.gt(a, b)
# operator.__lt__(a, b)
# operator.__le__(a, b)
# operator.__eq__(a, b)
# operator.__ne__(a, b)
# operator.__ge__(a, b)
# operator.__gt__(a, b)

# operator.not_(obj)
# operator.__not__(obj)

# operator.and_(a, b)
# operator.__and__(a, b)

# operator.or_(a, b)
# operator.__or__(a, b)



# operator.truth(obj)

# operator.is_(a, b)
# operator.is_not(a, b)


# operator.rshift(a, b)
# operator.__rshift__(a, b)

# operator.lshift(a, b)



# operator.neg(obj)
# operator.__neg__(obj)

# operator.pos(obj)
# operator.__pos__(obj)


# operator.abs(obj)
# operator.__abs__(obj)

# operator.add(a, b)
# operator.__add__(a, b)


def test_operator():

    pass


if __name__=="__main__":

    
    
    test_Intertools()


    pass