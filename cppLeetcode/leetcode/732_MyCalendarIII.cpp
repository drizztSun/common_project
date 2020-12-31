/*
# 732. My Calendar III

# Implement a MyCalendarThree class to store your events. A new event can always be added.

# Your class will have one method, book(int start, int end).
# Formally, this represents a booking on the half open interval [start, end),
# the range of real numbers x such that start <= x < end.

# A K-booking happens when K events have some non-empty intersection
# (ie., there is some time that is common to all K events.)

# For each call to the method MyCalendar.book, return an integer K representing the largest integer
# such that there exists a K-booking in the calendar.

# Your class will be called like this: MyCalendarThree cal = new MyCalendarThree(); MyCalendarThree.book(start, end)

# Example 1:
# MyCalendarThree();
# MyCalendarThree.book(10, 20); // returns 1
# MyCalendarThree.book(50, 60); // returns 1
# MyCalendarThree.book(10, 40); // returns 2
# MyCalendarThree.book(5, 15); // returns 3
# MyCalendarThree.book(5, 10); // returns 3
# MyCalendarThree.book(25, 55); // returns 3

# Explanation:
# The first two events can be booked and are disjoint, so the maximum K-booking is a 1-booking.
# The third event [10, 40) intersects the first event, and the maximum K-booking is a 2-booking.
# The remaining events cause the maximum K-booking to be only a 3-booking.
# Note that the last event locally causes a 2-booking, but the answer is still 3 because
# eg. [10, 20), [10, 40), and [5, 15) are still triple booked.
# Note:

# The number of calls to MyCalendarThree.book per test case will be at most 400.
# In calls to MyCalendarThree.book(start, end), start and end are integers in the range [0, 10^9].
"""

"""
Approach #1: Boundary Count [Accepted]
Intuition and Algorithm

When booking a new event [start, end), count delta[start]++ and delta[end]--. 
When processing the values of delta in sorted order of their keys, the largest such value is the answer.

In Python, we sort the set each time instead, as there is no analog to TreeMap available.

Complexity Analysis

Time Complexity: O(N^2), where N is the number of events booked. For each new event, we traverse delta in O(N) time. 
In Python, this is O(N^2*logN) owing to the extra sort step.

Space Complexity: O(N), the size of delta.
*/
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

class MyCalendarIII {

	/*
	732.My-Calendar-III
	此题有奇思妙解.

	我们设计一个顺序的multiset<pair<int,int>>Set,每次调用我们就往里面放置{start,1}和{end,-1}.然后遍历这个集合,按照从小到大的顺序更新一个计数器,遇到1就加一,遇到-1就减一.

	奇妙的就是,你这样可以实时得到的,就是当前k booking的状态.遍历完之后这个计数器的历史最大值就是答案.
	*/

	std::map<int, int> pts_;

public:

	MyCalendarIII() {}

	int book(int start, int end) {

		pts_[start]++;
		pts_[end]--;

		int ongoing = 0, K = 0;
		for (auto& item : pts_) {
			ongoing += item.second;
			K = std::max(K, ongoing);
		}
		
		return K;
	}
};


class MyCalendarIIISegementTree {

public:

	class Node {

	public:
		
		Node *left;
		Node *right;
		int count = 0;
		int x = 0;
		int y = 0;
		int mid = -1;

		Node(int x, int y, int count) {
			this->x = x;
			this->x = x;
			this->y = y;
			this->count = count;
			this->mid = -1;
		}
	};

	MyCalendarIIISegementTree() {
		this->root = new Node(0, 1000000000, 0);
	}

	int book(int start, int end) {
		add(start, end, root);
		return ans;
	}

private:

	int ans = 0;
	Node* root;

	void add(int start, int end, Node* root) {

		if (root->mid != -1) {
			if (start >= root->mid) {
				add(start, end, root->right);
			}
			else if (end <= root->mid) {
				add(start, end, root->left);
			}
			else {
				add(start, root->mid, root->left);
				add(root->mid, end, root->right);
			}
		}
		else {
			if (start == root->x && end == root->y) {
				root->count++;
				ans = max(ans, root->count);
			}
			else if (start == root->x) {
				root->mid = end;
				root->left = new Node(root->x, root->mid, root->count + 1);
				root->right = new Node(root->mid, root->y, root->count);
				ans = max(ans, root->count + 1);
			}
			else if (end == root->y) {
				root->mid = start;
				root->left = new Node(root->x, root->mid, root->count);
				root->right = new Node(root->mid, root->y, root->count + 1);
				ans = max(ans, root->count + 1);
			}
			else {
				root->mid = start;
				root->left = new Node(root->x, root->mid, root->count);
				root->right = new Node(root->mid, root->y, root->count);
				add(start, end, root->right);
			}
		}
	}

};

struct STreeNode
{
	STreeNode(int s, int e, int c = 1) :
		start(s), end(e), left(NULL), right(NULL), count(c) {
	
	}

	int start, end;
	int count;
	STreeNode* left, *right;

	int insert(STreeNode*& root)
	{
		if (root == NULL)
		{
			root = this;
			return root->count;
		}
		else if (start >= root->end)
			return  this->insert(root->right);

		else if (end <= root->start)
			return  this->insert(root->left);
		
		else
		{
			int leftreturn = 0, rightreturn = 0;
			if (start < root->start)
			{
				STreeNode* newleft = new STreeNode(start, root->start);
				leftreturn = newleft->insert(root->left);
			}
			else if (start > root->start)
			{
				STreeNode* newleft = new STreeNode(root->start, start, root->count);
				newleft->left = root->left;
				root->left = newleft;
				root->start = start;
			}

			if (end > root->end)
			{
				STreeNode* newright = new STreeNode(root->end, end);
				rightreturn = newright->insert(root->right);
			}
			else if (end < root->end)
			{
				STreeNode* newright = new STreeNode(end, root->end, root->count);
				newright->right = root->right;
				root->right = newright;
				root->end = end;
			}

			++(root->count);
			return max(leftreturn, max(root->count, rightreturn));

		}
	}

};


class MyCalendarThree {
public:
	STreeNode* root;
	int curCount;
	MyCalendarThree() :root(NULL), curCount(0) {

	}

	int book(int start, int end) {
		STreeNode* node = new STreeNode(start, end);
		int count = node->insert(root);
		curCount = max(count, curCount);
		return curCount;
	}
};

void Test_732_MyCalendarThree() {

	MyCalendarThree obj;

	int res = -1;

	res = obj.book(10, 20);
	res = obj.book(50, 60);
	res = obj.book(10, 40);
	res = obj.book(5, 15);
	res = obj.book(5, 10);
	res = obj.book(25, 55);

	return;
}