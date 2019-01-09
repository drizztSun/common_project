

/*



*/

#include <map>
#include <algorithm>
using namespace std;

class MyCalendarThree1 {

	std::map<int, int> pts_;

public:

	MyCalendarThree1() {}

	int book(int start, int end) {
		pts_[start]++;
		pts_[end]--;

		int ongoing = 0, K = 0;
		for (pair<int, int> item : pts_) {
			ongoing += item.second;
			K = max(K, ongoing);
		}
		
		return K;
	}
};


class MyCalendarThree2 {

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

	MyCalendarThree2() {
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