/*
 460. LFU Cache
 
 Design and implement a data structure for Least Frequently Used (LFU) cache.

 Implement the LFUCache class:

 LFUCache(int capacity) Initializes the object with the capacity of the data structure.
 int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
 void put(int key, int value) Sets or inserts the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be evicted.
 Notice that the number of times an item is used is the number of calls to the get and put functions for that item since it was inserted. This number is set to zero when the item is removed.

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

/*
class LFUCache {

    
    struct node {
        int _key, _val;
        node* _prev, _next;
        
        node(int key, int val) {
            _key = key, _val = val;
            _prev = nullptr, _next = nullptr;
        }
        
        void connect(node* next) {
            if (next == nullptr)
                return;
            
            this._next = next;
            p._prev = this
            
        }
    }
    
public:
    
    LFUCache(int capacity) {
        this._capacity = capcacity;
        this._head = new node(INT_MAX, 0);
        this._tail = new node(INT_MIN, 0);
        this._head.connect(this._tail);
        this._frequency[0] = this._tail;
    }
    
    ~LFUCache() {
        p = this._head;
        while (p) {
            n = p->_next;
            delete p;
            p = n;
        }
    }
    
    int get(int key) {
        if (this._keys.count(key) == 0)
            retun -1;

        auto& c = this._keys[key];
        int value = c.second;
        this.moveforward(key);
        return value;
    }
    
    void put(int key, int value) {
        
        if (this._capacity == 0)
            return -1;
        
        if (this._keys.count(key) > 0) {
            auto& c = this._keys[key];
            c.second = value;
            this.moveforward(c.first);
            return
        }
        
        if (this._keys.size() == this._capacity) {
            delete this.remove(this._tail._pre._key);
        }
        
        node* p = node(key, value);
        this.add(p, 0);
    }
    
private:

    void moveforward(int key) {
        
        if (this._keys.count(key) == 0)
            return;
        
        this.remove(key);
        auto& c = this._keys[key];
        c.first += 1;
        
        this.add(c.second, c.first);
    }
    
    node* remove(int key) {
        
        auto& c = this._keys[key];
        int cnt = c.first;
        node* p = c.second;
        
        if (this._frequency[cnt] != p) {
            this._frequency[cnt] = nullptr;
            
            if (this._frequency[p._next._key] == cnt) {
                this._frequency[cnt] = p._next;
            } else {
                this._frequency.delete(cnt);
            }
        }
        p._pre.connect(p._next);
        return p;
    }
    
    void add(node* p, int cnt) {
        
        node* pre = nullptr;
        if (this._frequency.count(cnt) == 0) {
            this._
        }
        
    }
    
    unordered_map<int, node*> _frequency;
    
    unordered_map<int, std::pair<int, node*>> _keys;
    
    node* _head, _tail;
    
    int _capacity;
};

*/
