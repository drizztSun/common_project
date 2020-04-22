from enum import Enum, unique, auto
from enum import IntEnum


class Color(Enum):
    RED = 1
    BLUE = 2
    GREEN = 3
    # GREED = 4  # error, enum members with the same name is invalid
    GLASSES_COLOR = 3  # However, two enum members are allowed to have the same value. Given two members A and B with the same value (and A defined first),
                       # B is an alias to A. By-value lookup of the value of A and B will return A. By-name lookup of B will also return A:
                       # It is gonna be the alias of the first item with same value.


    # The rules for what is allowed are as follows: names that start and end with a single underscore are reserved by enum
    # and cannot be used; all other attributes defined within an enumeration will become members of this enumeration,
    # with the exception of special methods (__str__(), __add__(), etc.), descriptors (methods are also descriptors), and variable names listed in _ignore_.
    #
    # Note: if your enumeration defines __new__() and/or __init__() then whatever value(s) were given to the enum member will be passed into those methods. See Planet for an example.
    def describe(self):
        # self is the member here
        return self.name, self.value

    def __str__(self):
        return 'my custome str {0}'.format(self.value)

    @classmethod
    def favorite_mood(cls):
        return cls.RED


class Shake(Enum):

    VANILLA = 7
    CHOCOLATE = 3
    COOKIES = 9
    MINT = 3  # enumerations allow multiple names as aliases for the same value


@unique
class Operator(Enum):
    # Using automatic values¶
    # If the exact value is unimportant you can use auto:
    eq = auto()
    not_eq = auto()
    less_than = auto()
    greater_than = auto()


# Ensuring unique enumeration values
# By default, enumerations allow multiple names as aliases for the same value.
# When this behavior isn’t desired, the following decorator
# @unique can be used to ensure each value is used only once in the enumeration:
@unique
class ShakeUnique(Enum):

    VANILLA = 7
    CHOCOLATE = 3
    COOKIES = 9
    # MINT = 3 # because of @Unique, doesn't enumerations allow multiple names as aliases for the same value


class AutoName(Enum):
    def _generate_next_value_(name, start, count, last_values): # The values are chosen by _generate_next_value_(), which can be overridden:
        return name


class Ordinal(AutoName):
    NORTH = auto()
    SOUTH = auto()
    EAST = auto()
    WEST = auto()


# Derived Enumerations
class Shape(IntEnum):
    CIRCLE = 1
    SQUARE = 2


class Request(IntEnum):
    POST = 1
    GET = 2


def test_derived_enum():

    # The first variation of Enum that is provided is also a subclass of int. Members of an IntEnum can be compared to integers;
    # by extension, integer enumerations of different types can also be compared to each other:
    print( Shape == 1 )
    print( Shape.CIRCLE == 1 )
    print( Shape.CIRCLE == Request.Post)


    




def test_basic_enum_automatic_values():

    print(list(Color))

    print(list(Ordinal))


def test_enum_operator():

    print(list(Color))

    # The special attribute __members__ is a read-only ordered mapping of names to members.
    # It includes all names defined in the enumeration, including the aliases:
    for name, member in Color.__members__.items():
        print(f"{name}, {member}")

    # The __members__ attribute can be used for detailed programmatic access to the enumeration members
    print([name for name, member in Color.__members__.items() if member.name != name])

    # Comparison
    print( Color.RED is Color.RED )
    print( Color.RED is Color.BLUE)
    print( Color.RED is not Color.BLUE)

    # Equality comparison
    print( Color.BLUE == Color.RED )
    print( Color.BLUE != Color.RED )
    print( Color.BLUE == Color.BLUE )

    # Allowed members and attributes of enumerations
    print( Color.favorite_mood() )
    print( Color.RED.describe() )
    print( str(Color.BLUE) )


def test_function_api():

    Animal = Enum('Animal', 'ANT BEE CAT DOG')

    print( Animal )
    print( Animal.ANT )
    print( Animal.ANT.value)
    print( list(Animal) )






def test_basic_enum():

    # Enumeration members have human readable string representations:
    print("color has ", Color)
    print("Red: ", Color.RED)
    print("BLUE: ", Color.BLUE)
    print("GREEN: ", Color.GREEN)

    print("ALL Color is ", list(Color))

    # …while their repr has more information:
    print("repr: ", repr(Color.RED))

    # The type of an enumeration member is the enumeration it belongs to:
    print("type: ", type(Color.RED))
    print("isinstance(color.GREEN, color): ", isinstance(Color.BLUE, Color))

    # Enum members also have a property that contains just their item name:
    # name is left
    print("Color.RED.name: ", Color.RED.name)

    # value is right part
    print("Color.RED.value: ", Color.RED.value)

    # Enumerations support iteration, in definition order:
    for shake in Shake:
        print(shake)

    # Enumeration members are hashable, so they can be used in dictionaries and sets:
    apples = {}

    apples[Color.RED] = 'red delicious'
    apples[Color.GREEN] = 'granny smith'

    print("apple is {Color.RED: 'red delicious', Color.GREEN: 'granny smith'} : ", apples == {Color.RED: 'red delicious', Color.GREEN: 'granny smith'})

    # Programmatic access to enumeration members and their attributes
    # Enum allows such access:
    print("Color(1): ", Color(1))
    print("Color(3): ", Color(3))

    # access enum members by name, use item access
    print("Color['RED']: ", Color['RED'])
    print("Color['BLUE']: ", Color['BLUE'])

    #  enum member and need its name or value:
    member = Color.RED
    print(f'Enum member, {member.name} : {member.value}')

    # Duplicating enum members and values
    print(f'{Color.GREEN} == {Color.GLASSES_COLOR}')


if __name__ == "__main__":

    test_function_api()

    test_enum_operator()

    test_basic_enum()

    test_basic_enum_automatic_values()



