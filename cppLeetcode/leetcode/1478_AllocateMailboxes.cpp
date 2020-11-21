/*
 1478. Allocate Mailboxes
 
 Given the array houses and an integer k. where houses[i] is the location of the ith house along a street, your task is to allocate k mailboxes in the street.

 Return the minimum total distance between each house and its nearest mailbox.

 The answer is guaranteed to fit in a 32-bit signed integer.

  

 Example 1:



 Input: houses = [1,4,8,10,20], k = 3
 Output: 5
 Explanation: Allocate mailboxes in position 3, 9 and 20.
 Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
 Example 2:



 Input: houses = [2,3,5,12,18], k = 2
 Output: 9
 Explanation: Allocate mailboxes in position 3 and 14.
 Minimum total distance from each houses to nearest mailboxes is |2-3| + |3-3| + |5-3| + |12-14| + |18-14| = 9.
 Example 3:

 Input: houses = [7,4,6,1], k = 1
 Output: 8
 Example 4:

 Input: houses = [3,6,14,10], k = 4
 Output: 0
  

 Constraints:

 n == houses.length
 1 <= n <= 100
 1 <= houses[i] <= 10^4
 1 <= k <= n
 Array houses contain unique integers.

 */
#include <vector>


using std::vector;


class AllocateMailboxes {
    
public:
    
    int doit_dp(vector<int>&& houses, int K) {
        
        auto n = houses.size();
        std::sort(houses.begin(), houses.end());
        houses.insert(houses.begin(), INT_MIN);
        vector<vector<int>> dp(n+1, vector<int>(K+1, 0));
        vector<vector<int>> range(n+1, vector<int>(n+1, 0));

        // range[i, j] houses from ith to jth, put only one mailbox, what minimum value will be.
        for (int i = 1; i <= n; i++)
            for (int j = i; j <= n; j++) {
                range[i][j] = 0;
                int median = houses[(i+j)/2];
                for (auto k = i; k <= j; k++)
                    range[i][j] += abs(houses[k] - median);
            }
        
        // dp[i, j] house from 1th to ith, put j mailboxes, what minmum value will be.
        for (int i=1; i <= n; i++)
            dp[i][1] = range[1][i];

        for (auto i = 1; i <= n; i++) {
            for (auto k = 2; k <= K; k++) {
                
                dp[i][k] = INT_MAX/2;
                for (auto j = 1; j + 1 <= i; j++) {
                    
                    dp[i][k] = std::min(dp[i][k], dp[j][k-1] + range[j+1][i]);
                }
            }
        }

        return dp[n][K];
    }
};


void test_1478_AllocateMailbox() {
    
    AllocateMailboxes().doit_dp(vector<int>{1, 8, 12, 10, 3}, 3);
    
    AllocateMailboxes().doit_dp(vector<int>{1, 4, 8, 10, 20}, 5);
}
