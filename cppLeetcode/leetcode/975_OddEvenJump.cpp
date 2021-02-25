/*
 # 975. Odd Even Jump

 # You are given an integer array A.  From some starting index, you can make a series of jumps.
 # The (1st, 3rd, 5th, ...) jumps in the series are called odd numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even numbered jumps.

 # You may from index i jump forward to index j (with i < j) in the following way:

 # During odd numbered jumps (ie. jumps 1, 3, 5, ...), you jump to the index j such that A[i] <= A[j] and A[j] is the smallest possible value.
 # If there are multiple such indexes j, you can only jump to the smallest such index j.

 # During even numbered jumps (ie. jumps 2, 4, 6, ...), you jump to the index j such that A[i] >= A[j] and A[j] is the largest possible value.
 # If there are multiple such indexes j, you can only jump to the smallest such index j.

 # (It may be the case that for some index i, there are no legal jumps.)
 # A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1) by jumping some number of times (possibly 0 or more than once.)

 # Return the number of good starting indexes.


 # Example 1:

 # Input: [10,13,12,14,15]
 # Output: 2
 # Explanation:
 # From starting index i = 0, we can jump to i = 2 (since A[2] is the smallest among A[1], A[2], A[3], A[4] that is greater or equal to A[0]), then we can't jump any more.
 # From starting index i = 1 and i = 2, we can jump to i = 3, then we can't jump any more.
 # From starting index i = 3, we can jump to i = 4, so we've reached the end.
 # From starting index i = 4, we've reached the end already.
 # In total, there are 2 different starting indexes (i = 3, i = 4) where we can reach the end with some number of jumps.

 # Example 2:

 # Input: [2,3,1,1,4]
 # Output: 3
 # Explanation:
 # From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:

 # During our 1st jump (odd numbered), we first jump to i = 1 because A[1] is the smallest value in (A[1], A[2], A[3], A[4]) that is greater than or equal to A[0].

 # During our 2nd jump (even numbered), we jump from i = 1 to i = 2 because A[2] is the largest value in (A[2], A[3], A[4]) that is less than or equal to A[1].
 # A[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3.

 # During our 3rd jump (odd numbered), we jump from i = 2 to i = 3 because A[3] is the smallest value in (A[3], A[4]) that is greater than or equal to A[2].

 # We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.

 # In a similar manner, we can deduce that:
 # From starting index i = 1, we jump to i = 4, so we reach the end.
 # From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
 # From starting index i = 3, we jump to i = 4, so we reach the end.
 # From starting index i = 4, we are already at the end.
 # In total, there are 3 different starting indexes (i = 1, i = 3, i = 4) where we can reach the end with some number of jumps.

 # Example 3:

 # Input: [5,1,3,4,2]
 # Output: 3
 # Explanation:
 # We can reach the end from starting indexes 1, 2, and 4.

 */
#include <vector>
#include <algorithm>
#include <map>

using std::map;
using std::vector;

#include <stack>
using std::stack;

class OddEvenJumps {

    /*
        975.Odd-Even-Jump

        令dp_odd[i]表示从位置i开始作为奇数次的起跳，能否到达终点；dp_even[i]表示从位置i开始作为偶数次的起跳，能否到达终点。

        从后往前考虑，对于元素A[i]，如果能寻找到它的下一步跳到的位置j，那么显然dp_odd[i] = dp_even[j]，dp_even[i] = dp_odd[j].

        怎么高效地从i找到j呢？对于奇数次跳跃，显然考虑将i之后的所有元素放在一起排个序，有就二分法A[j] = *lower_bound(A[i])，然后再从这个A[j]映射回j。
        
        同理，对于偶数次跳跃，也是考虑将i之后的所有元素放在一起排个序，有A[j] = *prev(upper_bound(A[i]),1)，然后再从这个A[j]映射回j。

        显然，要保证所有i之后的元素放在一起是自动有序的，数据结构必然选择set或者map。这样每加入一个新元素，都是以log(n)的代价继续保持这个set或map是有序的。用lower_bound或upper_bound非常方便。
            
    */
    int doit_dp_heap(vector<int>& A) 
    {
        int n = A.size();
        vector<bool> odd(n,0);
        vector<bool> even(n,0);
        odd[n-1] = true;
        even[n-1] = true;
                
        map<int,int> Map;        
        Map[A.back()] = n-1;
        
        for (int i = n-2; i >= 0; i--)
        {            
            auto iter1 = Map.lower_bound(A[i]);   
            if (iter1 != Map.end())
            {                
                if (even[iter1->second]) odd[i] = true;
            }
            
            auto iter2 = Map.upper_bound(A[i]);
            if (iter2 != Map.begin())
            {
                iter2 = prev(iter2,1);                
                if (odd[iter2->second]) even[i] = true;
            }
            
            Map[A[i]] = i;
        }
        
        int count = 0;
        for (int i = 0; i < n; i++)
            if (odd[i]) count++;
        return count;
    }

    int doit_(vector<int>& A) {

        int n  = A.size(), res = 1;
        vector<int> higher(n), lower(n);
        higher[n - 1] = lower[n - 1] = 1;
        
        map<int, int> map;
        map[A[n - 1]] = n - 1;
        
        for (int i = n - 2; i >= 0; --i) {
            auto hi = map.lower_bound(A[i]), lo = map.upper_bound(A[i]);
        
            if (hi != map.end()) higher[i] = lower[hi->second];
            if (lo != map.begin()) lower[i] = higher[(--lo)->second];
        
            if (higher[i]) res++;
            map[A[i]] = i;
        }
        
        return res;
    }

public:
    int doit(vector<int>&& A) {
        int N = A.size();
        vector<int> B(N, 0);
        for (int i = 0; i < N; i++)
            B[i] = i;

        auto make = [](vector<int>& B) -> vector<int> {
            vector<int> C(B.size(), -1);
            stack<int> st;
            
            for (int i = 0; i < B.size(); i++) {
                
                while (!st.empty() && B[i] > st.top()) {
                    C[st.top()] = B[i];
                    st.pop();
                }
                
                st.push(B[i]);
            }
            return C;
        };
        
        std::sort(B.begin(), B.end(), [&A](auto a, auto b) {
            return A[a] < A[b];
        });
        vector<int> oddnext = make(B);
        
        std::sort(B.begin(), B.end(), [&A](auto a, auto b) {
            return A[b] < A[a];
        });
        vector<int> evenext = make(B);
        
        vector<bool> odd(N, false);
        vector<bool> even(N, false);
        odd[N-1] = true, even[N-1] = true;
        
        for (int i = N - 2; i > -1; i--) {
            if (oddnext[i] != -1)
                odd[i] = even[oddnext[i]];
            if (evenext[i] != -1)
                even[i] = odd[evenext[i]];
        }
        
        int ans = 0;
        for (auto c: odd)
            ans += c ? 1 : 0;
        return ans;
    }
};