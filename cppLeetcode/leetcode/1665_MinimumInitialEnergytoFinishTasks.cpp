/*
1665. Minimum Initial Energy to Finish Tasks


You are given an array tasks where tasks[i] = [actuali, minimumi]:

    .actuali is the actual amount of energy you spend to finish the ith task.
    .minimumi is the minimum amount of energy you require to begin the ith task.

For example, if the task is [10, 12] and your current energy is 11, you cannot start this task. However, if your current energy is 13, you can complete this task, and your energy will be 3 after finishing it.

You can finish the tasks in any order you like.

Return the minimum initial amount of energy you will need to finish all the tasks.

 

Example 1:

Input: tasks = [[1,2],[2,4],[4,8]]
Output: 8
Explanation:
Starting with 8 energy, we finish the tasks in the following order:
    - 3rd task. Now energy = 8 - 4 = 4.
    - 2nd task. Now energy = 4 - 2 = 2.
    - 1st task. Now energy = 2 - 1 = 1.
Notice that even though we have leftover energy, starting with 7 energy does not work because we cannot do the 3rd task.
Example 2:

Input: tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
Output: 32
Explanation:
Starting with 32 energy, we finish the tasks in the following order:
    - 1st task. Now energy = 32 - 1 = 31.
    - 2nd task. Now energy = 31 - 2 = 29.
    - 3rd task. Now energy = 29 - 10 = 19.
    - 4th task. Now energy = 19 - 10 = 9.
    - 5th task. Now energy = 9 - 8 = 1.
Example 3:

Input: tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
Output: 27
Explanation:
Starting with 27 energy, we finish the tasks in the following order:
    - 5th task. Now energy = 27 - 5 = 22.
    - 2nd task. Now energy = 22 - 2 = 20.
    - 3rd task. Now energy = 20 - 3 = 17.
    - 1st task. Now energy = 17 - 1 = 16.
    - 4th task. Now energy = 16 - 4 = 12.
    - 6th task. Now energy = 12 - 6 = 6.
 

Constraints:

1 <= tasks.length <= 105
1 <= actual​i <= minimumi <= 104


*/

#include <vector>

using std::vector;


class MinimumEffort {

    /*
            1665.Minimum-Initial-Energy-to-Finish-Tasks
        我们令每个任务的actual cost属性为a，mimimum energy to start属性为m。我们先考虑：最优解T必然大于等于所有任务的a属性之和。所以即使任务次序任意打乱，总能保证做每个任务时都能有足够的energy被消耗。
        但是属性m要求某些任务必须在存留能量很高的时候才能被启动。所以一个比较自然的贪心想法就是将所有的任务按照属性b排序，优先做属性m较大的任务，这样可以最大程度保证它能启动。

        举个例子，如果按照属性b的次序排序样例2：[1,3],[2,4],[8,9],[10,11],[10,12]。我们从最终状态能量为0开始，逆推最初所需要的能量。我们可以写出这样的计算式：

        int ret = 0;
        for (int i=0; i<n; i++)
        ret = max(ret+tasks[i][0], tasks[i][1])``` //前者是考虑完成该任务需要消耗的能量，后者是考虑启动该任务前的能量下限
        但结果发现结果是33，并非是最优的32. 那么32是怎么得到的呢？实际的最优操作顺序是（从后往前）：[8,9],[10,11],[10,12],[2,4],[1,3]

        我们思考一下为什么需要把[1,3]的属性a和m都很小，但为什么会作为最先启动的任务？我们很容易发现它的m-a其实是所有任务里最大的。这是不是暗示了我们需要把任务按照m-a来排序呢？
        我们来实验一下：假设任务1(a1,m1)和任务2(a2,m2)，有m2-a2>m1-a1，我们来看一下分别用两种策略所得到的倒推最小初始能量的效果区别：

        倒推时先1后2之后的初始能量：T1 = max(max(a1, m1) + a2, m2) = max(max(a1+a2, m1+a2), m2)
        倒推时先2后1之后的初始能量：T2 = max(max(a2, m2) + a1, m1) = max(max(a2+a1, m2+a1), m1)
        因为m2-a2>m1-a1，所以m1+a2<m2+a1，所以一定有 max(a1+a2, m1+a2) < max(a2+a1, m2+a1)。 至此我们整理一下

        前提: m2-a2>m1-a1
        令: x1 = max(a1+a2, m1+a2)   (1)
            x2 = max(a2+a1, m2+a1)   (2)
        则: T1 = max(x1, m2)         (3)
            T2 = max(x2, m1)         (4)
        结论: 比较(1)(2)得 x1 < x2    (5)
            由(2)得 x2 > m2        (6)
        如果m2 < m1，那么由(3)(4)显然得到T1 < T2.

        如果m2 > m1，那么有(6)得到 x2 > m2 > m1，所以 T2 = max(x2, m1) = x2。因已知 x2>x1 (5) 并且 x2>m2 (6)，所以 T2 = x2 > T1.

        总之无论如何都有T1<T2，方案1更优。所以我们有结论：如果两个任务相邻，我们肯定会把m-a较小的认为放在倒推序列的前面。把这个结项想象成冒泡排序的规则，通过它我们就可以得到一个序列，使得通过倒推法得到的初始能量最小。

        PS：有一种“直观”的解释，为什么要根据 m - a排序？因为做这件任务之前，至少有能量m，减去a的消耗，那么做完之后一定保证剩余能量至少有m-a。我们自然希望做完任务之后的剩余能量越大越好，这样好做下一个任务。所以我们自然就会优先取做那些“保证剩余能量”更大的任务。
    */
    static bool cmp(vector<int>&a, vector<int>&b)
    {
        if (a[1]-a[0] == b[1]-b[0])
            return a[1]<b[1];
        else
            return a[1]-a[0]<b[1]-b[0];
    }

    int minimumEffort(vector<vector<int>>& tasks) 
    {
        std::sort(tasks.begin(), tasks.end(), cmp);        
        int start = 0;
        for (auto x: tasks)
        {            
            start = std::max(start+x[0], x[1]);     
        }
        return start;        
    }


public:

    int doit_greedy(vector<vector<int>>& tasks) {
        
        std::sort(begin(tasks), end(tasks), [](auto& a, auto& b) {
            return a[1] - a[0] < b[1] - b[0];
        });
        
        int start = 0;
        
        for (auto c: tasks) {
            
            if (start + c[0] > c[1]) {
                start += c[0];
            } else {
                start = c[1];
            }
        }
        
        return start;
    }
};