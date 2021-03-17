/*
# 753. Cracking the Safe

# There is a box protected by a password. The password is n digits,
# where each letter can be one of the first k digits 0, 1, ..., k-1.

# You can keep inputting the password, the password will automatically be matched against the last n digits entered.

# For example, assuming the password is "345", I can open it when I type "012345", but I enter a total of 6 digits.

# Please return any string of minimum length that is guaranteed to open the box after the entire string is inputted.

# Example 1:
# Input: n = 1, k = 2
# Output: "01"
# Note: "10" will be accepted too.

# Example 2:
# Input: n = 2, k = 2
# Output: "00110"
# Note: "01100", "10011", "11001" will be accepted too.

# Note:
# n will be in the range [1, 4].
# k will be in the range [1, 10].
# k^n will be at most 4096.

*/

#include <string>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>


using namespace std;


class CrackSafe {

	/*
		753.Cracking-the-Safe
		这道题是一个被研究过的经典问题，称为De Bruijin序列。Wikipedia有专门介绍的页面。这个问题可以转化为一个特定的有向图，求问是否有一条最短的路径使得能遍历所有的节点。答案是可以的，而且这个路径非常优秀，每个节点可以只需要访问一次，我们称这样的有向图是存在哈密尔顿路径的。

		注意，De Buijing序列并不是唯一的，有很多种生成方式。这里介绍一个比较简单的算法。就是将已经经历过的密码组合，取前n-1位作为key，最后一位作为val，放入哈希表中。
		当我们想在序列里添加一个新字符的时候，取当前序列的末尾n-1位作为哈希表的key，看看它对应的val是多少（注意val是之前已经尝试过的），那么这次我就在序列后添加val+1，这样就能生成一个新的n位的密码组合（记得同时更新哈希表的key-val）。依次重复下去，直到生成所有的k^n种密码组合为止。

		上面算法其实有个assumption，那就是任意的n-1位组成的key，恰好会在这个过程中出现k次，不会更多也不会更少。事实上这个assumption是满足的，但证明过程就不深究了。
	*/
	string crackSafe(int n, int k) 
    {
        string ans;
        ans.assign(n-1,'0');
        unordered_map<string,int> record;
        
        int total = pow(k,n);
        
        for (int i=0; i<total; i++)
        {
            string temp = ans.substr(ans.size()-(n-1),(n-1));
            record[temp] = (record[temp]+1)%k;;
            ans+= '0'+record[temp];
        }
        return ans;
    }

public:

	/*
		Approach #1: Hierholzer's Algorithm [Accepted]
		Intuition

		We can think of this problem as the problem of finding an Euler path (a path visiting every edge exactly once) on the following graph: there are k^{n-1}k 
		n−1
		nodes with each node having kk edges.

		For example, when k = 4, n = 3, the nodes are '00', '01', '02', ..., '32', '33' and each node has 4 edges '0', '1', '2', '3'. A node plus edge represents a complete edge and viewing that substring in our answer.

		Any connected directed graph where all nodes have equal in-degree and out-degree has an Euler circuit (an Euler path ending where it started.) Because our graph is highly connected and symmetric, we should expect intuitively that taking any path greedily in some order will probably result in an Euler path.

		This intuition is called Hierholzer's algorithm: whenever there is an Euler cycle, we can construct it greedily. The algorithm goes as follows:

		Starting from a vertex u, we walk through (unwalked) edges until we get stuck. Because the in-degrees and out-degrees of each node are equal, we can only get stuck at u, which forms a cycle.

		Now, for any node v we had visited that has unwalked edges, we start a new cycle from v with the same procedure as above, and then merge the cycles together to form a new cycle u \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow v \rightarrow \dots \rightarrow uu→⋯→v→⋯→v→⋯→u.

		Algorithm

		We will modify our standard depth-first search: instead of keeping track of nodes, we keep track of (complete) edges: seen records if an edge has been visited.

		Also, we'll need to visit in a sort of "post-order", recording the answer after visiting the edge. This is to prevent getting stuck. For example, with k = 2, n = 2, we have the nodes '0', '1'. If we greedily visit complete edges '00', '01', '10', we will be stuck at the node '0' prematurely. However, if we visit in post-order, we'll end up visiting '00', '01', '11', '10' correctly.

		In general, during our Hierholzer walk, we will record the results of other subcycles first, before recording the main cycle we started from, just as in our first description of the algorithm. Technically, we are recording backwards, as we exit the nodes.

		For example, we will walk (in the "original cycle") until we get stuck, then record the node as we exit. (Every edge walked is always marked immediately so that it can no longer be used.) Then in the penultimate node of our original cycle, we will do a Hierholzer walk and then record this node; then in the third-last node of our original cycle we will do a Hierholzer walk and then record this node, and so on.


		Complexity Analysis

		Time Complexity: O(n * k^n). We visit every edge once in our depth-first search, and nodes take O(n)O(n) space.

		Space Complexity: O(n * k^n), the size of seen.
	*/
	

	string doit(int n, int k) {

		string ans(n, '0');

		unordered_set<string> visited;
		visited.insert(ans);

		for (auto i = 0; i < pow(k, n); i++) {
			string cur = ans.substr(ans.length() - (n - 1), n - 1);

			for (auto j = k-1; j >= 0; j--) {
				string tmp = cur + to_string(j);
				if (visited.find(tmp) == visited.end()) {
					visited.insert(tmp);
					ans += to_string(j);
					break;
				}
			}
		}
		return ans;
	}

	string doit1(int n, int k) {

		int postfixCount = (int) pow(k, n - 1);
		int total = (int) pow(k, n);
		std::vector<bool> visit(total);
		string result(n, '0');
		visit[0] = true;
		int cur = 0;

		for (int i = 1; i < total; i++)
		{
			// cur = d1 d2 ... d[k] => prefix = d2 d3 ... d[k] 0
			int prefix = (cur % postfixCount) * k;

			for (int j = k - 1; j >= 0; j--)
			
				if (visit[prefix + j] == false)
				{
					cur = prefix + j;
					visit[cur] = true;
					result += '0' + j;
					break;
				}
		}

		return result;
	}
};