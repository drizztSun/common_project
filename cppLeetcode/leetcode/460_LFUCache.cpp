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
#include <list>
#include <climits>
#include <unordered_map>

using std::unordered_map;
using std::list;


/*
    460.LFU-Cache
    本题用到了STL里的一个新的数据结构，list。list和vector的用法差不多，但其在内存中的存储并不是线性的，而是链表状的，所以它的插入、删除都很方便（因为已经被封装好了，我们不必实现链表插入、删除的细节）。

    删除list中一个元素，可以有这些操作：pop_front(), pop_back(), erase(iterator);     在list中加入一个元素，push_back(value), 其对应的iterator就是 --List.end()

    本题的数据结构需要如下三个：

        int cap, minfreq;
        unordered_map<int,pair<int,int>>Map; // key -> value, freq;
        unordered_map<int,list<int>>freq; // freq -> keys
        unordered_map<int,list<int>::iterator>iter; // key -> the iterator of key in freq
    Map记录了一个key所对应的value和操作频率；
    freq记录了对应一个操作频率的key有哪些；
    iter记录了对应一个key，其在freq数据结构中的迭代器（或者说指针、内存位置）。

    对于get函数：

        int get(int key) 
        {
            if (Map.find(key)==Map.end()) return -1;
            int f=Map[key].second;
            freq[f].erase(iter[key]); // 原频次f里去除key，通过迭代器iter[key]来删除。
            freq[f+1].push_back(key);  // 新频次f+1里增加key，直接塞在链表的最末
            iter[key]=--freq[f+1].end();  //key的迭代器位置需要更新，现在是在freq[f+1]的链表末尾
            Map[key].second++;    // Map[key]的信息
            if (freq[minfreq].size()==0)
                minfreq++;
            return Map[key].first;
        }
    对于put函数

        void put(int key, int value) 
        {
            if (cap<=0) return;
            if (get(key)!=-1)  //已经收录了这个key，则get(key)包括了更新频次的操作
            {
                Map[key].first=value;  //此时只需要更新value
                return;
            }
            else
            {
                if (Map.size()>=cap)
                {
                    int minKey=freq[minfreq].front();  //找到需要弹出的minKey，位于freq[minfreq]链表的最前端
                    iter.erase(minKey);     //不再需要保留记录这个minKey的迭代器地址
                    Map.erase(minKey);      //不再需要保留记录这个minKey的值信息
                    freq[minfreq].pop_front();  //频次映射里也不再需要保留记录这个minKey的频次信息
                }
                Map[key]={value,1};
                freq[1].push_back(key);   //频次为1的映射里需要添加这个key
                iter[key]=--freq[1].end();  //迭代器映射里要添加这个key的指针地址
                minfreq=1;
                return;
            }
        }
*/
class LFUCache {
    int cap, minfreq;
    unordered_map<int, std::pair<int,int>>Map; // key -> value, freq;
    unordered_map<int,list<int>>freq; // freq -> keys
    unordered_map<int,list<int>::iterator>iter; // key -> iterator
public:
    LFUCache(int capacity) 
    {
        cap=capacity;
    }
    
    int get(int key) 
    {
        if (Map.find(key)==Map.end()) return -1;

        int f=Map[key].second;
        freq[f].erase(iter[key]);
        freq[f+1].push_back(key);
        iter[key]=--freq[f+1].end();
        Map[key].second++;

        if (freq[minfreq].size()==0)
            minfreq++;
            
        return Map[key].first;
    }
    
    void put(int key, int value) 
    {
        if (cap<=0) return;
        if (get(key)!=-1)
        {
            Map[key].first=value;
            return;
        }
        else
        {
            if (Map.size()>=cap)
            {
                int minKey=freq[minfreq].front();
                iter.erase(minKey);
                Map.erase(minKey);
                freq[minfreq].pop_front();
            }
            Map[key]={value,1};
            freq[1].push_back(key);
            iter[key]=--freq[1].end();
            minfreq=1;
            return;
        }
    }
};

class LFUCache {
    unordered_map<int,int>key2value;
    unordered_map<int, list<int>::iterator> key2iter;
    unordered_map<int, int>key2freq;
    unordered_map<int, list<int>>freq2list;
    int cap, minFreq;
    
    
public:
    LFUCache(int capacity) 
    {
        cap = capacity;
        minFreq = 0;
    }
    
    int get(int key) 
    {
        if (key2value.find(key)==key2value.end())
            return -1;
        
        int f = key2freq[key];
        freq2list[f].erase(key2iter[key]);
        freq2list[f+1].push_back(key);
        key2iter[key] = --freq2list[f+1].end();
        key2freq[key] = f+1;
        
        if (freq2list[minFreq].size()==0)
            minFreq+=1;
        
        return key2value[key];
    }
    
    void put(int key, int value) 
    {
        if (cap==0) return;
        
        if (get(key)!=-1)
        {
            key2value[key] = value;
            return;
        }
        
        if (key2value.size()==cap)
        {
            int k = freq2list[minFreq].front();

            key2value.erase(k);
            key2iter.erase(k);
            key2freq.erase(k);
            freq2list[minFreq].pop_front();
        }

        key2value[key] = value;
        key2freq[key] = 1;
        freq2list[1].push_back(key);
        key2iter[key] = --freq2list[1].end();
        
        minFreq = 1;
        
    }
};

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
        if (_key.count(key) == 0) return -1;
        
        int value = _key[key].first->_value;
        //int cnt = _key[key].second;
        
        moveforward(key);
        return value;
    }
    
    void put(int key, int value) {
        
        if (_capacity == 0) return;
        
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