
/*

 432 All One Data Structure

 For each value, I have a bucket with all keys which have that value. The buckets are in a list, sorted by value.
 That allows constant time insertion/erasure and iteration to the next higher/lower value bucket.
 A bucket stores its keys in a hash set for easy constant time insertion/erasure/check (see first two posts here if you’re worried).
 I also have one hash map to look up which bucket a given key is in.

 Based on a previously flawed Python attempt (I just couldn’t find a good way to get an arbitrary element from a set)
 but also influenced by an earlier version of @Ren.W’s solution. We ended up with quite similiar code, I guess there’s not much room for creativity
 once you decide on the data types to hold the data.


*/

#include <string>
#include <unordered_map>
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