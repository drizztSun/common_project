/*
209. Minimum Size Subarray Sum

Given an array of positive integers nums and a positive integer target, return the minimal length of a contiguous subarray 
[numsl, numsl+1, ..., numsr-1, numsr] of which the sum is greater than or equal to target. If there is no such subarray, return 0 instead.

 

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.
Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1
Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
 

Constraints:

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 105
 

Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).
*/
#include <vector>

using std::vector;

class MinumumSizeSubarraySum {


    /*
        209.Minimum-Size-Subarray-Sum
        基本思路：因为题意保证所有数组元素都是正数，可以用双指针定界。当双指针之间子数组和大于sum时，记录Len并left++；否则right++。

        实际编程中，用for循环来控制右指针的思路比较清晰，左指针仅当固定了一个右指针的前提下进行移动；相对而言，用while来控制双指针比较容易出错。

        细节：注意在什么条件下更新len。
    */
    int minSubArrayLen(int s, vector<int>& nums) 
    {
        int i=0;
        int j=0;
        int sum=0;
        int len=INT_MAX;
        
        for (int j=0; j<nums.size(); j++)
        {
            sum+=nums[j];
            
            if (sum<s)
                continue;
            else
            {
                while (sum>=s)
                {
                    len=min(len,j-i+1);
                    sum-=nums[i];
                    i++;
                }
            }
        }
        
        if (len==INT_MAX)
            len=0;
        
        return len;
    }

public:

    /*
        Intuition
        Shortest Subarray with Sum at Least K
        Actually I did this first, the same prolem but have negatives.
        I suggest solving this prolem first then take 862 as a follow-up.

        Explanation
        The result is initialized as res = n + 1.
        One pass, remove the value from sum s by doing s -= A[j].
        If s <= 0, it means the total sum of A[i] + ... + A[j] >= sum that we want.
        Then we update the res = min(res, j - i + 1)
        Finally we return the result res


        Complexity
        Time O(N)
        Space O(1)
    */
    int doit_sildingwindow(int s, vector<int>& A) {
        int i = 0, n = A.size(), res = n + 1;
        for (int j = 0; j < n; ++j) {
            s -= A[j];
            while (s <= 0) {
                res = std::min(res, j - i + 1);
                s += A[i++];
            }
        }
        return res % (n + 1);
    }



    /*
        Approach #3 Using Binary search [Accepted]
        Intuition

        We could further improve the Approach #2 using the binary search. Notice that we find the subarray with \text{sum} >=\text{s}sum>=s starting with an index ii in O(n)O(n) time. 
        But, we could reduce the time to O(\log(n))O(log(n)) using binary search. Note that in Approach #2, we search for subarray starting with index ii, until we find \text{sum}=\text{sums}[j] - \text{sums}[i] +\text{nums}[i]sum=sums[j]−sums[i]+nums[i] that is greater than \text{s}s. So, instead of iterating linearly to find the sum, we could use binary search to find the index that is not lower than \text{s}-\text{sums[i]}s−sums[i] in the \text{sums}sums, which can be done using \text{lower_bound} function in C++ STL or could be implemented manually.

        Algorithm

        Create vector sumssums of size n+1n+1 with : \text{sums}[0]=0\text{, }\text{sums}[i]=\text{sums}[i-1]+\text{nums}[i-1]sums[0]=0, sums[i]=sums[i−1]+nums[i−1]

        Iterate from i=1i=1 to nn:

        Find the value \text{to_find} in \text{sum}sum required for minimum subarray starting from index ii to have sum greater than ss, that is: \text{to_find}=\text{s}+\text{sums}[i-1]
        Find the index in \text{sums}sums such that value at that index is not lower than the \text{to_find} value, say \text{bound}bound
        If we find the \text{to_find} in \text{sums}sums, then:
        Size of current subarray is given by: \text{bound} - (\text{sums.begin}()+i-1)bound−(sums.begin()+i−1)
        Compare ansans with the current subarray size and store minimum in ansans

        Complexity analysis

        Time complexity: O(nlog(n)).
        For each element in the vector, find the subarray starting from that index, and having sum greater than ss using binary search. 
        Hence, the time required is O(n)O(n) for iteration over the vector and O(log(n)) for finding the subarray for each index using binary search.
        Therefore, total time complexity = O(n∗log(n))
        Space complexity: O(n). Additional O(n) space for \text{sums}sums vector
    */
    int doit_binary_search(int s, vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0) return 0;
        int ans = INT_MAX;
        vector<int> sums(n + 1, 0); //size = n+1 for easier calculations
        //sums[0]=0 : Meaning that it is the sum of first 0 elements
        //sums[1]=A[0] : Sum of first 1 elements
        //ans so on...
        for (int i = 1; i <= n; i++)
            sums[i] = sums[i - 1] + nums[i - 1];
        
        for (int i = 1; i <= n; i++) {
            int to_find = s + sums[i - 1];
            auto bound = lower_bound(sums.begin(), sums.end(), to_find);
            if (bound != sums.end()) {
                ans = std::min(ans, static_cast<int>(bound - (sums.begin() + i - 1)));
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }

    /*
        Approach #4 Using 2 pointers [Accepted]
        Intuition

        Until now, we have kept the starting index of subarray fixed, and found the last position. Instead, we could move the starting index of the current subarray as soon as 
        we know that no better could be done with this index as the starting index. We could keep 2 pointer,one for the start and another for the end of the current subarray,
         and make optimal moves so as to keep the \text{sum}sum greater than ss as well as maintain the lowest size possible.

        Algorithm

        Initialize \text{left}left pointer to 0 and \text{sum}sum to 0
        Iterate over the \text{nums}nums:
        Add \text{nums}[i]nums[i] to \text{sum}sum
        While \text{sum}sum is greater than or equal to ss:
        Update \text{ans}=\min(\text{ans},i+1-\text{left})ans=min(ans,i+1−left), where i+1-\text{left}i+1−left is the size of current subarray
        It means that the first index can safely be incremented, since, the minimum subarray starting with this index with \text{sum} \geq ssum≥s has been achieved
        Subtract \text{nums[left]}nums[left] from \text{sum}sum and increment \text{left}left
        Complexity analysis

        Time complexity:  O(n). Single iteration of O(n).
        Each element can be visited atmost twice, once by the right pointer(ii) and (atmost)once by the \text{left}left pointer.
        Space complexity: O(1) extra space. Only constant space required for \text{left}left, \text{sum}sum, \text{ans}ans and ii.
    */
    int doit_slidingwindow(int s, vector<int>& nums) {

        int total = 0, j = 0;
        int res = INT_MAX;

        for (int i = 0; i < nums.size(); i++) {

            total += nums[i];

            while (j <= i && total >= s) {
                res = std::min(res, i - j +1);
                total -= nums[j];
                j++;
            }
        }
        return res == INT_MAX ? 0 : res;
    }

    /*
        Approach #2 A better brute force [Accepted]
        Intuition

        In Approach #1, you may notice that the sum is calculated for every surarray in O(n)O(n) time. But, we could easily find the sum in O(1) time by storing the cumulative sum from the beginning(Memoization). 
        After we have stored the cumulative sum in \text{sums}sums, we could easily find the sum of any subarray from ii to jj.

        Algorithm

        The algorithm is similar to Approach #1.
        The only difference is in the way of finding the sum of subarrays:
        Create a vector \text{sums}sums of size of \text{nums}nums
        Initialize \text{sums}[0]=\text{nums}[0]sums[0]=nums[0]
        Iterate over the \text{sums}sums vector:
        Update \text{sums}[i] = \text{sums}[i-1] + \text{nums}[i]sums[i]=sums[i−1]+nums[i]
        Sum of subarray from ii to jj is calculated as: \text{sum}=\text{sums}[j] - \text{sums}[i] +\text{nums}[i]sum=sums[j]−sums[i]+nums[i], , wherein \text{sums}[j] - \text{sums}[i]sums[j]−sums[i] is the sum from (i+1i+1)th element to the jjth element.

        Complexity analysis

        Time complexity: O(n^2)
        Time complexity to find all the subarrays is O(n^2).

        Sum of the subarrays is calculated in O(1)O(1) time.
        Thus, the total time complexity: O(n^2 * 1) = O(n^2)
        Space complexity: O(n) extra space.

        Additional O(n) space for sums vector than in Approach #1.
    */
    int doit_(int s, vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0) return 0;
        int ans = INT_MAX;
        vector<int> sums(n);
        sums[0] = nums[0];

        for (int i = 1; i < n; i++)
            sums[i] = sums[i - 1] + nums[i];

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int sum = sums[j] - sums[i] + nums[i];
                if (sum >= s) {
                    ans = std::min(ans, (j - i + 1));
                    break; //Found the smallest subarray with sum>=s starting with index i, hence move to next index
                }
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }

    /*
        Approach #1 Brute force [Time Limit Exceeded]
        Intuition

        Do as directed in question. Find the sum for all the possible subarrays and update the \text{ans}ans as and when we get a better subarray that fulfill the requirements (\text{sum} \geq \text{s}sum≥s).

        Algorithm

        Initialize \text{ans}=\text{INT_MAX}
        Iterate the array from left to right using ii:
        Iterate from the current element to the end of vector using jj:
        Find the \text{sum}sum of elements from index ii to jj
        If sum is greater then ss:
        Update \text{ans} = \min(\text{ans}, (j - i + 1))ans=min(ans,(j−i+1))
        Start the next iith iteration, since, we got the smallest subarray with \text{sum} \geq ssum≥s starting from the current index.

        Complexity Analysis

        Time complexity: O(n^3) For each element of array, we find all the subarrays starting from that index which is O(n^2).
        Time complexity to find the sum of each subarray is O(n).
        Thus, the total time complexity : O(n^2 * n) = O(n^3)
        Space complexity: O(1) extra space.
    */
   int doit_brute_force_TLE(int s, vector<int>& nums)
    {
        int n = nums.size();
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int sum = 0;
                for (int k = i; k <= j; k++) {
                    sum += nums[k];
                }
                if (sum >= s) {
                    ans = min(ans, (j - i + 1));
                    break; //Found the smallest subarray with sum>=s starting with index i, hence move to next index
                }
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }

};