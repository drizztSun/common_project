
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
        raise Exception('spam', 'egg')
    except Exception as err:
        print("---- exception ------")
        print(type(err))
        print(err.args)
        print(err)

        x, y = err.args
        print("x = {0}, y = {1}".format(x, y))
        
            
        


if __name__ == "__main__":

    main()