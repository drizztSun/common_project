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


using namespace std;

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



class NumSimilarGroups {
public:
	int doit(vector<string>& A) {
		disjoint_set ds(A.size());

		for (auto i = 0; i < A.size(); i++)
			for (auto j = i + 1; j < A.size(); j++)
				if (similar(A[i], A[j]))
					ds.Union(i, j);

		return ds.getSize();
	}

};


void Test_839_SimilarStringGroups() {

	NumSimilarGroups st;
	int size = st.doit(vector<string>{"tars", "rats", "arts", "star"});

	int res2 = st.doit(vector<string>{"koqnn", "knnqo", "noqnk", "nqkon"});

	return;
}