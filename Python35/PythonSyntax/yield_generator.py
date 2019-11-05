
"""
    1) yield
    keyword "yield" is a keyword that is used like "return", except the function will return a "generator".

    2) generator
    To master yield, you must understand that when you call the function, the code you have written in the function body does not run. 
    The function only returns the generator object, this is a bit tricky 

    3) iterable
    Understanding the inner mechanisms of iteration
    Iteration is a process implying iterables (implementing the __iter__() method) and iterators (implementing the __next__() method).
    Iterables are any objects you can get an iterator from. Iterators are objects that let you iterate on iterables.

    https://pythontips.com/2013/09/29/the-python-yield-keyword-explained/

"""

# generator
def creategenerator(n):
    for c in range(n):
        yield c ** 2


def main():

    # list is iterable, everything could be feed into 'for ... in ...' is iterabe
    obj = [1, 2, 3, 4, 5]
    for c in obj:
        print(c)

    # generaotr
    mygenerator = (x**2 for x in range(4))
    print("generator type is {0}".format(type(mygenerator)))
    for c in mygenerator:
        print(c)
    
    objgenerator = creategenerator(10)
    print("objgenerator type is {0}".format(type(objgenerator)))
    for c in objgenerator:
        print(c)

    pass


if __name__ == "__main__":

    main()

