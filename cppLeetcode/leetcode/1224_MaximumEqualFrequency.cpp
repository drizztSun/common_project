/*
1224. Maximum Equal Frequency

Given an array nums of positive integers, return the longest possible length of an array prefix of nums, 
such that it is possible to remove exactly one element from this prefix so that every number that has appeared in it will have the same number of occurrences.

If after removing one element there are no remaining elements, it's still considered that every appeared number has the same number of ocurrences (0).

 

Example 1:

Input: nums = [2,2,1,1,5,3,3,5]
Output: 7
Explanation: For the subarray [2,2,1,1,5,3,3] of length 7, if we remove nums[4]=5, we will get [2,2,1,1,3,3], so that each number will appear exactly twice.
Example 2:

Input: nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
Output: 13
Example 3:

Input: nums = [1,1,1,2,2,2]
Output: 5
Example 4:

Input: nums = [10,2,8,9,3,8,1,5,2,3,7,6]
Output: 8
 

Constraints:

2 <= nums.length <= 10^5
1 <= nums[i] <= 10^5



*/
#include <vector>
#include <map>

using std::map;
using std::vector;

class MaximumEqualFrequency {

public:


    /*
        Intuition
        We need to count the frequency of numbers in A
        Also we need to know, for each frequency, we have how many different numbers.
        count[a] means the frequency of number a
        freq[c] means how many numbers that occur c times.


        Explanation
        Iterate the input array A and we count the n first numbers.

        There actually only 2 situation to discuss:

        1. we delete the current number a.
            In this case, the n - 1 first numbers have the same frequency,
            and we can easier detect this case when we iterate the previous number A[n - 1]

        2. we don't delete the current number a
            the current a occurs c times.
            So except all numbers that also occurs c times,
            it should leave one single number, or c + 1 same numeber.

        That's it, done.

        Complexity
        Time O(N)
        Space O(K), where K = set(A).length

    */
    int doit_search(vector<int>& A) {
        
        vector<int> count(100001), freq(100001);
        int res = 0, N = A.size(), a,c,d;
        for (int n = 1; n <= N; ++n) {
            a = A[n - 1];
            --freq[count[a]];
            c = ++count[a];
            ++freq[count[a]];

            if (freq[c] * c == n && n < N)
                res = n + 1;
            d = n - freq[c] * c;
            if ((d == c + 1 || d == 1) && freq[d] == 1)
                res = n;
        }
        return res;
    }

    int doit_search(vector<int>& nums) {
        int unq = 0,mx = 0,oneC = 0,mxC = 0;
        map<int,int>mp;
        int ans = 2;
        for(int i = 0; i < nums.size(); i++){
            if(mp.find(nums[i]) == mp.end())unq++;
            else if(mp.find(nums[i]) != mp.end() && mp[nums[i]] == 1)oneC--;
            
            mp[nums[i]]++; 
            
            if(mp[nums[i]] == 1){oneC++;}
            if(mx == mp[nums[i]])mxC++;
            else if(mx < mp[nums[i]]){mx = mp[nums[i]]; mxC = 1;}
            
            // cout<<i+1<<" unq "<<unq<<" mx "<<mx<<" mxC "<<mxC<<" oneC "<<oneC<<endl;
            if(oneC >= 1 && (i+1 == mx*(unq-1) + 1)){   ans = i+1;  }
            if(mxC == 1 && i+1 == (mx-1)*unq + 1){ans = i+1;    }
        }
        return ans;
    }
};