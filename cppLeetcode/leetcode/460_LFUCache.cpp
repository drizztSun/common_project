/*
 460. LFU Cache
 
 Design and implement a data structure for Least Frequently Used (LFU) cache.

 Implement the LFUCache class:

 LFUCache(int capacity) Initializes the object with the capacity of the data structure.
 int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
 void put(int key, int value) Sets or inserts the value if the key is not already present. When the cache reaches its capacity,
 it should invalidate the least frequently used item before inserting a new item. For this problem, when there is a tie
 (i.e., two or more keys with the same frequency), the least recently used key would be evicted.
 
 Notice that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted.
 This number is set to zero when the item is removed.

 Follow up:
 Could you do both operations in O(1) time complexity?

  

 Example 1:

 Input
 ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
 [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
 Output
 [null, null, null, 1, null, -1, 3, null, -1, 3, 4]

 Explanation
 LFUCache lFUCache = new LFUCache(2);
 lFUCache.put(1, 1);
 lFUCache.put(2, 2);
 lFUCache.get(1);      // return 1
 lFUCache.put(3, 3);   // evicts key 2
 lFUCache.get(2);      // return -1 (not found)
 lFUCache.get(3);      // return 3
 lFUCache.put(4, 4);   // evicts key 1.
 lFUCache.get(1);      // return -1 (not found)
 lFUCache.get(3);      // return 3
 lFUCache.get(4);      // return 4

 
 */
#include <memory>
#include <stdlib.h>
#include <list>
#include <climits>
#include <unordered_map>

using std::unordered_map;
using std::list;



class LFUCacheI {
    
    struct LFUCacheItem {
        int key;
        int value;
        int freq;
        LFUCacheItem(int _key,int _val):
                key(_key),value(_val),freq(1){}
    };
    
    int m_capacity;
    unordered_map<int,list<LFUCacheItem> > m_FreqItemMap;
    unordered_map<int,list<LFUCacheItem>::iterator> m_KeyItemMap;
    int lowestFreq;
    
public:
    
    LFUCacheI(int capacity) {
        m_capacity = capacity;
        lowestFreq = INT_MAX;
    }
    
    int get(int key) {
        if(m_KeyItemMap.find(key) == m_KeyItemMap.end())
            return -1;
        
        int oldFreq = m_KeyItemMap[key]->freq;
        m_KeyItemMap[key]->freq++;
        m_FreqItemMap[oldFreq+1].splice(m_FreqItemMap[oldFreq+1].end(), m_FreqItemMap[oldFreq], m_KeyItemMap[key]);
        m_KeyItemMap[key] = prev(m_FreqItemMap[oldFreq+1].end(),1);
        
        if(m_FreqItemMap[oldFreq].size() == 0 && oldFreq == lowestFreq) {
            lowestFreq++;
            oldFreq = lowestFreq;
        }
       
        return m_KeyItemMap[key]->value;
    }
    
    void put(int key, int value) {
        if(m_capacity == 0 )
            return;
        
        if(m_KeyItemMap.find(key) != m_KeyItemMap.end()) {
            int oldFreq = m_KeyItemMap[key]->freq;
            m_KeyItemMap[key]->freq++;
            m_KeyItemMap[key]->value = value;
            m_FreqItemMap[oldFreq+1].splice(m_FreqItemMap[oldFreq+1].end(),m_FreqItemMap[oldFreq],m_KeyItemMap[key]);
            m_KeyItemMap[key] = prev(m_FreqItemMap[oldFreq+1].end(),1);
            
            if(m_FreqItemMap[oldFreq].size() == 0 && oldFreq == lowestFreq) {
                lowestFreq++;
                oldFreq = lowestFreq;
            }
        } else {
            if(m_KeyItemMap.size() == m_capacity) {
                m_KeyItemMap.erase(m_FreqItemMap[lowestFreq].front().key);
                m_FreqItemMap[lowestFreq].pop_front();
            }
            m_FreqItemMap[1].emplace_back(LFUCacheItem(key,value));
            m_KeyItemMap[key] = prev(m_FreqItemMap[1].end(),1);
            lowestFreq = 1;
        }
    }
};


class LFUCache {
    
    
    struct node {
        
        int _key, _value;
        
        node *_prev, *_next;
        
        node(int key, int val) {
            _key = key;
            _value = val;
        }
        
        void connect(node* n) {
            
            this->_next = n;
            n->_prev = this;
        }
    };
    
    
    node *_head, *_tail;
    int _capacity;
    unordered_map<int, std::pair<node*, int>> _key;
    unordered_map<int, node*> _counter;
  
public:
    
    
    LFUCache(int cap): _capacity(cap) {
        
        _head = new node(INT_MAX, INT_MAX);
        _tail = new node(INT_MIN, INT_MIN);
        
        _head->connect(_tail);
        
        _key[INT_MIN] = {};
        _counter.insert({0, _tail});
    }
    
    ~LFUCache() {
        delete _head;
        delete _tail;
        _head = nullptr;
        _tail = nullptr;
    }
 
    
    int get(int key) {
        
        if (_key.count(key) == 0)
            return -1;
        
        int value = _key[key].first->_value;
        int cnt = _key[key].second;
        
        moveforward(key);
        
        return value;
    }
    
    void put(int key, int value) {
        
        if (_capacity == 0)
            return;
        
        if (_key.count(key) > 0) {
            _key[key].first->_value = value;
            moveforward(key);
            return;
        }
        
        if (_key.size() > _capacity) {
            remove(_tail->_prev->_key);
        }
        
        add(key, value, 0);
    }
    
    void moveforward(int key) {
        
        node* p = _key[key].first;
        int cnt = _key[key].second;
        
        add(INT_MAX, p->_value, cnt + 1);
        remove(key);
        
        _key[key] = _key[INT_MAX];
        _key[key].first->_key = key;
        _key.erase(INT_MAX);
    }
    
    void add(int key, int value, int cnt) {
        
        node * loc = _counter.count(cnt) ? _counter[cnt] : _counter[cnt - 1];
        
        node * p = new node(key, value);
        
        loc->_prev->connect(p);
        p->connect(loc);
        
        _counter[cnt] = p;
        _key[key] = {p, cnt};
    }
    
    void remove(int key) {
        
        node* p = _key[key].first;
        int cnt = _key[key].second;
        
        if (_counter[cnt] != p) {
            p->_prev->connect(p->_next);
        } else if (_key[p->_next->_key].second == cnt) {
            p->_prev->connect(p->_next);
            _counter[cnt] = p->_next;
        } else {
            p->_prev->connect(p->_next);
            _counter.erase(cnt);
        }
        
        _key.erase(key);
        delete p;
    }
    
};


void test_460_LFUCache() {
    
    LFUCache lfu(2);
    
    lfu.put(1, 1);
    lfu.put(2, 2);
    
    lfu.get(1);
    
    lfu.put(3, 3);
    
    lfu.get(2);
    
    lfu.get(3);
    
    lfu.put(4, 4);
    
    lfu.get(3);
    
    lfu.get(4);
    
    
    
}
