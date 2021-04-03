/*
 
 
 # 1024. Video Stitching

 # You are given a series of video clips from a sporting event that lasted T seconds.
 # These video clips can be overlapping with each other and have varied lengths.

 # Each video clip clips[i] is an interval: it starts at time clips[i][0] and ends at time clips[i][1].
 # We can cut these clips into segments freely: for example, a clip [0, 7] can be cut into segments [0, 1] + [1, 3] + [3, 7].

 # Return the minimum number of clips needed so that we can cut the clips into segments that cover the entire sporting event ([0, T]).
 # If the task is impossible, return -1.


 # Example 1:

 # Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
 # Output: 3
 # Explanation:
 # We take the clips [0,2], [8,10], [1,9]; a total of 3 clips.
 # Then, we can reconstruct the sporting event as follows:
 # We cut [1,9] into segments [1,2] + [2,8] + [8,9].
 # Now we have segments [0,2] + [2,8] + [8,10] which cover the sporting event [0, 10].

 # Example 2:

 # Input: clips = [[0,1],[1,2]], T = 5
 # Output: -1
 # Explanation:
 # We can't cover [0,5] with only [0,1] and [0,2].

 # Example 3:

 # Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
 # Output: 3
 # Explanation:
 # We can take clips [0,4], [4,7], and [6,9].

 # Example 4:

 # Input: clips = [[0,4],[2,8]], T = 5
 # Output: 2
 # Explanation:
 # Notice you can have extra video after the event ends.
 
 
 */

#include <algorithm>
#include <vector>
using std::vector;

class VideoStitching {

public:

    /*
        1024.Video-Stitching
        此题非常类似 45.Jump Game II，整体就是一个贪心的策略。略微的差异就是我们需要预先将这些clips排序，排序的原则就是左端点靠前的优先，其次右端点靠后的优先。

        我们从第一个区间[0,right]开始考虑，将之后所有左端点位于right之前的clips都查看一遍（意味着与之前的区间有overlap），考察他们各自的右端点，取最大值得到能够推进到最远的位置farReach。
        这对应增加一个clip的操作（这个clip的右端点就是farReach）。然后更新right=farReach，再重复之前的操作，直到抵达target。

        特别注意，如果更新farReach之后仍然等于right，就意味着没有其他clip与当前的区间能够overlap，应该及时返回-1，否则会死循环。
    */
    int doit_greedy(vector<vector<int>>& clips, int T) 
    {
        if (T==0) return 0;

        std::sort(clips.begin(),clips.end(), [](vector<int>&a, vector<int>&b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });        
        
        int far = 0;
        int i = 0;
        int count = 0;
                
        while (i < clips.size())
        {            
            int nextFar = far;
            while (i < clips.size() && clips[i][0] <= far)
            {
                nextFar = std::max(nextFar, clips[i][1]);
                i++;
            }
            count++;

            if (nextFar >= T)
                return count;
            else if (nextFar == far)
                return -1;                            
            far = nextFar;
        }        

        return -1;        
    }

public:

    // It is same as jump game, shoud be greedy and O(n)
    int doit_greedy_best(vector<vector<int>>& clips, int T) {
        
        if (T == 0) return 0;
    
        std::sort(begin(clips), end(clips), [](const auto&a, const auto&b) {
           return a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]);
        });
        
        int ans = 0, end = 0;
        
        for (int i = 0; i < clips.size();) {
            
            int far = end;
            ans++;
            while (i < clips.size() && clips[i][0] <= end) {
                far = std::max(far, clips[i][1]);
                i++;
            }
            
            if (far >= T) return ans;
            
            else if (far == end) return -1;
            
            end = far;
        }
        
        return -1;
    }


    int doit_greedy(vector<vector<int>>&& clips, int T) {
            
         std::sort(clips.begin(), clips.end(), [](auto& a, auto& b) ->bool {
             return (a[0] < b[0] || (a[0] == b[0] && a[1] > b[1]));
         });
         
         vector<vector<int>> buf;
         
         for (auto& c : clips) {
             
             if (buf.empty()) {
                 if (c[0] != 0)
                     return -1;
                 buf.push_back(c);
             } else {
                 auto top = buf.back();
                 
                 if (c[0] > top[1])
                     return -1;
                 
                 if (top[1] >= c[1])
                     continue;
                 else if (c[0] <= top[0] && top[1] < c[1]) {
                    // B   5 -- 9
                    // A   4 -- 7 
                    // Tail   6
                    // pick B not A
                     int t = top[0];
                     buf.pop_back();
                     buf.push_back(vector<int>{t, c[1]});
                 } else {
                     buf.push_back(vector<int>{top[1], c[1]});
                 }
             }
             
             if (buf.back()[1] >= T)
                 return static_cast<int>(buf.size());
         }
     
        return -1;
    }
    
    // O(n^2)
    int doit_dp(vector<vector<int>>&& clips, int T) {
        
        int n = clips.size();
        if (n == 0) return -1;
        
        std::sort(clips.begin(), clips.end(), [](const auto& v1, const auto& v2){
            return v1[0]<v2[0] || (v1[0]==v2[0] && v1[1]<=v2[1]);
        });
        
        int scope = T;
        for (auto& c: clips)
            scope = std::max(scope, c[1]);
        
        vector<int> dp (scope+2, 101);
        dp[0] = 0;
        
        for (auto& c : clips) {  
            if (c[0]>=T) break;
            for (int i=c[0]+1; i<=c[1]; i++) {
                dp[i] = std::min(dp[i], dp[c[0]]+1);
            }
        }
        
        return dp[T] == 101 ? -1 : dp[T];
    }
};