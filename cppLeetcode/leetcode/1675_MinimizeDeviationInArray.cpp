/*
 1675. Minimize Deviation in Array
 
 You are given an array nums of n positive integers.

 You can perform two types of operations on any element of the array any number of times:

 1. If the element is even, divide it by 2.
    For example, if the array is [1,2,3,4], then you can do this operation on the last element, and the array will be [1,2,3,2].
 2. If the element is odd, multiply it by 2.
    For example, if the array is [1,2,3,4], then you can do this operation on the first element, and the array will be [2,2,3,4].
 
 The deviation of the array is the maximum difference between any two elements in the array.

 Return the minimum deviation the array can have after performing some number of operations.

  

 Example 1:

 Input: nums = [1,2,3,4]
 Output: 1
 Explanation: You can transform the array to [1,2,3,2], then to [2,2,3,2], then the deviation will be 3 - 2 = 1.
 Example 2:

 Input: nums = [4,1,5,20,3]
 Output: 3
 Explanation: You can transform the array after two operations to [4,2,5,5,3], then the deviation will be 5 - 2 = 3.
 Example 3:

 Input: nums = [2,10,8]
 Output: 3
  

 Constraints:

 n == nums.length
 2 <= n <= 105
 1 <= nums[i] <= 109
 
 
 */
#include <vector>
#include <set>
#include <queue>

using std::multiset;
using std::vector;
using std::priority_queue;

class MinimumDeviation {

public:
    /*
        1675.Minimize-Deviation-in-Array
        对于奇数x，它可以变换成2x,x; 对于偶数x，它可以变换成x, x/2, x/4, ... 直至变成一个奇数。我们将每个数和它的变换数看作是一组。于是本题就是要求从每组里面取一个数，使得所取的这些数的range最小。
        这样看来，本题的本质就是和632.Smallest-Range-Covering-Elements-from-K-Lists一模一样了。

        具体的方法是，查看全局最大值x，考虑如果以x为range最大值时，此时最优的range最小值是什么？显然，除了x所在的“组”，其他的组我们都会选取该组的最大值，因为它们比同组的其他元素离x更近。
        于是等效于我们pick了所有组的最大元素组成一个range。如果我们用优先队列来盛装这n个元素组成的range，我们就可以知道这个range里面的最小值y，于是x-y就是deviation。

        接下来，我们会将全局最大值x扔掉，那么它所在组就会用该组第二大的元素来“替补”这个代表席位并放进range里。此时，全局次大值x'必然也在这个range里（因为它必然是此时某组的最大值。于是x'减去此时range的最小值，得到的就是x'所对应的最优range的deviation。

        依次类推，每一轮我们扔掉之前的全局最大值，同时递补进该组的下一个元素。此时range里面的n个元素的deviation，就对应了“当前最大值”作为“range最大值”时的最优解。

        此题本质上和632.Smallest-Range-Covering-Elements-from-K-Lists非常类似。
    */
    int doit_heap(vector<int>&& nums) {
        
        multiset<int> buff;

        for (auto c: nums) {
            if (c % 2 == 0)
                buff.insert(c);
            else
                buff.insert(c * 2);
        }
        
        int res = INT_MAX;
        while (true) {
            
            res = std::min(res, *buff.rbegin() - *buff.begin());
            int c = *buff.rbegin();
            buff.erase(c);
            
            if (c % 2 == 0)
                buff.insert(c/2);
            else
                break;
        }
        
        return res;
    }
    
    static vector<int> smallestRange(vector<vector<int>>& nums) {
        int rangeLeft = 0, rangeRight = INT_MAX;
        int size = nums.size();
        vector<int> next(size);
        auto cmp = [&](const int& u, const int& v) {
            return nums[u][next[u]] > nums[v][next[v]];
        };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        int minValue = 0, maxValue = INT_MIN;
        for (int i = 0; i < size; ++i) {
            pq.emplace(i);
            maxValue = std::max(maxValue, nums[i][0]);
        }

        while (true) {
            int row = pq.top();
            pq.pop();
            minValue = nums[row][next[row]];
            if (maxValue - minValue < rangeRight - rangeLeft) {
                rangeLeft = minValue;
                rangeRight = maxValue;
            }
            if (next[row] == nums[row].size() - 1) {
                break;
            }
            ++next[row];
            maxValue = std::max(maxValue, nums[row][next[row]]);
            pq.emplace(row);
        }

        return {rangeLeft, rangeRight};
    }
    
public:
    int minimumDeviation(vector<int>& nums) {
        // 这道题跟632一样。相当于k list找最小的interval实现覆盖。奇数的数据范围是x,2x
        // 偶数代表的数据范围是x, x/2, x/4...
        /**
        //////////////////////////////////
        // 这道题第一次见给我的直觉就是大数和小数朝中间靠。但是怎么靠，不清楚。
        // 对于每一个数。如果是偶数，那么一直除直到奇数就是可选的数。如果是奇数，乘以2是可选的数
        // 那么每个位置上其实是一系列的数。最终看你怎么选 从而整体的极差极小。(找最大最小值)
        // 用set维护一个从小到大的顺序。然后大的擦掉变小。小的变大？
        set<int> s;
        for (int &num : nums) {
            // 这里与python的第一个题解不一样。这里是从高到低。py用的从底到高
            s.insert(num % 2 ? num * 2 : num);
        }
        // 因为一开始都是大数。因此变化过程中最大值一直在变小。
        int res = *s.rbegin() - *s.begin();
        while (*s.rbegin() % 2 == 0) {
            // 最大值不能变小 说明那个list用光了
            s.insert(*s.rbegin() / 2);
            s.erase(*s.rbegin());
            res = min(res, *s.rbegin() - *s.begin());
        }
        return res;
        */
        /**
        // 将632封装成API使用
        // 对于每个数 xx，如果是奇数，我们就将 xx 和 2x2x 放入列表中；
        // 如果是偶数，就将其不断除以 22 并将所有得到的值都放入列表中。随后我们调用 API 求解即可。
        int n = nums.size();
        vector<vector<int>> v(n);
        for (int i = 0; i < n; i++) {
            if (nums[i] & 1) {
                v[i].push_back(nums[i]);
                v[i].push_back(nums[i] * 2);
            } else {
                while (!(nums[i] & 1)) {
                    v[i].push_back(nums[i]);
                    nums[i] /= 2;
                }
                v[i].push_back(nums[i]);
                reverse(v[i].begin(), v[i].end());
            }
        }
        auto ans = API::smallestRange(v);
        return ans[1] - ans[0];
        */
        // https://leetcode-cn.com/problems/minimize-deviation-in-array/solution/yi-chong-fu-za-du-geng-di-de-zuo-fa-by-heltion-2/
        // 算法优化。O(n(loga_max + logn))
        /**
        int p_max = 1;
        for (int a : nums) {
            while (a % 2 == 0) a /= 2;
            p_max = max(p_max, a);
        }
        vector<int> upper;
        int min = p_max;
        for (int a : nums) {
            if (a % 2 == 1) a *= 2;
            while (a >= 2 * p_max) a /= 2;
            if (a >= p_max) upper.push_back(a);
            min = std::min(min, a);
        }
        sort(upper.begin(), upper.end());
        int ans = upper.back() - min;
        for (int i = upper.size() - 1; upper[i] > p_max; i--) {
            min = std::min(min, upper[i] / 2);
            ans = std::min(ans, upper[i - 1] - min);
        }
        return ans;
        */
        // 继续优化loga_max 二进制位运算 降低复杂度到常数。因此可以进一步优化掉变成O(nlogn)
        int p_max = 1;
        for (int a : nums) {
            // 求a的奇数因子可以直接计算a几个0结尾然后向右移即可O(1)
            p_max = std::max(p_max, a >> (__builtin_ctz(a)));  // __builtin_ctz表示trailing zeros
        }
        vector<int> upper;
        int min = p_max;
        for (int a : nums) {
            if (a & 1) a <<= 1;
            if (a >= p_max) {
                // a是一个大于p_max的数 那么移动多少向a靠近呢？用leading zeros的差来做
                a >>= __builtin_clz(p_max) - __builtin_clz(a);
                if (a < p_max) a <<= 1; // 多了补回来即可
                upper.push_back(a);
            }
            min = std::min(min, a);
        }
        sort(upper.begin(), upper.end());
        int ans = upper.back() - min;
        
        for(int i = upper.size() - 1; upper[i] > p_max; i -= 1){
            min = std::min(min, upper[i] >> 1);
            ans = std::min(ans, upper[i - 1] - min);
        }
        return ans;
    }
};

void test_1675_minimum_deviation() {
    
    MinimumDeviation().doit_(vector<int>{1, 2, 3, 4});
}
