/*

1562. Find Latest Group of Size M

Given an array arr that represents a permutation of numbers from 1 to n. You have a binary string of size n that initially has all its bits set to zero.

At each step i (assuming both the binary string and arr are 1-indexed) from 1 to n, the bit at position arr[i] is set to 1. 
You are given an integer m and you need to find the latest step at which there exists a group of ones of length m. A group of ones is a contiguous substring of 1s such that it cannot be extended in either direction.

Return the latest step at which there exists a group of ones of length exactly m. If no such group exists, return -1.

 

Example 1:

Input: arr = [3,5,1,2,4], m = 1
Output: 4
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "00101", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "11101", groups: ["111", "1"]
Step 5: "11111", groups: ["11111"]
The latest step at which there exists a group of size 1 is step 4.
Example 2:

Input: arr = [3,1,5,4,2], m = 2
Output: -1
Explanation:
Step 1: "00100", groups: ["1"]
Step 2: "10100", groups: ["1", "1"]
Step 3: "10101", groups: ["1", "1", "1"]
Step 4: "10111", groups: ["1", "111"]
Step 5: "11111", groups: ["11111"]
No group of size 2 exists during any step.
Example 3:

Input: arr = [1], m = 1
Output: 1
Example 4:

Input: arr = [2,1], m = 2
Output: 2
 

Constraints:

n == arr.length
1 <= n <= 10^5
1 <= arr[i] <= n
All integers in arr are distinct.
1 <= m <= arr.length

*/
#include <vector>
#include <deque>

using std::deque;
using std::vector;

class {

    /*
            1562.Find-Latest-Group-of-Size-M
        解法1：deque
        首先要正确理解题意。举个例子，arr[3]=4的意思是，第3天的时候，将第4个bit位置为1. 如果需要，我们可以反过来定义一个day[4]=3，表示第4个bit位，我们在第3天的时候将其置为1.

        文中要找到某一天t，存在一个长度恰为m的区间[i,j]其bit为都是1。那么区间内所有bit对应的day都要小于等于t（不晚于第t天变成1）。显然，对于这个区间而言最早的t，就是这个区间内最大的那个day。也就是说，当[i,j]内最后一个bit变为1的时候，那么整个区间恰好都变成了1.

        同时因为“长度恰为m”，说明在第t天完成的时候，第i-1个bit位和第j+1个bit位必须都还是0，也就是要求day[i-1]>t 且 day[j+1]>t。如果满足上面的条件，就可以判定这个[i,j]区间就是我们想要找的“恰好长度为m的全1串”。

        本题中，我们很容易遍历一个长度m的滑窗[i,j]，根据这个滑窗内部的day的信息，套用sliding window maximum的做法，可以o(1)时间知道t = max(day[k]) k=i,...,j。然后只需查看一下是否day[i-1]>t且day[j+1]>t。
        是的话，那么意味着在t之后、min(day[i-1], day[j+1])之前的这段时间，这个全1的区间恰好就是m的长度。显然，我们会挑尽量靠后的日子，也就是 min(day[i-1], day[j+1])-1

        所以，最终的答案就是遍历长度为m的滑窗，如果判断出这个滑窗符合要求，那么就有机会用min(day[i-1], day[j+1])-1更新result. 最终result会取全局所有滑窗里最大的那个答案。

        参考 239. sliding window maximum 的deque方法，用o(n)时间求固定长度滑窗的最大值。

        解法2：区间合并
        我们给每一个已经翻转的位置存储一个range的属性，记录它所在的连续是1的区间的左边界和右边界。

        当我们在i天翻转flipIndex这个位置时，它可能连接起了左边的连续1区间和右边的连续1区间。我们查看flipIndex-1所属的区间范围，它的左边界就是新的左边界；同时查看flipIndex+1所属的区间范围，它的右边界就是新的右边界。
        同时我们要把这个newRange信息传播给整个大区间，但是不用传播给每一个位置，只要传播给当前大区间最左边的位置和最右边的位置即可。

        我们用一个countsForM来记录当前全局总共有多少个恰为M的连续1区间。当我们合并区间的操作中，如果合并的左区间长度就是M，那么这个计数器减一；如果合并的右区间长度也是M，那么这个计数器减一；如果合并后的大区间长度就是M，那么这个计数器加一。答案是保持countsForM > 0的最晚的一天。
    */
    int doit_(vector<int>& arr, int m) 
    {
        int n = arr.size();
        arr.insert(arr.begin(),0);
        int ret = -1;
        
        if (n == m) return n;

        // arr is arr[i], ith day fill arr[i] point
        // day is day[i] is gonnna fill point i.
        vector<int> day(n+1);  
        for (int i=1; i<=n; i++) day[arr[i]] = i;
        
        deque<int> dq;

        for (int i = 1; i <= n; i++)
        {
            while (dq.size() > 0 && day[dq.back()] < day[i])
                dq.pop_back();

            while (dq.size() > 0 && i - dq.front() >= m)
                dq.pop_front();
            
            dq.push_back(i);

            if (i < m) continue;

            int maxDay = day[dq.front()];

            int left = INT_MAX, right = INT_MAX;
            if (i-m >= 1) left = day[i-m];
            if (i+1<=n) right = day[i+1];
            
            if (maxDay < left && maxDay < right)
                ret = std::max(ret, std::min(left,right)-1);
        }
        return ret;
    }

    int doit_(vector<int>& arr, int m) 
    {
        const int n = arr.size();        
        vector<std::pair<int, int>> ranges(n, std::make_pair(-1, -1));
        
        int countsForM = 0;
        int ans = -1;
        for (int i = 0; i < n; ++i) 
        {
            int flipIndex = arr[i] - 1;
            
            std::pair<int, int> newRange{flipIndex, flipIndex};
            
            if (flipIndex < n - 1) 
            {
                auto nextRange = ranges[flipIndex + 1];
                if (nextRange.first != -1) 
                {
                    newRange.second = nextRange.second;                    
                    if (nextRange.second - nextRange.first + 1 == m) 
                        --countsForM;
                }
            }
            
            if (flipIndex > 0) 
            {
                auto prevRange = ranges[flipIndex - 1];
                if (prevRange.first != -1) 
                {
                    newRange.first = prevRange.first;                
                    if (prevRange.second - prevRange.first + 1 == m) 
                        --countsForM;
                }
            }
            
            if (newRange.second - newRange.first + 1 == m) 
                ++countsForM;
            
            if (countsForM > 0) 
                ans = i + 1;
            
            ranges[newRange.first] = newRange;
            ranges[newRange.second] = newRange;
            
        }
        
        return ans;
    }

public:

    /*
        Explanation
        When we set bit a, where a = A[i],
        we check the length of group on the left length[a - 1]
        also the length of group on the right length[a + 1].
        Then we update length[a - left], length[a + right] to left + right + 1.

        Note that the length value is updated on the leftmost and the rightmost bit of the group.
        The length value inside the group may be out dated.

        As we do this, we also update the count of length.
        If count[m] > 0, we update res to current step index i + 1.


        Complexity
        Time O(N)
        Space O(N)

        Solution 1: Count all lengths
    */
    int doit_sweeplines(vector<int>& A, int m) {
        int res = -1, n = A.size();
        vector<int> length(n + 2), count(n + 1);
        for (int i = 0; i < n; ++i) {
            int a = A[i], left = length[a - 1], right = length[a + 1];
            length[a] = length[a - left] = length[a + right] = left + right + 1;
            count[left]--;
            count[right]--;
            count[length[a]]++;
            if (count[m])
                res = i + 1;
        }
        return res;
    }

    int doit_sweeplines(vector<int>& A, int m) {
        int res = -1, n = A.size();
        if (n == m) return n;

        vector<int> length(n + 2);
        for (int i = 0; i < n; ++i) {
        
            int a = A[i], left = length[a - 1], right = length[a + 1];
        
            length[a - left] = length[a + right] = left + right + 1;
        
            if (left == m || right == m) res = i;
        }
        
        return res;
    }
}