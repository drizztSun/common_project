/*
881. Boats to Save People


You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit. 
Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.

 

Example 1:

Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)
Example 2:

Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)
Example 3:

Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
 

Constraints:

1 <= people.length <= 5 * 10^4
1 <= people[i] <= limit <= 3 * 10^4

*/
#include <vector>
#include <algorithm>

using std::vector;


class RescueBoats {

    /*
        881.Boats-to-Save-People

        解法1：
        容易想到比较严谨的贪心解，就是找到当前最重的小胖x，然后找到当前最大的小瘦y使得x+y<=limit，这样x和y的配对是对资源的最优利用。

        事实上这个贪心法可以进行松弛：对于当前最重的小胖x，只需要找到当前最小的小瘦y进行配对，就可以实现对资源的最优利用。分析如下。假设我们将所有人从轻到重排序y1,y2,y3,y4,...,x4,x3,x2,x1。
        对于当前最重的小胖对应的是x1，假设如果根据严谨的贪心算法找到的配对是y4（也就是恰好满足y4+x1<=limit），那么容易证明{x1,y1},{x2,y2},{x3,y3},{x4,y4}这四对其实都满足条件（即两个人加起来不超过limit）。
        所以我们可以将这四对剥离（因为已经充分利用了资源），对于剩下的人同理进行递归处理就可以了。

        于是这道题就转化为了双指针。左右指针朝中间移动，计算有多少对满足people[i]+people[j]<=limit.

        这种解法最大的隐患是时间复杂度需要O(NlogN)，勉强可以通过。

        解法2：
        如何避免排序就能确定最重的人是谁呢？我们可以借鉴桶排序的思想：用一个计数器数组p来记录每个重量的人数。

        假设当前最重的小胖的体重是x，那么对于x的值我们可以从limit开始往下猜，一旦发现p[x]>0，说明我们找到了这个最重的人。
        那么如何寻找x的最合理队友呢？我们可以从体重y=limit-x开始往下猜，一旦发现p[y]>0，就说明我们找到了最适合与x配对的小瘦（其体重为y）。记得每次配对之后，我们都需要及时更新计数器p[x]-- and/or p[y]--.

        这种解法最大的雷区在于：如果遇到了x==y的情况，说明小胖和小瘦的体重相同，那么对于小胖的处理次数就不是原先的p[x]了，而是需要及时减去一才对。

        解法3：
        可以将解法1的松弛贪心思想，以及解法2桶排序的思想结合起来。基本思想依然是双指针，但指针指的不是数组首尾的index，而是区间范围[1,limit]左右边界的value.

        假设当前最重的小胖的体重是x，那么对于x的值我们可以从limit开始往下猜，一旦发现p[x]>0，说明我们找到了这个最重的人。同时我们寻找当前最轻的小瘦，假设其体重为y，对于y的值我们可以从1开始往上猜，一旦发现p[y]>0，说明我们找到了当前最轻的人。
        对于每个小胖我们都试图寻找当前最轻的小瘦，如果符合x+y<0 && p[y]>0就说明存在它可以与小胖同船。

        显然容易分析出时间复杂度是o(N+limit)，比解法1要优秀.
    */
    int doit_greedy(vector<int>& people, int limit) {

        std::sort(people.begin(), people.end());
        int i=0, j=people.size()-1;
        int count = 0;
        while (i<=j)
        {
            if (people[i]+people[j]<=limit)
                i++;
            j--;
            count++;
        }
        return count;
    }

    int doit_greedy_1(vector<int>& people, int limit) {
        
        vector<int> p(limit+1,0);
        for (int w: people) p[w]++;
        
        int count = 0;
        for (int x = limit; x>0; x--)   // weight of the heaviest guy up to now
        {
            for (int i = p[x]; i>0; i--)
            {
                count++;
                p[x]--;
                
                int y = limit-x;
                while (y>0 && p[y]==0) y--;
                if (y>0) p[y]--;
                if (x==y) i--;
            }
        }
        return count;
    }

    int doit_greedy_2(vector<int>& people, int limit) {
        
        vector<int>p(limit+1,0);
        for (int w: people) p[w]++;
        
        int count = 0;
        int x = limit;
        int y = 1;
        
        while (x>0)
        {
            while (x>0 && p[x]==0) x--;

            if (x==0) break;
            
            count++;
            p[x]--;
            
            while (y+x<=limit && p[y]==0) y++;

            if (y+x<=limit && p[y]>0) p[y]--;
        }
                
        return count;
    }


public:
    
    int doit_(vector<int>& people, int limit) {
        


    }
};