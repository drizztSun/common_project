/*
421. Maximum XOR of Two Numbers in an Array

Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 ≤ i ≤ j < n.

Follow up: Could you do this in O(n) runtime?

 

Example 1:

Input: nums = [3,10,5,25,2,8]
Output: 28
Explanation: The maximum result is 5 XOR 25 = 28.
Example 2:

Input: nums = [0]
Output: 0
Example 3:

Input: nums = [2,4]
Output: 6
Example 4:

Input: nums = [8,10,2]
Output: 10
Example 5:

Input: nums = [14,70,53,83,49,91,36,80,92,51,66,70]
Output: 127
 

Constraints:

1 <= nums.length <= 2 * 104
0 <= nums[i] <= 231 - 1

*/
#include <vector>
#include <unordered_set>
#include <memory>

using std::unique_ptr;
using std::unordered_set;
using std::vector;

class TwoNumbersWithMaximumXOR {

public:

    /*

    */
    class TrieNode {
    public:
        TrieNode* next[2];
    };

    int doit_trie(vector<int>& nums) 
    {
        TrieNode* root = new TrieNode();
        // build Trie with each num binary content
        for (auto num: nums)
        {
            TrieNode* node = root;
            for (int k = 31; k >=0; k--)
            {
                if (node->next[(num>>k)&1]==NULL)
                    node->next[(num>>k)&1] = new TrieNode();
                node = node->next[(num>>k)&1];
            }
        }

        int ret = 0;
        for (auto num: nums)
        {
            // use each num as target, to go thought this Trie. Trie only has 32 levels. 
            // so time is O(32*n)
            TrieNode* node = root;
            int ans = 0;
            // for each num, go thought the Trie. if nth binary is 1, we seeking 0, then verse. 
            // it means 1 ^ 0. it is the bigger result.
            // if there is no 1 or 0, we do current we have.
            for (int k=31; k>=0; k--)
            {
                if (node->next[1 - (num>>k)&1] != NULL)
                {
                    ans = ans*2+1;
                    node = node->next[1 - (num>>k)&1];
                }                    
                else
                {
                    ans = ans*2+0;
                    node = node->next[(num>>k)&1];
                }
            }
            ret = std::max(ret, ans);
        }
        return ret;
    }

    int doit_hashtable(vector<int>& nums) {

        int max_xor = 0;
        for (int i = 31; i >= 0; i--) {
            max_xor <<= 1;
            unordered_set<int> prefix;
            for (auto c : nums)
                prefix.insert(c >> i);
            
            int cur_xor = max_xor | 1;

            for (auto p : prefix) {
                if (prefix.find(p ^ cur_xor) != prefix.end()) {
                    max_xor = cur_xor;
                    break;
                }
            }
        }
        return max_xor;
    }

    int doit_search(vector<int>& nums) {

        std::function<int(int, int, int, int, int, int )> quickSelect = [&](int ls, int le, int rs, int re, int xval, int bit) {
            if (ls == le || rs == re) return 0;
            if (bit == -1) return xval;
            int mask = 1 << bit;
            int i = ls, j = rs;
            for (int k = ls; k < le; k++) {
                if (nums[k] & mask) swap(nums[i++], nums[k]);
            }
            for (int k = rs; k < re; k++) {
                if (nums[k] & mask) swap(nums[j++], nums[k]);
            }
            int res = max(quickSelect(ls, i, j, re, xval|mask, bit-1),
                        quickSelect(i, le, rs, j, xval|mask, bit-1));

            return res != 0 ? res : quickSelect(ls, le, rs, re, xval, bit-1);
        };

        return quickSelect(0, nums.size(), 0, nums.size(), 0, 30);
    } 

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
    */

    class Trie {
    public:
        Trie(): children(2) {}
        vector<unique_ptr<Trie>> children;
    };

    int doit_trie(vector<int>& nums) {

        Trie root;
        auto insert = [&](int num) {
            Trie* p = &root;
            for (int i = 31; i >= 0; i--){
                
                int bit = (num >> i) & 1;

                if (!p->children[bit])
                    p->children[bit] = std::make_unique<Trie>();
                
                p = p->children[bit].get();
            }
        };

        auto query = [&](int num){

            int ans = 0;
            Trie* node = &root;

            for (int i = 32; i >= 0; i--) {
                
                int bit = (num >> i) & 1;
                if (node->children[1 - bit]) {
                    ans |= 1 << i;
                    node = node->children[1-bit].get();
                } else {
                    node = node->children[bit].get();
                }
            }
            return ans;
        };

        for (auto num: nums)
            insert(num);

        int ans = 0;
        for (auto num: nums)
            ans = std::max(ans, query(num));
        return ans;
    }
};