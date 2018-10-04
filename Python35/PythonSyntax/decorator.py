"""
Test the decrator of python

def fun1():
    pass

@fun1
def fun2():
    pass

is equal to 

func2 = func1(func2)

"""

# Python function is a object
def shut(word="yes"):
    return word.capitalize() + '!'

scream = shut
del shut

try:
    shut()
except NameError as e:
    print(e)

# scream is hooked shut body
scream()

# decreated function
def decratedfunc():
    print("I am decreated func")

# function call to simulate the decrator
def decrator(decrated_func):

    def wrapper_descriptor():
    
        print("before the decrate func run")
    
        decrated_func()

        print("after the decrate func run")

    return wrapper_descriptor

# write the 'decrator' to new enclosed function
decrator = decrator(decratedfunc)

def bread(fn):
    def wrapper():
        print("</...........\>")
        fn()
        print("<\.........../>")
    return wrapper

def ingrediant(fn):
    def wrapper():
        print("</-----------\>")
        fn()
        print("<\-----------/>")
    return wrapper

def sandwich():
    print("Hello SandWich")        

# before decrate it
sandwich()

"""
@bread
@ingrediant
def snadwich():
    pass
"""
sandwich = bread(ingrediant(sandwich))

# after decrate it
sandwich()

# A very simple decraotr (non-parameter)
def decrator1(fn):
    def wrapper1():
        print("decrator one")
        return "<b>" + fn() + "</b>"
    return wrapper1

def decrator2(fn):
    def wrapper2():
        print("decrator two")
        return "<i>" + fn() + "</r>"
    return wrapper2

@decrator1
@decrator2
def helloworld():
    return "Hello world"

# decrator(with parameter)
def decrator_wp1(fn):
    def wrapper(arg1, arg2):
        print("start decrator_wp1 from {0} to {1}".format(arg1, arg2))
        fn(arg1, arg2)
        print("end decrator_wp1 from {0} to {1}".format(arg1, arg2))
    return wrapper

def decraotr_wp2(fn):
    def wrapper(arg1, arg2):
        print("start decrator_wp2 from {0} to {1}".format(arg1, arg2))
        fn(arg1, arg2)
        print("end decrator_wp2 from {0} to {1}".format(arg1, arg2))
    return wrapper

@decrator_wp1
@decraotr_wp2
def helloworld_arg(arg1, arg2):
    print("hello world! from {0} to {1}".format(arg1, arg2))
    




def Main():

    decrator()

    print(helloworld())

    helloworld_arg('china', 'us')

    pass


if __name__ == "__main__":
    
    Main()