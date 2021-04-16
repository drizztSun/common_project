/*
347. Top K Frequent Elements


Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
 

Constraints:

1 <= nums.legth <= 105
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.
 

Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.

*/
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <queue>

using std::priority_queue;
using std::map;
using std::vector;
using std::unordered_map;

class TopKFrequent {

public:
    
    vector<int> doit_sort(vector<int>& nums, int k) {
        
        unordered_map<int, int> freq;
        for (auto c: nums) {
            freq[c]++;
        }
        
        vector<std::pair<int, int>> frequency;
        for (auto [k, v]: freq) {
            frequency.push_back({v, k});
        }
        
        std::sort(begin(frequency), end(frequency));
        
        vector<int> ans;
        
        for (int i = frequency.size()-1; k != 0 && i >= 0 ; i--, k--) {
            ans.push_back(frequency[i].second);
        }
        
        return ans;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        unordered_map<int, int> freq;
        for (auto c: nums) {
            freq[c]++;
        }
        
        vector<std::pair<int, int>> frequency;
        for (auto [k, v]: freq) {
            frequency.push_back({v, k});
        }
        
        std::nth_element(begin(frequency), begin(frequency)+k-1, end(frequency), [](auto& a, auto& b){
            return a.first > b.first;
        });
        
        vector<int> ans;
        
        for (int i = 0; k != 0 && i < frequency.size() ; i++, k--) {
            ans.push_back(frequency[i].second);
        }
        
        return ans;
    }

    /*
        Approach 1: Heap
        Let's start from the simple heap approach with \mathcal{O}(N \log k)O(Nlogk) time complexity. To ensure that \mathcal{O}(N \log k)O(Nlogk) is always less than \mathcal{O}(N \log N)O(NlogN), the particular case k = Nk=N could be considered separately and solved in \mathcal{O}(N)O(N) time.
    */
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // O(1) time
        if (k == nums.size()) {
            return nums;
        }

        // 1. build hash map : element and how often it appears
        // O(N) time
        map<int, int> count_map;
        for (int n : nums) {
            count_map[n] += 1;
        }

        // initialise a heap with most frequent elements at the top
        auto comp = [&count_map](int n1, int n2) { return count_map[n1] > count_map[n2]; };
        priority_queue<int, vector<int>, decltype(comp)> heap(comp);

        // 2. keep k top fequent elements in the heap
        // O(N log k) < O(N log N) time
        for (std::pair<int, int> p : count_map) {
            heap.push(p.first);
            if (heap.size() > k) heap.pop();
        }

        // 3. build an output array
        // O(k log k) time
        vector<int> top(k);
        for (int i = k - 1; i >= 0; i--) {
            top[i] = heap.top();
            heap.pop();
        }
        return top;
    }


    /*
        Approach 2: Quickselect (Hoare's selection algorithm)
        Quickselect is a textbook algorthm typically used to solve the problems "find kth something": kth smallest, kth largest, kth most frequent, kth less frequent, etc. Like quicksort, quickselect was developed by Tony Hoare, and also known as Hoare's selection algorithm.

        It has \mathcal{O}(N)O(N) average time complexity and widely used in practice. It worth to note that its worth case time complexity is \mathcal{O}(N^2)O(N 
        2
        ), although the probability of this worst-case is negligible.

        The approach is the same as for quicksort.
    */

    vector<int> unique;
    map<int, int> count_map;

    int partition(int left, int right, int pivot_index) {
        int pivot_frequency = this->count_map[this->unique[pivot_index]];
        // 1. move pivot to the end
        std::swap(this->unique[pivot_index], this->unique[right]);

        // 2. move all less frequent elements to the left
        int store_index = left;
        for (int i = left; i <= right; i++) {
            if (this->count_map[this->unique[i]] < pivot_frequency) {
                std::swap(this->unique[store_index], this->unique[i]);
                store_index += 1;
            }
        }

        // 3. move pivot to its final place
        std::swap(this->unique[right], this->unique[store_index]);

        return store_index;
    }

    void quickselect(int left, int right, int k_smallest) {
        /*
        Sort a list within left..right till kth less frequent element
        takes its place. 
        */

        // base case: the list contains only one element
        if (left == right) return;

        int pivot_index = left + rand() % (right - left + 1);

        // find the pivot position in a sorted list
        pivot_index = partition(left, right, pivot_index);

        // if the pivot is in its final sorted position
        if (k_smallest == pivot_index) {
            return;
        } else if (k_smallest < pivot_index) {
            // go left
            quickselect(left, pivot_index - 1, k_smallest);
        } else {
            // go right
            quickselect(pivot_index + 1, right, k_smallest);
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        // build hash map : element and how often it appears
        for (int n : nums) {
            this->count_map[n] += 1;
        }

        // array of unique elements
        size_t n = this->count_map.size();
        for (std::pair<int, int> p : this->count_map) {
            this->unique.push_back(p.first);
        }

        // kth top frequent element is (n - k)th less frequent.
        // Do a partial sort: from less frequent to the most frequent, till
        // (n - k)th less frequent element takes its place (n - k) in a sorted array.
        // All element on the left are less frequent.
        // All the elements on the right are more frequent.
        quickselect(0, n - 1, n - k);
        // Return top k frequent elements
        vector<int> top_k_frequent(k);
        copy(this->unique.begin() + n - k, this->unique.end(), top_k_frequent.begin());
        return top_k_frequent;
    }
};
