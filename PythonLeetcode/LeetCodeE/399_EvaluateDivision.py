

# 399. Evaluate Division


# Equations are given in the format A / B = k, where A and B are variables represented as strings,
# and k is a real number (floating point number). Given some queries, return the answers.
# If the answer does not exist, return -1.0.

# Example:
# Given a / b = 2.0, b / c = 3.0. 
# queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
# return [6.0, 0.5, -1.0, 1.0, -1.0 ].

# The input is: vector<pair<string, string>> equations, vector<double>& values, 
# vector<pair<string, string>> queries , where equations.size() == values.size(),
# and the values are positive. This represents the equations. Return vector<double>.

# According to the example above:

# equations = [ ["a", "b"], ["b", "c"] ],
# values = [2.0, 3.0],
# queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 


import collections

class calcEquation(object):


    # <steve>
    def doit1(self, equations, values, queries):
        """
        :type equations: List[List[str]]
        :type values: List[float]
        :type queries: List[List[str]]
        :rtype: List[float]
        """
        import itertools

        quot = collections. defaultdict(dict)
        for i, c in enumerate(equations):
            quot[c[0]][c[1]] = values[i]
            quot[c[1]][c[0]] = 1 / values[i]

        for k, i, j in itertools.permutations(quot, 3):
            if k in  quot[i] and j in quot[k]:
                quot[i][j] = quot[i][k] * quot[k][j]

        return [quot[k].get(j, -1.0) for k, j in queries]

    def doit2(self, equations, values, queries):
        """
        :type equations: List[List[str]]
        :type values: List[float]
        :type queries: List[List[str]]
        :rtype: List[float]
        """
        d={}
        v={}

        for i in range(len(equations)):
            if equations[i][0] not in d:
                d[equations[i][0]]=set([equations[i][1]])
            else:
                d[equations[i][0]].add(equations[i][1])

            if equations[i][1] not in d:
                d[equations[i][1]]=set([equations[i][0]])
            else:
                d[equations[i][1]].add(equations[i][0])

            v[(equations[i][0],equations[i][1])]=values[i]

            if values[i]!=0:
                v[(equations[i][1],equations[i][0])]=1.0/values[i]

        def dfs(x, y):
            
            if x not in d or y not in d:
                return -1.0
            if x==y:
                return 1.0
            else:
                if (x, y) in v:
                    return v[x,y]
                else:
                    visited.add(x)
                    for j in d[x]:
                        if j not in visited:
                            ans=dfs(j,y)
                            if ans!=-1:
                                d[x].add(y)
                                d[y].add(x)

                                v[(x,y)] = v[(x,j)] * ans

                                if v[(x,y)]!=0:
                                    v[(y,x)]=1.0/v[(x,y)]

                                return v[(x,y)]
                 #   visited.discard(x)
                    return -1.0
        l=[]

        for x, y in queries:
            visited=set([])
            
            l.append(dfs(x,y))

        return l
                



    def doit(self, equations, values, queries):
        """
        :type equations: List[List[str]]
        :type values: List[float]
        :type queries: List[List[str]]
        :rtype: List[float]
        """
        
        nodes_ = collections.defaultdict(dict)
        allnodes_ = set()

        for i, C in enumerate(equations):

            nodes_[C[0]][C[1]] = values[i]            
            nodes_[C[1]][C[0]] = 1 / values[i]
            allnodes_.add(C[0])
            allnodes_.add(C[1])

        def search(nodes_, allnodes_, s, e, path):
            
            if e in nodes_[s]:
                return nodes_[s][e]

            if len(path) == len(allnodes_):
                return 0
        
            minv = float('inf')
            for c in list(nodes_[s]):
                if c in path:
                    continue
                path.add(c)
                res = search(nodes_, allnodes_, c, e, path)
                if res:
                    minv = min(minv, res * nodes_[s][c])
                path.remove(c)
            
            nodes_[s][e] = minv
            if minv:
                nodes_[e][s] = 1 / minv
            
            return minv


        res = []                  
        for m in queries:

            result = -1.0
            if (m[0] not in allnodes_) or (m[1] not in allnodes_):
                res.append(-1.0)
                continue

            if m[0] == m[1]:
                res.append(1.0)
                continue

            res.append(search(nodes_, allnodes_, m[0], m[1], set(m[0])))

        return res
            

if __name__=="__main__":


    res = calcEquation().doit([ ["a", "b"], ["b", "c"] ], [2.0, 3.0], 
                [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ])



    res = calcEquation().doit([["a","b"],["c","d"]], [1.0, 1.0],
                [["a","c"],["b","d"],["b","a"],["d","c"]])



    res = calcEquation().doit([["x1","x2"],["x2","x3"],["x3","x4"],["x4","x5"]],
                [3.0,4.0,5.0,6.0],
                [["x1","x5"],["x5","x2"],["x2","x4"],["x2","x2"],["x2","x9"],["x9","x9"]])

    pass