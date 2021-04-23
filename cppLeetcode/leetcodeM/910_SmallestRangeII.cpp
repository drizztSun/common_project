/*
908. Smallest Range I

Given an array A of integers, for each integer A[i] we may choose any x with -K <= x <= K, and add x to A[i].

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the minimum value of B.

 

Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]
Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]
Example 3:

Input: A = [1,3,6], K = 3
Output: 0
Explanation: B = [3,3,3] or B = [4,4,4]
 

Note:

1 <= A.length <= 10000
0 <= A[i] <= 10000
0 <= K <= 10000
*/
#include <vector>
#include <algorithm>


using std::vector;


class SmallestRangeI {

public:

    int doit_(vector<int>& A, int K) {
        int maxv = *max_element(begin(A), end(A));
        int minv = *min_element(begin(A), end(A));
        return std::max(0, maxv - minv - 2 * K);
    }

    int doit_(vector<int>& A, int K) {
    {
        int min = A[0], max = A[0];
        for (int x: A) {
            min = std::min(min, x);
            max = std::max(max, x);
        }
        return std::max(0, max - min - 2*K);
    }
};


/*
910. Smallest Range II

Given an array A of integers, for each integer A[i] we need to choose either x = -K or x = K, and add x to A[i] (only once).

After this process, we have some array B.

Return the smallest possible difference between the maximum value of B and the minimum value of B.

 

Example 1:

Input: A = [1], K = 0
Output: 0
Explanation: B = [1]
Example 2:

Input: A = [0,10], K = 2
Output: 6
Explanation: B = [2,8]
Example 3:

Input: A = [1,3,6], K = 3
Output: 3
Explanation: B = [4,6,3]
 

Note:

1 <= A.length <= 10000
0 <= A[i] <= 10000
0 <= K <= 10000
*/


class SmallestRangeII {

    /*
        910.Smallest-Range-II
        首先要有一个直觉：我们将A排序之后，为了减少“贫富差距”，我们一定是将A的左边一部分元素都加上K，右边一部分元素都减去K。为什么左边那部分一定都是加上K，而不是加减交错呢？比如说，a<b<c，如果我们决策是 a+K, b-K, c+K 的话，b和c之间的差距不仅没有减小反而被拉大了。
        所以在最终的方案里，绝对不可能出现“加，减，加”交错操作的情况，唯一的方案就是：左边一部分加K，右边一部分减K。

        那么如果确定这个分界线呢？其实并没有更优秀的办法，挨个尝试就行了。假设这个分界线在A[i]后面，也即是说A[0]～A[i]都是加K，A[i+1]～A[n-1]都是减K，那么这个新数组B的最大值，其实可以从左右两部分分别的最大值得到，即MAX = max(A[i]+K, A.back()-K).
        同理，这个新数组B的最小值，其实可以从左右两部分分别的最小值得到，即MIN = min(A[0]+K, A[i+1]-K)。而我们的答案就是在所有的diff=MAX-MIN中挑选最小的那个。
    */
    int smallestRangeII(vector<int>& A, int K) 
    {
        sort(A.begin(), A.end());
        int diff = A.back()-A[0];
        for (int i=0; i<A.size()-1; i++)
        {
            int MAX = std::max(A[i]+K, A.back()-K);
            int MIN = std::min(A[0]+K, A[i+1]-K);
            diff = std::min(diff, MAX-MIN);
        }
        return diff;
    }


public:

    /*
        Approach 1: Linear Scan
        Intuition

        As in Smallest Range I, smaller A[i] will choose to increase their value ("go up"), and bigger A[i] will decrease their value ("go down").

        Algorithm

        We can formalize the above concept: if A[i] < A[j], we don't need to consider when A[i] goes down while A[j] goes up. 
        This is because the interval (A[i] + K, A[j] - K) is a subset of (A[i] - K, A[j] + K) (here, (a, b) for a > b denotes (b, a) instead.)

        That means that it is never worse to choose (up, down) instead of (down, up). We can prove this claim that one interval is a subset of another, by showing both A[i] + K and A[j] - K are between A[i] - K and A[j] + K.

        For sorted A, say A[i] is the largest i that goes up. Then A[0] + K, A[i] + K, A[i+1] - K, A[A.length - 1] - K are the only relevant values for calculating the answer: every other value is between one of these extremal values.

        Complexity Analysis

        Time Complexity: O(NlogN), where NN is the length of the A.

        Space complexity : O(N) or O(logN)

        The space complexity of the sorting algorithm depends on the implementation of each program language.

        For instance, the list.sort() function in Python is implemented with the Timsort algorithm whose space complexity is \mathcal{O}(N)O(N).

        In Java, the Arrays.sort() is implemented as a variant of quicksort algorithm whose space complexity is \mathcal{O}(\log{N})O(logN).
    */
    int doit_greedy_sort(vector<int>& A, int k) {
        
        int N = A.size();
        std::sort(begin(A), end(A));
        int ans = A[N-1] - A[0];
        
        for (int i = 0; i < A.size()-1; i++) {
            ans = std::min(ans, std::max(A[N-1]-k, A[i]+k) - std::min(A[0]+k, A[i+1]-k));
        }
        
        return ans;
    }
};