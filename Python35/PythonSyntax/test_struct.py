
from struct import *
from ctypes import *
import struct

from collections import namedtuple

# Structures and unions
# Structures and unions must derive from the Structure and Union base classes which are defined in the ctypes module. 
# Each subclass must define a _fields_ attribute. _fields_ must be a list of 2-tuples, containing a field name and a field type.S
# The field type must be a ctypes type like c_int, or any other derived ctypes type: structure, union, array, pointer.
# Here is a simple example of a POINT structure, which contains two integers named x and y, 
# and also shows how to initialize a structure in the constructor:
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

# Structure/union alignment and byte order
# By default, Structure and Union fields are aligned in the same way the C compiler does it. 
# It is possible to override this behavior be specifying a _pack_ class attribute in the subclass definition. 
# This must be set to a positive integer and specifies the maximum alignment for the fields. This is what #pragma pack(n) also does in MSVC.

# ctypes uses the native byte order for Structures and Unions. To build structures with non-native byte order, 
# you can use one of the BigEndianStructure, LittleEndianStructure, BigEndianUnion, and LittleEndianUnion base classes. These classes cannot contain pointer fields.

class Int(Structure):
    _fields_ = [
        ('first_16', c_int, 16),
        ('second_16', c_int, 16)
    ]

    def __init__(self):
        pass

    def __repr__(self):
        return '(%d, %d)' % (self.first_16, self.second_16)

# Bit fields in structures and unions
# It is possible to create structures and unions containing bit fields. Bit fields are only possible for integer fields, 
# the bit width is specified as the third item in the _fields_ tuples:
class Point(Structure):

    _fields_ = [
        ('x', c_int, 16),
        ('y', c_int, 16)
    ]


class Rect(Structure):

    _fields_ = [
        ("upperleft", Point),
        ("lowerright", Point)
    ]


def test_struct():

    print("--- test struct ---")
    #Point
    pt = Point(100, 200)
    print(pt.x, pt.y)

    pt1 = Point(y=10)
    print(pt1.x, pt1.y)

    rc = Rect(pt)
    print(rc.upperleft.x, rc.upperleft.y)
    print(rc.lowerright.x, rc.lowerright.y)

    rc1 = Rect(Point(1, 2), Point(3, 4))
    rc2 = Rect((1, 2), (3, 4))

    print(Point.x)
    print(Point.y)

    # Int
    a = Int()
    print("a :", a, a.first_16, a.second_16)

    a.first_16 = 100
    a.second_16 = 200

    print("a :", a, a.first_16, a.second_16)

    #IP
    
class PointArr(Structure):

    _fields_=[
        ("a", c_int),
        ("b", c_float),
        ("point_array", Point * 4)
    ]


def test_struct_advanced():

    # Array
    # Arrays are sequences, containing a fixed number of instances of the same type.
    # The recommended way to create array types is by multiplying a data type with a positive integer:

    TenPointsArrayType = Point * 10
    arr = TenPointsArrayType(Point(1, 2), Point(2, 3))
    print(len(arr))
    for pt in arr:
        print(pt.x, pt.y)

    print(len(PointArr().point_array))

    IntArray = c_int * 10
    arrint = IntArray(i for i in range(10))
    for i in arrint:
        print(i)

    # pointer
    # pointer instances are created by calling the pointer() function on a ctypes type:
    i = c_int(42)
    pi = pointer(i)

    # Pointer instances have a contents attribute which returns the object to which the pointer points, the i object above:
    print(pi.contents)

    # Note that ctypes does not have OOR (original object return), 
    # it constructs a new, equivalent object each time you retrieve an attribute:
    assert(pi.contents is not i)
    assert(pi.contents is not pi.contents)

    # Assigning another c_int instance to the pointer’s contents attribute would cause the pointer to point to the memory location where this is stored:
    pi.contents = c_int(99)
    
    # Pointer instances can also be indexed with integers:
    print(pi[0])

    # It is also possible to use indexes different from 0, but you must know what you’re doing, just as in C: 
    # You can access or change arbitrary memory locations. 
    # Generally you only use this feature if you receive a pointer from a C function, and you know that the pointer actually points to an array instead of a single item.
    pi[0] = 200
    print(pi[0])

    # Behind the scenes, the pointer() function does more than simply create pointer instances, it has to create pointer types first. 
    # This is done with the POINTER() function, which accepts any ctypes type, and returns a new type:
    PI = POINTER(c_int)
    try:
        print(PI(42))
    except TypeError:
        pass

    print(PI(c_int(42)))

    # Calling the pointer type without an argument creates a NULL pointer. NULL pointers have a False boolean value:
    null_ptr = POINTER(c_int)()
    print(bool(null_ptr))

    # ctypes checks for NULL when dereferencing pointers (but dereferencing invalid non-NULL pointers would crash Python):
    try:
        null_ptr[0]
        null_ptr[0] = 1234
    except TypeError:
        pass
    


def test_struct_func():

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

    test_struct_func()

    test_struct()
