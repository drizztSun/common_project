# 770. Basic Calculator IV

# Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1}
# (given in terms of evalvars = ["e"] and evalints = [1]),
# return a list of tokens representing the simplified expression, such as ["-1*a","14"]

# An expression alternates chunks and symbols, with a space separating each chunk and symbol.
# A chunk is either an expression in parentheses, a variable, or a non-negative integer.
# A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters,
# and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
# Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction.
# For example, expression = "1 + 2 * 3" has an answer of ["7"].

# The format of the output is as follows:

# For each term of free variables with non-zero coefficient,
# we write the free variables within a term in sorted order lexicographically.
# For example, we would never write a term like "b*a*c", only "a*b*c".

# Terms have degree equal to the number of free variables being multiplied, counting multiplicity.
# (For example, "a*a*b*c" has degree 4.)
# We write the largest degree terms of our answer first,
# breaking ties by lexicographic order ignoring the leading coefficient of the term.
# The leading coefficient of the term is placed directly to the left
# with an asterisk separating it from the variables (if they exist.)
# A leading coefficient of 1 is still printed.

# An example of a well formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"]
# Terms (including constant terms) with coefficient 0 are not included.
# For example, an expression of "0" has an output of [].

# Examples:

# Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
# Output: ["-1*a","14"]

# Input: expression = "e - 8 + temperature - pressure",
# evalvars = ["e", "temperature"], evalints = [1, 12]
# Output: ["-1*pressure","5"]

# Input: expression = "(e + 8) * (e - 8)", evalvars = [], evalints = []
# Output: ["1*e*e","-64"]

# Input: expression = "7 - 7", evalvars = [], evalints = []
# Output: []

# Input: expression = "a * b * c + b * a * c * 4", evalvars = [], evalints = []
# Output: ["5*a*b*c"]

# Input: expression = "((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))",
# evalvars = [], evalints = []
# Output: ["-1*a*a*b*b","2*a*a*b*c","-1*a*a*c*c","1*a*b*b*b","-1*a*b*b*c","-1*a*b*c*c","1*a*c*c*c","-1*b*b*b*c",
# "2*b*b*c*c","-1*b*c*c*c","2*a*a*b","-2*a*a*c","-2*a*b*b","2*a*c*c","1*b*b*b","-1*b*b*c","1*b*c*c","-1*c*c*c","-1*a*a","1*a*b","1*a*c","-1*b*c"]
# Note:

# expression will have length in range [1, 250].
# evalvars, evalints will have equal lengths in range [0, 100].

import re


class BasicCalculatorIV:
    def doit(self, expression, evalvars, evalints):
        """
        :type expression: str
        :type evalvars: List[str]
        :type evalints: List[int]
        :rtype: List[str]
        """
        def calculate(a, b, op):

            if op in ('+', '-'):
                ng = 1 if op == '+' else -1
                for k, v in b.items():
                    a[k] = a.get(k, 0) + v * ng
                return a

            elif op == '*':
                v = {}
                for k1, v1 in a.items():
                    for k2, v2 in b.items():
                        key = tuple(sorted(k1 + k2))
                        v[key] = v.get(key, 0) + v1 * v2
                return v

        vars = {evalvars[i]: evalints[i] for i in range(len(evalvars))}
        d = []  # operand
        op = []
        priority = {'(': 0, '+': 1, '-': 1, '*': 2}

        for t in re.findall(r'\(|\)|[a-z]+|[0-9]+|[\+\-\*]', expression):

            if t[0].isdigit():
                d.append({tuple(): int(t)})

            elif t[0].isalpha():
                if t in vars:
                    d.append({tuple(): vars[t]})
                else:
                    d.append({(t,): 1})

            elif t == '(':
                op.append(t)

            elif t == ')':
                while op and op[-1] != '(':
                    d.append(calculate(d.pop(-2), d.pop(-1), op.pop()))
                op.pop()

            elif t in ('+', '-', '*'):
                if not op or priority[t] > priority[op[-1]]:
                    op.append(t)
                else:
                    while op and priority[t] <= priority[op[-1]]:
                        d.append(calculate(d.pop(-2), d.pop(-1), op.pop()))
                    op.append(t)

        while op:
            d.append(calculate(d.pop(-2), d.pop(-1), op.pop()))

        res = []
        for x in sorted(d[0].keys(), key=lambda x: (-len(x), x)):
            v = d[0][x]
            if v != 0:
                if not x:
                    res.append(v)
                else:
                    res.append('%s*%s' % (v, '*'.join(x)))

        return res


class Solution:

    def calc(self, a, b, op):
        if op == '+':
            for k, v in b.items():
                a[k] = a.get(k, 0) + v
            return a
        elif op == '-':
            for k, v in b.items():
                a[k] = a.get(k, 0) - v
            return a
        elif op == '*':
            t = {}
            for k1, v1 in a.items():
                for k2, v2 in b.items():
                    newk = tuple(sorted(k1+k2))
                    t[newk] = t.get(newk, 0) + v1 * v2
            return t

    def basicCalculatorIV(self, expression, evalvars, evalints):
        vars = {n:v for n,v in zip(evalvars, evalints)}
        d = []  # operands
        op = []
        priority = {'(': 0, '+': 1, '-': 1, '*': 2}
        for t in re.findall(r'\(|\)|[a-z]+|[0-9]+|[\+\-\*]', expression):
            if t[0].isdigit():
                d.append({tuple():int(t)})
            elif t[0].isalpha():
                if t in vars:
                    d.append({tuple(): vars[t]})
                else:
                    d.append({(t,): 1})
            elif t == '(':
                op.append(t)
            elif t == ')':
                while op and op[-1] != '(':
                    d.append(self.calc(d.pop(-2), d.pop(-1), op.pop()))
                op.pop()
            elif t in '+-*':
                if not op or priority[t] > priority[op[-1]]:
                    op.append(t)
                else:
                    while op and priority[t] <= priority[op[-1]]:
                        d.append(self.calc(d.pop(-2), d.pop(-1), op.pop()))
                    op.append(t)
        while op:
            d.append(self.calc(d.pop(-2), d.pop(-1), op.pop()))

        res = []
        for k in sorted(d[0].keys(), key=lambda x: (-len(x), x)):
            v = d[0][k]
            if v != 0:
                if not k:
                    res.append(str(v))
                else:
                    res.append('%s*%s' % (v, '*'.join(k)))
        return res


if __name__ == "__main__":

    res = Solution().basicCalculatorIV("e + 8 - a + 5", ["e"], [1])

    res = BasicCalculatorIV().doit("e + 8 - a + 5", ["e"], [1])

    res = BasicCalculatorIV().doit("e - 8 + temperature - pressure", ["e", "temperature"], [1, 12]) # ["-1*pressure","5"]

    res = BasicCalculatorIV().doit("(e + 8) * (e - 8)", [], [])  # ["1*e*e","-64"]

    res = BasicCalculatorIV().doit("7 - 7", [], [])  # []

    res = BasicCalculatorIV().doit("a * b * c + b * a * c * 4", [], []) # ["5*a*b*c"]

    res = BasicCalculatorIV().doit("((a - b) * (b - c) + (c - a)) * ((a - b) + (b - c) * (c - a))", [], [])

    pass