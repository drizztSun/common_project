/*
1300. Sum of Mutated Array Closest to Target

Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, 
the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from arr.

 

Example 1:

Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.
Example 2:

Input: arr = [2,3,5], target = 10
Output: 5
Example 3:

Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361
 

Constraints:

1 <= arr.length <= 10^4
1 <= arr[i], target <= 10^5

*/
#include <vector>
#include <algorithm>

using std::vector;


class SumOfMutatedClosestToTarget {

    /*
            1300.Sum-of-Mutated-Array-Closest-to-Target
        这是一道典型的二分搜值的问题。我们猜测某个value，查看数组之后的sum是否大于target。如果sum>=target，那么说明我们可以把value降一点（这样使得sum会变小）。
        反之，如果sum>=target，那么说明我们可以把value升一点（这样使得sum会变大）。这样直至我们找到恰好使得sum比target大的那个value。自然，value-1就是恰好使得sum比target小的那个value。
        对于最终的答案，我们需要在二者之间选择一个更接近target的sum。

        但是本题有一个非常隐蔽的corner case。如果初始有的sum就已经小于target了，那么无论你如何操作都不能使得sum大于target。上述的二分法其实是失效的。对于这种情况，我们需要输出的答案是arr里面的最大值。  
    */
    
public:
    int doit_binary_search(vector<int>& arr, int target) 
    {

        vector<int>presum;
        sort(arr.begin(),arr.end());
        
        presum.resize(arr.size());
        presum[0] = arr[0];        
        for (int i=1; i<arr.size(); i++)
            presum[i] = presum[i-1]+arr[i];

        if (presum.back() <= target) return arr.back();
                    

        auto helper = [&](vector<int>&arr, int value)
        {
            auto iter = upper_bound(arr.begin(),arr.end(),value);
            int num = arr.end()-iter;
            if (iter-arr.begin()-1>=0)
                return presum[iter-arr.begin()-1]+(long long)num*value;
            else
                return (long long)num*value;
        };

        int left = 0;
        int right = 1e5;
        
        while (left<right)
        {
            int mid = left+(right-left)/2;
            if (helper(arr, mid)>=target)
                right = mid;
            else
                left = mid+1;
        }
        
        int a = helper(arr,left);
        int b = helper(arr,left-1);

        if (abs(a-target)<abs(target-b))
            return left;
        else
            return left-1;                
    }
    

public:

    /*
        Explanation
        Binary search is O(NlogMax(A)).
        In order to ruduce the difficulty, it constrains A[i] < 10 ^ 5.

        In this solution,
        we sort the input and compared A[i] with target one by one.

        1. Sort the array A in decreasing order.
        2. We try to make all values in A to be the min(A) (the last element)
        3. If target >= min(A) * n, we doesn't hit our target yet.
                We should continue to try a value bigger.
        4. So we pop the min(A) value.
                Consider that it won't be affected anymore,
                we can remove it from target by target -= A.pop()
        5. We continue doing step 2-4, until the next number is too big for target.
        6. We split the the target evenly, depending on the number of element left in A
        
        At this point, @bobalice help explain the round part:
        if A is empty means its impossible to reach target so we just return maximum element.
        If A is not empty, intuitively the answer should be the nearest integer to target / len(A).

        Since we need to return the minimum such integer if there is a tie,
        if target / len(A) has 0.5 we should round down,


        Complexity
        Time O(NlogN)
        Space O(1)      
    */
    int doit_sort(vector<int>& arr, int target) {

        std::sort(begin(arr), end(arr));

        int i = 0, n = arr.size();

        while (i < n && target > arr[i] * (n-i))
            target -= arr[i++];

        // if A is empty means its impossible to reach target so we just return maximum element.
        // If A is not empty, intuitively the answer should be the nearest integer to target / len(A).
        return i == n ? arr[n-1] : int(round((target - 0.0001) / (n - i)));
    }

    int doit_binary_search(vector<int>& arr, int target) {

        int left = 0, right = *max_element(begin(arr), end(arr));
        int diff = INT_MAX, res = INT_MAX;

        auto check = [&](int m) {

            int sums = 0;
            for (auto c: arr) 
                sums += c > m ? m : c;

            if (diff > abs(sums - target)) {
                diff = abs(sums - target);
                res = m;
            } else if (diff == abs(sums - target)) {
                res = std::min(res, m);
            }

            return sums >= target;
        };

        while (left <= right) {

            int mid = (left + right) / 2;

            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return res;
    }
};