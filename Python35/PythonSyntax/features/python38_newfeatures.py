
def assingment_expressions():

    # Assignment expressions
    # There is new syntax := that assigns values to variables as part of a larger expression. 
    # It is affectionately known as “the walrus operator” due to its resemblance to the eyes and tusks of a walrus.
    a = [i for i in range(10)]

    if (n := len(a)) > 0:
        print("current array size > 10 is : ", n)

    # Handle a matched regex
    if (match := pattern.search(data)) is not None:
        # Do something with match

    # A loop that can't be trivially rewritten using 2-arg iter()
    while chunk := file.read(8192):
        process(chunk)

    # Reuse a value that's expensive to compute
    [y := f(x), y**2, y**3]

    # Share a subexpression between a comprehension filter clause and its output
    filtered_data = [y for x in data if (y := f(x)) is not None]


def positional_only_parameters():

    # Positional-only parameters
    # There is a new function parameter syntax / to indicate that some function parameters must be specified positionally and cannot be used as keyword arguments. 
    # This is the same notation shown by help() for C functions annotated with Larry Hastings’ Argument Clinic tool.
    
    def f(a, b, /, c, d, *, e, f):
        print(a, b, c, d, e, f)

    # The following is a valid call:

    f(10, 20, 30, d=40, e=50, f=60)
    # However, these are invalid calls:

    f(10, b=20, c=30, d=40, e=50, f=60)   # b cannot be a keyword argument
    f(10, 20, 30, 40, 50, f=60)           # e must be a keyword argument


    One use case for this notation is that it allows pure Python functions to fully emulate behaviors of existing C coded functions. For example, the built-in pow() function does not accept keyword arguments:

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

def main():

    assingment_expressions()


if __name__ == '__main__':

    main()