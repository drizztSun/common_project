/*

# 530. Minimum Absolute Difference in BST

# Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

# Example:

# Input:

#    1
#     \
#      3
#     /
#    2

# Output:
# 1
#
# Explanation:
# The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
# Note: There are at least two nodes in this BST.

*/
#include <stdlib.h>
#include <tuple>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};



class MiniAbsDiffInBST {


public:

	tuple<int, int, int> search(TreeNode* node) {
		int a, b, c;
		int minv = node->val, maxv = node->val;
		int mind = INT_MAX;

		if (node->left) {
			tie(a, b, c) = search(node->left);
			minv = b;
			mind = min(c, min(mind, abs(node->val - a)));
		}

		if (node->right) {
			tie(a, b, c) = search(node->right);
			maxv = a;
			mind = min(c, min(mind, abs(b - node->val)));
		}

		return make_tuple(maxv, minv, mind);
	}


	int doit(TreeNode* root) {

		int a, b, c;
		tie(a, b, c) = search(root);
		return c;
	}


	int doit1(TreeNode* root) {

		TreeNode* node = root;
		stack<TreeNode*> st;
		int prev = INT_MAX, minv = INT_MAX;

		while (node || !st.empty()) {

			if (node) {
				st.push(node);
				node = node->left;
			}
			else {
				TreeNode* n = st.top();
				minv = min(minv, abs(n->val - prev));
				prev = n->val;
				node = n->right;
				st.pop();
			}
		}

		return minv;
	}

};



void Test_530_MiniAbsDifferenceInBST() {

	TreeNode root(0);
	TreeNode a1(100), b1(200), c1(40);
	root.right = &a1;
	root.right->right = &b1;
	root.right->left = &c1;

	auto res = MiniAbsDiffInBST().doit(&root);


}