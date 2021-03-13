/*
532. K-diff Pairs in an Array



Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.

A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:

0 <= i, j < nums.length
i != j
|nums[i] - nums[j]| == k
Notice that |val| denotes the absolute value of val.

 

Example 1:

Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.
Example 2:

Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
Example 3:

Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
Example 4:

Input: nums = [1,2,4,4,3,3,0,9,2,3], k = 3
Output: 2
Example 5:

Input: nums = [-1,-2,-3], k = 1
Output: 2
 

Constraints:

1 <= nums.length <= 10^4
-107 <= nums[i] <= 10^7
0 <= k <= 10^7


*/

#include <algorithm>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::vector;


class FindPairs {

    /*
        532.K-diff-Pairs-in-an-Array
        最简单的思路应该就是用双指针来做。

        将nums排序后，对应一个前指针i，移动后指针j查看是否有 nums[i]+k==nums[j]。如果有，则计数器加1.

        为了避免重复，保证前指针i跳过重复的元素。

        另外注意的一个细节就是，每确定一个指针i，都要重新定位j=i+1.
    
    */
    int findPairs(vector<int>& nums, int k) 
    {
        if (nums.size()<2) return 0;
        
        std::sort(nums.begin(),nums.end());
        
        int i=0;
        int j=1;
        int count=0;
        
        while (j<nums.size())
        {
            j=i+1;
            while (j<nums.size() && nums[j] < nums[i]+k) j++;
            if (j<nums.size() && nums[j] == nums[i]+k)
                count++;
            i++;
            while (i<nums.size() && nums[i]==nums[i-1]) i++;
        }
        
        return count;
    }


public:

    /*
        Approach 3: Hashmap
        Intuition

        This method removes the need to sort the nums array. Rather than that, we will be building a frequency hash map. This hash map will have every unique number in nums as keys and the number of times each number shows up in nums as values.

        For example:

        nums = [2,4,1,3,5,3,1], k = 3
        hash_map = {1: 2,
                    2: 1,
                    3: 2,
                    4: 1,
                    5: 1}
        Next, we look at a key (let's call x) in the hash map and ask whether:

        There is a key in the hash map which is equal to x+k IF k > 0.
        For example, if a number in nums is 1 (x=1) and k is 3, you would need to have 4 to satisfy this condition (thus, we need to look for 1+3 = 4 in the hash map). Using addition to look for a complement pair has the advantage of not double-counting the same pair, but in reverse order (i.e. if we have found a pair (1,4), we won't be counting (4,1)).
        There is more than one occurrence of x IF k = 0.
        For example, if we have nums = [1,1,1,1] and k = 0, we have one unique (1,1) pair. In this case, our hash map will be {1: 4}, and this condition is satisfied since we have more than one occurrence of number 1.
        If we can satisfy either of the above conditions, we can increment our placeholder result variable.

        Then we look at the next key in the hash map.

        Implementation


        Complexity Analysis

        Let NN be the number of elements in the input list.

        Time complexity : O(N).

        It takes O(N) to create an initial frequency hash map and another O(N)O(N) to traverse the keys of that hash map. One thing to note about is the hash key lookup. The time complexity for hash key lookup is O(1) but if there are hash key collisions, 
        the time complexity will become O(N)O(N). However those cases are rare and thus, the amortized time complexity is O(2N) \approx O(N)O(2N)≈O(N).
        Space complexity : O(N)

        We keep a table to count the frequency of each unique number in the input. In the worst case, all numbers are unique in the array. As a result, the maximum size of our table would be O(N).
    */

    int doit_hashtable(vector<int>& nums, int k) {
        
        unordered_map<int, int> buf;
        for (auto c : nums) buf[c]++;
        
        int ans = 0;
        for (auto it : buf) {
            int c = it.first;
            if (k == 0) 
                ans += buf[c] > 1 ? 1 : 0;
            else if (buf.count(c+k))
                ans++;
        }
    
        return ans;
    }

    /*
        pproach 2: Two Pointers
        Intuition

        We can do better than quadratic runtime in Approach 1. Rather than checking for every possible pair, we can have two pointers to point the left number and right number that should be checked in a sorted array.

        First, we have to initialize the left pointer to point the first element and the right pointer to point the second element of nums array. The way we are going to move the pointers is as follows:

        Take the difference between the numbers which left and right pointers point.

        If it is less than k, we increment the right pointer.
        If left and right pointers are pointing to the same number, we increment the right pointer too.
        If it is greater than k, we increment the left pointer.
        If it is exactly k, we have found our pair, we increment our placeholder result and increment left pointer.
        The idea behind the behavior of incrementing left and right pointers in the manner above is similar to:

        Extending the range between left and right pointers when the difference between left and right pointers is less than k (i.e. the range is too small).
        Therefore, we extend the range (by incrementing the right pointer) when left and right pointer are pointing to the same number.
        Contracting the range between left and right pointers when the difference between left and right pointers is more than k (i.e. the range is too large).
        This is the core of the idea but there is another issue which we have to take care of to make everything work correctly. We have to make sure duplicate pairs are not counted repeatedly. In order to do so, whenever we have a pair whose difference matches with k, we keep incrementing the left pointer as long as the incremented left pointer points to the number which is equal to the previous number.

        For nums = [2,5,1,2,8,1,3,5,7,1] and k = 2:

        Current
        1 / 24
        Implementation


        Complexity Analysis

        Time complexity : O(NlogN) where NN is the size of nums. The time complexity for sorting is O(N \log N)O(NlogN) while the time complexity for going through nums is O(N)O(N). One might mistakenly think that it should be O(N^2)O(N 
        2
        ) since there is another while loop inside the first while loop. The while loop inside is just incrementing the pointer to skip numbers which are the same as the previous number. The animation should explain this behavior clearer. Therefore, the final time complexity is O(N \log N) + O(N) \approx O(N \log N)O(NlogN)+O(N)≈O(NlogN).

        Space complexity : O(N) where NN is the size of nums. Similar to approach 1, this space complexity is incurred by the sorting algorithm. Space complexity is bound to change depending on the sorting algorithm you use. There is no additional space required for the part where two pointers are being incremented, apart from a single variable result. Therefore, the final space complexity is O(N) + O(1) \approx O(N)O(N)+O(1)≈O(N).
    
    */
    int doit_twopointer(vector<int>& nums, int k) {
        
        sort(begin(nums), end(nums));

        int i = 0, j = 0;
        int ans = 0;
        
        while (i < nums.size()) {
            
            j = i + 1;
            
            while (j < nums.size() && nums[j] - nums[i] < k) j++;
            
            if (j < nums.size() && nums[j] - nums[i] == k) ans++;
            
            i++;
            
            while (i < nums.size() && nums[i] == nums[i-1]) i++;
            
        }
        
        
        return ans;
    }
    

};