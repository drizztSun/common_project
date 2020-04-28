def test_all_any():
    a = [1, 2, 4, 5, 6, 7]
    print(all(a))
    # Return True if all elements of the iterable are true (or if the iterable is empty). Equivalent to:
    '''
    def all(iterable):
        for element in iterable:
            if not element:
                return False
        return True
    '''
    # None == False 
    # int, float: 0 == False, nonzero == True
    # str: len(string) == 0 is False
    # list, tuple, dict:  len(a) == 0 is False  
    print(any([[], 0, '', None, False])) 
    #Return True if any element of the iterable is true. If the iterable is empty, return False. Equivalent to:
    '''
    def any(iterable):
        for element in iterable:
            if element:
                return True
        return False
    '''
   
def test_filter_map_reduce():
    from functools import reduce
    a = [1, 2, 3, 4, 5, 6]
    b = filter(lambda x: x%2 == 0 , a)
    print(list(b))
    '''
    Construct an iterator from those elements of iterable for which function returns true. iterable may be either 
    a sequence, a container which supports iteration, or an iterator. If function is None, the identity function 
    is assumed, that is, all elements of iterable that are false are removed.
    Note that filter(function, iterable) is equivalent to the generator expression (item for item in iterable if 
    function(item)) if function is not None and (item for item in iterable if item) if function is None.

    See itertools.filterfalse() for the complementary function that returns elements 
    of iterable for which 0function returns false.
    '''




    a = [1, 2, 3, 4, 5, 6, 7, 8]

    c = map(lambda x:x**3, a)
    print(list(c))
    '''
    Return an iterator that applies function to every item of iterable, yielding the results. If additional 
    iterable arguments are passed, function must take that many arguments and is applied to the items from 
    all iterables in parallel. With multiple iterables, the iterator stops when the shortest iterable is 
    exhausted. For cases where the function inputs are already arranged into argument tuples, see itertools.starmap().
    '''
    d = reduce(lambda x, y: x*y, a)
    print(int(d))#d=(((((((1*2)*3)*4)*5)*6)*7)*8)


def test_split_join():

    a = "This is a test for split string"
    print(a.split())
    print(' '.join(a.split()))

    a = "This-is-a-test-for-split-string"
    print(a.split('-'))
    print('%'.join(a.split('-')))
def split1(s, tar):
    c = []
    h = 0
    if type(s) != str:
        raise ValueError 
    for i in range(len(s)):
        
        if s[i] == tar and h==0:
            
            c.append(s[:i])
            y = i
            h +=1
        elif s[i] == tar:
            c.append(s[y+1:i])
            h +=1

    return c   


def test_zip():
    a = [1, 2, 3, 4, 5]
    b = ['zipper', 'yeilder', 'mack', 'priet', 'brint']
    c = [10, 12, 9, 11, 15]
    d = ['boy', 'boy', 'girl', 'girl', 'boy']
    for i in zip(a, b, c, d):
        print(i)

    '''
    Make an iterator that aggregates elements from each of the iterables.

Returns an iterator of tuples, where the i-th tuple contains the i-th element from each of the argument sequences or iterables. The iterator stops when the shortest input iterable is exhausted. With a single iterable argument, it returns an iterator of 1-tuples. With no arguments, it returns an empty iterator. Equivalent to:

def zip(*iterables):
    # zip('ABCD', 'xy') --> Ax By
    sentinel = object()
    iterators = [iter(it) for it in iterables]
    while iterators:
        result = []
        for it in iterators:
            elem = next(it, sentinel)
            if elem is sentinel:
                return
            result.append(elem)
        yield tuple(result)
The left-to-right evaluation order of the iterables is guaranteed. This makes possible an

idiom for clustering a data series into n-length groups using zip(*[iter(s)]*n). This repeats the same iterator n 

times so that each output tuple has the result of n calls to the iterator. This has the effect of dividing the
 
input into n-length chunks.

zip() should only be used with unequal length inputs when you don’t care about trailing, 

unmatched values from the longer iterables. If those values are important, use itertools.zip_longest() instead.

zip() in conjunction with the * operator can be used to unzip a list:


>>> x = [1, 2, 3]
>>> y = [4, 5, 6]
>>> zipped = zip(x, y)
>>> list(zipped)
[(1, 4), (2, 5), (3, 6)]
>>> x2, y2 = zip(*zip(x, y))
>>> x == list(x2) and y == list(y2)
True

'''


def test_binary():

    # & | ^
    
    print( 1 & 2)

    print(1|2)


if __name__ == "__main__":

    test_all_any()
    
    test_filter_map_reduce()
    
    test_zip()
    
    test_split_join()
    
    print(split1('hello im python',' '))