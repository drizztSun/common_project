"""
1199. Minimum Time to Build Blocks

You are given a list of blocks, where blocks[i] = t means that the i-th block needs t units of time to be built.
A block can only be built by exactly one worker.

A worker can either split into two workers (number of workers increases by one) or build a block then go home.
Both decisions cost some time.

The time cost of spliting one worker into two workers is given as an integer split. Note that if two workers split at the same time,
they split in parallel so the cost would be split.

Output the minimum time needed to build all blocks.

Initially, there is only one worker.



Example 1:

Input: blocks = [1], split = 1
Output: 1
Explanation: We use 1 worker to build 1 block in 1 time unit.
Example 2:

Input: blocks = [1,2], split = 5
Output: 7
Explanation: We split the worker into 2 workers in 5 time units then assign each of them to a block so the cost is 5 + max(1, 2) = 7.
Example 3:

Input: blocks = [1,2,3], split = 1
Output: 4
Explanation: Split 1 worker into 2, then assign the first worker to the last block and split the second worker into 2.
Then, use the two unassigned workers to build the first two blocks.
The cost is 1 + max(3, 1 + max(1, 2)) = 4.


Constraints:

1 <= blocks.length <= 1000
1 <= blocks[i] <= 10^5
1 <= split <= 100


"""


class MinBuildTime:


    def doit_binary_search(self, blocks, split):

        def binary_search(time):
            worker = 1
            for c in blocks:
                if worker == 0 or c > time: # No time or no free workers left
                    return False

                # Keep splitting as long as we can split such that the biggest block can be built
                while c + split <= time:
                    worker *= 2
                    if worker > len(blocks):
                        return True  # We have more workers than no. of blocks, so exit as possible
                    time -= split
                worker -= 1
                return True

        low, high = 0, 2**31 - 1
        blocks.sort(reverse=True)
        ans = 0

        while low <= high:
            mid = (low + high) // 2
            if binary_search(mid):
                high = mid - 1
                ans = mid
            else:
                low = mid + 1
        return ans


    """
    I initially though this was a dynamic programming question, and was even assuming I was aiming for O(n^2) because the max number of blocks is so low at 1000.
    Normally this means O(n^2). But after a little thinking, I realised this is not the best way to approach it at all. We can do it greedily!

    We can model this entire question as a binary tree that we need to construct with a minimum max depth cost.
    Each of the blocks is a leaf node, with a cost of its face value. And then each inner node will be of cost split.
    nodes that are sitting at the same level represent work that is done in parallel.
    We know there will be len(blocks) - 1 of these inner nodes, so the question now is how can we construct the tree such that it has the minimum depth.

    For example, a possible (not optimal) tree for the data set
    [1, 2, 4, 7, 10] with split cost 3 is:
    (Sorry for ascii art, 2 AM is too late at night to do this properly :) )

    ........3
    ...../....\
    .....3.....\
    ../.....\....\
     3.......3....\
    /..\..../..\...\
    1...2...4...7...10

    This tree has a maximum depth of 16 (3 -> 3 -> 3 -> 7).

    So, how can we optimise the construction of this tree? Huffman's algorithm!

    I'm going to assume you're familiar with Huffman's algorithm. If not, google it or read this.
    Note that it's traditionally used for building compression codes, but there is no reason we can't also use it here.
    https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/

    Instead of actually building the whole tree, we can just keep track of the nodes the huffman algorithm still needs to consider, as the maximum depth below them.
    So put all the leaf node (blocks) onto a priority queue, and then repeatedly take the 2 smallest off and add split onto the biggest of the 2
    (this is Huffman's algorithm, it's greedy) and put the result back onto the priority queue.

    Once there is only one left, this is the depth of the root node, and we return it.

    It is O(n-log-n) because we are making 2n - 1 insertions into a heap and n removals, and both heap insertion and removal have a cost of O(log-n).
    We drop the constants, giving a final cost of O(n-log-n).

    And here is the code.

    """
    def doit_heap_huffman(self, blocks, split):

        import heapq
        heapq.heapify(blocks)
        while len(blocks) > 1:
            block_1 = heapq.heappop(blocks)
            block_2 = heapq.heappop(blocks)
            new_block = max(block_1, block_2) + split
            heapq.heappush(blocks, new_block)
        return blocks[0]

    def doit_dp(self, blocks, split):

        blocks.sort(reverse=True)
        dp = [0] * (len(blocks) + 1)

        for i in range(len(blocks)-1, -1, -1):
            dp[-1] = blocks[i]
            for k in range(len(blocks)-1, 0, -1):
                dp[k] = min(max(blocks[i], dp[k - 1]), split + (dp[k * 2] if k * 2 < len(blocks) else blocks[i]))
            dp[0] = float('inf')

        return dp[1]


if __name__ == '__main__':

    MinBuildTime().doit_binary_search(blocks = [1], split = 1)

    MinBuildTime().doit_binary_search(blocks = [1,2], split = 5)

    MinBuildTime().doit_dp(blocks = [1,2,3], split = 1)