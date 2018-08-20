


# 726. Number of Atoms

# Given a chemical formula (given as a string), return the count of each atom.

# An atomic element always starts with an uppercase character, then zero or more lowercase letters, 
# representing the name.

# 1 or more digits representing the count of that element may follow if the count is greater than 1. 
# If the count is 1, no digits will follow. For example, H2O and H2O2 are possible, but H1O2 is impossible.

# Two formulas concatenated together produce another formula. For example, H2O2He3Mg4 is also a formula.

# A formula placed in parentheses, and a count (optionally added) is also a formula. 
# For example, (H2O2) and (H2O2)3 are formulas.

# Given a formula, output the count of all elements as a string in the following form: 
# the first name (in sorted order), followed by its count (if that count is more than 1), 
# followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.


# Example 1:
# Input: 
# formula = "H2O"
# Output: "H2O"
# Explanation: 
# The count of elements are {'H': 2, 'O': 1}.

# Example 2:
# Input: 
# formula = "Mg(OH)2"
# Output: "H2MgO2"
# Explanation: 
# The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.

# Example 3:
# Input: 
# formula = "K4(ON(SO3)2)2"
# Output: "K4N2O14S4"
# Explanation: 
# The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.


# Note:

# All atom names consist of lowercase letters, except for the first character which is uppercase.
# The length of formula will be in the range [1, 1000].
# formula will only consist of letters, digits, and round parentheses, 
# and is a valid formula as defined in the problem.


import collections

class CountOfAtoms:


# The first regex ([A-Z]{1}[a-z]?|\(|\)|\d+) splits up the input string into a few kinds of tokens for parsing:
# (1) An atom (2) A number (3) Open bracket (4) Closing bracket. These are the only tokens we need to do our parsing.

# An input of Mg(OH)2 will be tokenized into: ['Mg', '(', 'O', 'H', ')', '2'].
# An input of K4(ON(SO3)2)2 will be tokenized into: ['K', '4', '(', 'O', 'N', '(', 'S', 'O', '3', ')', '2', ')', '2'].

# As we iterate through the tokens, there are three cases that we need to handle:

# Open bracket - We push a new dictionary onto a stack to keep track of the atoms and its count in this current group
# Close bracket - The next token might be a number/count. Check whether if it is a count. If it is, multiply all the atoms
# at the top of the stack by the count and combine it with a dictionary below it in the stack.
# Normal atom - The next token might be a number/count. Check whether if it is a count.
# If it is, add that atom and its count to the top of the stack.
# Cases 2 and 3 are very similar, so we can combine them.

# At the end, sort the atoms alphabetically and format them nicely to be returned.

#- Yangshun

    def doit(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        import re
        from collections import defaultdict

        tokens = list(filter(lambda c: c, re.split('([A-Z]{1}[a-z]?|\(|\)|\d+)', formula)))
        stack, i = [defaultdict(int)], 0

        while i < len(tokens):

            token = tokens[i]
            if token == '(':
                stack.append(defaultdict(int))
            else:
                count = 1
                # Check if next token is a number.
                if i + 1 < len(tokens) and re.search('^\d+$', tokens[i + 1]):
                    count, i = int(tokens[i + 1]), i + 1
                atoms = stack.pop() if token == ')' else { token: 1 }
                # Combine counts of atoms.
                for atom in atoms:
                    stack[-1][atom] += atoms[atom] * count

            i += 1

        return ''.join([atom + (str(count) if count > 1 else '') for atom, count in sorted(stack[-1].items())])

    # <>
    def doit(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        formula = '(' + formula + ')'
        stack, i = [], 0
        product = []
        unfolded = ''
        gross = collections.defaultdict(int)

        def generate(content, n):
            
            i, cur, num = 0, '', ''
            buff = product[-1]
            for k in buff.keys():
                buff[k] *= n

            while i < len(content) + 1:
        
                c = content[i] if i < len(content) else ''
                if c.isupper() or i == len(content):
                    if cur != '':
                        base = int(num) if num else 1
                        buff[cur] += base * n
                    cur = c
                    num = ''
                elif c.islower():
                    cur += c
                elif c.isdigit:
                    num += c

                i += 1

            return buff


        while i < len(formula):
            c = formula[i]
            if c == '(':
                stack.append('')
                product.append(collections.defaultdict(int))

            elif c == ')':
                j = i+1
                while j < len(formula) and formula[j].isdigit():
                    j += 1
                n = 1 if j == i+1 else int(formula[i+1:j])

                generate(stack.pop(), n)
                local = product.pop()
                if product:
                    for k in local.keys():
                        product[-1][k] += local[k]
                else:
                    gross = local

                i = j-1
            else:
                stack[-1] += c

            i += 1
            
        res = ''
        for key in sorted(gross.keys()):
            res += key + (str(gross[key]) if gross[key] > 1 else '')

        return res 
        

    # <TLE:
    
    def doit1(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        formula = '(' + formula + ')'
        stack, i = [], 0
        unfolded = ''

        while i < len(formula):
            c = formula[i]
            if c == '(':
                stack.append('')
            elif c == ')':
                j = i+1
                while j < len(formula) and formula[j].isdigit():
                    j += 1
                n = 1 if j == i+1 else int(formula[i+1:j])
                unfolded = stack.pop()
                if stack:
                    stack[-1] += unfolded * n                              
                i = j-1
            else:
                stack[-1] += c

            i += 1

        buff = collections.defaultdict(int)
        i, cur, num = 0, '', ''
        while i < len(unfolded) + 1:
        
            c = unfolded[i] if i < len(unfolded) else ''

            if c.isupper() or i == len(unfolded):
                if cur != '':
                    buff[cur] += int(num) if num else 1
                cur = c
                num = ''
            elif c.islower():
                cur += c
            elif c.isdigit:
                num += c

            i += 1
    
        res = ''
        for key in sorted(buff.keys()):
            res += key + (str(buff[key]) if buff[key] > 1 else '')

        return res

if __name__ == "__main__":


    res = CountOfAtoms().doit("K4(ON(SO3)2)2")

    res = CountOfAtoms().doit("Mg(OH)2")

    res = CountOfAtoms().doit("H2O")


    
    # "B18900Be18984C4200H5446He1386Li33894N50106O22638" # "B93145920Be2345280C3178560H992320He6985440Li75657120N2412328800O114095520"
    res = CountOfAtoms().doit("((N42)24(OB40Li30CHe3O48LiNN26)33(C12Li48N30H13HBe31)21(BHN30Li26BCBe47N40)15(H5)16)14")

    res = CountOfAtoms().doit("(((U42Se42Fe10Mc31Rh49Pu49Sb49)49V39Tm50Zr44Og6)33((W2Ga48Tm14Eu46Mt12)23(RuRnMn11)7(Yb15Lu34Ra19CuTb2)47(Md38BhCu48Db15Hf12Ir40)7CdNi21(Db40Zr24Tc27SrBk46Es41DsI37Np9Lu16)46(Zn49Ho19RhClF9Tb30SiCuYb16)15)37(Cr48(Ni31)25(La8Ti17Rn6Ce35)36(Sg42Ts32Ca)37Tl6Nb47Rh32NdGa18Cm10Pt49(Ar37RuSb30Cm32Rf28B39Re7F36In19Zn50)46)38(Rh19Md23No22PoTl35Pd35Hg)41)50")

    pass