/*
 
 We have a collection of rocks, each rock has a positive integer weight.

 Each turn, we choose any two rocks and smash them together.  Suppose the stones have weights x and y with x <= y.  The result of this smash is:

 If x == y, both stones are totally destroyed;
 If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
 At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)

  

 Example 1:

 Input: [2,7,4,1,8,1]
 Output: 1
 Explanation:
 We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
 we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
 we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
 we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.
  

 Note:

 1 <= stones.length <= 30
 1 <= stones[i] <= 100
 
 */

#include <numeric>
#include <vector>
using std::vector;


class LastStoneWeightII {

public:
    /*
     Overall, this question can be regarded as the following:

     Given a vector of numbers stones, divide these numbers into 2 groups and try to make these 2 groups have closest sum. Return the smallest possible difference of the sums.

     First, we notice that if the sum of all the numbers is odd. The smallest possible difference is 1 instead of 0 no matter how.

     Next, we can declare an int target to be the sum of EACH group that we want to find. For example, if the sum = 23, target can be either 11 (or 12),
     which means that we want to find some of the numbers to sum up to 11 (or 12).
     Notice that we can simply use 11 as target in this case since the other group will definitely sum up to 12 if we can find a group summing up to 11.

     Last, if we cannot find target, we need to double the difference between target and the closest (but not exceed) number to return.
     
     For example, in the previous case, if we can only find 9 (and 14) to be the closest sum, the returned value is 1 + 2 * (target - 9) = 5 since 14 - 9 = 5. There is a 1 since the total sum is odd.

     Method 1 : Dynamic Programing
     ---Time Complexity = O(sum * stones.size())
     ---Space Complexity = O(sum)

     After we find the target, we declare a vector called dp with size of target + 1 which stores all the possible sum from 0 to target (inclusive).
     dp[j] will be 1 if it's possible to find some numbers summing up to j.
     
     And then, we start to check from dp[target], if dp[k] is not 1, meaning that we cannot find some numbers summing up to target.
     Then we need to increase the returned value by 2. We repeat this process and decrease the checking number by 1 every time until we find a dp[k] is 1.
     */
    
    int doit(vector<int>&& stones) {
        
        int total = std::accumulate(stones.begin(), stones.end(), 0);
        int odd = total % 2;
        total /= 2;
        
        vector<bool> dp(total + 1);
        dp[0] = true;
        
        for (size_t i = 0; i < stones.size(); i++) {
            
            for (int weight = total - stones[i]; weight >= 0; weight--) {
                if (dp[weight])
                    dp[weight + stones[i]] = true;
            }
        }
        
        for (int k = total; k > 0; k--) {
            if (!dp[k])
                odd += 2;
            else
                break;
        }
        
        return odd;
    }
    
    /*
     Method 2 : Recursive
     ---Time Complexity = O(2 ^ stones.size())
     It's surprisingly fast (4 ms) probably because most of the test cases were able to find target.
     ---Space Complexity = O(1)

     Similar in the first steps, but this time we implement a function findTar to find target. We recursively call this function until we find target. Notice that we can always call this function if we do not take stones[i], but we can only call this function if stones[i] <= target in case we are taking stones[i]. We turn the bool found to true once we find target, and this function return without doing anything if found is turned true.
     */
    int doit2(vector<int>& stones) {
        int target = 0;
        for (auto x : stones)
            target += x;
        int odd = target % 2;
        target /= 2;
        int ret = target;
        bool found = false;
        
        findTar(stones, 0, target, ret, found);
        return ret * 2 + odd;
    }
    
    void findTar(vector<int>& stones, int pos, int target, int& ret, bool& found)
    {
        if (found == true)
            return;
        
        if (target == 0)
            found = true;
        
        if (target < ret)
            ret = target;
        
        if (pos == stones.size())
            return;
        
        findTar(stones, pos+1, target, ret, found);
        
        if (stones[pos] <= target)
            findTar(stones, pos+1, target - stones[pos], ret, found);
    }
};


void test_1049_LastStoneWeightII() {
    
    int res = LastStoneWeightII().doit(vector<int>{2, 7, 4, 1, 8, 1});
    
    int res1 = LastStoneWeightII().doit(vector<int>{1,1,2,3,5,8,13,21,34,55,89,14,23,37,61,98});
    
    return;
}
