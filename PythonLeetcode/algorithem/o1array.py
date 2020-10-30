
class DataContainer:

    class node:

        def __init__(self, key=float('inf')):
            self._key = key
            self._pre = None
            self._next = None

    def __init__(self):
        self._key = {}
        self._reference = []
        self._head = DataContainer.node()
        self._tail = DataContainer.node()

    def contains(self, k):
        return k in self._key

    def add(self, a):

        if self.containes(a):
            return

        c = DataContainer.node(a)
        self._tail._pre, self._tail._pre._next, c._next, c_pre = c, c, self._tail, self._tail._pre
        self._key[a] = len(self._data)
        self._data.append((a,c))

    def remove(self, b):
        if not self.contains(b):
            return

        idx = self._key[b]
        del self._key[b]

        k, c = self._data[idx]
        self._data[idx] = self._data[-1]
        self._data.pop()
        self._key[self._data[idx][0]] = idx
        c._pre._next, c._next._pre = c._next, c._pre

    def getlast(self):
        return self._tail._pre._key

    def getRamdom(self):
        from random import choice
        return choice(self._data)[0]
