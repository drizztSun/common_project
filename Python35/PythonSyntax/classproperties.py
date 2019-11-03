
# <Properties>
class CProp:
    def __init__(self, x):
        # self.__x is a private member
        self.__x = x
        self._temp = 0

    # define property with property function
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


    # Another way is @property

    @property
    def temperature(self):
        print("call temperature get function")
        return self._temp

    @temperature.setter
    def temperature(self, val):
        print("temperature set fucntion")
        self._temp = val

    @temperature.deleter
    def temperature(self):
        print("temperature delete function")
        del self._temp



if __name__ == "__main__":

    obj = CProp(5)

    print("x == {0}".format(obj.x))

    obj.x = 10

    print("x == {0}".format(obj.x))

    # del obj.x

    try:
        obj.x
    except (AttributeError, NameError) as error:
        print("catch a exception", error)


    print("Temperature = ", obj.temperature)

    print("Temperature = ", obj._temp)

    obj.temperature = 100

    print("Temperature = ", obj.temperature)

    print("Temperature = ", obj._temp)

    del obj.temperature

    try:
        obj.temperature
    except (AttributeError, NameError )as error:
        print("catch a exception", error)
