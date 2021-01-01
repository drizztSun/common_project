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

using std::unordered_map;
using std::shared_ptr;
using std::unique_ptr;


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