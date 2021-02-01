/*
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

*/
#include <functional>
#include <condition_variable>
#include <mutex>

using std::mutex;
using std::condition_variable;
using std::function;
using std::unique_lock;


#include<semaphore.h>


class ZeroEvenOdd {

protected:
    sem_t sem_z;
    sem_t sem_e;
    sem_t sem_o;

private:
    int n;

public:

    ZeroEvenOdd(int n) {
        this->n = n;
        sem_init(&sem_z, 0 ,1);
        sem_init(&sem_o, 0 ,0);
        sem_init(&sem_e, 0 ,0);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i++) {
            sem_wait(&sem_z);
            printNumber(0);
            if (i%2 == 0)
                sem_post(&sem_e);
            else
                sem_post(&sem_o);
        }
    }

    void even(function<void(int)> printNumber) {
        for (int i = 2; i <= n; i+= 2) {
            sem_wait(&sem_e);
            printNumber(i);
            sem_post(&sem_z);
        }
    }

    void odd(function<void(int)> printNumber) {
        for (int i = 1; i <= n; i+= 2) {
            sem_wait(&sem_o);
            printNumber(i);
            sem_post(&sem_z);
        }
    }
};


class ZeroEvenOdd {

private:
    int n;
    int count;
    int output;
    mutex m;
    condition_variable cv;
public:
    ZeroEvenOdd(int n) {
        this->n = 2*n;
        count = 0;
        output = 1;
    }

    void zero(function<void(int)> printNumber) {
        unique_lock<mutex> l(m);
        while(1)
        {
            cv.wait(l,[&](){return (count%2 == 0 || count > n-1);});
            if(count > n-1)
                break;
            printNumber(0);
            ++count;
            cv.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        unique_lock<mutex> l(m);
        while(1)
        {
            cv.wait(l,[&](){return ((count%2 == 1 && output%2 == 0) || count > n-1);});
            if(count > n-1)
                break;
            printNumber(output);
            ++count;
            ++output;
            cv.notify_all();
        }    
    }

    void odd(function<void(int)> printNumber) {
        unique_lock<mutex> l(m);
        while(1)
        {
            cv.wait(l,[&](){return ((count%2 == 1 && output%2 == 1) || count > n-1);});
            if(count > n-1)
                break;
            printNumber(output);
            ++count;
            ++output;
            cv.notify_all();
        }   
    }
};