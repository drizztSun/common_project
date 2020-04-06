/*
 
 981. Time Based Key-Value Store
 
 Create a timebased key-value store class TimeMap, that supports two operations.

 1. set(string key, string value, int timestamp)

 Stores the key and value, along with the given timestamp.
 
 2. get(string key, int timestamp)

 Returns a value such that set(key, value, timestamp_prev) was called previously, with timestamp_prev <= timestamp.
 
 If there are multiple such values, it returns the one with the largest timestamp_prev.
 If there are no values, it returns the empty string ("").
  

 Example 1:

 Input: inputs = ["TimeMap","set","get","get","set","get","get"], inputs = [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
 Output: [null,null,"bar","bar",null,"bar2","bar2"]
 Explanation:
 TimeMap kv;
 kv.set("foo", "bar", 1); // store the key "foo" and value "bar" along with timestamp = 1
 kv.get("foo", 1);  // output "bar"
 kv.get("foo", 3); // output "bar" since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 ie "bar"
 kv.set("foo", "bar2", 4);
 kv.get("foo", 4); // output "bar2"
 kv.get("foo", 5); //output "bar2"

 Example 2:

 Input: inputs = ["TimeMap","set","set","get","get","get","get","get"], inputs = [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
 Output: [null,null,null,"","high","high","low","low"]
 
 
 */

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <map>
using std::map;

class TimeMap {
    
    unordered_map<string, map<int, string>> time_buf;
    
public:

    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        
        time_buf[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        
        if (time_buf.count(key)== 0)
            return "";
        
        auto res = time_buf[key].lower_bound(timestamp);
        
        
        if (res == time_buf[key].end())
            return time_buf[key].rbegin()->second;
        else if (res ->first == timestamp)
            return res->second;
        else if (res == time_buf[key].begin())
            return "";
        else {
            res--;
            return res->second;
        }
            
    }
};


class TimeMap1 {
public:
    
    TimeMap1() {
        
    }
    
    void set(string key, string value, int timestamp) {
        time_map[key].push_back({value, timestamp});
    }
    
    string get(string key, int timestamp) {
        if (time_map.find(key) == end(time_map)) {
            return "";
        }
        vector<TimeBasedValue>& v = time_map[key];
        
        auto comp = [](int timestamp, const TimeBasedValue& a) {
            return timestamp < a.timestamp;
        };
        
        if (auto it = upper_bound(begin(v), end(v), timestamp, comp);
            it == end(v)) {
            return v.back().value;
        } else if (it == begin(v)) {
            return "";
        } else {
            return prev(it)->value;
        }
    }
    
private:
    
    struct TimeBasedValue {
        string value;
        int timestamp;
    };
    
    unordered_map<string, vector<TimeBasedValue>> time_map;
    
};

void test_981_time_based_key_value_store() {
    
    TimeMap obj;
    string res;
    
    obj.set("foo", "bar", 1);
    res = obj.get("foo", 1);
    res = obj.get("foo", 3);
    
    obj.set("foo", "bar2", 4);
    res = obj.get("foo", 4);
    res = obj.get("foo", 5);
    
    res = obj.get("foo", 0);
    return;
}
