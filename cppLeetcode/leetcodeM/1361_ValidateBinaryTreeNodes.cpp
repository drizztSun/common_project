/*
1361. Validate Binary Tree Nodes


You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], 
return true if and only if all the given nodes form exactly one valid binary tree.

If node i has no left child then leftChild[i] will equal -1, similarly for the right child.

Note that the nodes have no values and that we only use the node numbers in this problem.

 

Example 1:



Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
Output: true
Example 2:



Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
Output: false
Example 3:



Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
Output: false
Example 4:



Input: n = 6, leftChild = [1,-1,-1,4,-1,-1], rightChild = [2,-1,-1,5,-1,-1]
Output: false
 

Constraints:

1 <= n <= 10^4
leftChild.length == rightChild.length == n
-1 <= leftChild[i], rightChild[i] <= n - 1


*/
#include <vector>
#include <functional>
#include <unordered_set>

using std::unordered_set;
using std::vector;


class ValidateBinaryTreeNodes {


public:
    
    bool doit_dfs(int n, vector<int>& leftChild, vector<int>& rightChild) {

        vector<int> indegree(n);

        for (int i = 0; i < n; i++) {
            if (leftChild[i] != -1)
                indegree[leftChild[i]]++;
            if (rightChild[i] != -1)
                indegree[rightChild[i]]++;
        }

        vector<int> starts;
        for (int i = 0; i < n; i++) {
            if (indegree[i] > 2)
                return false;

            if (indegree[i] == 0)
                starts.push_back(i);
        }

        if (starts.size() != 1) 
            return false;

        int cnt = 0;
        vector<bool> visited(n, false);
        std::function<bool(int)>  dfs = [&](int i) -> bool {

            if (i == -1) return true;

            if (visited[i]) return false;

            visited[i] = true;
            cnt++;
            return dfs(leftChild[i]) && dfs(rightChild[i]);
        };

        return dfs(starts[0]) && cnt == n;
    }

    bool doit_dfs(int n, vector<int>& leftChild, vector<int>& rightChild) {

        vector<bool> visited(n);
        unordered_set<int> roots;

        std::function<bool(int, int)> dfs = [&](int i, int root) {
            if(i == -1) return true;
            if(i != root && roots.count(i)){
                roots.erase(i);
                return true;
            }
            if(visited[i]) return false;
            visited[i] = true;
            return dfs(leftChild[i], root) && dfs(rightChild[i], root);
        };

        for(int i = 0; i < n; i++){
            if(visited[i]) 
                continue;
            
            roots.insert(i);

            if(!dfs(i, i)) return false;
        }

        return roots.size() == 1;
    }
};