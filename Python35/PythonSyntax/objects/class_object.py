
# Class definitions, like function definitions (def statements) must be executed before they have any effect. (You could conceivably place a class definition in a branch of an if statement, or inside a function.)

# In practice, the statements inside a class definition will usually be function definitions,
# but other statements are allowed, and sometimes useful — we’ll come back to this later.
# The function definitions inside a class normally have a peculiar form of argument list, dictated by the calling conventions for methods — again, this is explained later.

# When a class definition is entered, a new namespace is created, and used as the local scope — thus, all assignments to local variables go into this new namespace. In particular, function definitions bind the name of the new function here.

# When a class definition is left normally (via the end), a class object is created. This is basically a wrapper around the contents of the namespace created by the class definition; we’ll learn more about class objects in the next section. The original local scope (the one in effect just before the class definition was entered) is reinstated, and the class object is bound here to the class name given in the class definition header (ClassName in the example).

class ClassName:

    def __init__(self, x, y ,z):

        # python doesn't control memmber access, use naming to show
        self.x = x  # public access
        self._y = y # private access
        self.__z = z # private access, python rename it as _ClassName__z, no access with __z

    # class function
    @classmethod
    def classname(cls):
        cls._name = 'classname'
        return cls._name

    @staticmethod
    def staticname(more):
        return 'result {more}' % more

    def update(self, x):
        self.x = x

    # class variable

    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            cls._instance = super(ClassName, cls).__new__(cls, *args, **kwargs)

        return cls._instance

    # private access
    __update = update # private copy of original update() method

    # Class objects support two kinds of operations: attribute references and instantiation.

    # Attribute references use the standard syntax used for all attribute references in Python: obj.name.
    x_member = 12345

    # *** property ***
    # define property with property function
    def xgetter(self):
        print("CProp : get")
        return self.__z

    def xsetter(self, n):
        print("CProp : set")
        self.__z = n

    def xdeletor(self):
        print("CProp : del")
        del self.__z

    x = property(xgetter, xsetter, xdeletor, "It is x property")


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


    def __getattribute__(self, name): # object.name

        return super().__getattribute__(name)

    def __setattr__(self, name, value): # object.name = value

        return super().__setattr__(name, value)

    def __delattr__(self, name): # del object.name

        return super().__delattr__(name)



if __name__ == '__main__':

    a = ClassName(1, 2, 3)

    print(dir(a))
