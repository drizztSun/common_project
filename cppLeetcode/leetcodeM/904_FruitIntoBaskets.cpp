/*
904. Fruit Into Baskets


In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice, then repeatedly perform the following steps:

    1. Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
    2. Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?

 

Example 1:

Input: [1,2,1]
Output: 3
Explanation: We can collect [1,2,1].
Example 2:

Input: [0,1,2,2]
Output: 3
Explanation: We can collect [1,2,2].
If we started at the first tree, we would only collect [0, 1].
Example 3:

Input: [1,2,3,2,2]
Output: 4
Explanation: We can collect [2,3,2,2].
If we started at the first tree, we would only collect [1, 2].
Example 4:

Input: [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can collect [1,2,1,1,2].
If we started at the first tree or the eighth tree, we would only collect 4 fruits.
 

Note:

1 <= tree.length <= 40000
0 <= tree[i] < tree.length

*/
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;


class TotalFruit {

public:
    
    int doit_slidingwindow(vector<int>& tree) {
        
        unordered_map<int, int> baskets;
        int kinds = 0, res = 0;
        
        for (int i = 0, j = 0; i < tree.size(); i++) {
            
            if (baskets[tree[i]]++ == 0) {
                kinds++;
            }
            
            while (kinds > 2) {
                if (--baskets[tree[j++]] == 0) {
                    kinds--;
                }
            }
            
            if (kinds <= 2)
                res = std::max(res, i - j + 1);
        }
        
        return res;
    }


    /*
        Problem
        "Start from any index, we can collect at most two types of fruits. What is the maximum amount"


        Translation
        Find out the longest length of subarrays with at most 2 different numbers?


        Explanation
        Solve with sliding window,
        and maintain a hashmap counter,
        which count the number of element between the two pointers.
        Find more infinite similar prolems in the end.
        
        Time O(N), Space O(N)
    */
    int totalFruit(vector<int> &tree) {
        unordered_map<int, int> count;
        int i, j;
        for (i = 0, j = 0; j < tree.size(); ++j) {
            count[tree[j]]++;
            if (count.size() > 2) {
                if (--count[tree[i]] == 0)count.erase(tree[i]);
                i++;
            }
        }
        return j - i;
    }
};