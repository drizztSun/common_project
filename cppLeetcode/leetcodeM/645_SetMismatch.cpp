/*
645. Set Mismatch

You have a set of integers s, which originally contains all the numbers from 1 to n. Unfortunately, due to some error, 
one of the numbers in s got duplicated to another number in the set, which results in repetition of one number and loss of another number.

You are given an integer array nums representing the data status of this set after the error.

Find the number that occurs twice and the number that is missing and return them in the form of an array.

 

Example 1:

Input: nums = [1,2,2,4]
Output: [2,3]
Example 2:

Input: nums = [1,1]
Output: [1,2]
 

Constraints:

2 <= nums.length <= 104
1 <= nums[i] <= 104

*/

#include <vector>


using std::vector;


class ErrorNums {

    /*
        645.Set-Mismatch
        此题其实就是442.Find-All-Duplicates-in-an-Array和448.Find-All-Numbers-Disappeared-in-an-Array的拼接。最后遍历到nums[i]!=i的位置时，说明nums[i]是duplicated number，而i就是missing number.
    */
    vector<int> findErrorNums(vector<int>& nums) 
    {
        int n = nums.size();
        nums.insert(nums.begin(), 0);
        for (int i=1; i<=n; i++)
        {
            while (nums[i]!=i && nums[i]<=n+1 && nums[i]!=nums[nums[i]])
            {
                std::swap(nums[i], nums[nums[i]]);
            }
        }
        
        for (int i=1; i<=n; i++)
        {
            if (nums[i]!=i)
               return {nums[i],i}; 
        }

        return {-1,-1};   
    }


public:
    
    
    vector<int> doit_indexing(vector<int>& nums) {

        int n = nums.size();
        vector<int> ans;

        for (int i = 0; i < nums.size(); i++) {

            while (nums[i] != i+1) {

                if(nums[nums[i]-1] == nums[i]) {
                    if (ans.empty())
                        ans.push_back(nums[i]);
                    break;
                }

                std::swap(nums[i], nums[nums[i]-1]);
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != i+1) {
                ans.push_back(i+1);
                break;
            }
        }

        return ans;
    }
};

