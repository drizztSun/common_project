
"""
CPython implementation detail: In CPython, due to the Global Interpreter Lock, only one thread can execute Python code at once (even though certain performance-oriented libraries might overcome this limitation).

If you want your application to make better use of the computational resources of multi-core machines, you are advised to use multiprocessing or concurrent.futures.ProcessPoolExecutor.

However, threading is still an appropriate model if you want to run multiple I/O-bound tasks simultaneously.


Lock Objects

A primitive lock is a synchronization primitive that is not owned by a particular thread when locked. In Python, it is currently the lowest level synchronization primitive available, implemented directly by the _thread extension module.

A primitive lock is in one of two states, “locked” or “unlocked”. It is created in the unlocked state. It has two basic methods, acquire() and release().

When the state is unlocked, acquire() changes the state to locked and returns immediately.

When the state is locked, acquire() blocks until a call to release() in another thread changes it to unlocked, then the acquire() call resets it to locked and returns.

The release() method should only be called in the locked state; it changes the state to unlocked and returns immediately. If an attempt is made to release an unlocked lock, a RuntimeError will be raised.

"""

import threading


def printFirst():
    print("First")


def printSecond():
    print("Second")


def printThird():
    print("Third")


class Printer:
    def __init__(self):
        self._lock = threading.Lock()

    def first(self, printFirst):
        self._lock.acquire()
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self._lock.release()

    def second(self, printSecond):
        self._lock.acquire()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self._lock.release()

    def third(self, printThird):
        self._lock.acquire()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()
        self._lock.release()


class Consumer(threading.Thread):

    def __init__(self, i, printer, printfunc):
        self._printer = printer
        self._printfunc = printfunc
        self._index = i

    def run(self):

        for _ in range(10):
            if self._index == 1:
                self._printer.first(self._printfunc)
            elif self._index == 2:
                self._printer.second(self._printfunc)
            elif self._index == 3:
                self._printer.third(self._printfunc)
            else:
                raise 1


if __name__ == '__main__':

    A = Printer()
    th = []

    for i, c in enumerate(len([printFirst, printSecond, printThird])):
        th.append(Consumer(i+1, A, c))

    for i in range(3):
        th[i].start()

    for i in range(3):
        th[i].join()
