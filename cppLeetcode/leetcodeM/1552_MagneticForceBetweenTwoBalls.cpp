/*
1552. Magnetic Force Between Two Balls


In universe Earth C-137, Rick discovered a special form of magnetic force between two balls if they are put in his new invented basket. 
Rick has n empty baskets, the ith basket is at position[i], Morty has m balls and needs to distribute the balls into the baskets such that the minimum magnetic force between any two balls is maximum.

Rick stated that magnetic force between two different balls at positions x and y is |x - y|.

Given the integer array position and the integer m. Return the required force.

 

Example 1:


Input: position = [1,2,3,4,7], m = 3
Output: 3
Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic force between ball pairs [3, 3, 6]. 
The minimum magnetic force is 3. We cannot achieve a larger minimum magnetic force than 3.
Example 2:

Input: position = [5,4,3,2,1,1000000000], m = 2
Output: 999999999
Explanation: We can use baskets 1 and 1000000000.
 

Constraints:

n == position.length
2 <= n <= 10^5
1 <= position[i] <= 10^9
All integers in position are distinct.
2 <= m <= position.length

*/
#include <vector>
#include <algorithm>

using std::vector;


class MagneticForceTwoBalls {

    /*
        1552.Magnetic-Force-Between-Two-Balls
        常规的二分搜值。猜测一个minimum magnetic force是F，然后查看能否在数组中挑选m个位置，使得这m个位置之间的距离都大于等于F。如果能够实现，那么尝试猜测更大的F；反之就猜测更小的F。
    */
    int maxDistance(vector<int>& position, int m) 
    {
        sort(position.begin(), position.end());
        int left = 1, right = position.back()-position[0];


        auto isOK = [&](int len, int m)
        {
            int j=0;
            int count = 1;
            
            for (int i=0; i<position.size(); )
            {
                j = i;
                while (j<position.size() && position[j]-position[i]<len)
                    j++;
                            
                if (j==position.size()) 
                    break;
                else
                {
                    count++;                
                    i=j;
                }
                if (count==m) return true;
                
            }
            return false;
        };

        while (left < right)
        {
            int mid = right-(right-left)/2;
            if (isOK(mid, m))
                left = mid;
            else
                right = mid-1;
        }
        return left;        
    }
    

public:
    
    int doit_binary_search(vector<int>& a, int m) {

        std::sort(a.begin(),a.end());
        long long int l = 1,r = a[a.size()-1] + 1, ans = 0;
        
        while(l <= r) {

            long long int mid = (l+r)/2, c = 1, prev = a[0];
            
            for(int i = 1; i < a.size(); i++) {
                
                if (a[i] - prev >= mid) {
                    prev = a[i];
                    c++;
                    if(c == m) break;
                }
            }

            if(c == m) {
                ans = mid;
                l = mid + 1;
            } else
                r = mid - 1;
        }
        return ans;
    }
};