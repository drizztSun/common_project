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

using std::unordered_map;
using std::vector;


class LongestWellPerformingInterval {

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