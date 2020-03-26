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
using std::vector;

#include <string>
using std::string;

class EquationsPossible {
public:
    bool doit(vector<string>&& equations) {
        
        
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
    
    bool doit2(vector<string>& e) {
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


void test_990_statifiability_of_equality_equations() {
    
    auto res1 = EquationsPossible().doit(vector<string>{"a==b","b!=a"});
    
    auto res2 = EquationsPossible().doit(vector<string>{"b==a","a==b"});
    
    auto res3 = EquationsPossible().doit(vector<string>{"a==b","b==c","a==c"});
    
    auto res4 = EquationsPossible().doit(vector<string>{"a==b","b!=c","c==a"});
    
    auto res5 = EquationsPossible().doit(vector<string>{"c==c","b==d","x!=z"});
}
