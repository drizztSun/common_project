
# Inheritance is the capability of one class to derive or inherit the properties from some another class.
# The benefits of inheritance are:

# It represents real-world relationships well.
# It provides reusability of a code. We don’t have to write the same code again and again. Also, it allows us to add more features to a class without modifying it.
# It is transitive in nature, which means that if class B inherits from another class A, then all the subclasses of B would automatically inherit from class A.

class basic_class(object):

    def __init__(self, x, y, z):

        self.x = x
        self._y = y
        self.__z = z


class derivced_class(basic_class):

    def __init__(self, x, y ,z):

        # basic_class.__init__(self, x, y, z) # call basic class __init__

        super().__init__(x, y, z) # or call super() function to get basic class


class base1(object):

    def __init__(self):
        self.name = 'base1'
        print('base1')

class base2(object):

    def __init__(self):
        self.name = 'base2'
        print('base2')

class multi_derived_class(base1, base2):

    def __init__(self):

        base1.__init__(self)
        base2.__init__(self) # since base1 and base2 has same member 'name', later one will cover the former one.
        print('derived class')


if __name__ == '__main__':

    b = derivced_class(1, 2, 3)

    c = multi_derived_class()
    print(c.name)

    print( 'b is derived from derived_class : ', isinstance(b, derivced_class))

    print( 'multi_derived_class inherited from [base1, base2] : ', issubclass(multi_derived_class, [base1, base2]))



