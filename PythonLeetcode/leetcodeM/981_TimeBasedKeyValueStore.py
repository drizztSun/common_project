# 981. Time Based Key-Value Store

# Create a timebased key-value store class TimeMap, that supports two operations.

# 1. set(string key, string value, int timestamp)

# Stores the key and value, along with the given timestamp.
# 2. get(string key, int timestamp)

# Returns a value such that set(key, value, timestamp_prev) was called previously, with timestamp_prev <= timestamp.
# If there are multiple such values, it returns the one with the largest timestamp_prev.
# If there are no values, it returns the empty string ("").


# Example 1:

# Input: inputs = ["TimeMap","set","get","get","set","get","get"], inputs = [[],["foo","bar",1],["foo",1],["foo",3],["foo","bar2",4],["foo",4],["foo",5]]
# Output: [null,null,"bar","bar",null,"bar2","bar2"]
# Explanation:
# TimeMap kv;
# kv.set("foo", "bar", 1); // store the key "foo" and value "bar" along with timestamp = 1
# kv.get("foo", 1);  // output "bar"
# kv.get("foo", 3); // output "bar" since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 ie "bar"
# kv.set("foo", "bar2", 4);
# kv.get("foo", 4); // output "bar2"
# kv.get("foo", 5); //output "bar2"

# Example 2:

# Input: inputs = ["TimeMap","set","set","get","get","get","get","get"], inputs = [[],["love","high",10],["love","low",20],["love",5],["love",10],["love",15],["love",20],["love",25]]
# Output: [null,null,null,"","high","high","low","low"]


# Note:

# All key/value strings are lowercase.
# All key/value strings have length in the range [1, 100]
# The timestamps for all TimeMap.set operations are strictly increasing.
# 1 <= timestamp <= 10^7
# TimeMap.set and TimeMap.get functions will be called a total of 120000 times (combined) per test case.


"""
Approach 1: HashMap + Binary Search
Intuition and Algorithm

For each key we get or set, we only care about the timestamps and values for that key.
We can store this information in a HashMap.

Now, for each key, we can binary search the sorted list of timestamps to find the relevant value for that key.

Complexity Analysis

Time Complexity: O(1)O(1) for each set operation, and O(\log N)O(logN) for each get operation, where NN is the number of entries in the TimeMap.

Space Complexity: O(N)O(N).
"""
import bisect


class TimeMap:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self._buff = {}

    def set(self, key: str, value: str, timestamp: int):

        if key not in self._buff:
            self._buff[key] = []

        self._buff[key].append((timestamp, value))

    def get(self, key: str, timestamp: int):

        A = self._buff.get(key, None)
        if A is None:
            return ''

        i = bisect.bisect(A, (timestamp, chr(127)))

        return A[i-1][1] if i else ''


if __name__ == '__main__':

    obj = TimeMap()

    obj.set('foo', 'bar', 1)
    obj.get('foo', 1)
    obj.get('foo', 3)
    obj.set('foo', 'bar2', 4)
    obj.get('foo', 4)
    obj.get('foo', 5)

    pass
