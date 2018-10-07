

# a will store the status among different function call. like [], [5], [7]
"""
    function is also a object, self-defined and exxcutable. 
    default parameter is like 'member instance', which staus is as long as function's lifecycle.
    and the status will be changed and updated each time.
    http://effbot.org/zone/default-values.htm
"""
def foo(a = []):
    print(a)
    a.append(5)
    return a

# a will be None or parameter passed
def fooN(a = None):
    if a is None:
        a = []
    print(a)
    return a
        

def main():

    print(id(foo())) # [] a [5]

    print(id(foo())) # [5] a [5, 5]

    print(id(foo())) # [5, 5] a [5, 5, 5]
    
    print(id(foo([1]))) # [5, 5]

    print(id(foo())) # [5, 5, 5] a [5, 5, 5, 5]

    print(id(foo())) # [5, 5, 5, 5] a [5, 5, 5, 5, 5]


if __name__ == "__main__":
    
    main()
