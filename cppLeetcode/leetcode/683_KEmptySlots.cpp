/*
 
 683. K Empty Slots
 
 
 You have n bulbs in a row numbered from 1 to n. Initially, all the bulbs are turned off. We turn on exactly one bulb every day until all bulbs are on after n days.

 You are given an array bulbs of length n where bulbs[i] = x means that on the (i+1)th day, we will turn on the bulb at position x where i is 0-indexed and x is 1-indexed.

 Given an integer k, return the minimum day number such that there exists two turned on bulbs that have exactly k bulbs between them that are all turned off. If there isn't such day, return -1.

  

 Example 1:

 Input: bulbs = [1,3,2], k = 1
 Output: 2
 Explanation:
 On the first day: bulbs[0] = 1, first bulb is turned on: [1,0,0]
 On the second day: bulbs[1] = 3, third bulb is turned on: [1,0,1]
 On the third day: bulbs[2] = 2, second bulb is turned on: [1,1,1]
 We return 2 because on the second day, there were two on bulbs with one off bulb between them.
 Example 2:

 Input: bulbs = [1,2,3], k = 1
 Output: -1
  

 Constraints:

 n == bulbs.length
 1 <= n <= 2 * 104
 1 <= bulbs[i] <= n
 bulbs is a permutation of numbers from 1 to n.
 0 <= k <= 2 * 104
 
 */
#include <vector>
#include <set>

using std::set;
using std::vector;

class KthEmptySlots {

    /*
        683.K-Empty-Slots
        此题可以用set的迭代器来做，每插入一个元素，只要在这个有序容器里找到前面和后面一个元素，看看之间是否相差ｋ即可．

        更巧妙的o(n)解法是一个贪心策略．

        我们将题目的条件转换成另一个数组days[i]，表示位置ｉ的花在days[i]这一天开放．那么我们希望得到什么呢？我们希望有这么一个宽度为k+1的区间[left,right],对于任意left<i<right，
        都有days[i]>days[left] && days[i]>days[right]．这说明这个区间内部的花都比两边的要晚开．等到left或right其中较晚的一个开放时，他们正好就是一对间隔Ｋ个ｐａｉｒ．

        那么如何找到这样一个窗口呢？我们尝试让它滑动起来．令left=0,right=left+k+1,然后逐个考察其中的ｉ是否符合条件．如果遇到不符合条件的，说明days[i]要比两边的都要早，
        成为了一个＂钉子户＂,所有小于i的left都不可能符合要求了．那么显然，我们的策略就是让这个钉子户作为新的left，进行下一次的搜索．

        注意,一旦找到一个合适的区间,那么输出的答案应该是max(days[left],days[right]),因为只有两边的花都开了,这个区间才成立.
    */
    int kEmptySlots(vector<int> &flowers, int k) 
    {
        int N = flowers.size();
        vector<int>days(N);
        for (int i=0; i<N; i++)
            days[flowers[i]-1] = i;
        
        int result = INT_MAX;
        int candidate;
        for (int i=0; i<N; i++)
        {
            int left = i;
            int right = left+k+1;
            if (right>=N) break;
            
            bool flag = 1;
            for (int j=left+1; j<=right-1; j++)
            {
                if (days[j]<days[left] || days[j]<days[right])
                {
                    flag = 0;
                    i = j-1;
                    break;
                }
            }
            if (flag) 
            {
                candidate = std::max(days[left],days[right])+1;
                result = std::min(result,candidate);
            }
        }
        if (result==INT_MAX)
            return -1;
        else
            return result;
    }



public:

    /*
        Approach #3: Sliding Window [Accepted]
        Intuition

        As in Approach #2, we have days[x] = i for the time that the flower at position x blooms. We wanted to find candidate intervals [left, right] where days[left], 
        days[right] are the two smallest values in [days[left], days[left+1], ..., days[right]], and right - left = k + 1.

        Notice that these candidate intervals cannot intersect: for example, if the candidate intervals are [left1, right1] and [left2, right2] with left1 < left2 < right1 < right2, 
        then for the first interval to be a candidate, days[left2] > days[right1]; and for the second interval to be a candidate, days[right1] > days[left2], a contradiction.

        That means whenever whether some interval can be a candidate and it fails first at i, indices j < i can't be the start of a candidate interval. This motivates a sliding window approach.

        Algorithm

        As in Approach #2, we construct days.

        Then, for each interval [left, right] (starting with the first available one), we'll check whether it is a candidate: whether days[i] > days[left] and days[i] > days[right] for left < i < right.

        If we fail, then we've found some new minimum days[i] and we should check the new interval [i, i+k+1]. If we succeed, then it's a candidate answer, and we'll check the new interval [right, right+k+1].

        Complexity Analysis

        Time and Space Complexity: O(N). The analysis is the same as in Approach #2.
    */
    int doit_greedy_slidingwindows(vector<int>& bulbs, int k) {
        
        vector<int> days(bulbs.size(), 0);
        for (auto i = 0; i < bulbs.size(); i++) {
            days[bulbs[i]-1] = i+1;
        }
        
        auto left = 0, right = k+1;
        int ans = bulbs.size() + 1;
        while (right < bulbs.size()) {
            
            auto i = left + 1;
            for (; i < right; i++) {
                if (days[i] < days[left] || days[i] < days[right]) {
                    left = i;
                    right = i + k + 1;
                    break;
                }
            }
            
            if (i == right) {
                ans = std::min(ans, std::max(days[left], days[right]));
                left = right;
                right = left + k + 1;
            }
        }
        
        return ans == bulbs.size() + 1 ? -1 : ans;
    }

    /*
        Approach #1: Insert Into Sorted Structure [Accepted]
        Intuition
        Let's add flowers in the order they bloom. When each flower blooms, we check it's neighbors to see if they can satisfy the condition with the current flower.

        Algorithm
        We'll maintain active, a sorted data structure containing every flower that has currently bloomed. When we add a flower to active,
         we should check it's lower and higher neighbors. If some neighbor satisfies the condition, we know the condition occurred first on this day.


        Complexity Analysis

        Time Complexity: O(NlogN), where NN is the length of flowers. Every insertion and search is O(\log N)O(logN).

        Time Complexity (Python): O(N^2)O(N 
        2
        ). As above, except list.insert is O(N)O(N).

        Space Complexity: O(N)O(N), the size of active.
    */
    int doit_hahstable(vector<int>& bulbs, int k) {
        
        set<int> pos;
        for (int i = 0; i < bulbs.size(); i++) {
            
            pos.insert(bulbs[i]);
            
            auto it = pos.find(bulbs[i]);
            
            if (it != begin(pos) && *it - *prev(it) - 1 == k) return i+1;
            
            if (it != end(pos) && *next(it) - *it - 1 == k) return i+1;
        }
        
        return -1;
    }
};
