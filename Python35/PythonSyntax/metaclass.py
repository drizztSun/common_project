"""

How to manage a 'Class', 'cls'

Python will use '__metaclass__' to create a object instance, if there is, or it use 'type'
Python will search '__metaclass__' first, from 'class', 'parent-class', and 'module'. 
if it can't find any, then it will use 'type', to create object

"""

class ObjectCreator(object):
    pass

def echo(o):
    print(o)

# create a class Dynamically
def choose_class(name):
    if name == 'foo':
        class Foo(object):
            pass
        return Foo
    elif name == 'Bar':
        class Bar(object):
            pass
        return Bar


def upper_attr(future_class_name, future_class_parents, future_class_attr):

    uppercase_attr = {}
    for name, value, in future_class_attr.items():

        if not name.startswith('__'):
            uppercase_attr[name.upper()] = value
        else:
            uppercase_attr[name] = value

    return type(future_class_name, future_class_parents, uppercase_attr)        

__metaclass__ = upper_attr

class Foo_meta(object):

    bar = 'bip'


"""
    Enum 
"""
# define ENUM
from enum import Enum
Animal = Enum('Animal', 'ant bee cat dog')

# it is equal to 
class Animal(Enum):
    ant = 1
    bee = 2
    cat = 3
    dog = 4
    

        
def main():

    print(type(1))

    print(type('1'))

    print(type(1.1))
    
    print(type(ObjectCreator))

    print(type(ObjectCreator()))

    print(isinstance(ObjectCreator(), ObjectCreator))

    print(ObjectCreator)

    # pass as parameter
    echo(ObjectCreator)    

    # check if there is a 'new_attribute' in class ObjectCreator 
    print(hasattr(ObjectCreator, 'new_attribute'))

    # create a new class variable
    ObjectCreator.new_attribute = 'foo'

    # check if it is there after creating it
    print(hasattr(ObjectCreator, 'new_attribute'))

    # output the new one
    print(ObjectCreator.new_attribute)

    # assign class to it
    ObjectCreateMirror = ObjectCreator
    
    #  new one has       
    print(ObjectCreateMirror.new_attribute)

    print(ObjectCreateMirror())


    # Create a class dynamically
    print(choose_class('foo'))

    print(choose_class('Bar'))

    # manually create classs
    Foo = type('Foo', (), {'bar': True})

    print(Foo)

    print(Foo())

    print(Foo().bar)
    
    # manually inherit a class
    def echo_bar(self, content):
        print("content = {0}".format(content))
        return True

    FooChild = type('FooChild', (Foo, ), {'echo_bar': echo_bar})

    print("FoodChild has bar {0}".format(FooChild().bar))

    print("FoodChild has fun echo_bar {0}".format(hasattr(FooChild, "echo_bar")))

    objFooChild = FooChild()
 
    print("FooChild has fun echo_bar {0}".format(objFooChild.echo_bar("veryifing")))


    # What is 'metadata', '__class__'
    age = 35
    print(age.__class__) # int
    print(id(age))

    name = 'bbb'
    print(name.__class__) # str
    print(id(name))

    def foo():
        pass

    print(foo.__class__) # function

    class Bar(object):
        pass

    print(Bar.__class__) # type

    b = Bar()
    print(id(b))
    print(b.__class__) # __main__.bar

    #
    print(age.__class__.__class__)
    print(name.__class__.__class__)
    print(foo.__class__.__class__)
    print(Bar.__class__.__class__)
    print(b.__class__.__class__)

    # 
    obj = Foo_meta()
    print(hasattr(Foo_meta, 'bar'))

    print(hasattr(Foo_meta, 'BAR'))
    
        
    


if __name__ == "__main__":

    main()