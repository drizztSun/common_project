
/*

 432 All One Data Structure

 For each value, I have a bucket with all keys which have that value. The buckets are in a list, sorted by value.
 That allows constant time insertion/erasure and iteration to the next higher/lower value bucket.
 A bucket stores its keys in a hash set for easy constant time insertion/erasure/check (see first two posts here if you�re worried).
 I also have one hash map to look up which bucket a given key is in.

 Based on a previously flawed Python attempt (I just couldn�t find a good way to get an arbitrary element from a set)
 but also influenced by an earlier version of @Ren.W�s solution. We ended up with quite similiar code, I guess there�s not much room for creativity
 once you decide on the data types to hold the data.


*/

#include <string>
#include <unordered_map>
#include <map>
#include <list>
#include <unordered_set>


using namespace std;

class AllOne {
public:

	void inc(string key) {

		// If the key doesn't exist, insert it with value 0.
		if (!bucketOfKey.count(key))
			bucketOfKey[key] = buckets.insert(buckets.begin(), { 0,{ key } });

		// Insert the key in next bucket and update the lookup.
		auto bucket = bucketOfKey[key];
		auto next = std::next(bucket);
		if (next == buckets.end() || next->value > bucket->value + 1)
			next = buckets.insert(next, { bucket->value + 1,{} });
		next->keys.insert(key);
		bucketOfKey[key] = next;

		// Remove the key from its old bucket.
		bucket->keys.erase(key);
		if (bucket->keys.empty())
			buckets.erase(bucket);
	}

	void dec(string key) {

		// If the key doesn't exist, just leave.
		if (!bucketOfKey.count(key))
			return;

		// Maybe insert the key in previous bucket and update the lookup.
		auto prev = bucketOfKey[key], bucket = prev--;
		bucketOfKey.erase(key);
		if (bucket->value > 1) {
			if (bucket == buckets.begin() || prev->value < bucket->value - 1)
				prev = buckets.insert(bucket, { bucket->value - 1,{} });
			prev->keys.insert(key);
			bucketOfKey[key] = prev;
		}

		// Remove the key from its old bucket.
		bucket->keys.erase(key);
		if (bucket->keys.empty())
			buckets.erase(bucket);
	}

	string getMaxKey() {
		return buckets.empty() ? "" : *(buckets.rbegin()->keys.begin());
	}

	string getMinKey() {
		return buckets.empty() ? "" : *(buckets.begin()->keys.begin());
	}

private:
	struct Bucket { int value; unordered_set<string> keys; };
	list<Bucket> buckets;
	unordered_map<string, list<Bucket>::iterator> bucketOfKey;
};


class AllOne1 {
	
	struct bucket{
		int value_;
		unordered_set<string> keys_;
	};

	list<bucket> buckets_;

	unordered_map<string, list<bucket>::iterator> bucketOfKeys_;

public :

	AllOne1() {

	}

	void inc(string key) {
		if (!bucketOfKeys_.count(key))
			bucketOfKeys_[key] = buckets_.insert(buckets_.begin(), { 0, {key} });

		auto next = bucketOfKeys_[key], bucket = next++;

		if (next == buckets_.end() || bucket->value_ + 1 < next->value_) {
			next = buckets_.insert(next, { bucket->value_ + 1, {} });
		}

		next->keys_.insert(key);
		bucketOfKeys_[key] = next;

		bucket->keys_.erase(key);
		if (bucket->keys_.empty()) {
			buckets_.erase(bucket);
		}
	}

	void dec(string key) {
		if (!bucketOfKeys_.count(key))
			return;

		auto prev = bucketOfKeys_[key];
		auto bucket = prev--;
		bucketOfKeys_.erase(key);

		if (bucket->value_ > 1) {
			if (bucket == buckets_.begin() || prev->value_ + 1 < bucket->value_) {
				prev = buckets_.insert(bucket, { bucket->value_ - 1, {} });
			}
			bucketOfKeys_[key] = prev;
			bucketOfKeys_[key]->keys_.insert(key);
		}

		bucket->keys_.erase(key);
		if (bucket->keys_.empty())
			buckets_.erase(bucket);
	}

	string getMaxKey() {
		return buckets_.empty() ? string("") : *buckets_.rbegin()->keys_.begin();
	}

	string getMinKey() {
		return buckets_.empty() ? string("") : *buckets_.begin()->keys_.begin();
	}

};


/*
	
	432.All-O-one-Data-Structure

	此题和146.LRU和460.LFU的解法非常相似．我们需要一个数据结构存储着所有的val，并且这个val是实时有序的（方便我们最快找到最大和最小的val），还要求所有的插入和删除都是o(1)。

	解决方案还是链表(list)。设计如下的数据结构

	list<int>List;
	unordered_map<int,list<int>iterator>val2iter;
	其中List是一个链表，存储着顺序的value．只要给出了迭代器的位置（可以理解为指针），那么在特定位置的插入和删除都是o(1)的操作．那么假设已知value，如何在这个链表里找到这个对应value的位置呢？就需要另一个Hash表val2iter来存储．总结来说，就是给出一个value，那么val2iter[value]给出了这个value在链表里的位置，可以进行删除或添加的操作．

	为什么List可以一直保持是顺序的呢？对于任何一个key的操作，题意要求就是将其value增（或者减）一．假设我们在链表中定位了value（如前所说：通过val2iter）,只需要在其后面相邻的地址插入一个value+1（或者在其前面相邻的地址插入一个vlaue-1)即可，所以这个链表始终可以保持顺序．

	解决了以上的问题之后，剩下的数据结构就不难设计:

	unordered_map<string,int>key2val;   // key->val
	unordered_map<int,unordered_set<string>>val2set;  //val->set of keys
	我们需要一个Hash表val2set，来存储从val到对应的key的集合。于是inc(key)的操作，就是将key从value对应的集合中删除，再把key加入value+1对应的集合中。对于dec(key)的操作同理。

	本题的一个细节之处是，对于val==0的处理。我们可以在list中加入一个dummy head，也就是val0=0来方便操作。但是要注意避免任何对于val2set[0]的删除操作（因为在初始化时，我们不可能在这个集合中加入无限多的元素，所以干脆永远保持val2set[0]是空的）。

*/
class AllOne {
    list<int>List; // ordered sequence of values
    unordered_map<string,int>key2val;   // key->val
    unordered_map<int,unordered_set<string>>val2set;  //val->set of keys
    unordered_map<int,list<int>::iterator>val2iter; //val-> iterator in list
    
public:
    /** Initialize your data structure here. */
    AllOne() {
        List.push_back(0);
        val2iter[0] = List.begin();
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) 
    {
        int val = key2val[key];
        
        key2val[key] = val+1;
        
        val2set[val+1].insert(key);
        if (val>0) val2set[val].erase(key);
            
        if (val2set[val+1].size()==1)
        {
            List.insert(next(val2iter[val]), val+1);
            val2iter[val+1] = next(val2iter[val]);
        }
            
        if (val>0 && val2set[val].size()==0)
        {
            List.erase(val2iter[val]);
        }   
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) 
    {
        int val = key2val[key];
        if (val==0) return;
        
        key2val[key] = val-1;
        
        if (val-1>0) val2set[val-1].insert(key);
        val2set[val].erase(key);
            
        if (val-1>0 && val2set[val-1].size()==1)
        {
            List.insert(val2iter[val], val-1);
            val2iter[val-1] = prev(val2iter[val]);
        }
            
        if (val2set[val].size()==0)
        {
            List.erase(val2iter[val]);
        }
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() 
    {
        if (List.size()==1)
            return "";
        else
            return *(val2set[List.back()].begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() 
    {
        if (List.size()==1)
            return "";
        else
            return *(val2set[*(++List.begin())].begin());;
    }
};



class AllOne {
    
    map<int, unordered_set<string>> counter;
    unordered_map<string, int> Map;
    
public:
    /** Initialize your data structure here. */
    AllOne() {}
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {    
        if (Map.count(key) == 0) {
            Map[key] = 1;
            counter[Map[key]].insert(key);
        } else {
            int cnt = Map[key];
            counter[cnt+1].insert(key);
            counter[cnt].erase(key);
            if (counter[cnt].size() == 0)
                counter.erase(cnt);
            Map[key]++;
        }
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        
        if (Map.find(key) == Map.end()) return;
        
        int cnt = Map[key];
        counter[cnt].erase(key);
        
        if (counter[cnt].size() == 0)
			counter.erase(cnt);
        
        if (cnt == 1) {
            Map.erase(key);
            return;
        }
        
        Map[key]--;
        counter[cnt-1].insert(key);
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if (counter.empty()) return "";
        
        return *(counter.rbegin()->second.begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if (counter.empty()) return "";
        return *(counter.begin()->second.begin());
    }
};



void Test_432_AllOneDataStructure() {


	AllOne obj;


	obj.inc("a");
	obj.inc("b");
	obj.inc("b");

	obj.inc("c");
	obj.inc("c");
	obj.inc("c");

	obj.dec("b");
	obj.dec("b");


	auto res = obj.getMaxKey();
	res = obj.getMinKey();

	obj.dec("df");
	obj.dec("a");

	res = obj.getMaxKey();
	res = obj.getMinKey();


}