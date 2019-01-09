





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
using namespace std;

//
//const int maxn = 105;
//int memo_[maxn][maxn][maxn];
//int c_[maxn];
//int len_[maxn];
//
//class RemoveBoxes {
//
//
//	/*
//	We use danymic programming to solve this problem.
//	step 1
//	First, we merge the blocks with same color to one segment.
//	for example, if we have 1 2 3 3 2 2 2 1, then we got 1 2 3 2 1. and at the same time 
//	,we use c[i] and len[i] to maintain the color and number of blocks of the i_th segment.
//	In the previous example, c[] is: 1 2 3 2 1, len[] is 1 1 2 3 1
//	
//	step 2
//	danymic programming, and this step is based on step1.
//	we use d[i, j, k] to show that: in [i, j], we got k blocks with same color of segment j after j.
//	and we have 2 ways to do next:
//
//	merge segment j and the k blocks after j because the have the same color:
//	d[i, j, k] = d[i, j - 1, 0] + (len[j] + k) * (len[j] + k)
//	we accumulate segment j and the k blocks to segment pos(pos is before j) if segment j and segment pos has the same color:
//
//	if (c[pos] == c[j]): d[i, j, k] = d[i, pos,len[j] + k] + d[pos + 1, j - 1, 0] (i <= pos < j)
//	
//	time complexity: O(n^4)
//	
//	*/
//	int dfs(int i, int j, int k) {
//
//		if (i > j)
//			return 0;
//
//		if (memo_[i][j][k] > 0)
//			return memo_[i][j][k];
//
//		memo_[i][j][k] = dfs(i, j - 1, 0) + (len_[j] + k) * (len_[j] + k);
//
//		for (int pos = i; pos < j; pos++) {
//			if (c_[pos] == c_[j]) {
//				memo_[i][j][k] = std::max(memo_[i][j][k], dfs(i, pos, len_[j] + k) + dfs(pos + 1, j - 1, 0));
//			}
//		}
//
//		return memo_[i][j][k];
//	}
//
//public:
//
//	RemoveBoxes() {
//
//	}
//
//	int doit(vector<int>& boxes) {
//
//		int n = 0;
//		memset(c_, 0, sizeof(c_));
//		memset(len_, 0, sizeof(len_));
//		memset(memo_, -1, sizeof(memo_));
//
//
//		for (int i = 0; i < boxes.size(); i++)
//			if (i == 0 || boxes[i] != boxes[i - 1]) {
//				c_[++n] = boxes[i];
//				len_[n] = 1;
//			}
//			else {
//				len_[n]++;
//			}
//
//		return dfs(1, n, 0);
//	}
//
//};




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

One natural approach is to consider dp(i, j) = the answer for A[i: j+1]. But this isn’t flexible enough for divide and conquer style strategies.
For example, with [1,2,2,2,1], we don’t have enough information when investigating things like [1,2,2,2] and [1] separately.

Let dp(i, j, k) = the maximum value of removing boxes if we have k extra boxes of color A[i] to the left of A[i: j+1].
(We would have at most k < len(A) extra boxes.)
Let m <= j be the largest value so that A[i], A[i+1], … A[m] are all the same color.
Because a^2 + b^2 < (a+b)^2, any block of contiguous boxes of the same color must be removed at the same time,

so in fact dp(i, j, k) = dp(m, j, k+(m-i))   ------------- (1).

Now, we could remove the k boxes we were carrying plus box A[i] (value: (k+1)**2), then remove the rest (value: dp(i+1, j, 0)).

Or, for any point m in [i+1, j] with A[i] == A[m], we could remove dp(i+1, m-1) first,
then [m, j] would have k+1 extra boxes of color A[m] behind, which has value dp(m, j, k+1).

The “i, k = m, k + m - i” part skips order (m-i)*(j-i) calls to dp, and is necessary to get this kind of solution to pass in Python.

"""

*/
class RemoveBoxes {

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

Getting memory limit errors for the last input, so sad.I read some of the top submissions and found out the reason : I was using STL vector instead of a C array…

Thanks to one of the top submission, which used the same idea as me, I have cleaned my code.

== == == == == == == == == == == = Explanation == == == == == == == == == == == == == =
First Attempt
The initial thought is straightforward, try every possible removal and recursively search the rest.No doubt it will be a TLE answer.Obviously there are a lot of recomputations involved here.Memoization is the key then.But how to design the memory is tricky.I tried to use a string of 0s and 1s to indicate whether the box is removed or not, but still getting TLE.

One step further
I think the problem of the approach above is that there are a lot of unnecessary computations(not recomputations).For example, if there is a formation of ABCDAA, we know the optimal way is B->C->D->AAA.On the other hand, if the formation is BCDAA, meaning that we couldn’t find an A before D, we will simply remove AA, which will be the optimal solution for removing them.Note this is true only if AA is at the end of the array.With naive memoization approach, the program will search a lot of unnecessary paths, such as C->B->D->AA, D->B->C->AA.

Therefore, I designed the memoization matrix to be memo[l][r][k], the largest number we can get using lth to rth(inclusive) boxes with k same colored boxes as rth box appended at the end.Example, memo[l][r][3] represents the solution for this setting: [b_l, ..., b_r, A, A, A] with b_r == A.

The transition function is to find the maximum among all b_i == b_r for i = l, ..., r - 1 :

	memo[l][r][k] = max(memo[l][r][k], memo[l][i][k + 1] + memo[i + 1][r - 1][0])

	Basically, if there is one i such that b_i == b_r, we partition the array into two : [b_l, ..., b_i, b_r, A, ..., A], and[b_{ i + 1 }, ..., b_{ r - 1 }].The solution for first one will be memo[l][i][k + 1], and the second will be memo[i + 1][r - 1][0].Otherwise, we just remove the last k + 1 boxes(including b_r) and search the best solution for lth to r - 1th boxes. (One optimization here : make r as left as possible, this improved the running time from 250ms to 35ms)

	The final solution is stored in memo[0][n - 1][0] for sure.

	I didn’t think about this question for a long time in the contest because the time is up.There will be a lot of room for time and space optimization as well.Thus, if you find any flaws or any improvements, please correct me.

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


void Test_546_RemoveBoxes() {


	RemoveBoxes A;
	vector<int> input{ 1, 3, 2, 2, 2, 3, 4, 3, 1 }; // 23
	auto res = A.doit( input );

	RemoveBoxes B;
	input = { 3, 8, 8, 5, 3, 9, 2, 4, 4, 6, 5, 8, 4, 8, 6, 9, 6, 2, 8, 6, 4, 1, 9, 5, 3, 10, 5, 3, 3, 9, 8, 8, 6, 5, 3, 7, 4, 9, 6, 3, 9, 4, 3, 5, 10, 7, 6, 10, 7}; // 133
	res = B.doit(input);

	return;
}