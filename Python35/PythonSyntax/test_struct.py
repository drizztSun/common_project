
import struct

from collections import namedtuple

def test_struct():

    print("--- test struct ---")


def test_ctype():

    # A basic example of packing/unpacking three integers:
    package = struct.pack('hhl', 1, 2, 3)
    print('package : ', package)

    res = struct.unpack('hhl', package)
    print('res : ', res)

    # Unpacked fields can be named by assigning them to variables or by wrapping the result in a named tuple:
    record = b'raymond   \x32\x12\x08\x01\x08'
    name, serialnum, school, gradelevel = struct.unpack('<10sHHb', record)
    
    Student = namedtuple('Student', 'name serialnum school gradelevel')
    st = Student._make(struct.unpack('<10sHHb', record))
    # Student(name=b'raymond   ', serialnum=4658, school=264, gradelevel=8)
    print('name : ', st.name)

    # The ordering of format characters may have an impact on size since the padding needed to satisfy alignment requirements is different:
    print( struct.pack('ci', b'*', 0x12131415)) # b'*\x00\x00\x00\x12\x13\x14\x15'
    print( 'ci size : ', struct.calcsize('ci'))

    print( struct.pack('ic', 0x12131415, b'*')) # b'\x12\x13\x14\x15*'
    print( 'ic size : ', struct.calcsize('ic'))

    # The following format 'llh0l' specifies two pad bytes at the end, assuming longs are aligned on 4-byte boundaries:
    print(struct.pack('llh0l', 1, 2, 3)) # b'\x00\x00\x00\x01\x00\x00\x00\x02\x00\x03\x00\x00'


if __name__ == '__main__':

    test_ctype()

    test_struct()
