"""
341. Flatten Nested List Iterator

Given a nested list of integers, implement an iterator to flatten it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Example 1:

Input: [[1,1],2,[1,1]]
Output: [1,1,2,1,1]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,1,2,1,1].
Example 2:

Input: [1,[4,[6]]]
Output: [1,4,6]
Explanation: By calling next repeatedly until hasNext returns false,
             the order of elements returned by next should be: [1,4,6].

"""


# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def isInteger(self) -> bool:
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        """
#
#    def getInteger(self) -> int:
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        """
#
#    def getList(self) -> [NestedInteger]:
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        """


class NestedIterator:

    def __init__(self, nestedList):
        self._buf = []
        for i in reversed(range(len(nestedList))):
            self._buf.append(nestedList[i])

    def next(self):
        return self._buf.pop().getInteger()

    def hasNext(self):

        while self._buf:

            if self._buf[-1].isInteger():
                return True

            newlist = self._buf.pop().getList()
            for i in reversed(range(len(newlist))):
                self._buf.append(newlist[i])

        return False


class NestedIterator:

    def __init__(self, nestedList):
        for i in reversed(range(len(nestedList))):
            self._buf.append(nestedList[i])

    def next(self):
        return self._buf[-1].pop().getInteger()

    def hasNext(self):

        while self._buf:
            index = self._buf[-1][1]
            if index == len(self._buf[-1]):
                self._buf.pop()

            if self._buf[-1][index].isInteger():
                return True
            else:
                self._buf[-1][1] += 1
                self._buf.append((self._buf[-1][0][index], 0))

        return False
