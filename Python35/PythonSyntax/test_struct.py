
from struct import *
from ctypes import *
import struct

from collections import namedtuple

class IP(Structure):

    _fields_ = [
        ("ihl",           c_ubyte, 4),
        ("version",       c_ubyte, 4),
        ("tos",           c_ubyte),
        ("len",           c_ushort),
        ("id",            c_ushort),
        ("offset",        c_ushort),
        ("ttl",           c_ubyte),
        ("protocol_num",  c_ubyte),
        ("sum",           c_ushort),
        ("src",           c_ulong),
        ("dst",           c_ulong)
    ]
    
    def __new__(self, socket_buffer=None):
            return self.from_buffer_copy(socket_buffer)


class Int(Structure):
    _fields_ = [
        ('first_16', c_int, 16),
        ('second_16', c_int, 16)
    ]

    def __init__(self):
        pass

    def __repr__(self):
        return '(%d, %d)' % (self.first_16, self.second_16)


def test_struct():

    print("--- test struct ---")
    # Int
    a = Int()
    print("a :", a, a.first_16, a.second_16)

    a.first_16 = 100
    a.second_16 = 200

    print("a :", a, a.first_16, a.second_16)

    #IP

    


def test_ctype():

    # A basic example of packing/unpacking three integers:
    package = struct.pack('hhl', 1, 2, 3)
    print('package : ', package)

    res = struct.unpack('hhl', package)
    print('res : ', res)

    # Unpacked fields can be named by assigning them to variables or by wrapping the result in a named tuple:
    record = b'raymond   \x32\x12\x08\x01\x08'
    name, serialnum, school, gradelevel = struct.unpack('<10sHHb', record)
    print(name, serialnum, school, gradelevel)
    
    Student = namedtuple('Student', 'name serialnum school gradelevel')
    st = Student._make(struct.unpack('<10sHHb', record))
    # Student(name=b'raymond   ', serialnum=4658, school=264, gradelevel=8)
    print('name : ', st.name)

    # The ordering of format characters may have an impact on size since the padding needed to satisfy alignment requirements is different:
    print( pack('ci', b'*', 0x12131415)) # b'*\x00\x00\x00\x12\x13\x14\x15'
    print( 'ci size : ', struct.calcsize('ci'))

    print( struct.pack('ic', 0x12131415, b'*')) # b'\x12\x13\x14\x15*'
    print( 'ic size : ', struct.calcsize('ic'))

    # The following format 'llh0l' specifies two pad bytes at the end, assuming longs are aligned on 4-byte boundaries:
    print(struct.pack('llh0l', 1, 2, 3)) # b'\x00\x00\x00\x01\x00\x00\x00\x02\x00\x03\x00\x00'


if __name__ == '__main__':

    test_ctype()

    test_struct()
