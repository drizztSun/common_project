"""
1116. Print Zero Even Odd


Suppose you are given the following code:

class ZeroEvenOdd {
  public ZeroEvenOdd(int n) { ... }      // constructor
  public void zero(printNumber) { ... }  // only output 0's
  public void even(printNumber) { ... }  // only output even numbers
  public void odd(printNumber) { ... }   // only output odd numbers
}
The same instance of ZeroEvenOdd will be passed to three different threads:

Thread A will call zero() which should only output 0's.
Thread B will call even() which should only ouput even numbers.
Thread C will call odd() which should only output odd numbers.
Each of the threads is given a printNumber method to output an integer. Modify the given program to output the series 010203040506... where the length of the series must be 2n.

 

Example 1:

Input: n = 2
Output: "0102"
Explanation: There are three threads being fired asynchronously. One of them calls zero(), the other calls even(), and the last one calls odd(). "0102" is the correct output.
Example 2:

Input: n = 5
Output: "0102030405"


"""


from threading import Lock, Semaphore

class ZeroEvenOdd:
    def __init__(self, n):
        self._n = n
        self._zerolock = Lock()
        self._evenlock = Lock()
        self._oddlock = Lock()
        
        self._evenlock.acquire()
        self._oddlock.acquire()
        
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        
        for i in range(1, self._n+1):
            
            self._zerolock.acquire()
            printNumber(0)
            
            if i % 2 == 0:
                self._evenlock.release()
            else:
                self._oddlock.release()
            
            
            
        
    def even(self, printNumber: 'Callable[[int], None]') -> None:
        
        for i in range(2, self._n+1, 2):
            self._evenlock.acquire()
            printNumber(i)
            self._zerolock.release()
        self._evenlock.release()
            
            
        
    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        
        for i in range(1, self._n+1, 2):
            self._oddlock.acquire()
            printNumber(i)
            self._zerolock.release()
        self._oddlock.release()


class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.num = 0
        self.evenSem = Semaphore(0)
        self.oddSem = Semaphore(0)
        self.zeroSem = Semaphore(1)
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber):
        """
        :type printNumber: method
        :rtype: void
        """
        parity = True
        for i in range(self.n):
            self.zeroSem.acquire()  
            
            printNumber(0)  
            
            parity = not parity
            self.num += 1
            
            if parity:
                self.evenSem.release()
            else:
                self.oddSem.release()
        
        self.evenSem.release()
        self.oddSem.release()
        
    def even(self, printNumber):
        """
        :type printNumber: method
        :rtype: void
        """
        while True:
            self.evenSem.acquire()
            shouldExit = self.num >= self.n - self.n % 2
            if self.num % 2 == 0 and self.num <= self.n:
                printNumber(self.num)
            self.zeroSem.release()
            if shouldExit: break
        
    def odd(self, printNumber):
        """
        :type printNumber: method
        :rtype: void
        """
        while True:
            self.oddSem.acquire()
            shouldExit = self.num >= self.n - (1 - self.n % 2)
            if self.num % 2 == 1 and self.num <= self.n:
                printNumber(self.num)
            self.zeroSem.release()
            if shouldExit: break