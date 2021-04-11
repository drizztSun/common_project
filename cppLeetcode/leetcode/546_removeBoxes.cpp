/*
# 546. Remove Boxes

# Given several boxes with different colors represented by different positive numbers.
# You may experience several rounds to remove boxes until there is no box left.
# Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1),
# remove them and get k*k points.
# Find the maximum points you can get.

# Example 1:
# Input:
# [1, 3, 2, 2, 2, 3, 4, 3, 1]
# Output:
# 23

# Explanation:
# [1, 3, 2, 2, 2, 3, 4, 3, 1]
# ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
# ----> [1, 3, 3, 3, 1] (1*1=1 points)
# ----> [1, 1] (3*3=9 points)
# ----> [] (2*2=4 points)
# Note: The number of boxes n would not exceed 100.

*/

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <functional>

using std::vector;
using std::unordered_map;

class RemoveBoxes {

	/*
		546.Remove-Boxes
		此题很难。本质上这题用了DP的状态转移的思想，但是bottom-up却并不好写，实际上用的是DFS＋记忆化的方法。当然，依然用到了状态数组，所以仍然可以看做一道DP题。

		此题第一眼看上去，很容易让人想尝试区间型DP的解法。毕竟有其他很多题都是类似的意境：比如312.Burst-Balloons，1000.Minimum-Cost-to-Merge-Stones等等。那我们先来尝试一下。

		我们考虑dp[l][r]表示在区间[l,r]内我们消灭所有盒子的最优值。区间型dp的目标是将大区间化成小区间，一个常见的突破口就是从最后一个元素入手，看它能够怎么处理掉。假设我们看到的这个区间长这个样子：

		... OOO  XXX OOO XXX OOO
		...   ^    ^   ^   ^   ^
		...   j1  i1  j0  i0   r
		最后一组OOO表示有若干个（可能只有一个）相同的元素（即boxes[r]）。同时在这个区间里有若干个subarray也有可能与boxes[r]相同，我们也用OOO标记出来。其他任何不包含boxes[r]的subarray都用XXX标记。

		最后一组OOO最粗暴的处理方法就是自己单独消去，那么至少有一个解就出来了：dp[l][i0] + count*count，其中count就是最后一组OOO的元素个数。

		当然，我们还会有其他的处理方式。比如说：先处理i0这组XXX，然后我们发现r这组OOO和j0这组OOO就可以接在了一起。那么这意味着这种方法做下去的最优解就是dp[l][i1]+(count0+count)*(count0+count)+dp[j0+1][i0]了吗？并不是，因为j0这组OOO虽然带上了r这组OOO，但并不意味着最优解一定是将count0+count这部分消去；有可能j0这组OOO（带着r这组OOO）附着于j1这组OOO一起消去是更优的。具体哪种做法更优，取决于的竟然是count的数目！

		举个例子：

		XX O  XX   O ** O
		^   ^   ^    ^
		j1  i0  j0   r 
		我们已经决定将j0和r这组O放在一起。在这个例子里，最优的决策是：先消灭j1，然后将4个X消灭，再消灭j0+r的这两个O. 最后的得分是1+16+4=21。

		再看另一个例子，唯一的区别就是r所属的O现在有3个。

		XX O  XX   O ** OOO
		^   ^   ^      ^
		j1  i0  j0     r 
		在这个例子里，最优的决策是：先消灭i0，然后将j1+j0+r这五个O消灭，最后再消灭最前的XX，总得分是4+25+4=32.

		所以结论是，当我们决定将r这组OOO跟着j0这组OOO的时候，对于[l,j0]这组区间的最优操作，需要参考r这组OOO的具体数目（也就是count）。因此常规的区间型DP的两个下标并不够，而需要第三个下标：dp[l][r][k]表示，对于区间[l,r]后面还跟着k个与boxes[r]相同的元素。注意这k个元素并不与r直接相连，而是经过其他之前的区间消除后剩下来的。

		于是本题的状态转移就是，考虑r这组OOO与它之间的哪组OOO相连。在这个例子里，r可以与j0相连，于是dp[l][r][0]转化为dp[l][j0][count] + dp[j0+1][i0][0]。也可以跳过j0这组OOO，与j1相连，于是于是dp[l][r][0]转化为dp[l][j1][count] + dp[j1+1][i0][0]。依次类推，取最大值。

		最后的结果是输出dp[0][N-1][0]

		注意，因为我们事前并无法确认第三个下标k对于哪些[l,r]是有意义的，所以dp比较难写。因此这题用top-down的记忆化搜索更方便些。
	*/
	vector<int>boxes;
    int dp[100][100][100];

    int removeBoxes(vector<int>& boxes) 
    {                
        this->boxes = boxes;       
        return DFS(0, boxes.size()-1, 0);        
    }
    
    int DFS(int l, int r, int k)
    {
        if (l>r) return 0;
        
        if (dp[l][r][k]!=0)
            return dp[l][r][k];                
        
        int i = r;
        int count = k;
        while (i>=l && boxes[i]==boxes[r]) 
        {
            i--;
            count++;
        }        
        dp[l][r][k] = DFS(l,i,0) + count*count;
        
        for (int j=i; j>=l; j--)
        {
            if (boxes[j]!=boxes[r]) continue;
            if (boxes[j]==boxes[r] && boxes[j+1]==boxes[r]) continue;
            dp[l][r][k] = max(dp[l][r][k], DFS(l,j,count)+DFS(j+1,i,0));
        }

        return dp[l][r][k];
    }

public:
    
    int removeBoxes(vector<int>& boxes) {
        
        vector<int> len_(boxes.size());
        unordered_map<int, int> m_;

        for (int i = 1; i < boxes.size(); ++i)
            if (boxes[i] == boxes[i - 1])  len_[i] = len_[i - 1] + 1;
        
        std::function<int(int, int, int)> dfs = [&](int l, int r, int k) {
          if (l > r)
              return 0;
          
          k += len_[r];
          r -= len_[r];

          int key = (l * 100 + r) * 100 + k;
          auto it = m_.find(key);
          
          if (it != m_.end())
              return it->second;
          
          int& ans = m_[key];
          ans = dfs(l, r - 1, 0) + (k + 1) * (k + 1);
          
            for (int i = l; i < r; ++i) {
                if (boxes[i] == boxes[r])
                    ans = std::max(ans, dfs(l, i, k + 1) + dfs(i + 1, r - 1, 0));
            }

          return ans;
        };

        return dfs(0, boxes.size() - 1, 0);
     }
    
    
    // O(n^4)
    int doit_dp_topdown(vector<int>& boxes) {
        
        const int n = boxes.size();
        
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));
        
        std::function<int(int, int, int)> dfs = [&](int i, int j, int k) {
        
            if (i > j) return 0;
            
            if (dp[i][j][k] > 0) return dp[i][j][k];

            int m = j;
            while (m - 1 >= i && boxes[m-1] == boxes[j])
                m--;
            
            k += j - m;
            j = m;
            
            int ans = dfs(i, j-1, 0) + (k+1) * (k+1);
            
            for (int m = i; m < j; m++) {
                if (boxes[m] == boxes[j]) {
                    ans = std::max(ans, dfs(i, m, k+1) + dfs(m+1, j-1, 0));
                }
            }
            
            dp[i][j][k] = ans;
            return dp[i][j][k];
        };
        
        return dfs(0, n-1, 0);
    }
    
    
    int doit_dp_1(vector<int>& boxes) {
        
        const int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));
        
        std::function<int(int, int, int)> dfs = [&](int i, int j, int k) {
        
            if (i > j) return 0;
            
            if (dp[i][j][k] > 0) return dp[i][j][k];
            
            // AxxxxxAxxxxA|AAAAAAA|
            // i.....m....j|   k   |
            int ans = dfs(i, j-1, 0) + (k+1) * (k+1);
            
            for (int m = i; m < j; m++) {
                if (boxes[m] == boxes[j]) {
                    ans = std::max(ans, dfs(i, m, k+1) + dfs(m+1, j-1, 0));
                }
            }
            
            dp[i][j][k] = ans;
            return dp[i][j][k];
        };
        
        return dfs(0, n-1, 0);
    }
};


	/*
	We use danymic programming to solve this problem.
	step 1
	First, we merge the blocks with same color to one segment.
	for example, if we have 1 2 3 3 2 2 2 1, then we got 1 2 3 2 1. and at the same time 
	,we use c[i] and len[i] to maintain the color and number of blocks of the i_th segment.
	In the previous example, c[] is: 1 2 3 2 1, len[] is 1 1 2 3 1
	
	step 2
	danymic programming, and this step is based on step1.
	we use d[i, j, k] to show that: in [i, j], we got k blocks with same color of segment j after j.
	and we have 2 ways to do next:

	merge segment j and the k blocks after j because the have the same color:
	d[i, j, k] = d[i, j - 1, 0] + (len[j] + k) * (len[j] + k)
	we accumulate segment j and the k blocks to segment pos(pos is before j) if segment j and segment pos has the same color:

	if (c[pos] == c[j]): d[i, j, k] = d[i, pos,len[j] + k] + d[pos + 1, j - 1, 0] (i <= pos < j)
	
	time complexity: O(n^4)
	
	*/




#define MAXN 105
/*
"""
Let A be the array of boxes.

One natural approach is to consider dp(i, j) = the answer for A[i: j+1]. But this isn�t flexible enough for divide and conquer style strategies.
For example, with [1,2,2,2,1], we don�t have enough information when investigating things like [1,2,2,2] and [1] separately.

Let dp(i, j, k) = the maximum value of removing boxes if we have k extra boxes of color A[i] to the left of A[i: j+1].
(We would have at most k < len(A) extra boxes.)
Let m <= j be the largest value so that A[i], A[i+1], � A[m] are all the same color.
Because a^2 + b^2 < (a+b)^2, any block of contiguous boxes of the same color must be removed at the same time,

so in fact dp(i, j, k) = dp(m, j, k+(m-i))   ------------- (1).

Now, we could remove the k boxes we were carrying plus box A[i] (value: (k+1)**2), then remove the rest (value: dp(i+1, j, 0)).

Or, for any point m in [i+1, j] with A[i] == A[m], we could remove dp(i+1, m-1) first,
then [m, j] would have k+1 extra boxes of color A[m] behind, which has value dp(m, j, k+1).

The �i, k = m, k + m - i� part skips order (m-i)*(j-i) calls to dp, and is necessary to get this kind of solution to pass in Python.

"""

*/
class RemoveBoxesII {

	typedef vector<vector<vector<int>>> Map3D;

	int dfs(vector<int>& boxes, int i, int j, int k, Map3D& p) {

		if (i > j)
			return 0;

		if (p[i][j][k] != 0) {
			return p[i][j][k];
		}

		int m = i;
		while (m + 1 <= j && boxes[m + 1] == boxes[i])
			m++;

		i = m;
		k += m - i;
		int ans = dfs(boxes, i + 1, j, 0, p) + (k + 1) * (k + 1);
		
		for (m = i + 1; m < j + 1; m++) {
			if (boxes[m] == boxes[i]) {
				ans = std::max( ans, dfs(boxes, i+1, m-1, 0, p) + dfs(boxes, m, j, k + 1, p) );
			}
		}

		p[i][j][k] = ans;
		return p[i][j][k];
	}


public:
	
	int doit(vector<int>& boxes) {
		int N = boxes.size();
		Map3D memo_(N, vector<vector<int>>(N, vector<int>(N)));
		return dfs(boxes, 0, N-1, 0, memo_);
	}

};







/*

Getting memory limit errors for the last input, so sad.I read some of the top submissions and found out the reason : I was using STL vector instead of a C array�

Thanks to one of the top submission, which used the same idea as me, I have cleaned my code.

== == == == == == == == == == == = Explanation == == == == == == == == == == == == == =
First Attempt
The initial thought is straightforward, try every possible removal and recursively search the rest.No doubt it will be a TLE answer.Obviously there are a lot of recomputations involved here.Memoization is the key then.But how to design the memory is tricky.I tried to use a string of 0s and 1s to indicate whether the box is removed or not, but still getting TLE.

One step further
I think the problem of the approach above is that there are a lot of unnecessary computations(not recomputations).For example, if there is a formation of ABCDAA, we know the optimal way is B->C->D->AAA.On the other hand, if the formation is BCDAA, meaning that we couldn�t find an A before D, we will simply remove AA, which will be the optimal solution for removing them.Note this is true only if AA is at the end of the array.With naive memoization approach, the program will search a lot of unnecessary paths, such as C->B->D->AA, D->B->C->AA.

Therefore, I designed the memoization matrix to be memo[l][r][k], the largest number we can get using lth to rth(inclusive) boxes with k same colored boxes as rth box appended at the end.Example, memo[l][r][3] represents the solution for this setting: [b_l, ..., b_r, A, A, A] with b_r == A.

The transition function is to find the maximum among all b_i == b_r for i = l, ..., r - 1 :

	memo[l][r][k] = max(memo[l][r][k], memo[l][i][k + 1] + memo[i + 1][r - 1][0])

	Basically, if there is one i such that b_i == b_r, we partition the array into two : [b_l, ..., b_i, b_r, A, ..., A], and[b_{ i + 1 }, ..., b_{ r - 1 }].The solution for first one will be memo[l][i][k + 1], and the second will be memo[i + 1][r - 1][0].Otherwise, we just remove the last k + 1 boxes(including b_r) and search the best solution for lth to r - 1th boxes. (One optimization here : make r as left as possible, this improved the running time from 250ms to 35ms)

	The final solution is stored in memo[0][n - 1][0] for sure.

	I didn�t think about this question for a long time in the contest because the time is up.There will be a lot of room for time and space optimization as well.Thus, if you find any flaws or any improvements, please correct me.

*/	
	
class RemoveBoxes1 {

public:

	int doit(vector<int>& boxes) {

		int N = boxes.size();
		int memo[100][100][100] = { 0 };

		return dfs(boxes, 0, N - 1, 0, memo);
	}

	int dfs(vector<int>& boxes, int i, int j, int k, int p[100][100][100]) {

		if (i > j) 
			return 0;
        

		if (p[i][j][k] != 0)
			return p[i][j][k];

		while (i < j && boxes[j - 1] == boxes[j]) {
			j--, k++;
		}

		int ans = dfs(boxes, i, j - 1, 0, p) + (k + 1) * (k + 1);

		for (int m = j - 1; m >= i; m--) {
			if (boxes[m] == boxes[j])
				ans = std::max(ans, dfs(boxes, m + 1, j - 1, 0, p) + dfs(boxes, i, m, k + 1, p));
		}
		
		p[i][j][k] = ans;
		return ans;
	}
};