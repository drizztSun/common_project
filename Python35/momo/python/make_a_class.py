


# We use keyword 'class'

class Animal(object):
    
    
    def roar(self):
        return "xxx"

class Pet(Animal):

    def __init__(self, name):
        self._name = name
    
    def roar(self):
        return "mamal roar"

    def food(self):
        return "nothing"

class Cat(Pet):

    def __init__(self, name, age, color,food):

        super().__init__(name)
        self._color = color
        self._age = age
        self._food = food
        self._x = 0
        self._y = 0

    def move(self, x, y):
        self._x += x
        self._y += y
        return (self._x, self._y)

    def __repr__(self):

        return 'Cat: {0} at ({1}, {2}),eats {3}'.format(self._name, self._x, self._y,self._food)

    def roar(self):
        return 'meow'

    def food(self):
        return 'fish'


class Dog(Pet):
    def __init__(self, name, age, color,adress,food):
        self._name = name
        self._age = age
        self._color = color
        self.__adress = adress
        self._food = food

    def roar(self):
        return 'woof woof'
        
    def __repr__(self):
        return '{0} is {1} years old. he is {2}, he is at {3}'.format(self._name,self._age,self._color,self.__adress)

    def food(self):
        return 'bones'


class P_3D(object):
    def __init__(self,x,y,z):
        self._x = 0
        self._y = 0
        self._z = 0
        
    
if __name__ == '__main__':

    cat1 = Cat('kitty', 1, 'red','fish')

    cat2 = Cat('meow meow', 2 ,'orange','fish')

    print(Cat)

    print(cat1)

    print(cat2)
    
    print(cat1.move(10, 24))

    print(cat1.food())

    print(type(cat1))

    print(dir(cat1))

    dog = Dog('puppy',10,'tan','78 Main.ST,Mami,FA','bones')
    print(dog)
    print()
    print(dog.food()) 