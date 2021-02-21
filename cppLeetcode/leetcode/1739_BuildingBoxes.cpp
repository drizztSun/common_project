/*
1739. Building Boxes

You have a cubic storeroom where the width, length, and height of the room are all equal to n units. 
You are asked to place n boxes in this room where each box is a cube of unit side length. There are however some rules to placing the boxes:

You can place the boxes anywhere on the floor.
If box x is placed on top of the box y, then each side of the four vertical sides of the box y must either be adjacent to another box or to a wall.
Given an integer n, return the minimum possible number of boxes touching the floor.

 

Example 1:



Input: n = 3
Output: 3
Explanation: The figure above is for the placement of the three boxes.
These boxes are placed in the corner of the room, where the corner is on the left side.
Example 2:



Input: n = 4
Output: 3
Explanation: The figure above is for the placement of the four boxes.
These boxes are placed in the corner of the room, where the corner is on the left side.
Example 3:



Input: n = 10
Output: 6
Explanation: The figure above is for the placement of the ten boxes.
These boxes are placed in the corner of the room, where the corner is on the back side.
 

Constraints:

1 <= n <= 109

*/
#include <cmath>
#include <vector>
#include <functional>

using std::vector;
using std::sqrt;


class BuildingBox {

public:

    /*
        1739.Building-Boxes
        此题有点像找规律。我们从直观上可以得知，最高效的摆放方法一定就是如示例中的形状，底边围着一个墙角对称地摆放成“等腰三角形”，然后每一层都是边长减一的等腰三角形。这样的“饱和金字塔”可以利用最小的底边堆叠最多的单元。

        如果没有一个恰好饱和的“金字塔”能够堆叠n个单元，那么我们势必需要先增加底边。怎么增加呢？显然也是尽量围成等腰三角形。如果不能恰好构成等腰三角形，我们就在最接近的等腰三角形的基础上，每一行增加一个单元。比如说：我们有13个单元做底边，只能拼出长宽为4的等腰三角形，多出来的3个单元，就添加在每行的末尾。

        4 3 3 2 1
        3 2 2 1
        2 1 1
        1
        图中的数字表示该位置最高能堆叠到第几层。

        我们可以发现，对于最底层，每行的个数是：5,4,3,1. 对于第二层，每行的个数是：4,3,1. 对于第三层，每行的个数是：3,1. 对于第四层，每行的个数是：1.

        我们发现每层所能摆放的个数，恰好底层序列的后缀！于是我们可以根据底层序列求出每层摆放的数量和整个金字塔的摆放数量。

        整体地，我们用二分搜值法。先猜测底层的area，根据area判断出底层序列，继而求出整个金字塔的数量，然后与需求n进行比较，调整下一轮area的猜测范围。

        Math


            4 3 3 2 1
            3 2 2 1
            2 1 1
            1

            so edge will be d, then d^2 < (1+d) * d <= 2 * area
            => d < sqrt(2*area) is upperbound, go d-- find smaller d.

            diff is more to fill ground

            n => area = 13 => d= 4 + 3 => n`

            5 4 3 1
            4 3 1
            3 1
            1

            # calculate the suffix total, of 5, 4, 3, 1
    */
    int doit_math(n) {
        /*
            imagine the bottom is a triangle with same yao. 
                     1
                   1   1
                  1  1   1
                1   1   1  1

            Per row increment 1, then the whole n could be incremented (row + 1) * row / 2.
            We are seeking the biggest row, make total just less than n

            Then rest of them, we can continue to fill cube on the ground to the top, on row + 1.
            if we can fill r on groud, the total increnment is r * (r+1) / 2.
        */

        if (n == 1) return 1;
        
        int row = 1, total_max_n = 1;
        int increment = 0;
        while (total_max_n < n) {
            row++;
            increment = (1 + row) * row / 2;
            total_max_n += increment;
        }

        total_max_n -= increment;
        row--;

        for (int r = 1; r < row+2; r++)
            if (r*(1+r) / 2 + total_max_n >= n)
                return r + row * (1+row) / 2;
    
        return 1;
    }

    typedef long long ll;

    int doit_binary_search_math(int n) {
        int left = 1, right = 1e9;

        std::function<ll(ll)> cal = [](ll area) {

            // d^2 < (1+d)*d <= 2 * area => d < sqrt(2*area), d upperbound
            ll d = (int)sqrt(2*area);
            while ((1+d)*d/2 > area)
                d--;
            
            ll diff = area - (1+d)*d/2;
            
            vector<ll>a(d);
            for (int i=0; i<d; i++)
                a[i] = d - i;
            
            for (int i=0; i<diff; i++)
                a[i] += 1;        
            
            ll total = 0;
            ll sufsum = 0;
            for (int i=d-1; i>=0; i--) {
                sufsum += a[i];
                total += sufsum;
            }

            return total;
        };

        while (left < right)
        {
            int mid = (right+left) / 2;
            if (cal(mid) >= n)
                right = mid;
            else
                left = mid+1;
        }
        return left;        
    }
    

};