


# We use keyword 'class'

class Animal(object):
    pass
class mamall(Animal):
    pass

class Cat(object):

    def __init__(self, name, age, color):

        self._name = name
        self._color = color
        self._age = age

        self._x = 0
        self._y = 0

    def move(self, x, y):
        self._x += x
        self._y += y
        return (self._x, self._y)

    def __repr__(self):

        return 'Cat: {0} at ({1}, {2})'.format(self._name, self._x, self._y)
    

if __name__ == '__main__':

    cat1 = Cat('kitty', 1, 'red')

    cat2 = Cat('meow meow', 2 ,'orange' )

    print(Cat)

    print(cat1)

    print(cat2)
    
    print(cat1.move(10, 24))

     