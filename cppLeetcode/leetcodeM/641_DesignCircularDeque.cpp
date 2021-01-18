/*
641. Design Circular Deque


Design your implementation of the circular double-ended queue (deque).

Your implementation should support following operations:

MyCircularDeque(k): Constructor, set the size of the deque to be k.
insertFront(): Adds an item at the front of Deque. Return true if the operation is successful.
insertLast(): Adds an item at the rear of Deque. Return true if the operation is successful.
deleteFront(): Deletes an item from the front of Deque. Return true if the operation is successful.
deleteLast(): Deletes an item from the rear of Deque. Return true if the operation is successful.
getFront(): Gets the front item from the Deque. If the deque is empty, return -1.
getRear(): Gets the last item from Deque. If the deque is empty, return -1.
isEmpty(): Checks whether Deque is empty or not. 
isFull(): Checks whether Deque is full or not.
 

Example:

MyCircularDeque circularDeque = new MycircularDeque(3); // set the size to be 3
circularDeque.insertLast(1);			// return true
circularDeque.insertLast(2);			// return true
circularDeque.insertFront(3);			// return true
circularDeque.insertFront(4);			// return false, the queue is full
circularDeque.getRear();  			// return 2
circularDeque.isFull();				// return true
circularDeque.deleteLast();			// return true
circularDeque.insertFront(4);			// return true
circularDeque.getFront();			// return 4
 

Note:

All values will be in the range of [0, 1000].
The number of operations will be in the range of [1, 1000].
Please do not use the built-in Deque library.




*/
#include <vector>

using std::vector;


class MyCircularDeque {

    vector<int> _buff;

    int _start;
    int _length;
    int _max_length;

public:
    
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k): _buff(k) {
        _start = 0;
        _length = 0;
        _max_length = k;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if (isFull()) return false;

        _start = (_start - 1 + _max_length) % _max_length;
        _buff[_start] = value;
        _length++;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if (isFull()) return false;

        _buff[(_start + _length) % _max_length] = value;
        _length++;
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if (isEmpty()) return false;

        _start = (_start + 1) % _max_length;
        _length--;
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty()) return false;
        _length--;
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        return isEmpty() ? -1 : _buff[_start];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        return isEmpty() ? - 1 : _buff[(_start + _length - 1) % _max_length];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return _length == 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return _length == _max_length;
    }
};
