"""
Test

try - exception - else - finaly

"""
try :
    import os
except ImportError:
    print("Get a import error")


class B(Exception):
    pass

class C(B):
    pass

class D(C):
    pass


# user-defined exception
class Error(Exception):
    pass

class InputError(Error):
    
    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

class TransitionError(Error):
    
    def __init__(self, previous, next, message):
        self.previus = previous
        self.next = next
        self.message = message


def divide(x, y):
    # 'else' will be call if not exception happened
    # 'finally' will be call both 'else' and 'except'
    try:
        r = x / y       
    except ZeroDivisionError as err:
        print("Exception: zero division error {0}".format(err))
    else:
        print("Exception No: result is {0} ".format(r))
    finally:
        print("finally: finally called in divide after except and else")


def main():

    # catch special exception
    try:
        a = 1 / 0
    except ZeroDivisionError:
        print("Exception: zero division error")
    except (RuntimeError, TypeError, NameError):
        print("Exception: one of RuntimeError, TypeError, NameError")
    except :
        print("Exception: Unknown error")


    # catch the exception from subcalss to parent-class
    for cls in [B, C, D]:
        try:
            raise cls()

        except D:
            print("Exception: D")
        except C:
            print("Exception: C")
        except B:
            print("Exception: B")
        except:
            print("Exception: all")  
    
    # catch an exception and use it as err variable
    try:
        f = open('myfile.txt')
        s = f.readline()
        i = int(s.strip())
    except OSError as err:
        print("Exception: OS err {0}".format(err))
    except ValueError as err:
        print("Exception: value error {0}".format(err))
    except :
        print("Exception: all")


    # how to use exception err
    try: 
        try:
            raise Exception('spam', 'egg')
        except Exception as err:
            print("---- exception ------")
            print(type(err))
            print(err.args)
            print(err)

            x, y = err.args
            print("x = {0}, y = {1}".format(x, y))

            # raise exception again
            raise
    except:
        print("Exception: catch the embeded exception")
        
    # divide
    divide(1, 0)
    divide(3, 2)   
            
        


if __name__ == "__main__":

    main()