/*
1521. Find a Value of a Mysterious Function Closest to Target



Winston was given the above mysterious function func. He has an integer array arr and an integer target and he wants to find the values l and r that make the value |func(arr, l, r) - target| minimum possible.

Return the minimum possible value of |func(arr, l, r) - target|.

Notice that func should be called with the values l and r where 0 <= l, r < arr.length.

 

Example 1:

Input: arr = [9,12,3,7,15], target = 5
Output: 2
Explanation: Calling func with all the pairs of [l,r] = [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]], 
Winston got the following results [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7 and 3, thus the minimum difference is 2.
Example 2:

Input: arr = [1000000,1000000,1000000], target = 1
Output: 999999
Explanation: Winston called the func with all possible values of [l,r] and he always got 1000000, thus the min difference is 999999.
Example 3:

Input: arr = [1,2,4,8,16], target = 0
Output: 0
 

Constraints:

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
0 <= target <= 10^7

*/
#include <vector>
#include <set>
#include <unordered_set>

using std::unordered_set;
using std::set;
using std::vector;


class  MysteriousFunc{

    /*
        1521.Find-a-Value-of-a-Mysterious-Function-Closest-to-Target
        考虑s集合包含了所有以元素i结尾的subarray的bitwise AND的结果。那么这个集合有多大呢？其实并没有i个，而是最多只有32个。因为这些subarray的bitwise AND的本质，都是针对A[i]的某些bit进行从1到0的翻转。
        并且这些subarray bitwise AND从后往前来看都是不可逆的。具体地说，A[i], A[i]&A[i-1], A[i]&A[i-1]&A[i-2], ... 它们的bit 1的个数只会越来越少。因为A[i]最多只有32个1，所以所有这些subarray最多只会有32个不同的bitwise AND的结果。

        既然s只有32个元素，那么只需要遍历一遍就可以找到最接近target的值。然后在考虑A[i+1]，并更新s集合：只需要将每个s的元素与A[i+1]进行AND，再添加A[i+1]即可。同理可知，此时的集合s依然最多只有32个元素。
    */
    int closestToTarget(vector<int>& arr, int target) {
        unordered_set<int>s;
        int ret = INT_MAX;
        for (int i = 0; i < arr.size(); i++)
        {
            unordered_set<int> s2;
            for (auto x: s)
                s2.insert(x&arr[i]);

            s2.insert(arr[i]);
            for (auto x: s2)
                ret = std::min(ret, abs(x-target));
            s = s2;
        }
        return ret;
    }

public:


    int doit_(vector<int>& arr, int target) {
        int res = INT_MAX; 
        set<int> pre = {arr[0]}, cur;
        
        for(auto x: arr){
            cur.insert(x);
            
            for(auto y: pre) 
                cur.insert(x&y);
            
            for(auto& z: cur) 
                res = min(res, abs(z-target));
            
            pre = move(cur);
        }          
        return res;
    }

    int dem[26];
    void add(int &sum, int x)
    {
        for (int i = 0; i <= 24; i++)
        {
            if (((x >> i) & 1) == 0)
            {
                dem[i]++;
                if (dem[i] == 1) sum = sum ^ (1 << i);
            }
        }
    }
    
    void remove(int &sum, int x)
    {
        for (int i = 0; i <= 24; i++)
        {
            if (((x >> i) & 1) == 0)
            {
                dem[i]--;
                if (dem[i] == 0) sum = sum | (1 << i);
            }
        }
    }
    
    int doit_slidingwindow_best(vector<int>& arr, int target) {
        int sum = (1 << 25) - 1;
        int ans = INT_MAX;
        memset(dem, 0, sizeof(dem));
        
        for (int l = 0, r = 0; r < arr.size(); r++)
        {
            add(sum, arr[r]);
            
            ans = std::min(ans, abs(sum - target));

            while (sum < target)
            {
                remove(sum, arr[l]);
                ans = std::min(ans, abs(sum - target));
                l++;
            }
        }
        return ans;
    }

    /*
        Observations:
        1. If we start taking AND of elements of any sequence, the AND value will either remain same or decrease
        let arr[1], arr[2], arr[3] be the sequence

        -> a1 = arr[1], 
        -> a2 = arr[1]&arr[2], 
        -> a3 = arr[1]&arr[2]&arr[3]
        We can say : a1 >= a2 >= a3
        because while taking AND we cannot set a bit so either the AND value will remain same or decrease
        
        2. AND value can decrease by atmost number of set bits in A times i.e at max max(log (A)) times.

        3. The number of unique AND of a subarrays starting at any position will change by atmost LOG( A[i] ) times ( A[i] is first element of subarray)

        4. The AND's of subarrays starting at ith index can be calculated from AND's of subarrays starting at (i+1)th index

        st[i] : contains AND values of subarrays starting from ith index

        for eg : arr[] = [2,6,7,2,4]; 	(0 based indexing)

        Subarrays starting at 4th index
            : [4]			            --> st[5] = { 4 }
        Subarrays starting at 3rd index
            : [2], [2,4] 			    --> st[4] = { 2, 0 }
        Subarrays starting at 2nd index
            : [7], [7,2], [7,2,4], 		--> st[3] = { 7, 2, 0 }
        AND_VAL[i, len] : AND of elements of subarray starting from 'ith' index of length 'len'
        Observe that

        AND_VAL[i,1] = arr[i];
        AND_VAL[i,2] = arr[i] & AND_VAL[i+1,1];
        AND_VAL[i,3] = arr[i] & AND_VAL[i+1,2];
        AND_VAL[i,4] = arr[i] & AND_VAL[i+1,3];
        .
        .
        AND_VAL[i,j] = arr[i] & AND_VAL[i+1,j-1];
        also AND_VAL[i+1, j] are present in st[i+1]. ( check definition of st[i] )
        Therefore st[i] can be calculated from st[i+1] as AND values of st[i] are nothing but AND of arr[i] with values in st[i+1]

        From Observation (3) we can conclude :
        st[i].size() <= log( max( A ) ) <= 20 as ( A <= 10^6 )

        Time Complexity : O( n * log( max( arr[i] ) ) )
        Code :


        Similar concept can be applied to bitwise OR / GCD because they too are monotonic when applied on a sequence and
        the values of cumulative bitwise OR / GCD changes atmost log( max( element) ) times
    */
    int doit(vector<int>& arr, int target) {
        int ans = INT_MAX, n = arr.size();
    
        set<int> st[n];
        // set[i] -> contains **unique** AND values of subarrays starting from ith index 

        st[n-1] = { arr[n-1] };
        for(int i = n-2; i >= 0; i--)
        {   
            // calcuting st[i] with help of st[i+1]
            st[i].insert(arr[i]);
            for(auto &val: st[i+1])
            {
                int new_val = (arr[i] & val);
                st[i].insert( new_val );
            }
        }
        
        // Iterate over all possible AND values and find the ans
        for(int i = 0; i < n; i++)
        {
            for(auto &val: st[i])
                ans = std::min(ans, abs(val - target));
        } 
        
        return ans;
    }
};