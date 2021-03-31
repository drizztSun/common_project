/*
1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits

Given a string num representing the digits of a very large integer and an integer k.

You are allowed to swap any two adjacent digits of the integer at most k times.

Return the minimum integer you can obtain also as a string.

 

Example 1:


Input: num = "4321", k = 4
Output: "1342"
Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
Example 2:

Input: num = "100", k = 1
Output: "010"
Explanation: It's ok for the output to have leading zeros, but the input is guaranteed not to have any leading zeros.
Example 3:

Input: num = "36789", k = 1000
Output: "36789"
Explanation: We can keep the number without any swaps.
Example 4:

Input: num = "22", k = 22
Output: "22"
Example 5:

Input: num = "9438957234785635408", k = 23
Output: "0345989723478563548"
 

Constraints:

1 <= num.length <= 30000
num contains digits only and doesn't have leading zeros.
1 <= k <= 10^9


https://zxi.mytechroad.com/blog/greedy/leetcode-1505-minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/

*/
#include <string>
#include <vector>
#include <queue>

using std::queue;
using std::vector;
using std::string;


class Fenwick {

public:

    explicit Fenwick(int n): _sums(n+1) {}

    void update(int i, int delta) {
        i++;
        while (i < _sums.size()) {
            _sums[i] += delta;
            i += i & -i;
        }
    }

    int query(int i) {
        i++;
        int ans = 0;
        while (i > 0) {
            ans += _sums[i];
            i -= i & -i;
        }
        return ans;
    }

    vector<int> _sums;
};


class MinimumPossibleIntegerAfterKSwap {

    /*    
        1505.Minimum-Possible-Integer-After-at-Most-K-Adjacent-Swaps-On-Digits
        首先，我们要明确贪心的策略。我们要确定第i位的数字时，肯定是找它右边存在的（可以是它自己）、可以搬运过来的最小数字，来放在第i位，然后其余的数字往后顺移。每一步都依次类推。

        为了避免我们在一个非常长的序列中遍历寻找这个“最小的数字”，一个比较常见的方法，就是根据题目的特点“只有10个数字种类”，提前把这个10个数字的排布都预处理，然后从小到大查看。
        事实上，我们不需要把每个数字的全部位置信息都找到，目前只需要找到数字j下一个出现的最近位置即可（后面会解释），我们标记为next[j]。

        在一般情况下，我们如果在确定第i位数字的时候，假设通过贪心的策略找到可以搬运过来的右边的“最小数字”是j，那么我们需要swap的次数就是next[j]-i. 但是我们知道，这个计算式并不准确。
        这是因为：如果next[j]后面的某个数字在前面的操作中已经被移动到前面去了，那么相当于数字j的位置要后移。所以我们维护一个后移变量offset[j]来标记要后移多少。于是，真正需要swap的次数就是next[j]+offset[j]-i.

        那么如何计算这个和维护这个offset数组呢？根据之前的描述，如果数字j需要前移到位置i，那么所有处在i和next[j]之前的数字都遇到了上面所说的情况。因此这些数字的offset都要加1. 实际上这个操作的代价很低，我们只需要遍历10个数字即可。

                    for (int k=0; k<10; k++)
                    {
                        if (next[k] < next[j])
                            offset[k]++;
                    }
        注意到，offset[d]是配合next[d]来使用。即使i和next[j]之间某个数字d出现了多次，也不需要将offset[d]多次自增。

        OK，现在我们已经把数字j从next[j]+offset[j]的位置搬到了i，那么我们需要更新next[j]。注意，其他数字的next都不需要变化，因为我们已经更新了必要的offset。如果找到新的next[j]呢？只要从之前的next[j]的位置往后无脑遍历就行，如果没有，那么next[j]标记为-1.

        此时最关键的一步是，对于数字j的offset已经失效了（记得offset[j]是配合next[j]使用的），针对这个新的next[j]，我们也需要更新offset[j]。这个怎么计算呢？我们之前说过，“新offset[j]”只能取决于有多少“新next[j]”右边的数字前移了。
        但是当前的offset[j]表示的是有多少“旧next[j]”右边的数字前移了。所以我们应该给新next[j]吐出一些offset来。这部分的数值是什么呢？就是处在新旧next[j]位置之间那些被前移的数字的个数。见下图，考察左边的j时，offset[j]=3；等到考察右边的j时，offset[j]=1。这中间的差值就是看两者之间有多少数字被前移了。

        j 4 3 X X j X 3 4
        所以这就提醒我们，每次前移一个数字，都要在它所在的位置标记一下，方便我们在更新offset[j]的时候使用。这一部分的代码是：

                    int start = next[j];
                    next[j] = -1;
                    for (int k=start+1; k<n; k++)
                    {
                        if (used[k]==true)
                            offset[j]--;
                        else if (num[k]==(j+'0'))
                        {
                            next[j] = k;
                            break;
                        }
                    }          
        这时我们需要理解一个事情。整个算法最外层的循环肯定是o(n)，上面的代码里面对于k的遍历看上去也是o(n)，总体的时间复杂度是不是o(n^2)。其实并不是。
        我们发现k的一次循环是从当前的j位置到下一个的j位置。如果以后的代码还会涉及到数字j，则这个k循环遍历的是从下一个j位置，到下下个j位置。所以无论i指向了数字j多少次，这个for循环总共只会完整地遍历一遍数组。
        考虑到只有10个数字，这个for循环只会完整地遍历数组10遍。所以说，并不是对于每次循环的i，上面的代码都会是跑o(n)级别。

        总结一下算法：

        当前位置是i，我们在i的右边定位最小的、能够搬运到i的数字j，以及它的位置next[j]
        计算消耗swap的次数是next[j]+offset[j]-i，并在next[j]的位置标记used.
        对于所有处于i和next[j]之间的数字d，更新offset[d]+=1
        从next[j]往后找到下一个j所在的位置，更新next[j]，并统计两者之间used的个数m，更新offset[j]-=m.
    */
    string minInteger(string num, int k) 
    {
        int n = num.size();
        vector<int>next(10,-1);
        vector<int>offset(10,0);
        for (int i=0; i<n; i++)
        {
            if (next[num[i]-'0']==-1)
                next[num[i]-'0'] = i;
        }

        vector<int>used(n, 0);
        string ret;
        auto ans = num;

        for (int i=0; i<num.size(); i++)
        {
            int j;
            for (j=0; j<10; j++)
            {
                if (next[j]==-1) continue;
                int d = next[j] + offset[j] - i;
                if (d <= k)
                {
                    k-=d;
                    break;
                }
            }
            ans[i] = num[next[j]];
            used[next[j]] = true;

            for (int k=0; k<10; k++)
            {
                if (next[k] < next[j])
                    offset[k]++;
            }

            int start = next[j];
            next[j] = -1;
            for (int k=start+1; k<n; k++)
            {
                if (used[k]==true)
                    offset[j]--;
                else if (num[k]==(j+'0'))
                {
                    next[j] = k;
                    break;
                }
            }            
        }
        return ans;
    }

public:
    
    /*
    Observation:

    1. If k is "large enough", the answer should be the sorted string. minNum("543210", inf) = "012345".

    2. Else fund the smallest movalbe number and move it to the front. minNum("543210", 2) = "354210"

    Very similar to bubble sort. We can do it recursively to build the right part of the string.

    minNum("543210", 10)

    = "0" + minNum("54321", 5)
    = "0" + "1" + minNUm("54321", 1)

    Time O(n^2)

    Constraints:

    1 <= num.length <= 30000
    num contains digits only and doesn’t have leading zeros.
    1 <= k <= 10^9
    Solution: Greedy + Recursion (Update: TLE after 7/6/2020)
    Move the smallest number to the left and recursion on the right substring with length equals to n -= 1.

    4321 k = 4 => 1 + solve(432, 4-3) = 1 + solve(432, 1) = 1 + 3 + solve(42, 0) = 1 + 3 + 42 = 1342.

    Time complexity: O(n^2)
    Space complexity: O(1)
    */
    string doit_greedy_recursive(string num, int k) {
        const int n = num.size();
        if (k >= n * (n - 1) / 2) {
            sort(begin(num), end(num));
            return num;
        }
        
        int s = 0;
        while (k > 0 && s < n) {
            auto bit = begin(num);
            auto it = std::min_element(bit + s, bit + std::min(s + k + 1, n));
            k -= distance(bit + s, it);
            rotate(bit + (s++), it, next(it));
        }
        return num;

    }

    /*
        cost of nums[i] is moving it to the front part of the stirng, and behead any char less than it. there are maybe multiple ones has been movec.
        so the cost is dynamic for each char, cost(nums[i]) = i - {how many chars has been moved before him}

        Moving elements in a string is a very expensive operation, basically O(n) per op. Actually, we don’t need to move the elements physically, 
        instead we track how many elements before i has been moved to the “front”. Thus we know the cost to move the i-th element to the “front”, 
        which is i – elements_moved_before_i or prefix_sum(0~i-1) if we mark moved element as 1.

        We know BIT / Fenwick Tree is good for dynamic prefix sum computation which helps to reduce the time complexity to O(nlogn).

        Time complexity: O(nlogn)
        Space complexity: O(n)
    */
    string doit_BIT_fenwick(string nums, int k) {

        int n = nums.size();
        vector<queue<int>> pos;
        for (int i = 0; i < nums.size(); i++)
            pos[nums[i] - '0'].push(i);

        Fenwick tree(n);
        vector<bool> used(n, false);
        string ans;

        while (k > 0 && ans.length() < n) {

            for (int cur = 0; cur < 10; cur++) {
                if (pos[cur].empty()) continue;

                /*
                    Always move the smaller digits to the head. if str[i] is smaller, it moves to the head. it wouldn't affect any num[j], j < i, steps to move.
                    but if j > i, if smaller num[i] moved first, then nums[j] will moves step less than 1. 
                    so for any position j, we need to know how many has been moved before it. and it will be i - query(i-1);
                */
                const int i = pos[cur].front();
                const int cost = i - tree.query(i-1);

                if (cost > k) continue;
                
                k -= cost;
                tree.update(i, 1);
                pos[cur].pop();
                used[i] = true;
                break;
            }
        }

        for (int i = 0; i < n; i++)
            if (!used[i])
                ans += nums[i];
        return ans;
    }
};