


# 341. Flatten Nested List Iterator 

# Given a nested list of integers, implement an iterator to flatten it.

# Each element is either an integer, or a list -- whose elements may also be integers or other lists.

# Example 1:
# Given the list [[1,1],2,[1,1]],

# By calling next repeatedly until hasNext returns false, the order of elements returned by next should 
# be: [1,1,2,1,1].

# Example 2:
# Given the list [1,[4,[6]]],

# By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].



# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
class NestedInteger(object):
    def isInteger(self):
        """
        @return True if this NestedInteger holds a single integer, rather than a nested list.
        :rtype bool
        """

    def getInteger(self):
        """
        @return the single integer that this NestedInteger holds, if it holds a single integer
        Return None if this NestedInteger holds a nested list
        :rtype int
        """

    def getList(self):
        """
        @return the nested list that this NestedInteger holds, if it holds a nested list
        Return None if this NestedInteger holds a single integer
        :rtype List[NestedInteger]
        """

class NestedIterator(object):

    def __init__(self, nestedList):
        """
        Initialize your data structure here.
        :type nestedList: List[NestedInteger]
        """
        self.root_ = nestedList
        self.stk_ = [iter(self.root_)]
        self.current_ = None
        self.curInteger_ = self.getNextOne_()

    def getNextOne_(self):
        
        while self.stk_ or self.current_:
            
            if not self.current_:
                self.current_ = self.stk_.pop()

            try :
                node = next(self.current_)
            except StopIteration:
                self.current_ = None
                continue

            if node.isInteger():
                return node
            else:
                self.stk_.append(self.current_)
                self.current_ = iter(node.getList())
                
        return None
                
    def next(self):
        """
        :rtype: int
        """
        val = self.curInteger_.getInteger()
        self.curInteger_ = self.getNextOne_()

        return val

    def hasNext(self):
        """
        :rtype: bool
        """
        return self.curInteger_


# 
class NestedIterator(object):
    #don't flatten all elements at once 
    #if the next() calls don't use all elements, this method has lower total time complexity
    #be careful of the return type of getList()
    def __init__(self, nestedList):
        """
        Initialize your data structure here.
        :type nestedList: List[NestedInteger]
        """
        self.elems = []
        for i in range(len(nestedList)-1, -1, -1):
            self.elems.append(nestedList[i])
                        
    def next(self):
        """
        :rtype: int
        """
        return self.elems.pop().getInteger()

    def hasNext(self):
        """
        :rtype: bool
        """
        while self.elems:
            if self.elems[-1].isInteger():
                return True
            else:
                currList = self.elems.pop().getList()
                for i in range(len(currList)-1, -1, -1):
                    self.elems.append(currList[i])
        return False


class NestedIterator(object):

    def __init__(self, nestedList):
        """
        Initialize your data structure here.
        :type nestedList: List[NestedInteger]
        """
        self.elems = []
        for c in reversed(nestedList):
            self.elems.append(c)

    def next(self):
        """
        :rtype: int
        """
        return self.elems.pop().getInteger()
        

    def hasNext(self):
        """
        :rtype: bool
        """
        while self.elems:
            if self.elems[-1].isInteger():
                return True
            else:
                first = self.elems.pop().getList()
                for c in reversed(first):
                    self.elems.append(c)
                    
        return False


class NestedIterator(object):

    def __init__(self, nestedList):
        """
        Initialize your data structure here.
        :type nestedList: List[NestedInteger]
        """
        self.stack = nestedList[::-1]
        
    def next(self):
        """
        :rtype: int
        """
        return self.stack.pop().getInteger()
        
    def hasNext(self):
        """
        :rtype: bool
        """
        while self.stack:
            top = self.stack[-1]
            if top.isInteger():
                return True
            self.stack = self.stack[:-1] + top.getList()[::-1]
        return False

if __name__=="__main__":

    # Your NestedIterator object will be instantiated and called as such:
    i, v = NestedIterator(nestedList), []
    while i.hasNext(): 
        v.append(i.next())

    print(v)
    pass