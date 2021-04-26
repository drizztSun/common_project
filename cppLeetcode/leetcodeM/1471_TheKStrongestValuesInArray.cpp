/*
1471. The k Strongest Values in an Array

Given an array of integers arr and an integer k.

A value arr[i] is said to be stronger than a value arr[j] if |arr[i] - m| > |arr[j] - m| where m is the median of the array.
If |arr[i] - m| == |arr[j] - m|, then arr[i] is said to be stronger than arr[j] if arr[i] > arr[j].

Return a list of the strongest k values in the array. return the answer in any arbitrary order.

Median is the middle value in an ordered integer list. More formally, if the length of the list is n, the median is the element in position ((n - 1) / 2) in the sorted list (0-indexed).

For arr = [6, -3, 7, 2, 11], n = 5 and the median is obtained by sorting the array arr = [-3, 2, 6, 7, 11] and the median is arr[m] where m = ((5 - 1) / 2) = 2. The median is 6.
For arr = [-7, 22, 17, 3], n = 4 and the median is obtained by sorting the array arr = [-7, 3, 17, 22] and the median is arr[m] where m = ((4 - 1) / 2) = 1. The median is 3.


Example 1:

Input: arr = [1,2,3,4,5], k = 2
Output: [5,1]
Explanation: Median is 3, the elements of the array sorted by the strongest are [5,1,4,2,3]. The strongest 2 elements are [5, 1]. [1, 5] is also accepted answer.
Please note that although |5 - 3| == |1 - 3| but 5 is stronger than 1 because 5 > 1.
Example 2:

Input: arr = [1,1,3,5,5], k = 2
Output: [5,5]
Explanation: Median is 3, the elements of the array sorted by the strongest are [5,5,1,1,3]. The strongest 2 elements are [5, 5].
Example 3:

Input: arr = [6,7,11,7,6,8], k = 5
Output: [11,8,6,6,7]
Explanation: Median is 7, the elements of the array sorted by the strongest are [11,8,6,6,7,7].
Any permutation of [11,8,6,6,7] is accepted.
Example 4:

Input: arr = [6,-3,7,2,11], k = 3
Output: [-3,11,2]
Example 5:

Input: arr = [-7,22,17,3], k = 2
Output: [22,17]


Constraints:

1 <= arr.length <= 10^5
-10^5 <= arr[i] <= 10^5
1 <= k <= arr.length
*/
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using std::priority_queue;
using std::multimap;
using std::vector;


class GetStrongest {

public:
    
    // O(nlog(n))
    vector<int> doit_sort(vector<int>& arr, int k) {
        
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int med = arr[(n-1)/2];
        
        auto func = [&](int a, int b) {
            if (abs(a - med) != abs(b - med))
                return (abs(a - med) > abs(b - med));
            return a > b;
        };
        
        sort(arr.begin(), arr.end(), func);
        return {begin(arr), begin(arr) + k};
    }

    vector<int> doit_(vector<int>& arr, int k) {

        sort(arr.begin(), arr.end());
        int n = arr.size();
        int m = (n - 1) / 2;
        
        multimap<int, int> M;
        for(int i = 0; i < arr.size(); i++) {
            M.insert({abs(arr[i] - arr[m]), i});
        }
        
        vector<int> ans;
        for (auto it = M.rbegin(); it != M.rend() && k != 0; ++it) {
            ans.push_back(arr[it->second]);
            k--;
        }

        return ans;
    }

    // n * log(k)
    vector<int> getStrongest(vector<int>& arr, int k) {
        
        int n = arr.size();
        
		// A STL method in C++ for quick select.
		// Pivot is the (n-1)/2 th element.
        nth_element(arr.begin(), arr.begin() + (n-1)/2, arr.end());
        
        int median = arr[(n-1)/2];
        
        priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<>> pq;
        
        for (int i = 0; i < n; i++) {
            pq.push({abs(arr[i]-median), arr[i]});
            if (pq.size() > k) pq.pop();
        }

        vector<int>res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
    
        return res;
    }

    // n*log(n) + n *log(k) 
    vector<int> doit_heap(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        auto compare = [](auto p1, auto p2) {
            return p1.first > p2.first || p1.first == p2.first && p1.second > p2.second;
        };
        
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        
        // priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, std::greater<>> pq; the same
        priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, decltype(compare)> pq(compare);
        
        for (int i = 0; i < n; i++) {
            pq.push({abs(arr[i]-median), arr[i]});
            if (pq.size() > k) pq.pop();
        }

        vector<int>res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
    
        return res;
    }


    struct compare {
        bool operator() (std::pair<int, int>p1, std::pair<int, int>p2) {
            return (p1.first == p2.first) ? p1.second < p2.second : p1.first < p2.first;
        }
    };

    vector<int> doit_heap(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        sort(arr.begin(), arr.end());
        int median = arr[(n-1)/2];
        
        priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, compare>pq;
        
        for (int i = 0; i < n; i++) {
            pq.push({abs(arr[i]-median), arr[i]});
            if (pq.size() > k)
                pq.pop();
        }

        vector<int>res;
        while (!pq.empty() && k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }
    
        return res;
    }

    /*
        What are we missing?
        
        Do we really need to sort the full array?
        Or do we need to find the (n-1/)2th element for finding median,
        and the first k elements after the question criteria given.

        We will use quickselect to acheive these tasks in O(n) time. (Worst case O(n^2)).

        QuickSelect is basically a partial sort in which we choose a pivot and then keep all smaller elements to the left, and bigger to the right.(We only need this in the question)

        For Finding the median

        Choose Pivot = (n-1)/2.
        Quickselect keeps smaller elements in left, bigger in right.
        So arr[n-1/2] will be the median (as defined by question)

        For finding the kth strongest

        Choose Pivot = k.
        We will use a custom comparator such that quickselect keeps greater elements to left and lower to right.
        First k elements will be the strongest.

        O(n)
    */
    vector<int> doit_quicksort(vector<int>& arr, int k) {

        int n = arr.size();
        
		// A STL method in C++ for quick select.
		// Pivot is the (n-1)/2 th element.
        nth_element(arr.begin(), arr.begin() + (n-1)/2, arr.end());
        
        int median = arr[(n-1)/2];
        
		// choose pivot = k and custom comparator to do as the question asks.
        nth_element(arr.begin(),arr.begin() + k, arr.end(), [&](int a, int b){
           int a1 = abs(a - median), b1 = abs(b - median);
           return a1 == b1 ? a > b : a1 > b1;
        });

        return {begin(arr), begin(arr) + k};
    }
};