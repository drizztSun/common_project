


# 385. Mini Parser

# Given a nested list of integers represented as a string, implement a parser to deserialize it.

# Each element is either an integer, or a list -- whose elements may also be integers or other lists.

# Note: You may assume that the string is well-formed:

# String is non-empty.
# String does not contain white spaces.
# String contains only digits 0-9, [, - ,, ].

# Example 1:

# Given s = "324",

# You should return a NestedInteger object which contains a single integer 324.

# Example 2:

# Given s = "[123,[456,[789]]]",

# Return a NestedInteger object containing a nested list with 2 elements:

# 1. An integer containing value 123.
# 2. A nested list containing two elements:
#    i.  An integer containing value 456.
#    ii. A nested list with one element:
#         a. An integer containing value 789.

# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """


class NestedInteger(object):
    def __init__(self, value=None):
        """
        If value is not specified, initializes an empty list.
        Otherwise initializes a single integer equal to value.
        """
        if value:
            self.val_ = int(value)
        self.nestedNI_ = []

    def isInteger(self):
        """
        @return True if this NestedInteger holds a single integer, rather than a nested list.
        :rtype bool
        """
        return len(self.nestedNI_)

    def add(self, elem):
        """
        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
        :rtype void
        """
        self.nestedNI_.append(elem)        

    def setInteger(self, value):
        """
        Set this NestedInteger to hold a single integer equal to value.
        :rtype void
        """
        self.val_ = value

    def getInteger(self):
        """
        @return the single integer that this NestedInteger holds, if it holds a single integer
        Return None if this NestedInteger holds a nested list
        :rtype int
        """
        return self.val_

    def getList(self):
        """
        @return the nested list that this NestedInteger holds, if it holds a nested list
        Return None if this NestedInteger holds a single integer
        :rtype List[NestedInteger]
        """
        return None if not self.nestedNI_ else self.nestedNI_


class MiniParserdeserialize(object):
    def doit(self, s):
        """
        :type s: str
        :rtype: NestedInteger
        """
        stack = []
        num = ''
        current = None
        for c in s:

            if c.isdigit() or c in ('+', '-'):
                num += c

            elif c == '[':
                stack.append(NestedInteger())

            elif c == ',':
                if num :
                    stack[-1].add(NestedInteger(num))
                num = ''

            elif c == ']':
                current = stack.pop()

                if num:
                    current.add(NestedInteger(num))
                    num = ''

                if stack:
                   stack[-1].add(current)

        if num and not current:
            current = NestedInteger(int(num))

        return current


    def doit1(self, s):
        """
        :type s: str
        :rtype: NestedInteger
        """
        return eval(s)


class Solution:
    def deserialize(self, s):
        """
        :type s: str
        :rtype: NestedInteger
        """
        def nestedInteger(x):
            if isinstance(x, int):
                return NestedInteger(x)
            else:
                lst = NestedInteger()
                for y in x:
                    lst.add(nestedInteger(y))
                return lst
        return nestedInteger(eval(s))


class Solution:
    def deserialize(self, s):
        n, i = self.parse(s, 0)
        
        assert i == len(s)
        
        return n
        
    def parse(self, s, i):
        assert i < len(s)
        
        if s[i].isdigit() or s[i] == '-':
            return self.parseInt(s, i)
        else:
            return self.parseList(s, i)
        
    def parseInt(self, s, i):
        assert i < len(s) and (s[i].isdigit() or s[i] == '-')
        
        sign = 1
        
        if s[i] == '-':
            sign = -1
            i += 1
        
        j = i + 1
        while j < len(s) and s[j].isdigit():
            j += 1
        
        return NestedInteger(sign * int(s[i:j])), j
        
    def parseList(self, s, i):
        assert i < len(s) and s[i] == '['
        
        i += 1
        n = NestedInteger()
        
        while s[i] != ']':
            x, i = self.parse(s, i)
            
            assert i < len(s)
            
            n.add(x.getInteger() if x.isInteger() else x.getList())
            
            if s[i] == ',':
                i += 1
                
        return n, i + 1

class Solution:
    def deserialize(self, s):
        """
        :type s: str
        :rtype: NestedInteger
        """
        if s[0] == '[':
            i, ans = self.parse(s, 1)
        else:
            i, ans = self.parse(s, 0)
        return ans
    
    def parse(self, s, i):
        buf = []
        list_ = NestedInteger()
        while i < len(s):
            if s[i] == '[':
                i, retVal = self.parse(s, i + 1)
                list_.add(retVal)
            elif s[i] == ',':
                if len(buf) > 0:
                    list_.add(int(''.join(buf)))
                    buf = []
            elif s[i] == ']':
                if len(buf) > 0:
                    list_.add(int(''.join(buf)))
                return i, list_
            else:
                buf.append(s[i])
            i = i + 1
        
        if len(buf) > 0:
            list_.setInteger(int(''.join(buf)))
        return i, list_


if __name__=="__main__":

    res = MiniParserdeserialize().doit("[]")

    res = MiniParserdeserialize().doit("[-1]")

    res = MiniParserdeserialize().doit("123")

    res = MiniParserdeserialize().doit("[123,[456,[789]]]")

    res = MiniParserdeserialize().doit("[123,456,[788,799,833],[[]],10,[]]")

    pass