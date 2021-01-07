/*
692. Top K Frequent Words

Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.


*/

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using std::priority_queue;
using std::unordered_map;
using std::string;
using std::vector;


class TopKFrequent {

public:

    /*
    Partial sort makes a heap with the first k elements, swaps in the elements that compare true to the first k and sorts the heap after all the elements have been compared.

    Partial sort can be replaced by:

    std::nth_element(v.begin(), v.begin() + k, v.end(), freq_comp);
    std::sort(v.begin(), v.begin() + k, freq_comp);
    This has better asymptotic complexity of O(n + klog(k)) for k not on the order of n, but has worse real life performance with randomized input: https://www.quora.com/Why-is-STLs-partial_sort-slower-than-the-asymptotic-lower-bound

    If the returned list did not have to be ordered as in the case of https://leetcode.com/problems/top-k-frequent-elements, a simple std::nth_element call would be sufficient with time complexity O(n).
    */
    vector<string> doit_(vector<string>& words, int k) {
        
        std::unordered_map<string, size_t> m;
        
        for (auto& w : words)
        {
            auto it = m.find(w);
            if (it == m.end())
                m.emplace(std::move(w), 0);
            else
                ++it->second;
        }
        
        vector<string> v;
        v.reserve(m.size());
        for (auto& item : m)
            v.emplace_back(item.first);
        
        auto freq_comp = [&] (const auto& lhs, const auto& rhs)
        {
            const auto freq_lhs = m[lhs];
            const auto freq_rhs = m[rhs];
            
            if (freq_lhs == freq_rhs)
                return lhs < rhs;
            else
                return freq_lhs > freq_rhs;
        };

        std::partial_sort(v.begin(), v.begin() + k, v.end(), freq_comp);
        
        v.resize(k);
        return v;
    }

    /*
        Min Heap (unordered_map and Priority Queue)
        If you don't want to make a custom comparator, use a Min Heap. More info by @codedayday available here
        Time Complexity: O (N (log K))
        Space Complexity: O (N)
    */
    vector<string> doit_heap(vector<string>& words, int k) {
        unordered_map <string, int> umap;
        for (string s: words) umap[s]++;

        priority_queue <std::pair<int, string>> pq;
        for (auto it: umap) {
            pq.push({-it.second, it.first});
            if(pq.size() > k) 
                pq.pop();
        }
        
        vector <string> res;
        while (k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        
        reverse (res.begin(), res.end());
        return res;
    }

    /*
        Max Heap (unordered_map and Priority Queue)
        If you want to make a custom comparator, use Max Heap.
        Time Complexity: O ((N+K) (log K))
        Space Complexity: O (N)
    */
    struct Comp {
        bool operator()(const std::pair<int, string>& lhs, const std::pair<int, string>& rhs) const {
            if (lhs.first != rhs.first)
                return lhs.first < rhs.first;
            return lhs.second > rhs.second;
        } //for more info refer Resource#3 mentioned below
    };
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map <string, int> umap;
        for (string s: words) umap[s]++;

        priority_queue <std::pair<int, string>, vector<std::pair<int, string>>, Comp> pq;
        for (auto it: umap) {
            pq.push({it.second, it.first});
        }

        vector <string> res;
        while (k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }

    /*
    Quick Select
    Time Complexity: Well, Quick Select is supposed to be O (N) in average case and O (N^2) but, I am sorting the tempRes function in the end which adds a time complexity of O (unique elements in array * (log of unique elements in array). 
    I am sure someone could improvise on this.
    Space Complexity: O (N)
    */
   int partition(vector<std::pair<int, string>>& tempRes, int start, int end) {
        int pivot = tempRes[start].first, s = start + 1, e = end;
        while (s <= e) {
            if (tempRes[s].first < pivot && tempRes[e].first > pivot) 
                swap(tempRes[s++], tempRes[e--]);
            if (tempRes[s].first >= pivot) s++;
            if (tempRes[e].first <= pivot) e--;
        }
        swap(tempRes[start], tempRes[e]);
        return e;
    }

    int quickSort(vector<std::pair<int, string>>& tempRes, int k) {
        int start = 0, end = tempRes.size() - 1;
        while (true) {
            int index = partition(tempRes, start, end);
            if (index == k - 1) 
                return index;
            if (index < k - 1) 
                start = index + 1;
            else 
                end = index - 1;
        }
    }
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map <string, int> umap;
        for (string s: words) umap[s]++;

        vector <std::pair<int, string>> tempRes;
        for (auto it: umap) {
            tempRes.push_back({it.second, it.first});
        }

        int index = quickSort(tempRes, k);
        sort (tempRes.begin(), tempRes.end(), [](std::pair <int, string> s1, std::pair <int, string>s2) {
            if (s1.first!=s2.first) return s1.first>s2.first;
            return s1.second<s2.second;
        });

        vector <string> res;
        for (int i=0; i<k; i++){
            res.push_back(tempRes[i].second);
        }
        return res;
    }  
};