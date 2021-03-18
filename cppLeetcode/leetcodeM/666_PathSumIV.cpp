/*
666. Path Sum IV

If the depth of a tree is smaller than 5, then this tree can be represented by a list of three-digits integers.

For each integer in this list:

1. The hundreds digit represents the depth D of this node, 1 <= D <= 4.
2. The tens digit represents the position P of this node in the level it belongs to, 1 <= P <= 8. The position is the same as that in a full binary tree.
3. The units digit represents the value V of this node, 0 <= V <= 9.
Given a list of ascending three-digits integers representing a binary tree with the depth smaller than 5, you need to return the sum of all paths from the root towards the leaves.

It's guaranteed that the given list represents a valid connected binary tree.

Example 1:

Input: [113, 215, 221]
Output: 12
Explanation: 
The tree that the list represents is:
    3
   / \
  5   1

The path sum is (3 + 5) + (3 + 1) = 12.
 

Example 2:

Input: [113, 221]
Output: 4
Explanation: 
The tree that the list represents is: 
    3
     \
      1

The path sum is (3 + 1) = 4.


*/

#include <vector>
#include <unordered_map>
#include <functional>

using std::vector;
using std::unordered_map;

class PathSumIV {

public:

    /*
        Approach #2: Direct Traversal [Accepted]
        Intuition and Algorithm

        As in Approach #1, we will depth-first search on the tree. One time-saving idea is that we can use num / 10 = 10 * depth + pos as a unique identifier for that node. 
        The left child of such a node would have identifier 10 * (depth + 1) + 2 * pos - 1, and the right child would be one greater.

        Complexity Analysis

        Time and Space Complexity: O(N). The analysis is the same as in Approach #1.
    */
    
    int doit_(vector<int>& nums) {
        
        unordered_map<int, int> buf;
        for(auto num: nums)
            buf.emplace(num/10, num%10);

        int ans = 0;
        std::function<void(int, int)> dfs = [&](int path, int total) {

            if (buf.count(path) == 0) return;

            total += buf[path];

            int l = path/10, o = path%10;
            int left = (l+1) * 10 + 2 * o - 1;
            int right = left + 1;

            if (buf.count(left) == 0 && buf.count(right) == 0) {
                ans += total;
                return;
            }

            if (buf.count(left))
                dfs(left, total);
            
            if (buf.count(right))
                dfs(right, total);
        };

        dfs(nums[0]/10, 0);
        return ans;
    }
};