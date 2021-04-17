/*
1109. Corporate Flight Bookings

There are n flights that are labeled from 1 to n.

You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi] 
represents a booking for flights firsti through lasti (inclusive) with seatsi seats reserved for each flight in the range.

Return an array answer of length n, where answer[i] is the total number of seats reserved for flight i.

 

Example 1:

Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]
Explanation:
Flight labels:        1   2   3   4   5
Booking 1 reserved:  10  10
Booking 2 reserved:      20  20
Booking 3 reserved:      25  25  25  25
Total seats:         10  55  45  25  25
Hence, answer = [10,55,45,25,25]
Example 2:

Input: bookings = [[1,2,10],[2,2,15]], n = 2
Output: [10,25]
Explanation:
Flight labels:        1   2
Booking 1 reserved:  10  10
Booking 2 reserved:      15
Total seats:         10  25
Hence, answer = [10,25]

 

Constraints:

1 <= n <= 2 * 104
1 <= bookings.length <= 2 * 104
bookings[i].length == 3
1 <= firsti <= lasti <= n
1 <= seatsi <= 104
*/


#include <vector>

using std::vector;


class CorpFlightBookings {

    /*
        1109.Corporate-Flight-Bookings
        本题用到了非常常见的差分数组的思想。

        对于[i,j,k]，我们不需要从i到j把这些元素全部遍历一遍来加上k，这样效率很低，特别是当i和j间隔非常大的时候。正确的方法是用差分数组diff[x]表示val[x]-val[x-1]，只记录“值的变化”而不是“值本身”。
        当diff构造完之后，可以从第一个元素开始，不断的通过cur=cur+diff[i]来恢复得到val[i]的值。
    */
    
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) 
    {
        vector<int>diff(n+2,0);
        for (auto p: bookings)
        {
            diff[p[0]]+=p[2];
            diff[p[1]+1]-=p[2];
        }
        vector<int>results;
        int cur = 0;
        for (int i=1; i<=n; i++)
        {
            cur += diff[i];
            results.push_back(cur);
        }
        return results;
        
    }


public:
    vector<int> doit_sweeplines(vector<vector<int>>& bookings, int n) {
        
        vector<int> buff(n);
        
        for (auto booking : bookings) {
            
            buff[booking[0]-1] += booking[2];
            if (booking[1] < n)
                buff[booking[1]] -= booking[2];
        }
        
        for (int i = 1; i < n; i++) {
            buff[i] += buff[i-1];
        }
        
        return buff;
    }
};