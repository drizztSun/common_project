/*

1124. Longest Well-Performing Interval

We are given hours, a list of the number of hours worked per day for a given employee.

A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.

A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

 

Example 1:

Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].
 

Constraints:

1 <= hours.length <= 10000
0 <= hours[i] <= 16

*/
#include <vector>
#include <unordered_map>
#include <map>
#include <stack>

using std::stack;
using std::map;
using std::unordered_map;
using std::vector;


class LongestWellPerformingInterval {

    /*
        1124.Longest-Well-Performing-Interval
        如果我们将所有的tiring day标记成为1，non-tiring day标记成为-1，那么题意就是说，在一个1和-1组成的数组里找一个最长的区间[i,j]，使得区间里面1的个数要多于-1的个数。

        如果我们继续转换一下这个数组变成前缀和数组presum，可以发现presum[i]表示的就是从第0天截止到第i天为止，tiring day与non-tiring day相比的数目之差。
        于是题意就转化成了：在这个presum数组里，找一对距离最远的pair(i,j)，使得presum[i-1] < presum[j]（这样就表示从区间[i,j]里tiring day与non-tiring day相比的数目之差是正数，符合题意）。

        于是这道题就变得和 962. Maximum Width Ramp 一样了，可以用单调栈的技巧在o(n)时间解决。

        事实上，这道题抽象起来就是求：任意数组A里最宽的一对pair(i,j)，使得 A[i]<A[j]（或者A[i]>A[j]），我们可以称之为“farthest greater element”。这和之前常做到的“next greater element”是恰好相反的题意。这两题都是可以用单调性完美地解决的。
    */
    int longestWPI(vector<int>& hours) 
    {
        vector<int>q({0});
        int count = 0;
        for (auto x:hours)
        {
            if (x>8)
                count++;
            else
                count--;
            q.push_back(count);
        }
        
        map<int,int>Map;
        Map[0] = 0;
        int result = 0;
        for (int i=1; i<q.size(); i++)
        {
            int k = INT_MAX;
            for (auto x:Map)
            {
                if (x.first >= q[i])
                    break;
                k = std::min(k, x.second);
            }
            result = std::max(result, i-k);
            if (Map.begin()->first > q[i])
            {
                Map[q[i]] = i;
            }                
        }
        return result;
    }

    int doit_stack(vector<int>& hours) 
    {
        vector<int>presum({0});
        int sum = 0;
        for (int x: hours)
        {
            if (x>8)
                sum+=1;
            else
                sum+=-1;
            presum.push_back(sum);
        }
        
        stack<int>Stack;
        for (int i=0; i<presum.size(); i++)
        {
            if (Stack.empty() || presum[Stack.top()] > presum[i])
                Stack.push(i);
        }
        
        int result = 0;
        for (int j = presum.size()-1; j>=0; j--)
        {
            while (!Stack.empty() && presum[Stack.top()] < presum[j])
            {
                result = std::max(result, j - Stack.top());
                Stack.pop();
            }   
        }
        return result;        
    }


    /*
        Intuition
        If working hour > 8 hours, yes it's tiring day.
        But I doubt if 996 is a well-performing interval.
        Life needs not only 996 but also 669.


        Explanation
        We starts with a score = 0,
        If the working hour > 8, we plus 1 point.
        Otherwise we minus 1 point.
        We want find the maximum interval that have strict positive score.

        After one day of work, if we find the total score > 0,
        the whole interval has positive score,
        so we set res = i + 1.

        If the score is a new lowest score, we record the day by seen[cur] = i.
        seen[score] means the first time we see the score is seen[score]th day.

        We want a positive score, so we want to know the first occurrence of score - 1.
        score - x also works, but it comes later than score - 1.
        So the maximum interval is i - seen[score - 1]


        Complexity
        Time O(N) for one pass.
        Space O(N) in worst case if no tiring day.
    */
    int doit_(vector<int>& hours) {
        int res = 0, score = 0, n = hours.size();
        unordered_map<int, int> seen;
        
        for (int i = 0; i < n; ++i) {
            score += hours[i] > 8 ? 1 : -1;
            if (score > 0) {
                res = i + 1;
            } else {
                if (seen.find(score) == seen.end())
                    seen[score] = i;

                if (seen.find(score - 1) != seen.end())
                    res = std::max(res, i - seen[score - 1]);
            }
        }
        return res;
    }

public:

    /*
        h = [9, 9,  6,  0,  6,  6,  9]
        v = [1, 1, -1, -1, -1, -1,  1]

        Reduced to target_sum == 1
        if sum(v[0:n]) > 0 return n

        Use a hashtable to store the first index of the cumulative sum
        ans = max(i - index[sum-1])

        Time complexity: O(n)
        Space complexity: O(n)
    */
    int doit_hashtable(vector<int>& hours) {
        
        unordered_map<int, int> buff;
        int accum = 0;
        int ans = 0;

        for (int i = 0; i < hours.size(); i++) {
 
            accum += hours[i] > 8 ? 1 : -1;

            if (accum > 0) {
                ans = i+1;
                continue;
            }
                
            if (!buff.count(accum))
                buff[accum] = i;

            if (buff.count(accum-1) > 0)
                ans = std::max(ans, i - buff[accum-1]); 
        }

        return ans;
    }
};