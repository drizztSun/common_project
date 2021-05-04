/*
# 839. Similar String Groups

# Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.

# For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar,
# but "star" is not similar to "tars", "rats", or "arts".

# Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.

# Notice that "tars" and "arts" are in the same group even though they are not similar.
# Formally, each group is such that a word is in the group if and only if it is similar
# to at least one other word in the group.

# We are given a list A of unique strings.  Every string in A is an anagram of every other string in A.
# How many groups are there?

# Example 1:

# Input: ["tars","rats","arts","star"]
# Output: 2
# Note:

# A.length <= 2000
# A[i].length <= 1000
# A.length * A[i].length <= 20000
# All words in A consist of lowercase letters only.
# All words in A have the same length and are anagrams of each other.
# The judging time limit has been increased for this question.

*/
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


using namespace std;

class NumSimilarGroups {

    bool similar(const string& A, const string& B) {
        int res = 0;
        for (auto i = 0; res < 3 && i < A.size(); i++) {
            if (A[i] != B[i])
                res++;
        }
        return res == 2;
    }

    class disjoint_set {
        vector<int> Parent_;
        int size_;

    public:
        disjoint_set(int n) {
            Parent_.resize(n);
            iota(Parent_.begin(), Parent_.end(), 0);
            size_ = n;
        }

        int Find(int x) {
            while (Parent_[x] != x) {
                Parent_[x] = Parent_[Parent_[x]];
                x = Parent_[x];
            }
            return x;
        }

        void Union(int x, int y) {
            x = Find(x);
            y = Find(y);
            if (x != y) {
                Parent_[x] = y;
                size_--;
            }
        }

        int getSize() {
            return size_;
        }

    };

    int doit_disjoint(vector<string>&& A) {

		disjoint_set ds(A.size());

		for (auto i = 0; i < A.size(); i++)
			for (auto j = i + 1; j < A.size(); j++)
				if (similar(A[i], A[j]))
					ds.Union(i, j);

		return ds.getSize();
	}

public:

    int doit_dfs(vector<string>&& strs) {
        
        int n = strs.size();
        vector<bool> visited(n, false);
        vector<vector<int>> graph(n);
        
        auto is_similar = [](const string&a, const string& b) {
            if (a.length() != b.length()) {
                return false;
            }
            
            int diff = 0, first = -1, second = -1;
            for (auto i = 0; i < a.length(); i++) {
                if (a[i] != b[i]) {
                    diff++;
                    if (diff > 2)
                        return false;
                    if (diff == 1)
                        first = i;
                    if (diff == 2)
                        second = i;
                }
            }
            
            if (diff == 1)
                return false;
            
            if (diff == 0)
                return true;
            
            return a[first] == b[second] && a[second] == b[first];
        };
        
        std::function<void(int)> dfs = [&](int a) {
            
            for(auto c : graph[a]) {
                if (!visited[c]) {
                    visited[c] = true;
                    dfs(c);
                }
            }
        };

        for (auto i = 0; i < n; i++)
            for (auto j = i+1; j < n; j++) {
                if (is_similar(strs[i], strs[j])) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        
        int cnt = 0;
        for (auto i = 0; i < n; i++) {
            if (!visited[i]) {
                cnt++;
                visited[i] = true;
                dfs(i);
            }
        }
        
        return cnt;
    }
};