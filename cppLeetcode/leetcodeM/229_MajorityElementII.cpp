/*
169. Majority Element

Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-231 <= nums[i] <= 231 - 1
 

Follow-up: Could you solve the problem in linear time and in O(1) space?

*/
#include <vector>

using std::vector;


class MajorityElement {

public:

    int doit_Boyer_Moore(vector<int>& nums) {
        int candidate = 0, counter = 0;

        for (auto c : nums) {
            if (counter == 0)
                candidate = c;

            counter += candidate == c ? 1 : -1;
        }

        return candidate;
    }
};


/*
229. Majority Element II

Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

Follow-up: Could you solve the problem in linear time and in O(1) space?

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 

Constraints:

1 <= nums.length <= 5 * 10^4
-109 <= nums[i] <= 10^9

*/


class MajorityElementII {

public:

    /*
        Approach 1: Boyer-Moore Voting Algorithm
        Intuition

        To figure out a O(1) space requirement, we would need to get this simple intuition first. For an array of length n:

        There can be at most one majority element which is more than ⌊n/2⌋ times.
        There can be at most two majority elements which are more than ⌊n/3⌋ times.
        There can be at most three majority elements which are more than ⌊n/4⌋ times.
        and so on.

        Knowing this can help us understand how we can keep track of majority elements which satisfies O(1)O(1) space requirement.

        Let's try to get an intuition for the case where we would like to find a majority element which is more than ⌊n/2⌋ times in an array of length n.

        The idea is to have two variables, one holding a potential candidate for majority element and a counter to keep track of whether to swap a potential candidate or not. Why can we get away with only two variables? Because there can be at most one majority element which is more than ⌊n/2⌋ times. Therefore, having only one variable to hold the only potential candidate and one counter is enough.

        While scanning the array, the counter is incremented if you encounter an element which is exactly same as the potential candidate but decremented otherwise. When the counter reaches zero, the element which will be encountered next will become the potential candidate. Keep doing this procedure while scanning the array. However, when you have exhausted the array, you have to make sure that the element recorded in the potential candidate variable is the majority element by checking whether it occurs more than ⌊n/2⌋ times in the array. In the original Majority Element problem, it is guaranteed that there is a majority element in the array so your implementation can omit the second pass. However, in a general case, you need this second pass since your array can have no majority elements at all!

        The counter is initialized as 0 and the potential candidate as None at the start of the array.

        Current
        1 / 10
        If an element is truly a majority element, it will stick in the potential candidate variable, no matter how it shows up in the array (i.e. all clustered in the beginning of the array, all clustered near the end of the array, or showing up anywhere in the array), after the whole array has been scanned. Of course, while you are scanning the array, the element might be replaced by another element in the process, but the true majority element will definitely remain as the potential candidate in the end.

        Now figuring out the majority elements which show up more than ⌊n/3⌋ times is not that hard anymore. Using the intuition presented in the beginning, we only need four variables: two for holding two potential candidates and two for holding two corresponding counters. Similar to the above case, both candidates are initialized as None in the beginning with their corresponding counters being 0. While going through the array:

        If the current element is equal to one of the potential candidate, the count for that candidate is increased while leaving the count of the other candidate as it is.
        If the counter reaches zero, the candidate associated with that counter will be replaced with the next element if the next element is not equal to the other candidate as well.
        Both counters are decremented only when the current element is different from both candidates.
        Current
        1 / 10
        Implementation


        Complexity Analysis

        Time complexity : O(N) where NN is the size of nums. We first go through nums looking for first and second potential candidates. We then count the number of occurrences for these two potential candidates in nums. Therefore, our runtime is O(N) + O(N) = O(2N) \approx O(N)O(N)+O(N)=O(2N)≈O(N).

        Space complexity : O(1) since we only have four variables for holding two potential candidates and two counters. Even the returning array is at most 2 elements.
    
    */


    vector<int> doit_(vector<int>& nums) {

        int cnt1 = 0, cnt2 = 0, candidate1 = INT_MIN, candidate2 = INT_MIN;

        for (auto c : nums) {

            if (candidate1 == c) {
                cnt1++;
            } else if (candidate2 == c) {
                cnt2++;
            } else if (cnt1 == 0) {
                candidate1 = c;
                cnt1++;
            } else if (cnt2 == 0) {
                candidate2 = c;
                cnt2++;
            } else {
                cnt2--;
                cnt1--;
            }
        }
        
        vector<int> ans;
        for (auto c1 : {candidate1, candidate2}) {
            int cnt = 0;
            for (auto c: nums)
                if (c == c1) cnt++;
            
            if (cnt > nums.size() / 3)
                ans.push_back(c1);
        }
        
        return ans;
    }

    /*
        229.Majority-Element-II
        本题的解法非常巧妙，令人印象深刻。第一次不会做没有关系，但第二次遇到就应该能牢牢记住。

        解法的基本思想就是：如果同时消去数组中互不相同的三个数，那么在剩下的数组中，超过1/3的那些数仍然是超过1/3的。所以我们只要不停找到三个互不相同的数并做消去，剩下的就是超过1/3的那些数（最多两个）。

        所以我们在遍历nums数组的过程中，设置两个容器：如果有对应是相同元素的容器，那么就放进那个容器里；如果容器有空的，那么新进来的数就放进容器里；如果两个容器都非空，并且这三个数互不相同，那么就把这三个都消去。

        注意，遍历完之后，最后剩下的两个容器里有可能都是答案，需要单独验证。

        显然，本题可以扩展到定义大于 N/4, N/5 ... 的majority element。只要设置更多的容器即可。      
    */
    vector<int> doit_greedy(vector<int>& nums) 
    {
        int x1,x2;
        int count1=0,count2=0;
        
        for (int i=0; i<nums.size(); i++)
        {
            if (count1>0 && nums[i]==x1)
            {
                count1++;
            }
            else if (count2>0 && nums[i]==x2)
            {
                count2++;
            }
            else if (count1==0)
            {
                x1=nums[i];
                count1=1;
            }
            else if (count2==0)
            {
                x2=nums[i];
                count2=1;
            }
            else if (nums[i]!=x1 && nums[i]!=x2)
            {
                count1--;
                count2--;
            }            
        }
                
        vector<int>results;
        count1=0;
        count2=0;
        for (int i=0; i<nums.size(); i++)
        {
            if (nums[i]==x1) count1++;
            if (nums[i]==x2) count2++;
        }  
        if (count1>nums.size()/3) results.push_back(x1);
        if (x1!=x2 && count2>nums.size()/3) results.push_back(x2);
        
        return results;
    }

};