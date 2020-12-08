/*

 659. Split Array into Consecutive Subsequences


 Given an array nums sorted in ascending order, return true if and only if you can split it into 1 or more subsequences such that each subsequence consists of consecutive integers and has length at least 3.

  

 Example 1:

 Input: [1,2,3,3,4,5]
 Output: True
 Explanation:
 You can split them into two consecutive subsequences :
 1, 2, 3
 3, 4, 5
 Example 2:

 Input: [1,2,3,3,4,4,5,5]
 Output: True
 Explanation:
 You can split them into two consecutive subsequences :
 1, 2, 3, 4, 5
 3, 4, 5
 Example 3:

 Input: [1,2,3,4,4,5]
 Output: False
  

 Constraints:

 1 <= nums.length <= 10000


 */

#include <unordered_map>
#include <vector>


using std::unordered_map;
using std::vector;


class SplitArrayIntoConsecutiveSubsequences {
    
public:
    bool doit_greedy(vector<int>& nums) {
        
        unordered_map<int, int> tail;
        unordered_map<int, int> counter;
        
        for (auto c : nums)
            counter[c]++;
        
        for (auto x : nums) {
            
            if (counter[x] == 0)
                continue;
            
            if (tail[x] > 0) {
                tail[x]--;
                tail[x+1]++;
            } else if (counter[x+1] > 0 && counter[x+2] > 0) {
                counter[x+1]--;
                counter[x+2]--;
                tail[x+3]++;
            } else {
                return false;
            }
            
            counter[x]--;
        }
        
        return true;
    }
};
