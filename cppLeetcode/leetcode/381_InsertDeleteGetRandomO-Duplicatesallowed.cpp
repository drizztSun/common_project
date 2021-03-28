/*
381. Insert Delete GetRandom O(1) - Duplicates allowed

Implement the RandomizedCollection class:

    . RandomizedCollection() Initializes the RandomizedCollection object.
    . bool insert(int val) Inserts an item val into the multiset if not present. Returns true if the item was not present, false otherwise.
    . bool remove(int val) Removes an item val from the multiset if present. Returns true if the item was present, false otherwise. Note that if val has multiple occurrences in the multiset, we only remove one of them.
    . int getRandom() Returns a random element from the current multiset of elements (it's guaranteed that at least one element exists when this method is called). 
            The probability of each element being returned is linearly related to the number of same values the multiset contains.
 

Example 1:

Input
["RandomizedCollection", "insert", "insert", "insert", "getRandom", "remove", "getRandom"]
[[], [1], [1], [2], [], [1], []]
Output
[null, true, false, true, 2, true, 1]

Explanation
RandomizedCollection randomizedCollection = new RandomizedCollection();
randomizedCollection.insert(1);   // return True. Inserts 1 to the collection. Returns true as the collection did not contain 1.
randomizedCollection.insert(1);   // return False. Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
randomizedCollection.insert(2);   // return True. Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
randomizedCollection.getRandom(); // getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
randomizedCollection.remove(1);   // return True. Removes 1 from the collection, returns true. Collection now contains [1,2].
randomizedCollection.getRandom(); // getRandom should return 1 and 2 both equally likely.
 

Constraints:

-231 <= val <= 231 - 1
At most 105 calls will be made to insert, remove, and getRandom.
There will be at least one element in the data structure when getRandom is called.
 

Follow up: Could you implement the functions of the class with each function works in average O(1) time?

*/
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::unordered_map;
using std::unordered_set;

class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        
    }
};


/*
    381.Insert-Delete-GetRandom-O1-Duplicates-allowed
    此题是380的follow up。

    设计数据结构的突破口就是在于getRandom的时间要求，o(1)必然说明我们需要维护一个数组nums，这样直接通过nums[rand()% nums.size()]就可以直接随机访问一个元素。

    那么如何处理remove的操作呢？对于数组而言删除一个中间元素的代价很大。一个常见的想法就是，将最后一个元素挪到被删除的元素的位置上去。这样保证了数组依然是线性连续的。所以我们需要维护一个hash表来存储每个数值所出现的（所有）index。具体的操作包括：

    1. 从Map[val]中挑一个位置pos，将nums.back()移过来。
    2. 从Map[val]中删除pos
    3. 更新Map[nums.back()]的位置，将原先的nums.size()-1改为pos
    4. nums.pop_back()
    5. 注意，如果Map[val]已经为空，那么请将val这个key从hash表中删除。
    特别注意：如果val就是nums末尾的元素，最好单独处理，否则容易出错。
*/
class RandomizedCollection {
    vector<int>nums;
    unordered_map<int,unordered_set<int>>val2pos;

public:
    /** Initialize your data structure here. */
    RandomizedCollection() {}
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) 
    {
        int flag = val2pos.find(val)==val2pos.end();        
        nums.push_back(val);
        val2pos[val].insert(nums.size()-1);
        return flag;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) 
    {
        int flag = val2pos.find(val)!=val2pos.end();
        if (flag==false) return false;

        int val2 = nums.back();
        
        if (val2==val)
        {
            val2pos[val].erase(nums.size()-1);
            nums.pop_back();            

            if (val2pos[val].size()==0)
                val2pos.erase(val);            
        }
        else
        {   
            int pos2 = nums.size()-1;
            int pos = *(val2pos[val].begin());            
            nums[pos] = val2;
            val2pos[val2].erase(pos2);
            val2pos[val2].insert(pos);
            val2pos[val].erase(pos);
            nums.pop_back();

            if (val2pos[val].size()==0)
                val2pos.erase(val);
        }
        
        return flag;
    }
    
    /** Get a random element from the collection. */
    int getRandom() 
    {
        int idx = rand()%nums.size();
        return nums[idx];
    }
};