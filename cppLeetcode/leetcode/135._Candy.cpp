/*
135. Candy

There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

    . Each child must have at least one candy.
    . Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.

 

Example 1:

Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
Example 2:

Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.
 

Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104

*/

#include <numeric>
#include <vector>

using std::vector;


class Candy {

    /*
        135.Candy
        此题是贪心法的经典题。所谓贪心法，并没有定式，是指可以人工找出最优的策略，当然这种策略必须可以直观或者严谨地证明。

        设置candy数组的初始值为1。

        先从左往右扫一遍，如果右边的rating高于左边，则设置右边的candy要比左边的多一颗。扫完之后就保证了所有的“右边大于左边”的情况都得到了满足。

        再从右往左扫一遍，如果左边的rating高于右边但糖果不比右边多，则设置左边的candy比右边多一颗。注意，这个操作并没有打破之前“右边大于左边”操作的结果。扫完之后就保证了所有的“左边大于右边”的情况都得到了满足。

        扫完两边后，“右边大于左边”、“左边大于右边”都得到了满足，那么就是符合题意的安排。
    */
    int doit_greedy(vector<int>& ratings) 
    {
        int N=ratings.size();
        vector<int>candy(N,1);
        for (int i=1; i<N; i++)
        {
            if (ratings[i]>ratings[i-1])
                candy[i]=candy[i-1]+1;
        }
        
        for (int i=N-2; i>=0; i--)
        {
            if (ratings[i]>ratings[i+1] && candy[i]<=candy[i+1])
                candy[i]=candy[i+1]+1;
        }
        
        int result=0;
        for (int i=0; i<N; i++)
            result+=candy[i];
        return result;
    }

public:

    /*
        Approach 3: Using one array
        Algorithm

        In the previous approach, we used two arrays to keep track of the left neighbor and the right neighbor relation individually and later on combined these two. 
        Instead of this, we can make use of a single array candies to keep the count of the number of candies to be allocated to the current student. In order to do so, firstly we assign 1 candy to each student. 
        Then, we traverse the array from left-to-right and distribute the candies following only the left neighbor relation i.e. 
        whenever the current element's ratings is larger than the left neighbor and has less than or equal candies than its left neighbor, we update the current element's candies in the candies array as candies[i] = candies[i-1] + 1. 
        While updating we need not compare candies[i] and candies[i - 1], since candies[i] <= candies[i - 1] before updating. 
        
        After this, we traverse the array from right-to-left. Now, we need to update the i'th element's candies in order to satisfy both the left neighbor and the right neighbor relation. 
        Now, during the backward traversal, if ratings[i] > ratings[i + 1], considering only the right neighbor criteria, we could've updated candies[i] as candies[i] = candies[i + 1] + 1. 
        But, this time we need to update candies[i] only if candies[i] <= candies[i + 1]. 
        
        This happens because this time we've already altered the candies array during the forward traversal and thus candies[i] isn't necessarily less than or equal to candies[i + 1]. 
        Thus, if ratings[i] > ratings[i + 1], we can update candies[i] as candies[i] = max(candies[i], candies[i + 1] + 1), which makes candies[i] satisfy both the left neighbor and the right neighbor criteria.

        Again, we need to sum up all the elements of the candies array to obtain the required result.

        \text{minimum\_candies} = \sum_{i=0}^{n-1} candies[i], \\ \text{where } n = \text{length of the ratings array.}minimum_candies=∑ 
        i=0
        n−1
        ​	
        candies[i],
        where n=length of the ratings array.
    */
    int doit_greedy(vector<int>& ratings) {
        
        int n = ratings.size();
        vector<int> res(n, 1);
        
        for (int i = 0; i < res.size()-1; i++) {
            if (ratings[i] < ratings[i+1]) {
                res[i+1] = res[i]+1;
            }
        }
        
        for (int i = res.size()-1; i > 0; i--) {
            if (ratings[i] < ratings[i-1]) {
                res[i-1] = std::max(res[i-1], res[i]+1);
            }
        }
        
        return accumulate(begin(res), end(res), 0);
    }
};