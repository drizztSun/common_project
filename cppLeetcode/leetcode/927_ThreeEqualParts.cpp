/*
You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.

If it is possible, return any [i, j] with i + 1 < j, such that:

arr[0], arr[1], ..., arr[i] is the first part,
arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
All three parts have equal binary values.
If it is not possible, return [-1, -1].

Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.

 
Example 1:

Input: arr = [1,0,1,0,1]
Output: [0,3]
Example 2:

Input: arr = [1,1,0,1,1]
Output: [-1,-1]
Example 3:

Input: arr = [1,1,0,0,1]
Output: [0,2]
 

Constraints:

3 <= arr.length <= 3 * 104
arr[i] is 0 or 1
 
 """
 Approach 1: Equal Ones

 Intuition

 Each part has to have the same number of ones in their representation. The algorithm given below is the natural continuation of this idea.

 Algorithm

 Say S is the number of ones in A. Since every part has the same number of ones, they all should have T = S / 3 ones.

 If S isn't divisible by 3, the task is impossible.

 We can find the position of the 1st, T-th, T+1-th, 2T-th, 2T+1-th, and 3T-th one. The positions of these ones form 3 intervals: [i1, j1], [i2, j2], [i3, j3].
 (If there are only 3 ones, then the intervals are each length 1.)

 Between them, there may be some number of zeros. The zeros after j3 must be included in each part: say there are z of them (z = S.length - j3).

 So the first part, [i1, j1], is now [i1, j1+z]. Similarly, the second part, [i2, j2], is now [i2, j2+z].

 If all this is actually possible, then the final answer is [j1+z, j2+z+1].

 Complexity Analysis

 Time Complexity: O(N), where NN is the length of S.

 Space Complexity: O(N).

 """
 
 */

#include <vector>
#include <numeric>

using std::vector;

class ThreeEqualParts {

    /*
                927.Three-Equal-Parts
        本题的突破口就是全局1的个数。首先，整个数组里面1的个数必须要能被3整除。其次，确定了每个part里面1的个数后（记为count），从后往前数count个1，就已经确定了这个数长什么样了（记为X）。

        然后我们从数组最前端开始忽略若干个先导零，从第一个出现1的地方开始判断这个subarray是否等于X。如果OK，那么我们再忽略若干个先导零，在从下一个出现1的地方开始判断这个subarray是否等于X。如果再OK，那么three equal parts就已经划分好了。
    */
    vector<int> threeEqualParts(vector<int>& A) 
    {
        vector<int> rets;
        
        int count = 0;
        for (auto x: A)
            if (x==1) count++;
        if (count%3!=0) return {-1,-1};
        if (count==0) return {0, A.size()-1};
        count/=3;
        
        int j = A.size();
        while (count)
        {
            j--;
            if (A[j]==1) count--;
        }
        
        int i = 0;
        while (A[i]==0) i++;
        int k = j;
        while (k<A.size() && A[i]==A[k])
        {
            i++;
            k++;
        }
        if (k!=A.size()) return {-1,-1};
        rets.push_back(i-1);
        
        while (A[i]==0) i++;
        k = j;
        while (k<A.size() && A[i]==A[k])
        {
            i++;
            k++;
        }
        if (k!=A.size()) return {-1,-1};
        rets.push_back(i);
        
        return rets;
    }
    
public:

    /*
        Approach 1: Equal Ones
        Intuition

        Each part has to have the same number of ones in their representation. The algorithm given below is the natural continuation of this idea.

        Algorithm

        Say S is the number of ones in A. Since every part has the same number of ones, they all should have T = S / 3 ones.

        If S isn't divisible by 3, the task is impossible.

        We can find the position of the 1st, T-th, T+1-th, 2T-th, 2T+1-th, and 3T-th one. 
        
        The positions of these ones form 3 intervals: [i1, j1], [i2, j2], [i3, j3]. (If there are only 3 ones, then the intervals are each length 1.)

        Between them, there may be some number of zeros. The zeros after j3 must be included in each part: say there are z of them (z = S.length - j3).

        So the first part, [i1, j1], is now [i1, j1+z]. Similarly, the second part, [i2, j2], is now [i2, j2+z].

        If all this is actually possible, then the final answer is [j1+z, j2+z+1].


        Complexity Analysis

        Time Complexity: O(N)O(N), where NN is the length of S.

        Space Complexity: O(N)O(N).
    
    */
    
    vector<int> doit(vector<int>&& A) {
    
        int total = std::accumulate(A.begin(), A.end(), 0);
        
        if (total % 3)
            return {-1, -1};
        
        if (total == 0)
            return vector<int>{0, static_cast<int>(A.size()) - 1};
        
        int t = total / 3;
        int c = 0;
        int i1, i2, i3, j1, j2, j3;
        
        for (int i = 0; i < A.size(); i++) {
            if (A[i] == 1) {
                c++;
                
                if (c == 1)
                    i1 = i;
                if (c == t)
                    j1 = i;
                if (c == t+1)
                    i2 = i;
                if (c == 2*t)
                    j2 = i;
                if (c == 2*t+1)
                    i3 = i;
                if (c == 3*t)
                    j3 = i;
            }
        }
        
        if (j1 - i1 != j2 - i2 || j2 - i2 != j3 - i3)
            return {-1, -1};
            
        for (int i = 0; i < (j1 - i1); i++) {
            if (A[i1+i] != A[i2+i] || A[i2+i] != A[i3+i])
                return {-1, -1};
        }
        
        int x = i2 - j1 - 1;
        int y = i3 - j2 - 1;
        int z = static_cast<int>(A.size()) - j3 - 1;

        if (x < z || y < z) return {-1, -1};
        
        return {j1 + z, j2 + z + 1};
    }
};