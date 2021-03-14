/*
 
 1687. Delivering Boxes from Storage to Ports
 
 You have the task of delivering some boxes from storage to their ports using only one ship. However, this ship has a limit on the number of boxes and the total weight that it can carry.

 You are given an array boxes, where boxes[i] = [ports​​i​, weighti], and three integers portsCount, maxBoxes, and maxWeight.

 ports​​i is the port where you need to deliver the ith box and weightsi is the weight of the ith box.
 portsCount is the number of ports.
 maxBoxes and maxWeight are the respective box and weight limits of the ship.
 The boxes need to be delivered in the order they are given. The ship will follow these steps:

 The ship will take some number of boxes from the boxes queue, not violating the maxBoxes and maxWeight constraints.
 For each loaded box in order, the ship will make a trip to the port the box needs to be delivered to and deliver it. If the ship is already at the correct port, no trip is needed, and the box can immediately be delivered.
 The ship then makes a return trip to storage to take more boxes from the queue.
 The ship must end at storage after all the boxes have been delivered.

 Return the minimum number of trips the ship needs to make to deliver all boxes to their respective ports.

  

 Example 1:

 Input: boxes = [[1,1],[2,1],[1,1]], portsCount = 2, maxBoxes = 3, maxWeight = 3
 Output: 4
 Explanation: The optimal strategy is as follows:
 - The ship takes all the boxes in the queue, goes to port 1, then port 2, then port 1 again, then returns to storage. 4 trips.
 So the total number of trips is 4.
 Note that the first and third boxes cannot be delivered together because the boxes need to be delivered in order (i.e. the second box needs to be delivered at port 2 before the third box).
 Example 2:

 Input: boxes = [[1,2],[3,3],[3,1],[3,1],[2,4]], portsCount = 3, maxBoxes = 3, maxWeight = 6
 Output: 6
 Explanation: The optimal strategy is as follows:
 - The ship takes the first box, goes to port 1, then returns to storage. 2 trips.
 - The ship takes the second, third and fourth boxes, goes to port 3, then returns to storage. 2 trips.
 - The ship takes the fifth box, goes to port 3, then returns to storage. 2 trips.
 So the total number of trips is 2 + 2 + 2 = 6.
 Example 3:

 Input: boxes = [[1,4],[1,2],[2,1],[2,1],[3,2],[3,4]], portsCount = 3, maxBoxes = 6, maxWeight = 7
 Output: 6
 Explanation: The optimal strategy is as follows:
 - The ship takes the first and second boxes, goes to port 1, then returns to storage. 2 trips.
 - The ship takes the third and fourth boxes, goes to port 2, then returns to storage. 2 trips.
 - The ship takes the fifth and sixth boxes, goes to port 3, then returns to storage. 2 trips.
 So the total number of trips is 2 + 2 + 2 = 6.
 Example 4:

 Input: boxes = [[2,4],[2,5],[3,1],[3,2],[3,7],[3,1],[4,4],[1,3],[5,2]], portsCount = 5, maxBoxes = 5, maxWeight = 7
 Output: 14
 Explanation: The optimal strategy is as follows:
 - The ship takes the first box, goes to port 2, then storage. 2 trips.
 - The ship takes the second box, goes to port 2, then storage. 2 trips.
 - The ship takes the third and fourth boxes, goes to port 3, then storage. 2 trips.
 - The ship takes the fifth box, goes to port 3, then storage. 2 trips.
 - The ship takes the sixth and seventh boxes, goes to port 3, then port 4, then storage. 3 trips.
 - The ship takes the eighth and ninth boxes, goes to port 1, then port 5, then storage. 3 trips.
 So the total number of trips is 2 + 2 + 2 + 2 + 3 + 3 = 14.
  

 Constraints:

 1 <= boxes.length <= 105
 1 <= portsCount, maxBoxes, maxWeight <= 105
 1 <= ports​​i <= portsCount
 1 <= weightsi <= maxWeight
 
 */

#include <stdio.h>
#include <vector>

using std::vector;


class BoxDelivering {
    
public:
    
    /*
     
     1687.Delivering-Boxes-from-Storage-to-Ports
     我们先来考察一下贪心的解法为什么会有局限性。我们考察从第一个盒子开始，假设到第5个盒子为止，区间[1:5]是用一次船载的极限（考虑了盒子总数、盒子总重的约束）。

     idx   1 2 3 4 5
     port: 1 2 3 4 5
     在上面的例子中总共需要6段航程（包括回港）。那么为什么我们充分利用了船载极限，不见得是最优解呢？其实是和之后的行程有关系。看下面的例子：

     idx   1 2 3 4 5 6
     port: 1 2 3 4 5 5
     如果按照之前的方案，我们需要两次船载，分别是运载[1:5]，需要6段trip，然后运载[6]，需要2段trip。总共需要8段trip。但是更优的方案是，第一次运载[1:4]，需要5段trip；第二次运载[5:6]需要2段trip，总共就是7段trip。

     我们发现了什么？第一种贪心方案，会使得port 5的两个箱子被拆分成了两次船载来运输，中间白白浪费了一次回港的trip。而更优的方案是，我们不使用船载的极限，而是把盒子5的机会留到下一次船载，使得第二次出船的时候，一次就把两个箱子都运走。这就是为什么极限贪心的方法不是最优解的原因。

     于是我们拓展一下，考虑当前这船的货物，从第i个箱子开始，船载极限允许最多装到第j个箱子。令dp[x]表示运送前i个盒子最少需要的trip数目。

     idx    i .....   j j+1
     port   X X X X X X  X
     第一种方案，就是极限贪心。如下图，我们可以知道dp[j] = dp[i-1] + tripNums[i:j] + 1，其中tripNums[i:j]就是从仓库出发依次走完i~j所在港口数目，最后一个1是回港的trip。

     idx    i .....   j j+1
     port  [X X X X X X] X
     第二种方案，就是当返现j+1和j的盒子属于同一个港口的时候，退让一部分容量，将与j+1相同港口的盒子都留到下一次去。假设箱子j-1、j都是与j+1同港口的，那么我们就有dp[j-2] = dp[i-1] + tripNums[i:j-2] + 1

     idx    i ..... j-1 j j+1
     port  [X X X X] Y  Y Y
     
     
     plan1 dp[j] <= dp[i-1] + trip[i:j] + 1
     
     plan2 dp[j-2] <= dp[i-1] + trip[i:j-2] + 1
     
     
     注意，我们为什么不把断点设置在j-1和j之间呢？原因是，那样做的话并没有起到预期的节省trip的作用，到达Y港口的次数依然被割裂为两次出海。与其这样没有起到节省trip的效果，那还不如第一种方案，把船载容量用到极限。

     所以总结一下，如果我们从i个箱子开始装船，那么其实就两种方案。第一种方案就是用来船载的极限，装到箱子j为止，这样我们就可以更新dp[j]。第二种方案，就是发现如果箱子j和箱子j+1在同一个港口，那么我们往前回溯同一个港口的连续的箱子直至j'，于是我们更新dp[j'-1]。

     这里我们有一个疑问，那么处于i和j之间的这些dp，我们并没有更新到，这有问题吗？其实没有问题，对于我们没有更新到的dp[x]，意味着以x为船载最后一箱的方案并不是optimal的。事实上，我们只依据之前的两种方案去做装载分配的话，永远不会产生这样的情况。

     此外，还有一个问题。我们永远按照这两种方案去做，那么一定能更新到最后一个箱子的dp[n]吗？答案是的。第一种极限贪心可以保证装到最后一个箱子（即使没有到船载极限），并在遍历到最后一个箱子时更新dp[n]。
     
     dp[x]: minimum trips to deliver first x boxes. x is the last boxes.
     
     */
    int doit_dp_greedy_slidingwindow(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        
        int n = boxes.size();
        boxes.insert(begin(boxes), {-1, 0});
        
        vector<int> dp(n+1, INT_MAX/2);
        dp[0] = 0;
        
        int j = 0;
        int weightSum = 0;
        int tripNum = 0;
        int lastPort = -1;
        int lastj;
        
        for (int i = 1; i <= n; i++) {
            
            while (j+1 <= n && j+1 - i+1 <= maxBoxes && weightSum + boxes[j+1][1] <= maxWeight) {
                j++;
                weightSum += boxes[j][1];
                
                if (boxes[j][0] != boxes[j-1][0])
                    tripNum++;
                
                if (boxes[j][0] != lastPort) {
                    lastj = j;
                    lastPort = boxes[j][0];
                }
            }
            
            // update dp[j]
            dp[j] = std::min(dp[j], dp[i-1] + tripNum + 1);
            
            // in some cases, update dp[lastj-1] where boxes[lastj:j] has same port.
            if (j+1 <= n && boxes[j][0] == boxes[j+1][0]) {
                dp[lastj-1] = std::min(dp[lastj-1], dp[i-1] + tripNum);
            }
            
            // like sliding window, from [i:j] => [i+1:j], update weightSum and tripSum
            weightSum -= boxes[i][1];
            tripNum -= (i+1 <= n && boxes[i][0] != boxes[i+1][0]);
        }
        
        return dp[n];
    }
};
