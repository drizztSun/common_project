
/*
 
 # 1001. Grid Illumination

 # On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.

 # Initially, some number of lamps are on.  lamps[i] tells us the location of the i-th lamp that is on.
 # Each lamp that is on illuminates every square on its x-axis, y-axis, and both diagonals (similar to a Queen in chess).

 # For the i-th query queries[i] = (x, y), the answer to the query is 1 if the cell (x, y) is illuminated, else 0.

 # After each query (x, y) [in the order given by queries], we turn off any lamps that are at cell (x, y)
 # or are adjacent 8-directionally (ie., share a corner or edge with cell (x, y).)

 # Return an array of answers.  Each value answer[i] should be equal to the answer of the i-th query queries[i].


 # Example 1:

 # Input: N = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
 # Output: [1,0]
 # Explanation:
 # Before performing the first query we have both lamps [0,0] and [4,4] on.
 # The grid representing which cells are lit looks like this, where [0,0] is the top left corner, and [4,4] is the bottom right corner:
 # 1 1 1 1 1
 # 1 1 0 0 1
 # 1 0 1 0 1
 # 1 0 0 1 1
 # 1 1 1 1 1
 # Then the query at [1, 1] returns 1 because the cell is lit.  After this query, the lamp at [0, 0] turns off, and the grid now looks like this:
 # 1 0 0 0 1
 # 0 1 0 0 1
 # 0 0 1 0 1
 # 0 0 0 1 1
 # 1 1 1 1 1
 # Before performing the second query we have only the lamp [4,4] on.  Now the query at [1,0] returns 0, because the cell is no longer lit.


 # Note:

 # 1 <= N <= 10^9
 # 0 <= lamps.length <= 20000
 # 0 <= queries.length <= 20000
 # lamps[i].length == queries[i].length == 2
 
 */

#include <vector>
using std::vector;

#include <unordered_set>
using std::unordered_set;
using std::unordered_multiset;

#include <set>
using std::set;

#include <map>
using std::map;

#include <unordered_map>
using std::unordered_map;
/*
namespace std{

    template<>
    class hash<pair<int, int>> {
    public:
        auto operator()(const pair<int, int>& a) {
            return hash<int>()(a.first) ^ hash<int>()(a.second);
        }
    };
}*/

namespace std {
    template <> struct hash<std::pair<int, int>> {
        inline size_t operator()(const std::pair<int, int> &v) const {
            std::hash<int> int_hasher;
            return int_hasher(v.first) ^ int_hasher(v.second);
        }
    };
}

class GridIllumination {
    
public:
    vector<int> doit(int N, vector<vector<int>>&& lamps, vector<vector<int>>&& queries) {
        
        unordered_map<int, int> rows;
        unordered_map<int, int> cols;
        unordered_map<int, int> ld;
        unordered_map<int, int> dd;
        unordered_set<std::pair<int, int>> lampset;
        
        auto index_ld = [N](int x, int y) -> int {
            return N -1 - y + x;
        };
        
        auto index_dd = [](int x, int y) -> int {
            return x + y;
        };
        
        for (auto& c : lamps) {
            
            rows[c[0]]++;
            cols[c[1]]++;

            ld[index_ld(c[0], c[1])]++;
            dd[index_dd(c[0], c[1])]++;
            
            lampset.insert({c[0], c[1]});
        }
        
        vector<int> res;
        
        for (auto& c: queries) {
            
            if (rows[c[0]] + cols[c[1]] + ld[index_ld(c[0], c[1])] + dd[index_dd(c[0], c[1])] == 0) {
                res.push_back(0);
                continue;
            }
            
            res.push_back(1);
            
            for (auto d1 : vector<int>{-1, 0, 1}) {
                
                for (auto d2 : vector<int>{-1, 0, 1}) {
                    
                    int x = c[0] + d1, y = c[1] + d2;
                    if (x >= 0 && x < N && y >= 0 && y < N && lampset.count({x, y}) > 0) {
                        lampset.erase({x, y});
                        rows[x]--;
                        cols[y]--;
                        ld[index_ld(x, y)]--;
                        dd[index_dd(x, y)]--;
                    }
                }
            }
                
        }
     
        return res;
    }
};

bool kk(unordered_multiset<int> &a,int b) {
    return a.find(b)!=a.end();
}

int64_t code(int x, int y) {
    return int64_t(x) + (int64_t(y)<<32);
    
}

class GridIlluminationI {
public:
    
    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
    
        unordered_multiset<int> hor,ver,pos,neg;
        unordered_set<int64_t> lamp2id;
        for(int i = 0; i < lamps.size(); i++ )
        {
            vector<int> &lamp = lamps[i];
            int x = lamp[0], y = lamp[1];
            hor.insert(x);
            ver.insert(y);
            pos.insert(x-y);
            neg.insert(x+y);
            lamp2id.insert(code(x,y));
        }
        vector<int> o;
        for(auto &query:queries)
        {
            int x = query[0], y = query[1];
            if( kk(hor,x) || kk(ver,y) || kk(pos,x-y) || kk(neg,x+y) )
            {
                o.push_back(1);
                for(int dx = -1; dx <= 1; dx++)
                    for(int dy = -1; dy <= 1; dy++)
                    {
                        int lx = x+dx, ly = y+dy;
                        if(lx<0||ly<0||lx>=N||ly>=N)continue;
                        unsigned long cc = code(lx,ly);
                        unordered_set<int64_t>::iterator it = lamp2id.find(cc);
                        if(it!=lamp2id.end())
                        {
                            lamp2id.erase(it);
                            hor.erase(hor.find(lx));
                            ver.erase(ver.find(ly));
                            pos.erase(pos.find(lx-ly));
                            neg.erase(neg.find(lx+ly));
                        }
                    }
            }
            else o.push_back(0);
        }
        return o;
    }
};

void test_1001_grid_illumination() {
    
    auto res1 = GridIllumination().doit(5, vector<vector<int>>{{0, 0}, {4, 4}}, vector<vector<int>>{{1, 1}, {1, 0}});
    
    auto res2 = GridIllumination().doit(5, vector<vector<int>>{{0, 0}, {0, 4}}, vector<vector<int>>{{0, 4}, {0, 1}, {1, 4}});
    
    return;
}
