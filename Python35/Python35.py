import os







class C:
    def __init__(self, x):
        self._x = x
    
    def xgetter(self):
        return self._x

    def xsetter(self, n):
        self._x = n
    
    def xdeletor(self):
        del self._x

    x = property(xgetter, xsetter, xdeletor, "It is x property")

def Main():

    pass

if '__main__' == __name__:

    Main()
    