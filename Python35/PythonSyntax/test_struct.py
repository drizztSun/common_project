
import struct
from ctypes import *


class Student(struct):

    _fields_ = [

    ]

    def __init__(self):
        pass


def test_struct():

    print("--- test struct ---")


def test_ctype():

    package = struct.pack('hhl', 1, 2, 3)
    print('package : ', package)

    res = struct.unpack('hhl', package)
    print('res : ', res)


if __name__ == '__main__':

    test_ctype()

    test_struct()
