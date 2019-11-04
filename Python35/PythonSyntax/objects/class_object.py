
# Class definitions, like function definitions (def statements) must be executed before they have any effect. (You could conceivably place a class definition in a branch of an if statement, or inside a function.)

# In practice, the statements inside a class definition will usually be function definitions,
# but other statements are allowed, and sometimes useful — we’ll come back to this later.
# The function definitions inside a class normally have a peculiar form of argument list, dictated by the calling conventions for methods — again, this is explained later.

# When a class definition is entered, a new namespace is created, and used as the local scope — thus, all assignments to local variables go into this new namespace. In particular, function definitions bind the name of the new function here.

# When a class definition is left normally (via the end), a class object is created. This is basically a wrapper around the contents of the namespace created by the class definition; we’ll learn more about class objects in the next section. The original local scope (the one in effect just before the class definition was entered) is reinstated, and the class object is bound here to the class name given in the class definition header (ClassName in the example).

class ClassName(object):

    # class variable
    __instance = None
    @classmethod
    def newInstance(cls):
        if cls.__instance is None:
            cls.__instance = ClassName()

        return cls.__instance

    # That __new__ accepts cls as it's first parameter and __init__ accepts self,
    # because when calling __new__ you actually don't have an instance yet, therefore no self exists at that moment,
    # whereas __init__ is called after __new__ and the instance is in place, so you can use self with it.
    # The new-style classes let the developer override both __new__ and __init__ and they have distinct purposes,
    # __new__ (the constructor) is solely for creating the object and __init__ (the initializer) for initializing it.
    def __new__(cls, *args, **kwargs):
        if not hasattr(cls, '_instance'):
            cls._instance = super(ClassName, cls).__new__(cls)
            # cls._instance.__init__(*args, **kwargs)
        return cls._instance

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


# in python 2.x, it is inherits from 'type'
# in python 3.x, it is inherited from 'object'
# In python 3 there aren't new or old styles of classes and they inherit directly from 'object' so there is no need to specify it as a base anymore.
class A:  # ->
    pass


if __name__ == '__main__':

    print( issubclass(ClassName, object))

    print( issubclass(A, type))
    print( issubclass(A, object))

    a = ClassName(1, 2, 3)

    print(dir(a))

    ClassName.classname()

    ClassName.staticname('class')

    a.staticname()
