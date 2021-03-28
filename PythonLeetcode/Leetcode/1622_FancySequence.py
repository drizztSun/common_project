"""
1622. Fancy Sequence

Write an API that generates fancy sequences using the append, addAll, and multAll operations.

Implement the Fancy class:

Fancy() Initializes the object with an empty sequence.
void append(val) Appends an integer val to the end of the sequence.
void addAll(inc) Increments all existing values in the sequence by an integer inc.
void multAll(m) Multiplies all existing values in the sequence by an integer m.
int getIndex(idx) Gets the current value at index idx (0-indexed) of the sequence modulo 109 + 7. If the index is greater or equal than the length of the sequence, return -1.


Example 1:

Input
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
Output
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]

Explanation
Fancy fancy = new Fancy();
fancy.append(2);   // fancy sequence: [2]
fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
fancy.append(7);   // fancy sequence: [5, 7]
fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // return 10
fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
fancy.append(10);  // fancy sequence: [13, 17, 10]
fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // return 26
fancy.getIndex(1); // return 34
fancy.getIndex(2); // return 20


Constraints:

1 <= val, inc, m <= 100
0 <= idx <= 10^5
At most 105 calls total will be made to append, addAll, multAll, and getIndex.

"""

"""
Explanation
Count the prefix sum add of addAll
Count the prefix mul mul of mulAll


Complexity
Time O(1) for all
Space O(N)

"""
class Fancy(object):

    def __init__(self):
        self.A = []
        self.add = [0]
        self.mul = [1]

    def append(self, a):
        self.A.append(a)
        self.add.append(self.add[-1])
        self.mul.append(self.mul[-1])

    def addAll(self, inc):
        self.add[-1] += inc

    def multAll(self, m):
        self.add[-1] = self.add[-1] * m % (10 ** 9 + 7)
        self.mul[-1] = self.mul[-1] * m % (10 ** 9 + 7)

    def getIndex(self, i):
        if i >= len(self.A): return -1
        mod = 10 ** 9 + 7
        m = self.mul[-1] * pow(self.mul[i], mod - 2, mod) 
        inc = self.add[-1] - self.add[i] * m
        return (self.A[i] * m + inc) % mod


"""
Instead of adding to or multiplying all the values, add to or multiply a transformation function, and apply that transformation only when a value is requested with getIndex.

Since we only add and multiply, the transformation is a linear function x ↦ ax + b, defined by a and b. When we add, we change it to (ax + b) + inc = ax + (b+inc), i.e., we just add inc to b. 
When we multiply, we change it to (ax + b) * m = (am)x + (bm), i.e., we multiply both a and b by m.

Then getIndex(i) applies the transformation, i.e., returns a * x[i] + b. But wait, if we just appended some value val and then immediately request it with getIndex, won't the transformation distort it? 
Yes, which is why we don't store val as-is. Instead we apply the inverse of the current transformation and store the result of that as x. 
Then whengetIndex applies the transformation, we get the correct val. 
In other words, when we shall append val, we store an x such that ax + b = val. That is, we store x = (val - b) * a**-1. 
Conveniently, Python's pow does support negative exponents. And that appears to be 2-3 times faster than using exponent p-2 based on Fermat, see my comment with benchmarks.
"""


class FancySequence:

    def __init__(self):
        self._datas = []
        self._m = 1
        self._a = 0
        self._hmod = 10 ** 9 + 7

    def append(self, val: int) -> None:
        from math import pow
        self._datas.append((val - self._a) * pow(self._m, -1, self._hmod))

    def addAll(self, inc: int) -> None:
        self._a += inc

    def multAll(self, m: int) -> None:
        self._m *= m % self._hmod
        self._a *= m % self._hmod

    def getIndex(self, idx: int) -> int:
        if idx >= len(self._datas):
            return -1
        return (self._datas[idx] * self._m + self._a) % self._hmod


"""
Solution 2: Faster
While pow(a, -1, p) is decently fast (and faster than pow(a, p-2, p)), it is slower than just a multiplication. 
Since the multiplier m is guaranteed to be 1 to 100, we can just compute the inverses of 1 to 100 once, 
and use them to update the inverse of a which we keep around as well. Got "760 ms, faster than 100.00%".
"""


class FancySequenceII:

    def __init__(self):
        self.x = []
        self.a = 1
        self.ainv = 1
        self.b = 0
        self.p = 10 ** 9 + 7
        self.inv = [None] + [pow(m, -1, self.p) for m in range(1, 101)]

    def append(self, val):
        self.x.append((val - self.b) * self.ainv)

    def addAll(self, inc):
        self.b += inc

    def multAll(self, m):
        self.a = self.a * m % self.p
        self.ainv = self.ainv * self.inv[m] % self.p
        self.b = self.b * m % self.p

    def getIndex(self, idx):
        if idx >= len(self.x):
            return -1
        return (self.a * self.x[idx] + self.b) % self.p


"""
Solution 3: Encapsulate the modulo
Encapsulates the whole modulo stuff, so that the actual solution becomes nicer. The name Zp really means Z/pZ, but that's not a valid class name. 
Despite the overhead, still got "1196 ms, faster than 35.50%".
"""


class Zp(int):
    p = 10**9 + 7
    def __add__(self, other): return Zp((int(self) + int(other)) % self.p)
    def __sub__(self, other): return Zp((int(self) - int(other)) % self.p)
    def __mul__(self, other): return Zp(int(self) * int(other) % self.p)
    def __truediv__(self, other): return self * Zp(pow(int(other), -1, self.p))
    def __radd__(self, other): return Zp(other) + self
    def __rsub__(self, other): return Zp(other) - self
    def __rmul__(self, other): return Zp(other) * self
    def __rtruediv__(self, other): return Zp(other) / self


class FancySequenceIII:

    def __init__(self):
        self.x = []
        self.a = Zp(1)
        self.b = Zp(0)

    def append(self, val):
        self.x.append((val - self.b) / self.a)

    def addAll(self, inc):
        self.b += inc

    def multAll(self, m):
        self.a *= m
        self.b *= m

    def getIndex(self, idx):
        if idx >= len(self.x):
            return -1
        return self.a * self.x[idx] + self.b