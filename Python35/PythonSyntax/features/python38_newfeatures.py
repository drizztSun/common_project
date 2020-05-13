import re

def assingment_expressions():

    # Assignment expressions
    # There is new syntax := that assigns values to variables as part of a larger expression. 
    # It is affectionately known as “the walrus operator” due to its resemblance to the eyes and tusks of a walrus.
    a = [i for i in range(10)]
    if (n := len(a)) > 0: # := makes 'n' declare and assignment in one line
        print("current array size > 10 is : ", n)

    # A similar benefit arises during regular expression matching where match objects are needed twice,
    # once to test whether a match occurred and another to extract a subgroup:
    discount = 0.0
    advertisement = '1230.0'
    if (mo := re.search(r'(\d+)% discount', advertisement)):
        discount = float(mo.group(1)) / 100.0

    # The operator is also useful with while-loops that compute a value to test loop termination and then need that same value again in the body of the loop:
    # Loop over fixed length blocks
    f = open('./python38_newfeatures.py', 'r')Positional-only parameters
    while (block := f.read(256)) != '':
        print(block)

    # Reuse a value that's expensive to compute
    a = [y := 2, y**2, y**3]

    # Share a subexpression between a comprehension filter clause and its output
    data = range(10)
    def f(x):
        return x % 2
    filtered_data = [y for x in data if (y := f(x)) is not None]


def positional_only_parameters():

    # Positional-only parameters
    # There is a new function parameter syntax '/' to indicate that some function parameters must be specified positionally
    # and cannot be used as keyword arguments.
    # This is the same notation shown by help() for C functions annotated with Larry Hastings’ Argument Clinic tool.

    # a, b ahead '/' is no keyword argument
    # c, d between '/' and '*' is with or without keyword argument
    # e, f after '*' must be keyword argument
    def f(a, b, /, c, d, *, e, f):
        print(a, b, c, d, e, f)

    # The following is a valid call:

    f(10, 20, 30, d=40, e=50, f=60)
    # However, these are invalid calls:
    # f(10, b=20, c=30, d=40, e=50, f=60)   # b cannot be a keyword argument
    # f(10, 20, 30, 40, 50, f=60)           # e must be a keyword argument
    # A further benefit of marking a parameter as positional-only is that it allows the parameter name to be changed in the future without risk of breaking client code.

    # One use case for this notation is that it allows pure Python functions to fully emulate behaviors of existing C coded functions.
    # For example, the built-in pow() function does not accept keyword arguments:

    def pow(x, y, z=None, /):
        "Emulate the built in pow() function"
        r = x ** y
        return r if z is None else r%z
    
    # Another use case is to preclude keyword arguments when the parameter name is not helpful. For example, the builtin len() function has the signature len(obj, /). This precludes awkward calls such as:

    len(obj='hello')  # The "obj" keyword argument impairs readability
    # A further benefit of marking a parameter as positional-only is that it allows the parameter name to be changed in the future without risk of breaking client code. For example, in the statistics module, the parameter name dist may be changed in the future. This was made possible with the following function specification:

    # def quantiles(dist, /, *, n=4, method='exclusive')
    #    ...
    # Since the parameters to the left of / are not exposed as possible keywords, the parameters names remain available for use in **kwargs:

    # >>>
    # >>> def f(a, b, /, **kwargs):
    # ...     print(a, b, kwargs)
    # ...
    # >>> f(10, 20, a=1, b=2, c=3)         # a and b are used in two ways
    # 10 20 {'a': 1, 'b': 2, 'c': 3}
    # This greatly simplifies the implementation of functions and methods that need to accept arbitrary keyword arguments. For example, here is an excerpt from code in the collections module:

class Counter(dict):

    def __init__(self, iterable=None, /, **kwds):
        # Note "iterable" is a possible keyword argument
        pass


def more_precise_types():
    '''
    Python’s typing system is quite mature at this point. However, in Python 3.8, some new features have been added to typing to allow more precise typing:
        1. Literal types
        2. Typed dictionaries
        3. Final objects
        4. Protocols
    Python supports optional type hints, typically as annotations on your code:
    '''

def main():

    assingment_expressions()


if __name__ == '__main__':

    main()