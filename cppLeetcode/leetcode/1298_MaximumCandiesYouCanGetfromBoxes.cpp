/*
1298. Maximum Candies You Can Get from Boxes


Given n boxes, each box is given in the format [status, candies, keys, containedBoxes] where:

status[i]: an integer which is 1 if box[i] is open and 0 if box[i] is closed.
candies[i]: an integer representing the number of candies in box[i].
keys[i]: an array contains the indices of the boxes you can open with the key in box[i].
containedBoxes[i]: an array contains the indices of the boxes found in box[i].
You will start with some boxes given in initialBoxes array. You can take all the candies in any open box and you can use the keys in it to open new boxes and you also can use the boxes you find in it.

Return the maximum number of candies you can get following the rules above.

 

Example 1:

Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
Output: 16
Explanation: You will be initially given box 0. You will find 7 candies in it and boxes 1 and 2. Box 1 is closed and you don't have a key for it so you will open box 2. You will find 4 candies and a key to box 1 in box 2.
In box 1, you will find 5 candies and box 3 but you will not find a key to box 3 so box 3 will remain closed.
Total number of candies collected = 7 + 4 + 5 = 16 candy.
Example 2:

Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]], containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
Output: 6
Explanation: You have initially box 0. Opening it you can find boxes 1,2,3,4 and 5 and their keys. The total number of candies will be 6.
Example 3:

Input: status = [1,1,1], candies = [100,1,100], keys = [[],[0,2],[]], containedBoxes = [[],[],[]], initialBoxes = [1]
Output: 1
Example 4:

Input: status = [1], candies = [100], keys = [[]], containedBoxes = [[]], initialBoxes = []
Output: 0
Example 5:

Input: status = [1,1,1], candies = [2,3,2], keys = [[],[],[]], containedBoxes = [[],[],[]], initialBoxes = [2,1,0]
Output: 7
 

Constraints:

1 <= status.length <= 1000
status.length == candies.length == keys.length == containedBoxes.length == n
status[i] is 0 or 1.
1 <= candies[i] <= 1000
0 <= keys[i].length <= status.length
0 <= keys[i][j] < status.length
All values in keys[i] are unique.
0 <= containedBoxes[i].length <= status.length
0 <= containedBoxes[i][j] < status.length
All values in containedBoxes[i] are unique.
Each box is contained in one box at most.
0 <= initialBoxes.length <= status.length
0 <= initialBoxes[i] < status.length

*/

#include <vector>
#include <queue>
#include <unordered_set>

using std::unordered_set;
using std::queue;
using std::vector;

class MaxCandies {

    /*
        1298.Maximum-Candies-You-Can-Get-from-Boxes
        本题只要读清题意就不难。我们手头有些已经开启的盒子，盒子里面有糖果（收益）、钥匙（可以开启其他盒子）和其他的盒子（可能已经开启，也可能还未开启需要钥匙）。问题是不断打开我们能打开的盒子，最终的总收益是多少。

        用BFS可以比较容易解决。队列里永远是还没有被打开的盒子。每一个回合，检查一遍队列里的盒子：1.如果盒子还不能打开（状态是关闭并且没有钥匙），则继续塞回队列。2.如果盒子能够打开，那么就打开它，拿取收益、收藏钥匙、将新盒子塞进队列。

        直至队列在经过一个回合之后没有任何变化，即没有任何盒子被打开，那么就说明进入了僵局不会再可能有进展，即终止程序。
    */
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) 
    {
        unordered_set<int>key;
        int ret = 0;
        queue<int>q;
        for (auto b: initialBoxes)
            q.push(b);
        
        bool changed = 1;
        while (q.size()>0 && changed)
        {
            changed = 0;
            int len = q.size();
            while (len--)
            {
                int b = q.front();
                q.pop();
                
                if (status[b]==0 && key.find(b)==key.end())
                {
                    q.push(b);
                }
                else
                {
                    changed = 1;
                    ret+=candies[b];
                    for (auto k: keys[b])
                        key.insert(k);
                    for (auto bb: containedBoxes[b])
                        q.push(bb);                
                }
            }
        }
        return ret;    
    }

public:
    
    int doit_bfs(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        
        int n = status.size();
        int candys = 0;
        vector<int> visited(n, false);
        vector<int> avaiablekeys(n, false);
        
        queue<int> qu;
        unordered_set<int> availableBox;
        for (int i = 0; i < initialBoxes.size(); i++) {
            if (status[initialBoxes[i]] == 1) {
                qu.push(initialBoxes[i]);
                visited[initialBoxes[i]] = true;
            }
            else
                availableBox.insert(initialBoxes[i]);
        }

        while (!qu.empty()) {
            
            int cur = qu.front(); qu.pop();
            
            candys += candies[cur];
            
            for (auto key : keys[cur]) {
                avaiablekeys[key] = true;
                if (availableBox.count(key) && !visited[key]){
                    visited[key]= true;
                    status[key] = 1;
                    qu.push(key);
                }
            }
            
            for (auto b : containedBoxes[cur]) {
                if ((status[b] || avaiablekeys[b]) && !visited[b]) {
                    visited[b]= true;
                    qu.push(b);
                } else {
                    availableBox.insert(b);
                }
            }
        }

        return candys;
    }
};