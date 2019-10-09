from enum import Enum

class Color(Enum):
    RED = 1
    BLUE = 2
    GREEN = 3


class Shake(Enum):

    VANILLA = 7
    CHOCOLATE = 3
    COOKIES = 9
    MINT = 3


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
    print("apple is {Color.RED: 'red delicious', Color.GREEN: 'granny smith'} : ", apples == {Color.RED: 'red delicious', Color.GREEN:'granny smith'}) 

    # Enum allows such access:
    print("Color(1): ", Color(1))
    print("Color(3): ", Color(3))

    print("Color['RED']: ", Color['RED'])
    print("Color['BLUE']: ", Color['BLUE'])


