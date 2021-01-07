/*
1707. Maximum XOR With an Element From Array

You are given an array nums consisting of non-negative integers. You are also given a queries array, where queries[i] = [xi, mi].

The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi. 
In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. If all elements in nums are larger than mi, then the answer is -1.

Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.

 

Example 1:

Input: nums = [0,1,2,3,4], queries = [[3,1],[1,3],[5,6]]
Output: [3,3,7]
Explanation:
1) 0 and 1 are the only two integers not greater than 1. 0 XOR 3 = 3 and 1 XOR 3 = 2. The larger of the two is 3.
2) 1 XOR 2 = 3.
3) 5 XOR 2 = 7.
Example 2:

Input: nums = [5,2,4,6,6,3], queries = [[12,4],[8,1],[6,3]]
Output: [15,-1,5]
 

Constraints:

1 <= nums.length, queries.length <= 10^5
queries[i].length == 2
0 <= nums[j], xi, mi <= 10^9


*/
#include <vector>
#include <memory>
#include <algorithm>

using std::vector;
using std::unique_ptr;


class MaximizeXor {

public:

    /*
        We can build a prefix tree (Trie) to answer whether there is a number in the array starts with a given substring in O(1)

        1) If there is only one path, follow that path.
        2) If there are two paths, chose the complement one, e.g. 1 - current_bit.

        We move in the trie from hightest bit to lowest bit.
        (31 bits for signed 32-bit integers)

        For each number
        We query the Trie in O(31)

        Time complexity: O(31*n)
        Space complexity: O(31*n)



        Go back to the original problem, we can use the similar idea to solve it but need some transformations first.
        Since all the queries are given as once (offline processing), we can process them in any order.

        Silmilar to LC 1697 checking existence of Edge length limited paths. 

        1. Sort queries by limit.
        2. Sort numbers.


        We can build the trie on the fly: inserting numbers that are less or equal to the limit of the current query, query the trie to find the maximum xor of the current number
        and numbers in the given array that are <= limit.


        We can build the trie on the fly by sorting nums in ascending order and queries by its limit, insert nums into the trie up the limit.

        Time complexity: O(nlogn + QlogQ)
        Space complexity: O(n)

    */

    class Trie {
    public:
        Trie(): children{nullptr, nullptr} {}  
        Trie* children[2];
    };

    vector<int> doit_trie(vector<int>& nums, vector<vector<int>>& queries) {

        const int n = nums.size();
        sort(begin(nums), end(nums));    
        
        const int Q = queries.size();
        for (int i = 0; i < Q; ++i)
            queries[i].push_back(i);

        std::sort(begin(queries), end(queries), [](const auto& q1, const auto& q2) {
            return q1[1] < q2[1];
        });
        
        Trie root;    
        auto insert = [&](int num) {
            Trie* node = &root; 
            for (int i = 31; i >= 0; --i) {
                int bit = (num >> i) & 1;
                if (!node->children[bit])
                    node->children[bit] = new Trie();
                node = node->children[bit];
            }
        };
            
        auto query = [&](int num) {
            Trie* node = &root;
            int sum = 0;
            for (int i = 31; i >= 0; --i) {
                if (!node) return -1;
                int bit = (num >> i) & 1;
                if (node->children[1 - bit]) {
                    sum |= (1 << i);
                    node = node->children[1 - bit];
                } else {
                    node = node->children[bit];
                }
            }
            return sum;
        };
        
        vector<int> ans(Q);
        int i = 0;
        for (const auto& q : queries) {
            
            while (i < n && nums[i] <= q[1]) insert(nums[i++]);

            ans[q[2]] = query(q[0]);
        }  
        return ans;
    }

    /*

    1707.Maximum-XOR-With-an-Element-From-Array
    我们将query按照m的大小逐个处理。对于每个query而言，就是在一堆数里面挑选一个与x亦或值最大的数。
    因此，本题的本质就是421. Maximum XOR of Two Numbers in an Array.具体算法是：我们将这堆数按照32位二进制编码构造一个Trie，然后在这棵前缀树里，尽量按照x的相反数（bit-flipped）去探索，只需要移动32次就能找到与x亦或值最大的数。

    接下来再处理下一个query时，我们只需要在已有的前缀树里再增加若干节点即可（也就是比当前m小的数），然后同样地重复之前的步骤。

    这种对于query排序的思路，很像1697.Checking-Existence-of-Edge-Length-Limited-Paths。在1697中，每次处理新query之前，会在一个已有的union网络里添加一些新的连接。

    */
    class TrieNode
    {
        public:
        TrieNode* next[2];
    };
    static bool cmp(vector<int>&a, vector<int>&b)
    {
        return a[1]<b[1];
    }
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) 
    {        
        int n = queries.size();
        for (int i=0; i<queries.size(); i++)
            queries[i].push_back(i);
        sort(queries.begin(), queries.end(), cmp);
        sort(nums.begin(), nums.end());

        vector<int>rets(n);
        TrieNode* root = new TrieNode();        
        int i = 0;
        for (auto q: queries)
        {
            while (i<nums.size() && nums[i]<=q[1])
            {
                TrieNode* node = root;
                for (int k=31; k>=0; k--)
                {
                    if (node->next[(nums[i]>>k)&1]==NULL)
                        node->next[(nums[i]>>k)&1] = new TrieNode();
                    node = node->next[(nums[i]>>k)&1];
                }
                i++;
            }
            
            if (i==0)
            {
                rets[q[2]]=-1;
                continue;
            }
                        
            TrieNode* node = root;
            int ret = 0;
            for (int k=31; k>=0; k--)
            {
                if (node->next[1-((q[0]>>k)&1)] != NULL)
                {
                    node = node->next[1-((q[0]>>k)&1)];
                    ret = ret*2 + 1;
                }                    
                else
                {
                    node = node->next[((q[0]>>k)&1)];
                    ret = ret*2 + 0;
                }
            }
            rets[q[2]] = ret;            
        }
        return rets;        
    }
};