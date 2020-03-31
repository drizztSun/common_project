from enum import Enum, unique


class Color(Enum):
    RED = 1
    BLUE = 2
    GREEN = 3


class Shake(Enum):

    VANILLA = 7
    CHOCOLATE = 3
    COOKIES = 9
    MINT = 3  # enumerations allow multiple names as aliases for the same value

# Ensuring unique enumeration values
# By default, enumerations allow multiple names as aliases for the same value.
# When this behavior isn’t desired, the following decorator can be used to ensure each value is used only once in the enumeration:


@unique
class ShakeUnique(Enum):

    VANILLA = 7
    CHOCOLATE = 3
    COOKIES = 9
    # MINT = 3 # because of @Unique, doesn't enumerations allow multiple names as aliases for the same value


if __name__ == "__main__":

    # Enumeration members have human readable string representations:
    print("color has ", Color)
    print("Red: ", Color.RED)
    print("BLUE: ", Color.BLUE)
    print("GREEN: ", Color.GREEN)

    # …while their repr has more information:
    print("repr: ", repr(Color.RED))
    # The type of an enumeration member is the enumeration it belongs to:
    print("type: ", type(Color.RED))
    print("isinstance(color.GREEN, color): ", isinstance(Color.BLUE, Color))

    # Enum members also have a property that contains just their item name:
    print("name: ", Color.RED.name)

    # Enumerations support iteration, in definition order:
    for shake in Shake:
        print(shake)

    # Enumeration members are hashable, so they can be used in dictionaries and sets:
    apples = {}
    apples[color.RED] = 'red delicious'
    apples[color.GREEN] = 'granny smith'
    print("apple is {Color.RED: 'red delicious', Color.GREEN: 'granny smith'} : ", apples == {Color.RED: 'red delicious', Color.GREEN: 'granny smith'})

    # Enum allows such access:
    print("Color(1): ", Color(1))
    print("Color(3): ", Color(3))

    print("Color['RED']: ", Color['RED'])
    print("Color['BLUE']: ", Color['BLUE'])
