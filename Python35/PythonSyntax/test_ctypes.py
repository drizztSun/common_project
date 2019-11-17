from ctypes import *


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


def test_linux_dll():

    # On Linux, it is required to specify the filename including the extension to load a library, so attribute access can not be used to load libraries.
    # Either the LoadLibrary() method of the dll loaders should be used, or you should load the library by creating an instance of CDLL by calling the constructor:
    cdll.LoadLibrary("lib.so.6")


if __name__ == '__main__':

    test_win_dll()