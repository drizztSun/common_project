import sys

def divide(x, y):
    
    try:
        result = x / y

        # when division exception happend, below code won't happen
        print("division error not happened")

    except ZeroDivisionError:
        # hanlde exception
        print("division by zero !")
    else:
        # No exception, then go else
        print("result is ", result)
    finally:
        # no matter expcetion happened, it goes to finally, 
        print("executing finally clause")

# User-Defined Exceptions
class Error(Exception):
    """basic defination of customer exception"""
    pass

class InputEror(Error):
    """Exception raised for errors in the input.

    Attributes:
        expression -- input expression in which the error occurred
        message -- explanation of the error
    """

    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

class TransitionEror(Error):

    """Raised when an operation attempts a state transition that's not
    allowed.

    Attributes:
        previous -- state at beginning of transition
        next -- attempted new state
        message -- explanation of why the specific transition is not allowed
    """

    def __init__(self, previous, next, message):
        self.previous = previous
        self.next = next
        self.message = message

class B(Exception):
    pass

class C(B):
    pass

class D(C):
    pass

def test_handle_exception():

# The try statement works as follows.

# First, the try clause (the statement(s) between the try and except keywords) is executed.

# If no exception occurs, the except clause is skipped and execution of the try statement is finished.

# If an exception occurs during execution of the try clause, the rest of the clause is skipped. 
# Then if its type matches the exception named after the except keyword, the except clause is executed, 
# and then execution continues after the try statement.

# If an exception occurs which does not match the exception named in the except clause, 
# it is passed on to outer try statements; if no handler is found, it is an unhandled exception and execution stops with a message as shown above.

# A try statement may have more than one except clause, to specify handlers for different exceptions. 
# At most one handler will be executed. Handlers only handle exceptions that occur in the corresponding try clause, not in other handlers of the same try statement. An except clause may name multiple exceptions as a parenthesized tuple, for example:

    try:
        raise Exception('spam', 'egg')
    except Exception as e:

        print(type(e))
        print(e.args)
        print(e)

        x, y = e.args
        print('x = ', x)
        print('y = ', y)

    # An except clause may name multiple exceptions as a parenthesized tuple
    except (RuntimeError, TypeError, NameError):
        pass


    divide(2, 1)

    divide(2, 0)

    # A class in an except clause is compatible with an exception 
    # if it is the same class or a base class thereof (but not the other way around — 
    # an except clause listing a derived class is not compatible with a base class). 
    # For example, the following code will print B, C, D in that order:
    for cls in [B, C, D]:
        try:
            raise cls()
        except D:
            print("D")
        except C:
            print("C")
        except B:
            print("B")
    # Note that if the except clauses were reversed (with except B first), 
    # it would have printed B, B, B — the first matching except clause is triggered.


    try:
        f = open('myfile.txt')
        s = f.readline()
        i = int(s.strip())
    except OSError as err:
        print("OS error: {0}".format(err))
    except ValueError:
        print("Could not convert data to an integer.")
    except:
        print("Unexpected error:", sys.exc_info()[0])
        # rasie the exception again
        raise 
    else:
        print("No Exception happens")
        f.close()


if __name__ == "__main__":

    test_handle_exception()