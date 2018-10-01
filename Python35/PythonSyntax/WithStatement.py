
"""

Test some basic python language features


Remember, PEP 310 proposes roughly this syntax (the "VAR =" part is optional):

with VAR = EXPR:
    BLOCK
which roughly translates into this:

VAR = EXPR
VAR.__enter__()
try:
    BLOCK
finally:
    VAR.__exit__()


https://www.python.org/dev/peps/pep-0343/


"""
import os

from contextlib import contextmanager # context to support 'With'

# <with statement>
class WithStateMent:
    
    def __init__(self, path):
        self.__path = path

    def __enter__(self):
        print("WithStatement : enter ")
        self.__fd = open(self.__path, "r")
        return self.__fd

    def __exit__(self, type, value, traceback):
        self.__fd.close()

# <with statement> another one
@contextmanager
def opened(filename, mode="r"):

    f = open(filename, mode)
    try:
        yield f
    finally:
        f.close()



def main():

    with WithStateMent('./PythonSyntax/WithStatement.py') as w:
        print(w.read())

    with opened('./PythonSyntax/WithStatement.py', 'r') as w:
        print(w.read())

    res = 1

if __name__ == "__main__":

    main()