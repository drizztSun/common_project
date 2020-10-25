"""
1206. Design Skiplist

Design a Skiplist without using any built-in libraries.

A Skiplist is a data structure that takes O(log(n)) time to add, erase and search. Comparing with treap and red-black tree which has the same function and performance,
the code length of Skiplist can be comparatively short and the idea behind Skiplists are just simple linked lists.

For example: we have a Skiplist containing [30,40,50,60,70,90] and we want to add 80 and 45 into it. The Skiplist works this way:


Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons

You can see there are many layers in the Skiplist. Each layer is a sorted linked list. With the help of the top layers, add , erase and search can be faster than O(n).
It can be proven that the average time complexity for each operation is O(log(n)) and space complexity is O(n).

To be specific, your design should include these functions:

bool search(int target) : Return whether the target exists in the Skiplist or not.
void add(int num): Insert a value into the SkipList.
bool erase(int num): Remove a value in the Skiplist. If num does not exist in the Skiplist, do nothing and return false. If there exists multiple num values, removing any one of them is fine.
See more about Skiplist : https://en.wikipedia.org/wiki/Skip_list

Note that duplicates may exist in the Skiplist, your code needs to handle this situation.



Example:

Skiplist skiplist = new Skiplist();

skiplist.add(1);
skiplist.add(2);
skiplist.add(3);
skiplist.search(0);   // return false.
skiplist.add(4);
skiplist.search(1);   // return true.
skiplist.erase(0);    // return false, 0 is not in skiplist.
skiplist.erase(1);    // return true.
skiplist.search(1);   // return false, 1 has already been erased.


Constraints:

0 <= num, target <= 20000
At most 50000 calls will be made to search, add, and erase.


"""
import random
import math

class SkiplistII(object):

    class Node:
        __slots__ = 'val', 'levels'

        def __init__(self, val, levels):
            self.val = val
            self.levels = [None] * levels

    def __init__(self):
        self.head = SkiplistII.Node(-1, 16)

    def _iter(self, num):
        cur = self.head
        for level in range(15, -1, -1):
            while True:
                future = cur.levels[level]
                if future and future.val < num:
                    cur = future
                else:
                    break
            yield cur, level

    def search(self, target):
        for prev, level in self._iter(target):
            pass
        cur = prev.levels[0]
        return cur and cur.val == target

    def add(self, num):
        nodelvls = min(16, 1 + int(math.log2(1.0 / random.random())))
        node = SkiplistII.Node(num, nodelvls)

        for cur, level in self._iter(num):
            if level < nodelvls:
                future = cur.levels[level]
                cur.levels[level] = node
                node.levels[level] = future

    def erase(self, num):
        ans = False
        for cur, level in self._iter(num):
            future = cur.levels[level]
            if future and future.val == num:
                ans = True
                cur.levels[level] = future.levels[level]
        return ans


class skipnode:

    def __init__(self, val, level):
        self._val = val
        self._forward = [None] * level

class Skiplist:

    def __init__(self, level = 8):
        self._level = level
        self._head = skipnode(float('-inf'), level=self._level)
        self._size = 0

    def search(self, target: int) -> bool:
        x = self._head
        for i in reversed(range(self._level)):
            while x._forward[i] and x._forward[i].val < target:
                x = x._forward[i]

        return x._forward[0] and x._forward[0]._val == target

    def add(self, num: int) -> None:
        x = self._head
        forwards = [None] * self._level
        for i in reversed(range(self._level)):
            while x._forward[i] and x._forward[i]._val < num:
                x = x._forward[i]
            forwards[i] = x

        if x._forward[0] and x._forward[0]._val == num:
            return

        n = skipnode(num, random.randint(0,self._level))

        for i in range(len(n._forward)):
            forwards[i]._forward[i], n._forward[i] = n, forwards[i]._forward[i]

        self._size += 1

    def erase(self, num: int) -> bool:
        x = self._head
        forwards = [None] * self._level
        for i in reversed(range(self._level)):
            while x._forward[i] and x._forward[i].val < num:
                x = x._forward[i]
            forwards[i] = x

        if x._forward[0] and x._forward[0]._val != num:
            return False

        x = x._forward[0]
        for i in range(len(x._forward)):
            forwards[i]._forward[i] = x._forward[i]

        self._size -= 1


if __name__ == '__main__':

    sl = Skiplist()

    sl.add(1)
    sl.add(2)
    sl.add(3)

    sl.search(0)

    sl.add(4)
    sl.search(1)

    sl.erase()
    sl.erase()

    sl.search()