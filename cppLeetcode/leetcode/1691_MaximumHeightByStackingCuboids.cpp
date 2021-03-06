/*
 1691. Maximum Height by Stacking Cuboids
 
 Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed). Choose a subset of cuboids and place them on each other.

 You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj.
 You can rearrange any cuboid's dimensions by rotating it to put it on another cuboid.

 Return the maximum height of the stacked cuboids.

  

 Example 1:



 Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
 Output: 190
 Explanation:
 Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
 Cuboid 0 is placed next with the 45x20 side facing down with height 50.
 Cuboid 2 is placed next with the 23x12 side facing down with height 45.
 The total height is 95 + 50 + 45 = 190.
 Example 2:

 Input: cuboids = [[38,25,45],[76,35,3]]
 Output: 76
 Explanation:
 You can't place any of the cuboids on the other.
 We choose cuboid 1 and rotate it so that the 35x3 side is facing down and its height is 76.
 Example 3:

 Input: cuboids = [[7,11,17],[7,17,11],[11,7,17],[11,17,7],[17,7,11],[17,11,7]]
 Output: 102
 Explanation:
 After rearranging the cuboids, you can see that all cuboids have the same dimension.
 You can place the 11x7 side down on all cuboids so their heights are 17.
 The maximum height of stacked cuboids is 6 * 17 = 102.
  

 Constraints:

 n == cuboids.length
 1 <= n <= 100
 1 <= widthi, lengthi, heighti <= 100
 
 */

#include <stdio.h>
#include <vector>
#include <array>

using std::vector;
using std::array;


class MaximumHeightByStackingCuboids {
    
public:
    
    /*
     
     解法1
     因为题目允许任意旋转长方体，我们尝试将每个长方体的六个旋转变种都考虑进来。这样总共有6n个cuboids。

     因为从下往上堆叠的次序必须是按照长度递减的，所以我们自然会将所有的6n个cuboids按照长度降排列。那么对于长度相同的长方体呢？我们可以再按宽度降序排列；对于宽度也相同的长方体，按照高度降序排列。这样，符合要求的堆叠方案必然是这个序列的一个subsequece。
     
     注意，并不是说这个序列的任何一个subsequence都是符合要求的堆叠方案。

     接下来，从这个降序序列里面找总高度最大的序列，类似于求LIS的做法。令dp[i]表示以i为最上层长方体的堆叠总高度。

     for (int i=0; i<6*n; i++)
     {
       dp[i] = height[i];
       for (int j=0; j<n; j++)
         if (length[j]<=length[j] && width[j]<=width[i] && height[j]<=height[i])
           dp[i] = max(dp[i], dp[j]+height[i]);
     }
     但此时有一个问题，如何保证我们选取的这个LIS里不含有同一个长方体的若干个变体呢？事实上，通常情况下这个并不会发生，因为同一个长方体c的任何两个变体c1和c2，不可能实现c1在c2上的顺利堆叠。举个例子，令长方体的三条边为L>M>S，那么我们按照高的选择分类为三种：

     c1: base (L,M), height (S)
     c2: base (L,S), height (M)
     c3: base (M,S), height (L)
     如果按照高度的约束来看，这三种变体的堆叠只能是c1在c2上、c2在c3上。但是从底面积的约束来看，必须是c3在c2上、c2在c1上。这个是矛盾的。所以在两层循环里，我们通常是无法找到一对符合条件i和j恰好是同一个长方体的变体。

     但是以上有个问题，就是如果M==S的话，那么c1和c2就长得完全一样，那么仍有可能动态规划的时候会把c1放在c2之上。解决方案是给每个长方体带上原始的编号信息，并作为第四个下标参与排序。这样的话，两个相同的长方体变种一定会相邻，并且在探索i和j配对的时候通过这个编号信息(&&idx[i]!=idx[j])来排除这样的配对。
     
     */
    
    int doit_dp(vector<vector<int>>&& cuboids) {
        
        int n = cuboids.size();
        vector<array<int,4>>p;
        
        for (int i = 0; i < cuboids.size(); i++)
        {
            auto c = cuboids[i];
            p.push_back({c[0], c[1], c[2], i});
            p.push_back({c[0], c[2], c[1], i});
            p.push_back({c[1], c[0], c[2], i});
            p.push_back({c[1], c[2], c[0], i});
            p.push_back({c[2], c[0], c[1], i});
            p.push_back({c[2], c[1], c[0], i});
        }
        
        sort(p.begin(), p.end());
        vector<int> dp(6 * n);
        
        for (int i = 0; i < 6 * n; i++)
        {
            dp[i] = p[i][2];
            for (int j = 0; j < i; j++)
            
                if (p[j][0] <= p[i][0] && p[j][1] <= p[i][1] && p[j][2] <= p[i][2] && p[j][3] != p[i][3])
                    dp[i] = std::max(dp[i], dp[j]+p[i][2]);
        }

        int ret = 0;
        for (int i=0; i<6*n; i++)
            ret = std::max(ret, dp[i]);
        return ret;
    }
    
    /*
     
     解法2
     我们考虑一个合法的堆叠A(a1,a2,a3)可以放在B(b1,b2,b3)之上，即a1<=b1, a2<=b2, a3<=b3. 那么可以证明max(a1,a2,a3) <= max(b1,b2,b3), mid(a1,a2,a3) <= mid(b1,b2,b3), min(a1,a2,a3) <= min(b1,b2,b3). 第一个和第三个结论显然，第二个结论通过反正：如果不是的话，是无法同时存在条件中的三个不等式的。

     于是我们发现，只要A可以放在B之上，那么A的变体(min(a1,a2,a3), mid(a1,a2,a3), max(a1,a2,a3))也一定可以放在B的变体(min(b1,b2,b3), mid(b1,b2,b3), max(b1,b2,b3))之上。
     所以对于任何一个合法的堆叠序列，我们都可以将其中的每个长方体变化为：最短边作为length、中等边作为width、最长边作为height。变化之后，原序列依然是一个合法的堆叠，而且总高度只增不减。所以重新考虑原题，最优的解一定是把每个长方体的最长边作为height。
     所以对于每种长方体，我们只需要选择如上的这一种变体即可，我们能够保证：一定有一个合法的堆叠序列，并且得到的序列总高度是最高的。

     于是我们将所有n个长方体经过变形后（将最短边作为length、中等边作为width、最长边作为height）按照长度和宽度进行降序排列。接下来按照解法1的思想，用N^2的LIS DP方法找到最高的总堆叠高度。因为每个长方体我们只放了一个变种，所以不需要记录idx来避免同一个长方体的duplicate。
     
     */
    
    int dpit_dp(vector<vector<int>>&& cuboids) {
        
        int n = cuboids.size();
        for (auto& c:cuboids)
        {
            sort(c.begin(), c.end());
        }
        sort(cuboids.begin(), cuboids.end());

        vector<int>dp(n);
        for (int i=0; i<n; i++)
        {
            dp[i] = cuboids[i][2];
            for (int j=0; j<i; j++)
                if (cuboids[j][0]<=cuboids[i][0] && cuboids[j][1]<=cuboids[i][1] && cuboids[j][2]<=cuboids[i][2])
                    dp[i] = std::max(dp[i], dp[j]+cuboids[i][2]);
        }

        int ret = 0;
        for (int i=0; i<n; i++)
            ret = std::max(ret, dp[i]);
        return ret;    }
};
