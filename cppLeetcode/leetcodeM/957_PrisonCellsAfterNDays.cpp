/*
 
 
 957. Prison Cells After N Days
 
 There are 8 prison cells in a row, and each cell is either occupied or vacant.

 Each day, whether the cell is occupied or vacant changes according to the following rules:

 If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.

 Otherwise, it becomes vacant. (Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.)

 We describe the current state of the prison in the following way: cells[i] == 1 if the i-th cell is occupied, else cells[i] == 0.

 Given the initial state of the prison, return the state of the prison after N days (and N such changes described above.)

  

 Example 1:

 Input: cells = [0,1,0,1,1,0,0,1], N = 7
 Output: [0,0,1,1,0,0,0,0]
 Explanation:
 The following table summarizes the state of the prison on each day:
 Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
 Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
 Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
 Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
 Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
 Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
 Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
 Day 7: [0, 0, 1, 1, 0, 0, 0, 0]

 Example 2:

 Input: cells = [1,0,0,1,0,0,1,0], N = 1000000000
 Output: [0,0,1,1,1,1,1,0]
 
 
 */

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <string>
using std::string;


class PrisonAfterNDays {
    
    /*
        957.Prison-Cells-After-N-Days
        我们首先解决这个问题：从一个状态到下一个状态，如何高效地进行转换。用8个bit位来代表0/1是比较自然的想法。假设当前的状态用整形k来表示，下一个状态用k'来表示。我们发现，k'除去首尾，其余所有位置上，第i位的bit取决于上一个状态时第i-1位的bit是否和第i+1位的bit相等，
        即bit(i)=~(bit(i-1)^bit(i+1))。

        我们将k右移一位记作k1，同时将k左移一位记作k2，我们将k1和k2对齐。我们发现，上述的操作就等价于bit(k_i)=~(bit(k1_i)^bit(k2_i))，也就是k'=~(k1^k2)。

        k =   abcdefgh
        k1 =  xabcdefg
        k2 =  bcdefghx
        另外注意，k'的首尾bit注定是0，所以我们额外加上需要加上一个mask=01111110来将首尾强制置为0.因此最终一次变换的表达式就是k=~((k>>1)^(k<<1))&126

        接下来考虑，我们是否要真的做N次变换来得到最终结果呢？考虑到N的数量级很大，肯定是不合适的。我们发现，k总共8个bit位，除去首尾必须是0，那么总共只有2^6=64种可能。
        所以一定存在一个有限长度的循环节。我们最多模拟64个回合，就一定能找到循环节的起始点S和长度L。也就是说，从K0开始变换S次进入循环节，再变换L次就又重复这个循环节。

        所以我们对于非常大的N，预处理为N = (N-S)%L+S。然后从K0开始，变换N次即可。
    */
    vector<int> doit_(vector<int>& cells, int N) 
    {
        int K = 0;
        for (int i=0; i<8; i++)
            K += (cells[i]<<i);
        int K0 = K;

        unordered_map<int,int>Map;
        int t = 0;
        while (Map.find(K)==Map.end())
        {
            Map[K] = t;
            K = (~((K>>1)^(K<<1)))&126;
            t++;
        }
        int S = Map[K];
        int L = t - S;

        int M = K0;
        if (N >= S)
            N = (N-S) % L + S;

        for (int i=0; i<N; i++)
        {
            M = (~((M>>1)^(M<<1)))&126;
        }
        
        vector<int>results(8,0);
        for (int i=0; i<8; i++)
            results[i] = ((M>>i)&1);
        return results;
    }
    
public:
    /*
     
     Approach 1: Simulation
     Intuition

     We simulate each day of the prison.

     Because there are at most 256 possible states for the prison, eventually the states repeat into a cycle rather quickly. We can keep track of when the states repeat to find the period t of this cycle, and skip days in multiples of t.

     Algorithm

     Let's do a naive simulation, iterating one day at a time. For each day, we will decrement N, the number of days remaining, and transform the state of the prison forward (state -> nextDay(state)).

     If we reach a state we have seen before, we know how many days ago it occurred, say t. Then, because of this cycle, we can do N %= t. This ensures that our algorithm only needs O(2**{\text{cells.length}})O(2∗∗cells.length) steps.
     
     */
    vector<int> doit_hashtable(vector<int>&& cells, int N) {
        
        auto change = [](string& cur) {
            string base = cur;
            for (int i = 0; i < 8; i++) {
                if (i - 1 >= 0 && i + 1 < 8 && base[i-1] == base[i+1])
                    cur[i] = '1';
                else
                    cur[i] = '0';
            }
        };
        
        unordered_map<string, int> seen;
        string cur;
        for (auto c : cells) {
            cur += c ? '1' : '0';
        }
        
        while (N>0) {
            
            if (seen.find(cur) != seen.end()) {
                N %= seen[cur] - N;
            }
            seen[cur] = N;
            
            if (N >= 1) {
                N--;
                change(cur);
            }
        }
        
        vector<int> ans;
        for (size_t i = 0; i < cur.length(); i++) {
            ans.push_back(cur[i] - '0');
        }
        
        return ans;
    }
};