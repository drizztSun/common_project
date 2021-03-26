/*

146. LRU Cache

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
Follow up:
Could you do get and put in O(1) time complexity?

 

Example 1:

Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]

Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
 

Constraints:

1 <= capacity <= 3000
0 <= key <= 3000
0 <= value <= 104
At most 3 * 104 calls will be made to get and put.

*/
#include <unordered_map>
#include <list>
#include <memory>

using std::list;
using std::unordered_map;
using std::shared_ptr;
using std::unique_ptr;


/*
	146.LRU-Cache

	本题类似460，更简单些。考虑到o(1)的时间要求，所以用C++自带的链表结构list。访问list类似于访问vector，但对于非首尾两端的元素，只能通过迭代器（可以理解为指针）来访问。

	设计如下的数据结构：

	unordered_map<int,int>key2val; //记录 key -> val
	list<int>List; //把所有key按照recently visited的先后顺序排列
	unordered_map<int,list<int>::iterator>key2iter; //记录key对应的在List中的迭代器位置
	对于get函数，首先考虑是否在key2val中有key的记录，没有就只能退出。然后在List里删除key，并把key再装在List的末尾。显然，访问List里的Key需要通过key2iter[Key],最后也要更新key2iter[Key]。

	对于put函数，首先调用get(key)查看是否已经存在。如果已经存在，则只需要更新key2val[key]。另外注意到一个trick，在调用get(key)的时候，已经更新了key在List中的顺序，所以这个情况下，就可以安心退出了。

	如果get(key)==-1，那么就需要加入一个key。两种情况：一种是List.size()<cap，那么直接加key（需要添加key2val[key]、添加List、添加key2iter[key]）；另一种是List.size()==cap，那么需要先删除一个元素，再加上key.删除key需要的操作有：确定要删除的keyDel（就在List最首），在List里删除keyDel，在key2val里删除keyDel.

	总之，既然建立了三个数据结构 key2val, List, key2iter，那么在每一步操作的时候，注意都要更新这三个东西，就不会遗漏操作了。对于460题也是如此。
*/
class LRUCache {
    unordered_map<int,int>key2val;
    list<int>List;
    unordered_map<int, list<int>::iterator>key2iter;
    int cap;
    
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) 
    {
        if (key2val.find(key)==key2val.end())
            return -1;
        auto iter = key2iter[key];
        List.erase(iter);
        List.push_back(key);
        key2iter[key] = --List.end();
        return key2val[key];
    }
    
    void put(int key, int value) 
    {
        if (get(key)!=-1)
        {
            key2val[key] = value;
            return;
        }
        
        if (key2val.size()==cap)
        {
            int keyDel = *List.begin();
            key2val.erase(keyDel);
            key2iter.erase(keyDel);
            List.erase(List.begin());
        }
        key2val[key] = value;
        List.push_back(key);
        key2iter[key] = --List.end();
    }
};


class LRUCache {
	struct DoubleLink {

		int _key, _val;
		DoubleLink *_prev, *_next;

		DoubleLink(int key, int val) : _key(key), _val(val), _prev(nullptr), _next(nullptr) {}

		void connect(DoubleLink* ptr) {
			this->_next = ptr;
			ptr->_prev = this;
		}
	};

	DoubleLink *_head, *_tail;

	unordered_map<int, DoubleLink*> _elements;

	int _capacity;
	int _amount;

public:

	LRUCache(int capacity) {
		_capacity = capacity;
		_amount = 0;
		_head = new DoubleLink(INT_MAX, INT_MAX);
		_tail = new DoubleLink(INT_MIN, INT_MIN);
		_head->connect(_tail);
	}

    ~LRUCache() {
        DoubleLink* pnode = _head;
        while (pnode) {
            DoubleLink* tmp = pnode;
            pnode = pnode->_next;
            tmp->_next = nullptr;
            tmp->_prev = nullptr;
            delete tmp;
        }
    }

	void moveToHead(DoubleLink* pobj) {
		if (pobj->_prev == _head) return;

		DoubleLink* pNext = _head->_next;
		_head->connect(pobj);
		pobj->connect(pNext);
	}

	void removeFromTail() {
		DoubleLink *pobj = _tail->_prev;
		removeFromLink(pobj);
		_elements.erase(pobj->_key);
		clear(pobj);
	}

	void removeFromLink(DoubleLink* pobj) {
		DoubleLink *pPre = pobj->_prev, *pNext = pobj->_next;
		pPre->connect(pNext);
	}

	void clear(DoubleLink* pobj) {
		if (pobj == nullptr)
			return;
		pobj->_val = 0;
		pobj->_prev = nullptr;
		pobj->_next = nullptr;
		delete pobj;
	}

	int get(int key) {
		if (_elements.count(key) == 0)
			return -1;
		int val = _elements[key]->_val;
		DoubleLink* tmp = _elements[key];
		if (tmp->_prev != _head) {
			removeFromLink(tmp);
			moveToHead(tmp);
		}
		return val;
	}

	void put(int key, int value) {

		DoubleLink* pNode = nullptr;
		if (_elements.count(key) > 0) {
			pNode = _elements[key];
			pNode->_val = value;
			if (pNode->_prev == _head)
                return;
			removeFromLink(pNode);
		}
		else {
			pNode = new DoubleLink(key, value);
			_elements[key] = pNode;
			_amount++;
		}

		moveToHead(pNode);

		if (_amount > _capacity) {
			removeFromTail();
			_amount--;
		}
	}
};