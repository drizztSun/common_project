
# <Properties>
class CProp:
    def __init__(self, x):
        # self.__x is a private member
        self.__x = x
    
    def xgetter(self):
        print("CProp : get")
        return self.__x

    def xsetter(self, n):
        print("CProp : set")
        self.__x = n
    
    def xdeletor(self):
        print("CProp : del")
        del self.__x

    x = property(xgetter, xsetter, xdeletor, "It is x property")



if __name__ == "__main__":

    obj = CProp(5)

    print("x == {0}".format(obj.x))

    obj.x = 10

    print("x == {0}".format(obj.x))

    del obj.x
    
    try:

        obj.x

    except:
        print("catch a exception")