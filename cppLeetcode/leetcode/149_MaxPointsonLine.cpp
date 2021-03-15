/*
149. Max Points on a Line


Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, 
return the maximum number of points that lie on the same straight line.

 

Example 1:


Input: points = [[1,1],[2,2],[3,3]]
Output: 3
Example 2:


Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
 

Constraints:

1 <= points.length <= 300
points[i].length == 2
-104 <= xi, yi <= 104
All the points are unique.

*/

#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>

using std::map;
using std::unordered_map;
using std::vector;


class MaxPoints {

    /*
        149.Max-Points-on-a-Line
        解法1
        此题不能试图固定一个点、再构建直线斜率的hash表 map<double,int>Map 来确定直线的种类。因为靠相除得到的斜率会有数值误差，在最新的测试样例中无法通过。
        对于一个点 (x0,y0),判断是否和另外两点(x1,y1),(x2,y2)构成直线的判据是

        (y1-y0)*(x2-x0)==(y2-y0)*(x1-x0)
        正确的思路：
        遍历点P[i]. 对于固定的起始点P[i]，考虑会和剩下的点构成多少不同的直线。

        于是遍历剩下的点，比如P[j]，看是否P[j]和P[i]能构成一个新的直线。建立一个Hash Map，如果在这个表中发现已经有一条直线P[k]，使得P[k],P[j],P[i]满足之前的那个关系，
        说明P[j]已经属于P[k]、P[i]构成的直线上，则Map[k]++. 如果遍历Map之后没有找到任何归属，就将这个点加入hash表作为新的key，即Map[j]=1，表示连接P[i]、P[j]所代表的一条新直线。遍历完所有的j之后，查看此时Map里面最多个数的那项，代表P[i]所能构建的最多点的直线。    

        最外边的大循环，遍历完P[i]之后，最大的结果就出来了。

        注意点：

        如果P[j]和P[i]重合，那么这些点可归属任意的直线，需要在Map里特殊处理。
        如果用C++，则在上述的判断三点共线的数学等式里，必须都转换为long long类型才能得到正确的比较结果。
        解法2
        之前提到，如果计算斜率 k = (y1-y0)/(x1-x0)作为key的话，会因为精度不足而产生错误。

        一个巧妙的解决方法是，因为x0,y0,x1,y1都是整数，可以令 a=y1-y0, b=x1-x0, 那么一对tuple值 (a/gcd(a,b), b/gcd(a,b))则可以代表一条直线斜率的特征，成为可以信赖的key放入字典内统计该直线上的点的数目.
    
    */
    int doit_hashtable(vector<vector<int>>& points) 
    {
        int result=0;
        
        for (int i=0; i<points.size(); i++)
        {
            unordered_map <int,int> Map;
            int countSame=0;
            
            for (int j=0; j<points.size(); j++)
            {
                if (j==i) continue;
                
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1])
                {
                    countSame++;
                    continue;
                }
                
                int flag=0;
                for (auto a:Map)
                {
                    auto& p = points[a.first];
                    if ( (long long)(p[1]-points[i][1])*(points[j][0]-points[i][0]) == (long long)(points[j][1]-points[i][1])*(p[0]-points[i][0]) )
                    {
                        flag=1;
                        Map[a.first]++;
                        break;
                    }
                }
                
                if (flag==0)                
                    Map[j]=1;                               
            }
            
            int temp=0;
            for (auto a:Map)
                temp = std::max(temp,a.second);
            temp+=(countSame+1);
            result=std::max(result,temp);
        }
        
        return result;
    }


    int doit_hashtable(vector<vector<int>>& points) {
     
        int ret = 0;
            
        for (int i=0; i<points.size(); i++)
        {
            map<std::pair<int,int>, int> count;
            int verticle = 0;
            int same = 0;
            
            for (int j=0; j<points.size(); j++)
            {
                if (i==j)  continue;
                if (points[i]==points[j])
                {
                    same++;
                    continue;
                }
                
                int dy = points[j][1]-points[i][1];
                int dx = points[j][0]-points[i][0];
                
                if (dx==0)
                {
                    verticle ++;
                    continue;
                }
                
                int a = dy/gcd(dy,dx);
                int b = dx/gcd(dy,dx);
                
                count[{a,b}] ++;
            }
            
            ret = std::max(ret, same + 1);
            ret = std::max(ret, verticle + same +1 );
            for (auto x: count)
                ret = std::max(ret, x.second + same + 1);
        }
        
        return ret;
    }



public:
    
    int doit_(vector<vector<int>>& points) {
        
    }
};