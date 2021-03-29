/*

 659. Split Array into Consecutive Subsequences


 Given an array nums sorted in ascending order, return true if and only if you can split it into 1 or more subsequences such that each subsequence consists of consecutive integers and has length at least 3.

  

 Example 1:

 Input: [1,2,3,3,4,5]
 Output: True
 Explanation:
 You can split them into two consecutive subsequences :
 1, 2, 3
 3, 4, 5
 Example 2:

 Input: [1,2,3,3,4,4,5,5]
 Output: True
 Explanation:
 You can split them into two consecutive subsequences :
 1, 2, 3, 4, 5
 3, 4, 5
 Example 3:

 Input: [1,2,3,4,4,5]
 Output: False
  

 Constraints:

 1 <= nums.length <= 10000


 */

#include <unordered_map>
#include <vector>


using std::unordered_map;
using std::vector;


class SplitArrayIntoConsecutiveSubsequences {

    /*
        659.Split-Array-into-Consecutive-Subsequences
        假设我们当前处理的数字是x。下面分两种情况讨论：

        如果之前的处理过的元素里，已经有以x-1为结尾的、长度大于等于3的序列，那么我们必然会将x接在这个已有的序列上。为什么呢？如果我们不接，那么x必然是作为一段新序列的首元素。但是如果后面没有x+1和x+2接上，那么x这个新序列就无法满足长度要求。而如果后面有x+1和x+2，那么我们何不将x,x+1,x+2一并都接在以x-1为结尾的序列上呢？可见不管后面是否有x+1/x+2，将x接在已有的序列上，都是最保险的决策。

        如果之前的处理过的元素里，已经有以x-1为结尾的、长度大于等于3的序列，那么我们该怎么办呢？我们就必须创建以x为首元素的新序列，同时为了保证该新序列的最终长度要大于等于3，我们必须向后面“预支”两个元素：x+1和x+2。如果我们能提前知道后面已经没有了x+1和x+2，那么我们就可以返回false。

        所以我们需要两个哈希表。seq[x]表示目前为止已经构建了多少个以x为结尾的、长度大于等于3的序列。left[x]表示后面还有多少个x没有被处理（初始值就是原数组中的x的个数）。当第一种情况时，以x-1结尾的序列会变成以一个新的以x为结尾的序列。第二种情况时，会增加一个以x+2为结尾的序列，同时注意相应的left[x],left[x+1],left[x+2]都需要自减1.
    */
    bool isPossible(vector<int>& nums) 
    {
        unordered_map<int,int>left;
        unordered_map<int,int>seq;
        for (auto x: nums)
            left[x]++;

        for (auto x: nums)
        {
            if (left[x]==0) continue;
            if (seq[x-1]>0)
            {                
                left[x]--;
                seq[x-1]-=1;
                seq[x]+=1;
            }
            else
            {
                if (left[x+1]==0 || left[x+2]==0) return false;
                left[x]--;
                left[x+1]--;
                left[x+2]--;
                seq[x+2]+=1;
            }
            
        }
        return true;        
    }
    
public:
    
    /*
        Approach #2: Greedy [Accepted]
        Intuition

        Call a chain a sequence of 3 or more consecutive numbers.

        Considering numbers x from left to right, if x can be added to a current chain, it's at least as good to add x to that chain first, rather than to start a new chain.

        Why? If we started with numbers x and greater from the beginning, the shorter chains starting from x could be concatenated with the chains ending before x, possibly helping us if there was a "chain" from x that was only length 1 or 2.

        Algorithm

        Say we have a count of each number, and let tails[x] be the number of chains ending right before x.

        Now let's process each number. If there's a chain ending before x, then add it to that chain. Otherwise, if we can start a new chain, do so.

        It's worth noting that our solution can be amended to take only O(1)O(1) additional space, since we could do our counts similar to Approach #1, and we only need to know the last 3 counts at a time.


        Complexity Analysis

        Time Complexity: O(N), where NN is the length of nums. We iterate over the array.
        Space Complexity: O(N), the size of count and tails.
    */

    bool doit_greedy(vector<int>& nums) {
        
        unordered_map<int, int> tail;
        unordered_map<int, int> counter;
        
        for (auto c : nums)
            counter[c]++;
        
        for (auto x : nums) {
            
            if (counter[x] == 0)
                continue;
            
            if (tail[x] > 0) {
                tail[x]--;
                tail[x+1]++;
            } else if (counter[x+1] > 0 && counter[x+2] > 0) {
                counter[x+1]--;
                counter[x+2]--;
                tail[x+3]++;
            } else {
                return false;
            }
            
            counter[x]--;
        }
        
        return true;
    }
};
