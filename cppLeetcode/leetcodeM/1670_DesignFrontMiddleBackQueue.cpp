/*
 
 1670. Design Front Middle Back Queue
 
 
 
 Design a queue that supports push and pop operations in the front, middle, and back.

 Implement the FrontMiddleBack class:

 FrontMiddleBack() Initializes the queue.
 void pushFront(int val) Adds val to the front of the queue.
 void pushMiddle(int val) Adds val to the middle of the queue.
 void pushBack(int val) Adds val to the back of the queue.
 int popFront() Removes the front element of the queue and returns it. If the queue is empty, return -1.
 int popMiddle() Removes the middle element of the queue and returns it. If the queue is empty, return -1.
 int popBack() Removes the back element of the queue and returns it. If the queue is empty, return -1.
 Notice that when there are two middle position choices, the operation is performed on the frontmost middle position choice. For example:

 Pushing 6 into the middle of [1, 2, 3, 4, 5] results in [1, 2, 6, 3, 4, 5].
 Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in [1, 2, 4, 5, 6].


 Example 1:

 Input:
 ["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
 [[], [1], [2], [3], [4], [], [], [], [], []]
 Output:
 [null, null, null, null, null, 1, 3, 4, 2, -1]

 Explanation:
 FrontMiddleBackQueue q = new FrontMiddleBackQueue();
 q.pushFront(1);   // [1]
 q.pushBack(2);    // [1, 2]
 q.pushMiddle(3);  // [1, 3, 2]
 q.pushMiddle(4);  // [1, 4, 3, 2]
 q.popFront();     // return 1 -> [4, 3, 2]
 q.popMiddle();    // return 3 -> [4, 2]
 q.popMiddle();    // return 4 -> [2]
 q.popBack();      // return 2 -> []
 q.popFront();     // return -1 -> [] (The queue is empty)


 Constraints:

 1 <= val <= 109
 At most 1000 calls will be made to pushFront, pushMiddle, pushBack, popFront, popMiddle, and popBack.


 */
#include <vector>
#include <list>

using std::list;
using std::vector;

/*
    1670.Design-Front-Middle-Back-Queue
    解法1
    考虑到如果使用最粗暴的数组来实现这个数据结构的话，数组里最多有1000个元素，每次增删一个元素最多调整1000个元素的位置。10^6的复杂度是足够解这道题了。

    解法2
    更高级的数据结构是用双端链表，这样所有的增删操作都是o(1)。C++里面的list就可以实现这样的功能。我们另外还需要维护一个迭代器list::iterator mid用来存放middle元素所在的位置。

    push_front:
    当n为偶数时，mid不用变化。
    OXOO
    YOXOO 
    当n为奇数时，mid需要前移一位。 
    OOXOO
    YOOXOO
    push_back:
    当n为偶数时，mid需要后移一位。
    OXOO
    OXOOY
    当n为奇数时，mid不用变化。
    OOXOO
    OOXOOY
    push_middle:
    当n为偶数时，新mid会插在mid后面。
    OXOO
    OXYOO
    当n为奇数时，新mid会插在mid前面。
    OOXOO
    OOYXOO
    pop_front:
    当n为偶数时，mid需要后移一位。
    OXOO
    XOO
    当n为奇数时，mid不需要变化
    OOXOO
    OXOO
    pop_back:
    当n为偶数时，mid不需要变化
    OXOO
    OXO
    当n为奇数时，mid需要前移一位
    OOXOO
    OOXO
    pop_middle:
    当n为偶数时，mid需要后移一位。
    OXOO
    O OO
    当n为奇数时，mid需要前移一位。
    OOXOO
    OO OO

*/

class FrontMiddleBackQueueI {

    vector<int> _buff;
    
public:
    
    FrontMiddleBackQueueI() {
        
        
    }
    
    void pushFront(int val) {
    
        _buff.insert(begin(_buff), val);
        
    }
    
    void pushMiddle(int val) {
        _buff.insert(begin(_buff) + _buff.size() / 2, val);
    }
    
    void pushBack(int val) {
        _buff.push_back(val);
    }
    
    int popFront() {
        if (_buff.empty())
            return -1;
        
        int ret = _buff.front();
        _buff.erase(begin(_buff));
        return ret;
    }
    
    int popMiddle() {
        if (_buff.empty())
            return -1;
        
        int ret = _buff[(_buff.size()-1) / 2];
        _buff.erase(begin(_buff)+(_buff.size()-1)/ 2);
        return ret;
    }
    
    int popBack() {
        if (_buff.empty())
            return -1;
        int ret = _buff.back();
        _buff.pop_back();
        return ret;
    }
};


class FrontMiddleBackQueuelinked {
    
    list<int> _link;
    int _count;
    list<int>::iterator _mid;
    
public:
    FrontMiddleBackQueuelinked() {
        _count = 0;
    }
    
    void pushFront(int val) {
    
        _link.push_front(val);
        
        if (_count == 0)
            _mid = _link.begin();
        else if (_count % 2 == 1)
            _mid = prev(_mid);
        
        _count++;
    }
    
    void pushMiddle(int val) {
        if (_count == 0) {
            _link.push_back(val);
            _mid = begin(_link);
        }
        else if (_count % 2 == 0) {
            _link.insert(next(_mid), val);
            _mid = next(_mid);
        } else {
            _link.insert(_mid, val);
            _mid = prev(_mid);
        }
        _count++;
    }
    
    void pushBack(int val) {
        _link.push_back(val);
        if (_count == 0)
            _mid = _link.begin();
        else if (_count % 2 == 0)
            _mid = next(_mid);
        _count++;
    }
    
    int popFront() {
        
        if (_count == 0)
            return -1;
        
        int ret = _link.front();
        if (_count % 2 == 0)
            _mid = next(_mid);
        _link.pop_front();
        _count--;
        return ret;
    }
    
    int popMiddle() {
        if (_count == 0)
            return -1;
        
        int ret = *_mid;
        auto tmp = _mid;
        if (_count % 2 == 1)
            _mid = prev(_mid);
        else
            _mid = next(_mid);
        _link.erase(tmp);
        _count--;
        return ret;
    }
    
    int popBack() {
        
        if (_count == 0)
            return -1;
        
        int ret = _link.back();
        if (_count % 2 == 1)
            _mid = prev(_mid);
        _link.pop_back();
        _count--;
        return ret;
    }
};
