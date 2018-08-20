import os

# 65. Valid Number
# Validate if a given string is numeric.
# Some examples:
# "0" => true
# " 0.1 " => true
# "abc" => false
# "1 a" => false
# "2e10" => true


class isNumber:
    def doit(self, s):
        """
        :type s: str
        :rtype: bool
        """
        s = s.strip()

        hasnumber, hasE, hasDot, afterE = False, False, False, True
        
        for i, c in enumerate(s):

            if c == 'e':
                if hasE or not hasNum:
                    return False
                hasE = True
                afterE = False
            
            elif c == '.':
                if hasDot or hasE:
                    return True

                hasDot = True

            elif c in ('+', '-'):
                if i-1 >= 0 and s[i-1] != 'e':
                    return False

            elif c.isnumeric():
                hasNum = True
                afterE = True

            else:
                return False
                
        return hasNum and afterE


# I was asked in the interview of linkedIn, writing it directly can be extremely complicated, 
# for there are many special cases we have to deal with, and the code I wrote was messy. 
# Then I failed to pass the interview.
# Here’s a clear solution. With DFA we can easily get our idea into shape and then debug, and the source code is clear and simple.
# DFA        https://en.wikipedia.org/wiki/DFA_minimization


    def doit1(self, s):
        """
        # using DFA
        """
        DFA = [{},
                # State (1) - initial state (scan ahead thru blanks)
               {"blank": 1, "sign": 2, "digit": 3, ".": 4},
                # State (2) - found sign (expect digit/dot)
               {"digit": 3, ".": 4 },
                # State (3) - digit consumer (loop until non-digit)
               {"digit": 3, ".": 5, "e": 6, "blank": 9},
                # State (4) - found dot (only a digit is valid)
               {"digit": 5},
                # State (5) - after dot (expect digits, e, or end of valid input)
               {"digit": 5, "e": 6, "blank": 9},
                # State (6) - found 'e' (only a sign or digit valid)
               {"sign" : 7, "digit": 8},
                # State (7) - sign after 'e' (only digit)
               {"digit": 8 },
                # State (8) - digit after 'e' (expect digits or end of valid input) 
               {"digit": 8, "blank": 9},
                # State (9) - Terminal state (fail if non-blank found)
               {"blank": 9}
              ]
        

        status = 1
        for i, c in enumerate(s):
            id = ''
            if c in ('+', '-'):
                id = 'sign'
            elif c.isnumeric():
                id = 'digit'          
            elif c == ' ':
                id = 'blank'
            else:
                id = c

            if id not in DFA[status].keys():
                return False

            status = DFA[status][id]

        return status in (3, 5, 8, 9)        


    def doit3(self, s):
        """
        """
        pass

        



if __name__=="__main__":

    
    res = isNumber().doit("0")

    res = isNumber().doit("0.1")

    res = isNumber().doit("abc")

    res = isNumber().doit("1 a")

    res = isNumber().doit("2e10")

    res = isNumber().doit(".")

    res = isNumber().doit("  ")

    res = isNumber().doit("-1.")
    
    res = isNumber().doit("+1.")

    res = isNumber().doit("-1.")

    res = isNumber().doit("-1.")

    res = isNumber().doit("6+1") # False

    res = isNumber().doit(" 005047e+6") # True

    res = isNumber().doit(" 005047e-6") # True



    pass
        