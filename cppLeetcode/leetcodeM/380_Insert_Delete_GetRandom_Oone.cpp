/*
380. Insert Delete GetRandom O(1)


Implement the RandomizedSet class:

    . RandomizedSet() Initializes the RandomizedSet object.
    . bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
    . bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
    . int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
 

Example 1:

Input
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]
Output
[null, true, false, true, 2, true, false, 2]

Explanation
RandomizedSet randomizedSet = new RandomizedSet();
randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].
randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.
 

Constraints:

-231 <= val <= 231 - 1
At most 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
 

Follow up: Could you implement the functions of the class with each function works in average O(1) time?

*/
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class RandomizedSet {
    
    unordered_map<int, int> _pos;
    vector<int> _nums;
    
public:
    /** Initialize your data structure here. */
    RandomizedSet() {}
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        
        if (_pos.count(val) > 0) return false;
        
        _nums.push_back(val);
        _pos[val] = _nums.size()-1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        
        if (_pos.count(val) == 0) return false;
        
        int index = _pos[val];
        int lastone = _nums.back();
        _pos[lastone] = index;
        _nums[index] = lastone;
        _nums.pop_back();
        _pos.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return _nums[rand() % _nums.size()];
    }
};

/*
380.Insert-Delete-GetRandom-O(1)
插入是o(1)操作的，只有数组的push_back，否则用链表至少o(logn)，还得保证是有序的；

同理，删除是o(1)操作的，只有数组的pop_back，否则至少o(logn)；

查找是o(1)操作的只有哈希表。

因此考虑到用Map和数组。Map记录元素和数组位置之间的对应关系。

特别注意remove所需要的几个操作，把val和数组尾的元素对调：

        if (Map.find(val)==Map.end())
            return false;
        else
        {
            q[Map[val]] = q.back();  //  将数组尾元素放在val的位置上
            Map[q.back()] = Map[val];  // 修改数组尾元素的新位置映射
            q.pop_back();  // 数组丢弃尾元素
            Map.erase(val);  // 映射丢弃原来的val
            return true;
        }
特别需要小心的细节就是，Map.erase(val)和Map[q.back()]=pos的操作顺序，前者必须放在最后。否则若 val=q.back()时，val并不能真正从Map里删除，因为Map[q.back()]=pos又会把其加回去。

另外，随机生成整形随机数的函数 rand(); 如果需要0~N-1范围内的随机数，就是 rand() % N
*/

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() 
    {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) 
    {
        if (Map.find(val)!=Map.end())
            return false;
        else
        {
            Map[val]=q.size();
            q.push_back(val);
            return true;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) 
    {
        if (Map.find(val)==Map.end())
            return false;
        else
        {
            q[Map[val]] = q.back();
            Map[q.back()] = Map[val];
            q.pop_back();
            Map.erase(val);
            return true;
        }
    }
    
    /** Get a random element from the set. */
    int getRandom() 
    {
        int pos = rand()%q.size();
        return q[pos];
    }
    
private:    
    unordered_map<int,int>Map;
    vector<int>q;
};