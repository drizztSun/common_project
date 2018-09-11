# 640. Solve the Equation

# Solve a given equation and return the value of x in the form of string "x=#value". 
# The equation contains only '+', '-' operation, the variable x and its coefficient.

# If there is no solution for the equation, return "No solution".

# If there are infinite solutions for the equation, return "Infinite solutions".

# If there is exactly one solution for the equation, we ensure that the value of x is an integer.

# Example 1:
# Input: "x+5-3+x=6+x-2"
# Output: "x=2"

# Example 2:
# Input: "x=x"
# Output: "Infinite solutions"

# Example 3:
# Input: "2x=x"
# Output: "x=0"

# Example 4:
# Input: "2x+3x-6x=x+2"
# Output: "x=-1"

# Example 5:
# Input: "x=x+2"
# Output: "No solution"

class SolveEquation:
    def doit(self, equation):
        """
        :type equation: str
        :rtype: str
        """
        left, right = tuple(equation.split('='))

        def argparse(st):
            i = 0
            cur_num, cur_para = 0, 0
            end, sigal = False, 1

            while i < len(st) and not end:
                j = i                 
                while j < len(st) and (j == 0 or st[j] not in ('+', '-')):
                    j += 1

                next, old = st[i:j], sigal
                if j == len(st):
                    end = True
                else:
                    sigal = -1 if st[j] == '-' else 1

                if next[-1] == 'x':
                    if next == 'x':
                        next = '1x'
                    elif next == '-x':
                        next = '-1x'
                    cur_para += old * int(next[:-1])
                else:
                    cur_num += old * int(next)

                i = j + 1

            return cur_para, cur_num

        left_para, left_num = argparse(left)
        right_para, right_num = argparse(right)
        total_para = left_para - right_para
        total_num =  right_num - left_num

        if total_para == 0 and total_num == 0:
            return "Infinite solutions"
        elif total_para == 0 and total_num != 0:
            return "No solution"
        else:
            return total_num // total_para
        

if __name__ == "__main__":

    res = SolveEquation().doit("-x=-1")

    res = SolveEquation().doit("x+5-3+x=6+x-2")

    res = SolveEquation().doit("x=x")

    res = SolveEquation().doit("2x=x")

    res = SolveEquation().doit("2x+3x-6x=x+2")

    res = SolveEquation().doit("x=x+6")

    res = 1        

