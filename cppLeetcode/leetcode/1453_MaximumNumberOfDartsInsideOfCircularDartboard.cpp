/*
1453. Maximum Number of Darts Inside of a Circular Dartboard


You have a very large square wall and a circular dartboard placed on the wall. You have been challenged to throw darts into the board blindfolded. 
Darts thrown at the wall are represented as an array of points on a 2D plane. 

Return the maximum number of points that are within or lie on any circular dartboard of radius r.

 

Example 1:



Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
Output: 4
Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
Example 2:



Input: points = [[-3,0],[3,0],[2,6],[5,4],[0,9],[7,8]], r = 5
Output: 5
Explanation: Circle dartboard with center in (0,4) and radius = 5 contain all points except the point (7,8).
Example 3:

Input: points = [[-2,0],[2,0],[0,2],[0,-2]], r = 1
Output: 1
Example 4:

Input: points = [[1,2],[3,5],[1,-1],[2,3],[4,1],[1,3]], r = 2
Output: 4
 

Constraints:

1 <= points.length <= 100
points[i].length == 2
-10^4 <= points[i][0], points[i][1] <= 10^4
1 <= r <= 5000

*/
#include <vector>

using std::vector;


const int MAXN = 100;
const double pi = acos(-1);

class MaximumNumberOfDartsInsideCircular {

    /*
        1453.Maximum-Number-of-Darts-Inside-of-a-Circular-Dartboard
        解法1：
        看不懂，不解释。 https://sumygg.com/2013/08/06/Radius-Circle-Cover/

        解法2：
        对于任何一个符合要求（包含最多的点）的圆，我们都可以让其适度收缩，使得其圆周恰好经过两点。

        于是我们可以遍历任意两点的组合，再根据圆的半径最大为r的条件，可以确定一个圆，令其圆心位置(x,y)。再查看这个的圆能涵盖多少个点。最终答案就是取包含点最多的那个圆。注意，根据圆上两点和半径，这样的圆心位置有两个。

        具体算法涉及到一些向量几何的知识。我们假设两点是A和B，中点位置是C。令向量n=(x1-x2, y1-y2)表示向量AB，我们可以知道与AB垂直的单位法向量v。具体方法是：令v=(a,b),那么有如下的条件：

        n*v = 0
        |v| = 1
        即

        (x1-x2)*a+(y1-y2)*b=0
        a^2++b^2 = 1
        于是可以解出a和b的值。注意答案有两组。并且当x1==x2的时候，为了避免分母是零，向量v会有特解(1,0)和(-1,0)。

        我们可以知道C和圆心O之间的距离是d。那么圆心位置就可以确定是：

        x = C_x + a * d
        y = C_y + b * d
        这个方法的时间复杂度是o(N^3).    
    */
    int numPoints(vector<vector<int>>& points, int r) 
    {
        double R = r+0.0001;
        double x,y;
        int ret = 0;
        
        for (int i=0; i<points.size(); i++)
            for (int j=i+1; j<points.size(); j++)
            {
                double x1 = points[i][0];
                double y1 = points[i][1];
                double x2 = points[j][0];
                double y2 = points[j][1];
                double x0 = (x1+x2)/2;
                double y0 = (y1+y2)/2;
                double d = sqrt(r*r*1.0 - ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/4);
                int count1=0, count2=0;
                double a,b;
                                
                b = x1==x2 ? 0: 1.0/sqrt((y1-y2)*(y1-y2)/(x1-x2)/(x1-x2) + 1);
                a = x1==x2 ? 1: -(y1-y2)/(x1-x2)*b;
                x = x0+a*d;
                y = y0+b*d;
                                                                
                for (int k=0; k<points.size(); k++)
                    if ((points[k][0]-x)*(points[k][0]-x)+(points[k][1]-y)*(points[k][1]-y)<=R*R)
                        count1++;
                
                b = x1==x2 ? 0: -1.0/sqrt((y1-y2)*(y1-y2)/(x1-x2)/(x1-x2) + 1);
                a = x1==x2 ? -1: -(y1-y2)/(x1-x2)*b;
                x = x0+a*d;
                y = y0+b*d;
                                                                
                for (int k=0; k<points.size(); k++)
                    if ((points[k][0]-x)*(points[k][0]-x)+(points[k][1]-y)*(points[k][1]-y)<=R*R)
                        count2++;
                
                ret = max(ret, max(count1, count2));
            }
        
        return max(1,ret);
    }

public:

    struct point
    {
        double x, y;
    };    
    struct interval
    {
        double arg;
        bool flag;
        bool operator<(const interval &T) const
        {
            return arg < T.arg;
        }
    };
    
    interval event[4 * MAXN];
    
    double dis(vector<int> a, vector<int> b)
    {
        return sqrt((a[0] - b[0])*(a[0] - b[0]) + (a[1] - b[1])*(a[1] - b[1]));
    }
    
    int numPoints(vector<vector<int>>& points, int R)
    {
        int n = points.size();
        int num, res, ans;
        
        double r = R+0.01;
        double dist, a1, a2, delta, cta;
        ans = -1;

        for(int i = 0; i < n; i++)
        {
            num = 0;
            for(int j = 0; j < n; j++)
            {
                if(i == j) continue;
                dist = dis(points[i], points[j]);
                if(dist <= 2.0 * r)
                {
                    cta = atan2(points[j][1] - points[i][1], points[j][0] - points[i][0]);
                    if(cta < 0) cta += 2 * pi;
                    delta = acos(dist / 2.0 / r);
                    a1 = cta - delta, a2 = cta + delta;
                    if(a1 < 0)
                    {
                        event[num].arg = a1 + 2 * pi, event[num++].flag = true;
                        event[num].arg = a2 + 2 * pi, event[num++].flag = false;
                    }
                    else
                    {
                        event[num].arg = a1, event[num++].flag = true;
                        event[num].arg = a2, event[num++].flag = false;
                        event[num].arg = a1 + 2 * pi, event[num++].flag = true;
                        event[num].arg = a2 + 2 * pi, event[num++].flag = false;
                    }
                }
            }
            if(num < ans) continue;
            std::sort(event, event + num);
            res = 0;
            for(int j = 0; j < num; j++)
            {
                if(event[j].flag) res++;
                else res--;
                if(ans < res) ans = res;
            }
        }
        if(ans != -1) return(ans + 1);
        else return 1;
    }

public:


};