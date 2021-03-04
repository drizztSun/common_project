/*

# 768. Max Chunks To Make Sorted II

# Given an array arr of integers (not necessarily distinct),
# we split the array into some number of "chunks" (partitions),
# and individually sort each chunk.
# After concatenating them, the result equals the sorted array.

# What is the most number of chunks we could have made?

# Example 1:

# Input: arr = [5,4,3,2,1]
# Output: 1
# Explanation:
# Splitting into two or more chunks will not return the required result.
# For example, splitting into [5, 4], [3, 2, 1] will result in [4, 5, 1, 2, 3], which isn't sorted.

# Example 2:

# Input: arr = [2,1,3,4,4]
# Output: 4
# Explanation:
# We can split into two chunks, such as [2, 1], [3, 4, 4].
# However, splitting into [2, 1], [3], [4], [4] is the highest number of chunks possible.
# Note:

# arr will have length in range [1, 2000].
# arr[i] will be an integer in range [0, 10**8].



*/
#include <vector>
#include <algorithm>
#include <stack>

using std::stack;
using std::vector;

class MaxChunksToSorted {

	/*
			768.Max-Chunks-To-Make-Sorted-II
		解法1
		我们很容易想到将原数组arr排个序得到expect新数组，比较一下它们有什么区别。

		举个例子

		arr：[4,1,3,2],5,6
		exp：[1,2,3,4],5,6
		我们可以知道前四个元素是属于同一个chunk的。有什么快速判定的方法呢？其实只要arr的前k个元素的和等于exp的前k个元素的和，那么就意味着arr的前k个元素一定就是exp的前k个元素的permutation。
		这是因为exp是循序递增的，它的k-presum，一定是arr里所有k-sum里面最小的。因此，exp的k-presum，一定对应了arr里面唯一的一组k-sum（也就是最小的k个元素）。

		所以利用这个规律，我们只要不停地推进索引k，当发现第一个k能使得arr和exp的前k个元素和相同，它们一定是一组permutation，并且是符合题意的最小的chunk。然后清空两个sum的计数器，从下一个数开始重复这个过程寻找接下来的chunk。

		解法2：单调栈
		本题用单调栈有非常amazing的线性时间解法。我们来看一个例子：...3, [7,8,4,6,5],9....

		其中中括号部分的是一个符合题意的chunk（需要内部排序）。chunk的特点是里面的所有元素都比chunk前的数大，同时比chunk后的数小，同时内部是乱序。

		我们从起始元素顺次观察到7和8的时候，都没有问题，每个元素都可以独自构成一个chunk。但是看到4的时候，我们发现4太小了，想让它回到期望的位置必须挤掉7和8.这就意味着[7,8,4]必须属于一个chunk。
		我们再看6，发现6其实也应该是属于这个chunk里面，因为6比8小，说明6的位置也不是expected。再看5也是同理。这就意味着我们需要记录一下curMax，当后面的数比它小的时候，就意味着这个小数应该与curMax一起属于同一chunk。

		所以这就提示我们维护一个单调递增的栈，所有违反递增规律的数都会被过滤掉。但是同一chunk里面没有违法递增规律的数还是会保留下来。
		根据上面的例子，我们的单调栈里面是3,[7,8],9...这时候我们想，如果我们能让每个chunk里面只保留一个数，那么最后栈里面剩多少个数不就意味着多少个chunk吗？那么这个例子里面，我们肯定会保留8，因为它是这个chunk的最大值。
		那么7通过什么方法去掉呢？其实我们当初在查看4的时候就提到过它会挤掉7和8.于是我们就想到了这样一个算法：如果当前查看的数小于curMax，它会挤掉所有栈顶比它大的数（因为这些都会是和它处于同一个chunk的数），但是我们保留curMax仍然再放回栈里面去。
		
		这是因为curMax就是用来判定新数是否属于同一chunk的，我们需要时刻把它放在栈顶。

		还是取上面那个例子，栈的变化如下：

		...3
		...3,7
		...3,7,8
		...3,7,8,4 => ...3,8  （4把7和8弹走，但是保留8加回来）
		...3,8,6 => ...3,8 （6把8弹走，但是保留8加回来）
		...3,8,5 => ...3,8 （5把8弹走，但是保留8加回来）
		...3,8,9
		可以看出，最后整个chunk只剩8会被保留在栈中，并且以后永远不会再被改动（因为后面的chunk的数都会比8大）。考察完所有的数之后，栈里有多少元素，就有多少个chunk。
			
	*/
	int doit_monotonic_stack(vector<int>& arr) 
    {
		// increasing monotonic stack
        stack<int>Stack;
        int curMax;
        for (auto x: arr)
        {
            if (Stack.empty() || Stack.top() <= x)
            {
                Stack.push(x);
                curMax = x;
            }                
            else
            {
                while (!Stack.empty() && Stack.top() > x)
                    Stack.pop();
					
                Stack.push(curMax);
            }
        }
        return Stack.size();
    }

    int doit_sort(vector<int>& arr) 
    {
        auto expect = arr;
        sort(expect.begin(), expect.end());

        long long sum1 = 0, sum2 = 0;
		int count = 0;
        for (int i=0; i<arr.size(); i++)
        {
            sum1+=arr[i];
            sum2+=expect[i];

            if (sum1==sum2) {
                count++;
                sum1 = sum2 = 0;
            }
        }
        return count;
    }


public:
	int doit_twopointer(vector<int>& arr) {

		int length = arr.size();
		vector<int> leftMax(length), rightMin(length);
	
		leftMax[0] = arr[0];
		for (auto i = 1; i < arr.size(); i++) {
			if (leftMax[i - 1] > arr[i])
				leftMax[i] = leftMax[i - 1];
			else
				leftMax[i] = arr[i];
		}

		rightMin[length - 1] = arr[length - 1];
		for (auto i = length - 2; i >= 0; i--) {
			if (rightMin[i + 1] < arr[i])
				rightMin[i] = rightMin[i + 1];
			else
				rightMin[i] = arr[i];
		}

		int maxChunks = 0;
		for (auto i = 0; i < arr.size()-1; i++) {
			if (leftMax[i] <= rightMin[i + 1])
				maxChunks++;
		}

		return maxChunks + 1;
	}
};