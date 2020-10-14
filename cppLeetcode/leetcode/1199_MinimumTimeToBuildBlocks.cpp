/*
 1199. Minimum Time to Build Blocks
 
 You are given a list of blocks, where blocks[i] = t means that the i-th block needs t units of time to be built. A block can only be built by exactly one worker.

 A worker can either split into two workers (number of workers increases by one) or build a block then go home. Both decisions cost some time.

 The time cost of spliting one worker into two workers is given as an integer split. Note that if two workers split at the same time, they split in parallel so the cost would be split.

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
 
 */
#include <vector>

using std::vector;

class MinBuildTime {

public:
    
    int doit_binary_search(vector<int>& blocks, int split) {
        
        sort(blocks.rbegin(), blocks.rend());
        int l = 0;
        int r = 1e9 + 7;
        int ans = -1;
        
        while(l <= r) {
            
            int m = (l + r) / 2;
            
            if(bs(blocks, split, m)) {
                ans = m;
                r = m - 1;
            }
            else
                l = m + 1;
        }
        
        return ans;
    }
    
    bool bs(vector<int>& blocks, int split, int time) {
        int workers = 1;
        
        for(int i = 0; i < blocks.size(); i++) {
            if(!workers || blocks[i] > time)
                return false; // No time or no free workers left
            
            // Keep splitting as long as we can split such that the biggest block can be built
            while(blocks[i] + split <= time) {
                workers *= 2;
                if(workers > blocks.size())
                    return true; // We have more workers than no. of blocks, so exit as possible
                time-= split;
            }
            workers--;
        }
        
        return true;
        
    }
};
