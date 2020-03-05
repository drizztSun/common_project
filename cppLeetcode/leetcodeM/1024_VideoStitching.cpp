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

    int doit(vector<vector<int>>&& clips, int T) {
            
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
    
    int doit1(vector<vector<int>>&& clips, int T) {
        
        int n = clips.size();
        if (n==0)
            return -1;
        
        sort(clips.begin(), clips.end(), [](auto& v1, auto& v2) -> bool{
            if (v1[0]<v2[0])
                return true;
            else if (v1[0]==v2[0])
                return v1[1]<=v2[1];
            else
                return false;
        });
        
        vector<int> dp (101, 101);
        dp[0] = 0;
        
        for (auto& c : clips) {  
            if (c[0]>T)
                break;
            for (int i=c[0]+1; i<=c[1]; i++) {
                dp[i] = std::min(dp[i], dp[c[0]]+1);
            }
        }
        
        return dp[T]==101 ? -1 : dp[T];
    }
};


void test_1024_VideoStitching() {
    
    auto res1 = VideoStitching().doit(vector<vector<int>>{{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}},10);
    
    auto res2 = VideoStitching().doit(vector<vector<int>>{{5,7},{1,8},{0,0},{2,3},{4,5},{0,6},{5,10},{7,10}}, 5);
    
    //auto res2 = VideoStitching().doit();
    
    //auto res3 = VideoStitching().doit();
    
    //auto res4 = VideoStitching().doit();
    
    return;
}
