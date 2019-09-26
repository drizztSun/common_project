import os


def fib(i):

    if i == 1:
        return 1
    else:
        return fib(i-1) + fib(i-2)


def Main():
    print(fib(1))
    
def add(a, b):
    return a + b

def muf(a,b):
    return a*b

def muf1(a, b):
    return a**b
    

if '__main__' == __name__:

    a = 1
    a = 2
    a = 3
    Main()

    print(muf(6667,100000))
    print(muf1(8,2))


