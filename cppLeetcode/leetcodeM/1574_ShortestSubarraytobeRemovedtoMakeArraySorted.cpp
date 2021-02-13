/*

1574. Shortest Subarray to be Removed to Make Array Sorted


Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.

A subarray is a contiguous subsequence of the array.

Return the length of the shortest subarray to remove.

 

Example 1:

Input: arr = [1,2,3,10,4,2,3,5]
Output: 3
Explanation: The shortest subarray we can remove is [10,4,2] of length 3. The remaining elements after that will be [1,2,3,3,5] which are sorted.
Another correct solution is to remove the subarray [3,10,4].
Example 2:

Input: arr = [5,4,3,2,1]
Output: 4
Explanation: Since the array is strictly decreasing, we can only keep a single element. Therefore we need to remove a subarray of length 4, either [5,4,3,2] or [4,3,2,1].
Example 3:

Input: arr = [1,2,3]
Output: 0
Explanation: The array is already non-decreasing. We do not need to remove any elements.
Example 4:

Input: arr = [1]
Output: 0
 

Constraints:

1 <= arr.length <= 10^5
0 <= arr[i] <= 10^9
*/
#include <vector>

using std::vector;

class ShortesSubarryToMakeArraySorted {

public:

    /*
        1574.Shortest-Subarray-to-be-Removed-to-Make-Array-Sorted
        我们对于探索subarray的题目，归根结底就是确定它的两个边界。我们将整个数组可以分为三段[0,i],[i+1,j-1],[j,n-1]，中间的那段就是我们尝试删除的subarray。我们需要满足三个条件：[0:i]是单调增的，[j:n-1]是单调增的，并且arr[j]>=arr[i].

        让我们尝试从头到尾遍历i可能的位置。条件1是比较容易判断的。一旦发现arr[i]<arr[i-1]的时候，条件1不能满足，注定就没有解了，整个搜索过程就可以终止了。

        条件3也是容易实现的。就是从后往前遍历，可以找到最前的一个j使得满足[j:n-1]是单调的。

        那么条件2怎么满足呢？如果此时arr[j]<arr[i]怎么办？显然因为[j:n-1]是单调增的，我们可以尝试往右移动j找到满足arr[j]>=arr[i]的第一个位置。此时我们就找到了一组{i,j}对应的是一个合法的拆分原数组的解（不见得是最优解）。

        接下来我们遍历i的下一个位置。此时j怎么移动呢？我们发现，因为i的移动必须保证[0:i]单调增，所以arr[i]会变大，所以arr[j]必然也要增大以保证arr[j]>=arr[i]。我们还发现[j:n-1]也是单调增的区间，所以我们必然会将j右移。
        这样我们会找到下一个合适的j，使得此时的{i,j}成为一组合适的解。

        同理的分析，我们每向右移动一次i指针，必然也必须向右移动j指针以寻找合适的{i,j}。这就是一个双指针的模式。所以我们用o(n)的时间复杂度就可以探索到所有合适的{i,j}.
    */
    int doit_greedy(vector<int>& arr) 
    {
        int n = arr.size();
        int ret = n-1;
        
        int j = n-1;
        while (j-1>=0 && arr[j-1]<=arr[j])
            j--;

        ret = min(ret, j);        
        if (ret==0) return 0;
        
        for (int i=0; i<n; i++)
        {
            if (i>=1 && arr[i]<arr[i-1]) break;
            while (j<n && arr[j]<arr[i])
                j++;
            ret = min(ret, j-i-1);
        }
        
        return ret;
    }

    int doit_greedy_1(vector<int>& arr) {
        int size{(int)arr.size()}, min_{size}, i{0}, j{size-1};
        while(i < size-1 && arr[i+1] >= arr[i]) ++i;
        while(j > i && arr[j-1] <= arr[j]) --j;
        
        if(j == i) return 0;
        
        for(int k{0}; k <= i; ++k) {
            auto it{std::upper_bound(arr.begin()+j, arr.end(), arr[k]-1)};
            int dist{(int)(it-(arr.begin()+k)-1)};
            min_ = std::min(min_, dist);
        }

        for(int k{size-1}; k >= j; --k) {
            auto it{std::upper_bound(arr.begin(), arr.begin()+i+1, arr[k]-1)};
            int dist{(int)(arr.begin()+k-it)};
            min_ = std::min(min_, dist);
        }
        
        return min_;
    }
};