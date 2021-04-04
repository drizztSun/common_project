/*
 
 
 990. Satisfiability of Equality Equations
 
 
 Given an array equations of strings that represent relationships between variables, each string equations[i] has length 4 and takes one of two different forms: "a==b" or "a!=b".  Here, a and b are lowercase letters (not necessarily different) that represent one-letter variable names.

 Return true if and only if it is possible to assign integers to variable names so as to satisfy all the given equations.

  

 Example 1:

 Input: ["a==b","b!=a"]
 Output: false
 Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.  There is no way to assign the variables to satisfy both equations.
 Example 2:

 Input: ["b==a","a==b"]
 Output: true
 Explanation: We could assign a = 1 and b = 1 to satisfy both equations.
 Example 3:

 Input: ["a==b","b==c","a==c"]
 Output: true
 Example 4:

 Input: ["a==b","b!=c","c==a"]
 Output: false
 Example 5:

 Input: ["c==c","b==d","x!=z"]
 Output: true
 
 */

#include <vector>
#include <string>

using std::vector;
using std::string;

class EquationsPossible {

    /*
        990.Satisfiability-of-Equality-Equations
        容易想到如果遇到a==b，那么a和b可以通过Union Find聚为一类。

        如果遇到a!=b，那么我们会检查a和b是否已经聚成了一类，是的话就说明引入了矛盾，返回false；如果不是的话，目前但前暂时没有导出矛盾。但问题是，我们如何保证之后再遇到a==b时能记住之前的a!=b呢？

        解决方法很简单，就是先考察所有的等式，将所有的能聚类的元素都聚起来。然后再考察所有的不等式，考察是否有与之前那些等式相矛盾的地方。没有任何矛盾的话就返回true。
    */

    vector<int>Father;

    bool equationsPossible(vector<string>& equations) 
    {
        Father.resize(26);
        for (int i=0; i<26; i++)
            Father[i] = i;

        for (auto & eq: equations)
        {            
            if (eq[1]=='=')
            {
                int a = eq[0]-'a';
                int b = eq[3]-'a';
                if (FindFather(a)!=FindFather(b))
                    Union(a,b);
            }
        }

        for (auto & eq: equations)
        {            
            if (eq[1]=='!')
            {
                int a = eq[0]-'a';
                int b = eq[3]-'a';
                if (FindFather(a)==FindFather(b))
                    return false;
            }
        }

        return true;
    }

    int FindFather(int x)
    {
        if (Father[x]!=x)
            Father[x] = FindFather(Father[x]);
        return Father[x];
    }
    
    void Union(int x, int y)
    {
        x = Father[x];
        y = Father[y];
        if (x<y)
            Father[y] = x;
        else
            Father[x] = y;
    }


public:

    /*
        Approach 1: Connected Components
        Intuition

        All variables that are equal to each other form connected components. For example, if a=b, b=c, c=d then a, b, c, d are in the same connected component as they all must be equal to each other.

        Algorithm

        First, we use a depth first search to color each variable by connected component based on these equality equations.

        After coloring these components, we can parse statements of the form a != b. If two components have the same color, then they must be equal, so if we say they can't be equal then it is impossible to satisfy the equations.

        Otherwise, our coloring demonstrates a way to satisfy the equations, and thus the result is true.


        Complexity Analysis

        Time Complexity: O(N) where NN is the length of equations.

        Space Complexity: O(1), assuming the size of the alphabet is O(1).
    */
    bool doit_color(vector<string>&& equations) {
        
        vector<vector<int>> graph(26, vector<int>());
        
        for (auto& c : equations) {
            if (c[1] == '=') {
                int x = c[0] - 'a', y = c[3] - 'a';
                graph[x].push_back(y);
                graph[y].push_back(x);
            }
        }
        
        vector<int> colors(26, -1);
        for (int i = 0; i < 26; i++) {
            if (colors[i] == -1) {
                vector<int> st;
                st.push_back(i);
                
                while (!st.empty()) {
                    int n = st.back();
                    st.pop_back();
                    colors[n] = i;
                    
                    for (auto& c : graph[n]) {
                        if (colors[c] == -1)
                            st.push_back(c);
                    }
                }
            }
        }
        
        for (auto& c: equations) {
            
            if (c[1] == '!') {
                int x = c[0] - 'a', y = c[3] - 'a';
                if (x == y)
                    return false;
                
                if (colors[x] != -1 && colors[x] == colors[y]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    
public:
    
    int find(int* parent, int x)
    {
        if(parent[x]==x) return x;
        int px=find(parent,parent[x]);
        parent[x]=px;
        return px;
    }
    
    void unionn(int* parent, int* rank, int x, int y)
    {
        int px=find(parent, x);
        int py=find(parent, y);
        if(px!=py)
        {
            if(rank[px]>rank[py])
            {
                parent[py]=px;
            }
            else if(rank[py]>rank[px])
            {
                parent[px]=py;
            }
            else
            {
                parent[py]=px;
                rank[px]++;
            }
        }
    }
    
    bool doit_disjoint(vector<string>& e) {
        int parent[26], rank[26];
        for(int i=0;i<26;i++)
        {
            parent[i]=i;
            rank[i]=1;
        }
        
        for(int i=0;i<e.size();i++)
        {
            if(e[i][1]=='=') //union of parents of all == equations
            {
                int p1=find(parent,((int)e[i][0])-((int)'a'));
                int p2=find(parent,((int)e[i][3])-((int)'a'));
                unionn(parent,rank,p1,p2);
            }
        }
        
        //check if any != equations are equal
        for(int i=0;i<e.size();i++)
        {
            if(e[i][1]=='!')
            {
                int p1=find(parent,((int)e[i][0])-((int)'a'));
                int p2=find(parent,((int)e[i][3])-((int)'a'));
                if(p1==p2) return false;
            }
        }
        return true;
    }
};