/*
 
 1157. Online Majority Element In Subarray
 
 Implementing the class MajorityChecker, which has the following API:

 MajorityChecker(int[] arr) constructs an instance of MajorityChecker with the given array arr;
 int query(int left, int right, int threshold) has arguments such that:
 0 <= left <= right < arr.length representing a subarray of arr;
 2 * threshold > right - left + 1, ie. the threshold is always a strict majority of the length of the subarray
 Each query(...) returns the element in arr[left], arr[left+1], ..., arr[right] that occurs at least threshold times, or -1 if no such element exists.

  

 Example:

 MajorityChecker majorityChecker = new MajorityChecker([1,1,2,2,1,1]);
 majorityChecker.query(0,5,4); // returns 1
 majorityChecker.query(0,3,3); // returns -1
 majorityChecker.query(2,3,2); // returns 2
  

 Constraints:

 1 <= arr.length <= 20000
 1 <= arr[i] <= 20000
 For each query, 0 <= left <= right < len(arr)
 For each query, 2 * threshold > right - left + 1
 The number of queries is at most 10000

 
 
 */

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <set>

using std::set;
using std::unordered_map;
using std::vector;



class MajorityChecker {
    
    unordered_map<int, vector<int>> _num_idx;
    
    vector<int> _order_amount;
    
public:
    
    MajorityChecker(vector<int>& arr) {
        
        set<int> tmp;
        for (int i = 0; i < arr.size(); i++) {
            _num_idx[arr[i]].push_back(i);
            tmp.insert(arr[i]);
        }
        
        vector<int> order(begin(tmp), end(tmp));
        std::sort(begin(order), end(order), [&](auto a, auto b) {
            return _num_idx[a].size() > _num_idx[b].size();
        });
        
        _order_amount.swap(order);
    }
    
    int query(int left, int right, int threshold) {
        
        for (auto c : _order_amount) {
            
            if (_num_idx[c].size() < threshold)
                return -1;
            
            auto& target = _num_idx[c];
            
            int leftindex = std::lower_bound(begin(target), end(target), left) - begin(target);
            int rightindex = std::upper_bound(begin(target), end(target), right) - begin(target);
            
            if (rightindex - leftindex >= threshold)
                return c;
        }
        
        return -1;
    }
};


void test_1157_only_majority() {
    
    vector<int> arr{1, 1, 2, 2, 1, 1};
    
    MajorityChecker obj(arr);
    
    obj.query(2, 3, 2);
    
    obj.query(0, 5, 4);
    
    obj.query(0, 3, 3);
}

