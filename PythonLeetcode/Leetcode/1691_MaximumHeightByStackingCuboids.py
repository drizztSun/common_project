

class MaximumHeightByStackingCuboids:

    def doit_dp(self, cuboids: list) -> int:

        cuboidsgroups = []
        for i, c in enumerate(cuboids):
            cuboidsgroups.extend([(c[0], c[1], c[2], i), (c[0],c[2],c[1], i), (c[1], c[0], c[2], i), (c[1],c[2],c[0], i), (c[2], c[1], c[0], i), (c[2],c[0],c[1], i)])

        cuboidsgroups.sort()
        dp = [c[2] for c in cuboidsgroups]
        ans = 0

        for i in range(len(cuboidsgroups)):

            for j in range(i-1, -1, -1):

                if cuboidsgroups[i][3] != cuboidsgroups[j][3] and cuboidsgroups[i][0] >= cuboidsgroups[j][0] and cuboidsgroups[i][1] >= cuboidsgroups[j][1] and cuboidsgroups[i][2] >= cuboidsgroups[j][2]:
                    dp[i] = max(dp[i], dp[j] + cuboidsgroups[i][2])

            ans = max(ans, dp[i])
        return ans

    """
      解法2
     我们考虑一个合法的堆叠A(a1,a2,a3)可以放在B(b1,b2,b3)之上，即a1<=b1, a2<=b2, a3<=b3. 那么可以证明max(a1,a2,a3) <= max(b1,b2,b3), mid(a1,a2,a3) <= mid(b1,b2,b3), min(a1,a2,a3) <= min(b1,b2,b3). 
     第一个和第三个结论显然，第二个结论通过反正：如果不是的话，是无法同时存在条件中的三个不等式的。

     于是我们发现，只要A可以放在B之上，那么A的变体(min(a1,a2,a3), mid(a1,a2,a3), max(a1,a2,a3))也一定可以放在B的变体(min(b1,b2,b3), mid(b1,b2,b3), max(b1,b2,b3))之上。
     所以对于任何一个合法的堆叠序列，我们都可以将其中的每个长方体变化为：最短边作为length、中等边作为width、最长边作为height。变化之后，原序列依然是一个合法的堆叠，而且总高度只增不减。所以重新考虑原题，最优的解一定是把每个长方体的最长边作为height。
     所以对于每种长方体，我们只需要选择如上的这一种变体即可，我们能够保证：一定有一个合法的堆叠序列，并且得到的序列总高度是最高的。

     于是我们将所有n个长方体经过变形后（将最短边作为length、中等边作为width、最长边作为height）按照长度和宽度进行降序排列。接下来按照解法1的思想，用N^2的LIS DP方法找到最高的总堆叠高度。因为每个长方体我们只放了一个变种，所以不需要记录idx来避免同一个长方体的duplicate。
     
    O(n^2)
    """
    def doit_dp_best(self, cuboids: list) -> int:

        cuboidsgroups = sorted([sorted(c) for c in cuboids])
        dp = [c[2] for c in cuboidsgroups]
        ans = 0

        for i in range(len(cuboidsgroups)):
            for j in range(i-1, -1, -1):
                if cuboidsgroups[i][0] >= cuboidsgroups[j][0] and cuboidsgroups[i][1] >= cuboidsgroups[j][1] and cuboidsgroups[i][2] >= cuboidsgroups[j][2]:
                    dp[i] = max(dp[i], dp[j] + cuboidsgroups[i][2])
            ans = max(ans, dp[i])
        return ans








