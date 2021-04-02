/*
406. Queue Reconstruction by Height

You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). 
Each people[i] = [hi, ki] represents the ith person of height hi with exactly ki other people in front who have a height greater than or equal to hi.

Reconstruct and return the queue that is represented by the input array people. 
The returned queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).

 

Example 1:

Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
Explanation:
Person 0 has height 5 with no other people taller or the same height in front.
Person 1 has height 7 with no other people taller or the same height in front.
Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
Person 3 has height 6 with one person taller or the same height in front, which is person 1.
Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
Person 5 has height 7 with one person taller or the same height in front, which is person 1.
Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
Example 2:

Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
 

Constraints:

1 <= people.length <= 2000
0 <= hi <= 10^6
0 <= ki < people.length
It is guaranteed that the queue can be reconstructed.

*/
#include <vector>
#include <map>
#include <list>
#include <map>
#include <algorithm>

using std::list;
using std::map;
using std::map;
using std::vector;


class ReconstructQueue {

    /*
        406.Queue-Reconstruction-by-Height
        此题我们来这样考虑，比如对于[h,k]来说，如果只考虑那些身高比他高、位置比他靠前的人群，他是排第k+1个。那如果我们把所有身高比他高的人都已经拉了出来排成一排，我们再将这个人塞进第k+1位，也是不违和的。因为剩下那些比他矮的人，无论放在哪里，都不会再影响到k这个数值。

        于是，贪心的方法很简单。我们按身高依次处理。当处理某人时，所有比他高的都已经处理完了，然后将该人放在第k+1个位置即可。他的插入不会对之前那些“高人”的排名产生任何的影响。依次类推处理完所有的人。

        这里，当有两个人的身高相同怎么办呢？先处理k小的，他优先插入，优先得到更靠前的位置。
    */
    static bool cmp(const vector<int>& a,  const vector<int>& b)
    {
        if (a[0] ==b[0])
            return a[1] < b[1];
        else
            return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) 
    {
        std::sort(people.begin(),people.end(),cmp);
        vector<vector<int>>results;
        for (int i=0; i<people.size(); i++)
        {
            if (results.size()==0)
            {
                results.push_back(people[i]);
                continue;
            }
            
            int pos = people[i][1];
            results.insert(results.begin()+pos,people[i]);
        }
        return results;
    }


public:

    vector<vector<int>> doit_(vector<vector<int>>& people) {
        
        map<int, vector<int>> cnt;
        
        for (int i = 0; i < people.size(); i++)
            cnt[people[i][1]].push_back(i);
        
        list<int> _root;
        
        for (auto it = begin(cnt); it != end(cnt); it++) {
            std::sort(begin(it->second), end(it->second), [&](int i, int j){
                return people[i][0] < people[j][0];
            });
            
            for (auto i : it->second) {
             
                int height = people[i][0], c = people[i][1];
                
                if (c == 0) {
                    _root.push_back(i);
                    continue;
                }
                
                auto iter = begin(_root);
                
                while (iter != end(_root)) {
                    
                    if (c == 0) {
                        if (people[*iter][0] > height) break;
                        
                    } else if (people[*iter][0] >= height) {
                        c--;   
                    }
                    
                    iter++;
                }
                
                _root.insert(iter, i);
            }
        }
        
        
        vector<vector<int>> ans;
        for (auto it = begin(_root); it != end(_root); it++)
            ans.push_back(people[*it]);
        
        return ans;

    }
};

