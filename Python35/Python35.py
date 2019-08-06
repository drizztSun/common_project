import os


def fib(i):

    if i == 1:
        return 1
    else:
        return fib(i-1) + fib(i-2)


def Main():
    print(fib(1))


if '__main__' == __name__:

    a = 1
    a = 2
    a = 3
    Main()
