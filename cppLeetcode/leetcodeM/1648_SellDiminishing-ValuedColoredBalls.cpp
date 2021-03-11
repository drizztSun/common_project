/*
1648. Sell Diminishing-Valued Colored Balls

You have an inventory of different colored balls, and there is a customer that wants orders balls of any color.

The customer weirdly values the colored balls. Each colored ball's value is the number of balls of that color you currently have in your inventory. 
For example, if you own 6 yellow balls, the customer would pay 6 for the first yellow ball. 
After the transaction, there are only 5 yellow balls left, so the next yellow ball is then valued at 5 (i.e., the value of the balls decreases as you sell more to the customer).

You are given an integer array, inventory, where inventory[i] represents the number of balls of the ith color that you initially own. 
You are also given an integer orders, which represents the total number of balls that the customer wants. You can sell the balls in any order.

Return the maximum total value that you can attain after selling orders colored balls. As the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:


Input: inventory = [2,5], orders = 4
Output: 14
Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
The maximum total value is 2 + 5 + 4 + 3 = 14.
Example 2:

Input: inventory = [3,5], orders = 6
Output: 19
Explanation: Sell the 1st color 2 times (3 + 2) and the 2nd color 4 times (5 + 4 + 3 + 2).
The maximum total value is 3 + 2 + 5 + 4 + 3 + 2 = 19.
Example 3:

Input: inventory = [2,8,4,10,6], orders = 20
Output: 110
Example 4:

Input: inventory = [1000000000], orders = 1000000000
Output: 21
Explanation: Sell the 1st color 1000000000 times for a total value of 500000000500000000. 500000000500000000 modulo 109 + 7 = 21.
 

Constraints:

1 <= inventory.length <= 10^5
1 <= inventory[i] <= 10^9
1 <= orders <= min(sum(inventory[i]), 10^9)
*/
#include <vector>
#include <algorithm>

using std::vector;


class ColoredBalls {

    /*
        1648.Sell-Diminishing-Valued-Colored-Balls
        解法1：数学贪心
        本题的基本策略是：将所有的颜色按照数量从高到低排列。我们优先对当前数量最多（a）的颜色取一个球，这样总价值+a。然后再对当前剩余数量最多（b）的颜色取一个球（可能仍然是同一种颜色），这样总价值+b...直到我们操作的次数达到orders。

        举个例子，我们将inventory从高到低排序之后，假设数组长这个样子：

        10 7 4 3 2 1
        第一回合：数值最大的10就是我们的操作目标，我们取一个球，总价值加10分。但是取完之后发现最大数量的颜色依然是它，但是9个球，意味着我们还可以再取一个球再增加9分。我们可以不断地取这个颜色，直至该颜色的数目和第二多的颜色数目持平（都是7）。所以这一轮我们的价值增加的是(10+9+8).

        第二回合：当前数值最大的7就是我们的操作目标。注意这次我们可以取2个球：包括颜色数量排名第一和第二的两种颜色。此外，我们可以从+7，+6，一直取到+5（因为数量第三多的颜色数量是4），故增加的价值是(7+6+5)*2

        可见每个回合，我们就推进了一种颜色。在处理第i种颜色时，我们可以一轮取i+1个球，这些球对应的分值是相同的，从inventory[i]、inventory[i]+1...直至inventory[i+1]+1。

        这里有一个比较关键的地方，就是总球数达到orders的时候，我们必须停下来。在哪个回合的哪一轮停下来，“零头”是多少，需要好好处理。从上述可知，在第i回合中，每轮可以取i+1个球，可知需要进行q = orders/(i+1)轮，剩下的零头r = orders%(i+1)个球对应的分数就是inventory[i]-q.

        另一个注意的点是，对于10 10 8....这种情况，根据上述的算法，第一回合其实不用做任何操作，因为第一和第二的颜色数目相同。在第二回合的操作里直接一并取两个球。

        解法2：二分搜值
        因为每轮我们所取的球的分值都是递减1的，我们可以尝试猜测最后一整轮的球的分值是k，另外可能还有一些零头的球它们的分值是k-1. 我们需要寻找最大的k，使得分值大于等于k的球的总数不超过orders。

        对于任何一种颜色inventory[i]，如果inventory[i]>=k，那么它必然能贡献inventory[i]-k+1个球，其中最大分数是inventory[i]，最小分数是k。扫描一遍整个数组，我们就能把总球数求出来，与orders比较一下。如果大于orders，说明取的球太多了，k要提升一下。反之，k就要下降一点。

        确定了k之后，我们还要手工计算一下零头的数量是多少，他们每个球贡献的分数是k-1.
    */
    int doit_sort(vector<int>& inventory, int orders) 
    {
        sort(inventory.begin(), inventory.end());
        reverse(inventory.begin(), inventory.end());
        int n = inventory.size();
        inventory.push_back(0);
        long long M = 1e9+7;
        
        long long ret = 0;
        for (int i=0; i<n; i++)
        {
            long long a = inventory[i];
            long long b = inventory[i+1];
            long long total = (a-b)*(i+1);
            
            if (total <= (long long)orders)
            {
                ret += (a+b+1)*(a-b)/2*(i+1);
                orders -= total;
                ret %= M;
            }
            else
            {                
                long long k = orders/(i+1);
                ret += (a+a-k+1)*k/2*(i+1);
                ret %= M;
                                
                long long m = orders%(i+1);
                ret += (a-k)*m;
                ret %= M;
                break;
            }                                   
            if (orders<=0) break;
        }
        return ret;
        
    }

    int doit_binary_search(vector<int>& inventory, int orders) 
    {
        long long M = 1e9+7;
        sort(inventory.begin(), inventory.end());
        reverse(inventory.begin(), inventory.end());

        auto count = [&](int k)
        {
            long long total = 0;
            for (int i=0; i<inventory.size(); i++)
            {
                if (inventory[i]<k) break;
                total += inventory[i]-k+1;
            }
            return total;
        };

        int left = 1, right = inventory[0];
        while (left <right)
        {
            int mid = left+(right-left)/2;
            if (count(mid) <= orders)
                right = mid;
            else
                left = mid+1;
        }
        long long x = left;
        long long ret = 0;

        for (int i=0; i<inventory.size(); i++)
        {            
            if (inventory[i]<x) break;
            ret += (inventory[i]+x)*(inventory[i]-x+1)/2%M;
            ret %= M;
        }
        ret += (x-1)*(orders-count(x)) % M;
        ret %= M;

        return ret;
    }

public:

    /*
        The idea is we first want to find a target value T which is the smallest value we will add to our score within a transaction. 
        Since the trend is monotonic, we can use Binary Search to find the value T. 
        We simply guess a value to see 
        how many orders we can make with the value. If the result is less the 
        value orders we are given, then we know the value we guessed is too high that cannot be the target value (that's why set hi=mid-1). 
        When we know the target value T, we need to notice that 
        we are not necessarily buying all those balls with target value,
        but it is guaranteed that we need to buy all the balls with value greater than 
        target value T(that's why we set low = low+1). 
        After that, we ran out of the balls with value greater than target value, 
        now, we can only add balls with target value for (orders we left) times.
    */
    long check(vector<int>& inventory, int target) {// count how many orders with buying balls with value at least target
		long sum = 0;
		for(auto& x:inventory) {
			if(x >= target) {
				sum += x - target + 1;
			}
		}
		return sum;
	}
	int doit_binary_search(vector<int>& inventory, int orders) {
		long low = 1;
		long hi = INT_MAX;
		int kMod = 1e9 + 7;

		while(low < hi) {
			long mid = low + (hi - low+1) /2;
			long res = check(inventory, mid);
			if(res < orders) {
				hi = mid - 1;
			} else {
				low = mid;
			}
		}

		long ans = 0;
		low = low + 1; // buy all balls with this value and above
		for(auto& x:inventory) {
			if(x >= low ) {
				ans += (low + x)*(x-low + 1)/2;
				ans = ans%kMod;
				orders -= x-low+1;
			}
		}
		
        low = low - 1;
		for(int i=0;i<orders;i++) {
			ans += low;
			ans = ans%kMod;

		}
		return ans;
	}

    int doit_sort(vector<int>& inventory, int orders) {
        
        std::sort(begin(inventory), end(inventory), [](auto a, auto b){ return a > b; });
        int i = 0, n = inventory.size(), mod = 1e9 + 7;
        inventory.push_back(0);
        long long total = 0;
        
        while (orders) {
            
            while (i < n && inventory[i] == inventory[i+1]) i++;
            
            long a = inventory[i], b = inventory[i+1];
            long diff = a - b;
            
            if (diff * (i+1) < orders) {
                orders -= diff * (i+1);
                total = (total + (a+b+1) * diff / 2 * (i+1)) % mod;
                inventory[i] = inventory[i+1];
            } else {
                long c = orders % (i+1);
                long r = orders / (i+1);
                total = (total + r * (2 * inventory[i] - r + 1) /2 * (i+1)) % mod + c * (inventory[i] - r);
                orders = 0;
            }
        }
        
        return total%mod;
    }
};


