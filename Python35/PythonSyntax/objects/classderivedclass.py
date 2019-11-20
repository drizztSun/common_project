class MyClass:

    def __init__(self, arg1, arg2, arg3):
        print(f'An instanve of {type(self).__name__} created')
        print(f'arg1:{arg1}  arg2:{arg2}  arg3:{arg3}')

        self.x = arg1 # it could be change outside of class
        self._y = arg2  # by routine, it could n't be change outside the class
        self.__z = arg3 # double underscore __ will make variant change to '_MyClass__z'

    def set_y(self, v):
        self._y = v
    
    def get_y(self):
        return self._y

    @property
    def z(self):
        return self.__z

    @z.setter 
    def z(self, z):
        self.__z = z

    @z.deleter
    def z(self):
        del self.__z

    @staticmethod
    def common_static_name(arg):
        print('static method common_static_name called')
        print('arg {arg}')
        return 'my_static_name_id_xxx'

    @classmethod
    def cls_common_name(cls, arg):
        print('class method cls_common_name called')
        print(f'cls: {cls}')
        print(f'arg: {arg}')
        return 

    def output(self):
        print('instance method f called')
        print(f'instance: {self}')
        print(f'instance attributes:\n{vars(self)}')
        print(f'class: {type(self)}')
        print("x: {self.x}, _y: {self._y}, __z: {self.__z}")


class MyOtherClass(MyClass):

    def __init__(self, x, y, z, a, b, c):
        super().__init__(x, y, z)
        self.a = a
        self._b = b
        self.__c = c

    def output(self, arg):
        print('instance method output_ called')
        print(f'instance: {self}')
        print(f'instance attributes:\n{vars(self)}')
        print(f'class: {type(self)}')
        print(f'arg: {arg}')
        print(f'a {self.a}, b {self._b}, c {self.__c}, x {self.x}, y {self._y}, z')

    


if __name__ == '__main__':

    m = MyClass(2, 4, 8)

    print(vars(m))  # vars()  {'x': 2, '_y': 4, '_MyClass__z': 8}

    print(m.__dict__) # 

    m.output()

    MyClass.cls_common_name([1, 2, 3])

    m.common_static_name([1, 2, 3])

    n = MyOtherClass(2, 4, 8, 1, 3, 5)

    print(vars(n))

    n.output([1, 2, 3])

