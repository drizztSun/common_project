


# <Properties>
class CProp:
    def __init__(self, x):
        self._x = x
    
    def xgetter(self):
        print("CProp : get")
        return self._x

    def xsetter(self, n):
        print("CProp : set")
        self._x = n
    
    def xdeletor(self):
        print("CProp : del")
        del self._x

    x = property(xgetter, xsetter, xdeletor, "It is x property")

def main():


    # test 'WithStatement'
    with WithStateMent('./functions.py') as f:
        print(f.read())

    

    res = 1


if __name__ == "__main__":

    main()    
