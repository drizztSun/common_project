/*
1424. Diagonal Traverse II


Given a list of lists of integers, nums, return all elements of nums in diagonal order as shown in the below images.
 

Example 1:



Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,4,2,7,5,3,8,6,9]
Example 2:



Input: nums = [[1,2,3,4,5],[6,7],[8],[9,10,11],[12,13,14,15,16]]
Output: [1,6,2,8,7,3,9,4,12,10,5,13,11,14,15,16]
Example 3:

Input: nums = [[1,2,3],[4],[5,6,7],[8],[9,10,11]]
Output: [1,4,2,5,3,8,6,9,7,10,11]
Example 4:

Input: nums = [[1,2,3,4,5,6]]
Output: [1,2,3,4,5,6]
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i].length <= 10^5
1 <= nums[i][j] <= 10^9
There at most 10^5 elements in nums.
*/

#include <vector>

using std::vector;


class DuagonalTraverseMatrix {

public:
    vector<int> doit_(vector<vector<int>>& nums) {
       
        int m = nums.size();
        int maxcolumns = 0;
        for (int i = 0; i < m; i++)
            maxcolumns = std::max(maxcolumns, int(nums[i].size()));
        
        vector<vector<int>> buff(m + maxcolumns - 1);
        int total = 0;
        for (int i = 0; i < m; i++) {
            total += nums[i].size();
            for (int j = 0; j < nums[i].size(); j++) {
                buff[i+j].push_back(nums[i][j]);
            }
        }
        
        vector<int> res(total);
        int t = 0;
        for (int i = 0; i < buff.size(); i++) {
            for (auto it = rbegin(buff[i]); it != rend(buff[i]); it++) {
                res[t++] = *it; 
            }
        }
        
        return res;
    }
};