/*
356. Line Reflection

Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points symmetrically, in other words, 
answer whether or not if there exists a line that after reflecting all points over the given line the set of the original points is the same that the reflected ones.

Note that there can be repeated points.

Follow up:
Could you do better than O(n2) ?

 

Example 1:


Input: points = [[1,1],[-1,1]]
Output: true
Explanation: We can choose the line x = 0.
Example 2:


Input: points = [[1,1],[-1,-1]]
Output: false
Explanation: We can't choose a line.
 

Constraints:

n == points.length
1 <= n <= 10^4
-10^8 <= points[i][j] <= 10^8

*/

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

using std::set;
using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::string;


class IsReflected {

    /*
                
        356.Line-Reflection
        首先，需要确定这些点关于x的对称中心位置，即镜面位置。注意到重复点在本题只算一个点，所以需要借助Set排除重复的干扰。
        根据数学关系，易知：x1,x2,...,x_n的对称中心，应该等于(x1+x2+...+x_n)/N

                unordered_set<int>Set;
                for (int i=0; i<N; i++)        
                    Set.insert(points[i].first);               
                float x0=0;
                for (auto a:Set)
                    x0+=a;
                x0=x0/Set.size();
        然后要判断这些点关于x=x0镜面对称，需要先保证对称点都在同一个y坐标上。所以利用Map来对这些点关于y的位置进行分类。

                unordered_map<int,set<int>>Map;
                for (int i=0; i<N; i++)
                {
                    Map[points[i].second].insert(points[i].first);
                }
        对于每个y位置，都有一个集合包括了若干个不重复的x位置，我们需要保证它们两两关于x0对称。利用了set的自动排序特点，我们可以用双指针从两边往中间夹逼。

                for (auto a:Map)
                {
                    vector<int>q(a.second.begin(),a.second.end()); //因为set是有序的，直接导入一个数组中。
                    int i=0;
                    int j=q.size()-1;
                    while (i<=j)
                    {
                        if (q[i]+q[j]!=x0*2)  // 关于x0对称的判据
                            return false;
                        i++;
                        j--;
                    }
                }
    */
    bool isReflected(vector<vector<int>>& points) 
    {
        
        int N=points.size();
        if (N==0) return true;
        
        unordered_map<int,set<int>>Map;
        unordered_set<int>Set;
        for (int i=0; i<N; i++)
        {
            Map[points[i][1]].insert(points[i][0]);
            Set.insert(points[i][0]);
        }
        
        float x0=0;
        for (auto a:Set) x0+=a;
        x0=x0/Set.size();
        
        for (auto a:Map)
        {
            vector<int>q(a.second.begin(),a.second.end());
            int i=0;
            int j=q.size()-1;

            while (i<=j)
            {
                if (q[i]+q[j] != x0*2) return false;
                i++;
                j--;
            }
        }
        
        return true;
    }


public:
    
    bool doit_hashtable(vector<vector<int>>& points) {
        
        unordered_map<int, set<int>> buf;
        for (const auto& a : points) {
            buf[a[1]].insert(a[0]);
        }

        double line = INT_MAX;

        for (auto it : buf) {

            int size = (it.second.size() + 1) / 2;
            auto s = begin(it.second);
            auto e = rbegin(it.second);
            double median = 0;

            while (size--) {

                median = double(*s + *e) / 2;

                if (line == INT_MAX) line = median;

                if (median != line) return false;

                s++;
                e++;
            }
        }

        return true;
    }
};
