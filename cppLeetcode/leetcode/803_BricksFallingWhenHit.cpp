/*

# 803. Bricks Falling When Hit

# We have a grid of 1s and 0s; the 1s in a cell represent bricks.
# A brick will not drop if and only if it is directly connected to the top of the grid,
# or at least one of its (4-way) adjacent bricks will not drop.

# We will do some erasures sequentially. Each time we want to do the erasure at the location (i, j),
# the brick (if it exists) on that location will disappear, and then some other bricks may drop because of that erasure.

# Return an array representing the number of bricks that will drop after each erasure in sequence.

# Example 1:
# Input:
# grid = [[1,0,0,0],[1,1,1,0]]
# hits = [[1,0]]
# Output: [2]
# Explanation:
# If we erase the brick at (1, 0), the brick at (1, 1) and (1, 2) will drop. So we should return 2.

# Example 2:
# Input:
# grid = [[1,0,0,0],[1,1,0,0]]
# hits = [[1,1],[1,0]]
# Output: [0,0]
# Explanation:
# When we erase the brick at (1, 0), the brick at (1, 1) has already disappeared due to the last move. So each erasure will cause no bricks dropping.
# Note that the erased brick (1, 0) will not be counted as a dropped brick.


# Note:

# The number of rows and columns in the grid will be in the range [1, 200].
# The number of erasures will not exceed the area of the grid.
# It is guaranteed that each erasure will be different from any other erasure, and located inside the grid.
# An erasure may refer to a location with no brick - if it does, no bricks drop.



# Union-Find

# I think for this problem, it is not easy to think the hit sequence recursely.
# However, this is the first essential step to solve this problem.
# In the Union Find, I used a dummy node m*n to denote the roof node.
# So, the 1 in the first row will be connected to this roof node.

# The method to calculate how many bricks are fall is to calcuate the rank difference of the roof node.
#
# There are a few cases to handle :
#
# hit to 0. In this case, we simply add 0 to the result, since this will make no difference for the grid.
# hit to 1. But this 1 is not connected to roof. So the falling brick will be curRoofRank - prevRoofRank.
# hit to 1. But this 1 is connected to roof. So the falling brick will be curRoofRank - prevRoofRank - 1.

*/
#include <vector>

using namespace std;



class HitBricks {

	/*
	
		803.Bricks-Falling-When-Hit
		这题咋看上去很难，但实际上用“时光倒流”的想法就很方便。

		假想在所有的erasure完成之后，这些砖块有些与top相连（成为大陆）），有些则是孤立的岛屿。我们考察最后一次抽掉的砖块，如果“复原”它能使得一些孤立的岛屿与大陆相连的话，那么这些岛屿的面积S，其实就是最后一次erasure所造成砖块掉落的数量。
		OK，就算这次“复原”不能使得任何岛屿与大陆相连，但也有可能会使得一部分岛屿之间相连，这样下一次“复原”的时候就有可能使得这一块更大的岛屿与大陆相连。以此方法不停地往回追溯上去。

		此题我觉得用DFS来做更直观一点。我的做法是：

		1.将所有的要被erasure的砖块都抹去，也就是标记0（这里我标记为-1便于与原先真正的“海洋”区别）。

		2.用DFS的方法确定所有与上顶端相连的“大陆”，标记为2.

		3.“时光倒流”，处理最后一次erasure。如果这个砖块的周围有大陆（标记是2），那么它就可能将一部分岛屿（标记是1）与大陆相连。所以从该点出发进行DFS，找出所有标记是1的格子，就是答案（也就是因为这次erasure造成的砖块掉落的数量），记得将这些已经并入大陆的格子也都标记成2。
		如果这个砖块的周围没有大陆，那么就简单的将这个位置的的标记恢复为1就行（也就是岛屿）。

		4.依次类推处理所有的erasure。
	*/
	vector<vector<int>>visited; // 1: land, -1 : erased, 2 : connected
    vector<pair<int,int>>dir;

    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) 
    {
        int m = grid.size();
        int n = grid[0].size();
        dir = {{1,0},{-1,0},{0,1},{0,-1}};
        
        visited = grid;
        for (auto point:hits)        
            visited[point[0]][point[1]] *= -1;        
                        
        for (int j=0; j<n; j++)        
            if (visited[0][j]==1)
            {
                int num = 0;
                dfs(0,j,num);                        
            }
        
        vector<int>ret;
        reverse(hits.begin(),hits.end());
        for (auto point:hits)
        {
            int i = point[0];
            int j = point[1];
                        
            if (visited[i][j]!=-1) 
            {
                ret.push_back(0);
                continue;
            }
            bool find = (i==0);
            for (int k=0; k<4; k++)
            {
                int x = i+dir[k].first;
                int y = j+dir[k].second;
                if (!isValid(x,y)) continue;
                if (visited[x][y]==2)
                {
                    find = true;
                    break;
                }                
            }
            
            if (find)
            {
                int num = -1;
                dfs(i,j,num);                        
                ret.push_back(num);
            }
            else
            {
                visited[i][j] = 1;            
                ret.push_back(0);
            }                            
        }
        
        reverse(ret.begin(),ret.end());
        return ret;
    }
    
    bool isValid(int x, int y)
    {
        int m = visited.size();
        int n = visited[0].size();
        return !(x<0||x>=m||y<0||y>=n);
    }
    
    void dfs(int i, int j, int &num)
    {
        visited[i][j] = 2;
        num++;
        for (int k=0; k<4; k++)
        {
            int x = i+dir[k].first;
            int y = j+dir[k].second;
            if (!isValid(x,y)) continue;
            if (visited[x][y]==1)
                dfs(x,y,num);
        }        
    }


public:

	vector<int> doit(vector<vector<int>>&& grid, vector<vector<int>>&& hits) {

		int M = grid.size(), N = grid[0].size();

		for (auto& c : hits) {
			grid[c[0]][c[1]] -= 1;
		}

		for (auto j = 0; j < N; j++) {
			if (grid[0][j] == 1) {

				vector<pair<int, int>> stack;
				stack.push_back({ 0, j });
				grid[0][j] += 1;

				while (!stack.empty()) {
					auto c = stack.back();
					stack.pop_back();

					for (auto& s : vector<pair<int, int>>{ {-1, 0}, {1, 0}, {0, 1}, {0, -1} }) {
						int xx = c.first + s.first, yy = c.second + s.second;

						if (xx >= 0 && xx < M && yy >= 0 && yy < N && grid[xx][yy] == 1) {
							stack.push_back(make_pair(xx, yy));
							grid[xx][yy] += 1;
						}
					}
				}
			}
		}

		vector<int> res(hits.size());

		for (int i = hits.size() - 1; i >= 0; i--) {

			auto c = hits[i];
			int x = c[0], y = c[1];
			grid[x][y] += 1;

			if (grid[x][y] == 1 && (x == 0 ||
									(y < N - 1 && grid[x][y + 1] == 2) ||
									(x < M - 1 && grid[x + 1][y] == 2) ||
									(y > 0 && grid[x][y - 1] == 2) ||
									grid[x - 1][y] == 2))

			{
				int k = 0;
				vector<pair<int, int>> st{ {x, y} };
				grid[x][y] += 1;

				while (!st.empty()) {
					auto c = st.back();
					st.pop_back();

					for (auto s : vector<pair<int, int>>{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} }) {

						int xx = c.first + s.first, yy = c.second + s.second;

						if (xx >= 0 && xx < M && yy >= 0 && yy < N && grid[xx][yy] == 1) {
							st.push_back({ xx, yy });
							grid[xx][yy] += 1;
							k += 1;
						}
					}
				}
				res[i] = k;
			}
		}


		return res;
	}
};


int* hitBricks(int** grid, int gridRowSize, int *gridColSizes, int** hits, int hitsRowSize, int *hitsColSizes, int* returnSize);


class Solution {
public:
	vector<int> hitBricks(vector<vector<int>>&& grid, vector<vector<int>>&& hits) {
		int** c_grid = (int**)malloc(grid.size() * sizeof(int*));
		for (int i = 0; i < grid.size(); i++)
			c_grid[i] = grid[i].data();

		int** c_hits = (int**)malloc(hits.size() * sizeof(int*));
		for (int i = 0; i < hits.size(); i++)
			c_hits[i] = hits[i].data();

		int gridRowSize = grid.size();
		int gridColSizes = grid[0].size();
		int hitsRowSize = hits.size();
		int hitsColSizes = hits[0].size();

		int returnSize = 0;
		int *c_ret = ::hitBricks(c_grid, gridRowSize, &gridColSizes, c_hits, hitsRowSize, &hitsColSizes, &returnSize);

		vector<int> ret(c_ret, c_ret + returnSize);

		free(c_ret);
		free(c_hits);
		free(c_grid);

		return ret;
	}
};



/**
* Return an array of size *returnSize.
* Note: The returned array must be malloced, assume caller calls free().
*/
struct array_res {
	int *arr;
	int cap;
	int size;
};

int array_res_alloc(struct array_res **ares, int cap)
{
	*ares = (struct array_res*) malloc(sizeof(struct array_res));
	(*ares)->cap = cap;
	(*ares)->size = 0;

	(*ares)->arr = (int*)malloc(cap * sizeof(int));
	return 0;
}

int array_res_add(struct array_res *ares, int val)
{
	if (ares->size >= ares->cap) {
		ares->arr = (int*)realloc(ares->arr, 2 * ares->cap * sizeof(int));
		ares->cap = 2 * ares->cap;
	}

	ares->arr[ares->size++] = val;
	return 0;
}

int array_res_get(struct array_res *ares, int idx)
{
	return ares->arr[idx];
}

void array_res_put(struct array_res *ares, int idx, int val)
{
	ares->arr[idx] = val;
	// return 0;
}

int find(int u, struct array_res *parents, struct array_res *sz)
{
	int oldu = u;

	while (u != array_res_get(parents, u))
		u = array_res_get(parents, u);

	while (oldu != u) {
		int nu = array_res_get(parents, oldu);
		array_res_put(parents, oldu, u);
		oldu = nu;
	}
	return u;
}

void unionf(int u, int v, struct array_res *parents, struct array_res* sz)
{
	int pu = find(u, parents, sz);
	int pv = find(v, parents, sz);

	if (pu == pv)
		return;

	if (array_res_get(sz, u) < array_res_get(sz, v)) {
		// u goes under v
		array_res_put(parents, pu, pv);
		array_res_put(sz, pv, array_res_get(sz, pv) + array_res_get(sz, pu));
		return;
	}

	array_res_put(parents, pv, pu);
	array_res_put(sz, pu, array_res_get(sz, pv) + array_res_get(sz, pu));

	return;
}

int df(int **auxg, int i, int j, int m, int n, int label, int *count, int* reach)
{
	int vi[] = { 0, 0, -1, 1 };
	int vj[] = { -1, 1, 0, 0 };

	if (auxg[i][j] != -1)
		return -1;

	// mark it as visited
	auxg[i][j] = label;
	if (i == 0)
		*reach = 1;
	(*count)++;

	// go to it's neighbours
	for (int k = 0; k < 4; k++) {
		int ii = i + vi[k];
		int jj = j + vj[k];
		if (ii < 0 || jj < 0 || ii >= m || jj >= n)
			continue;
		df(auxg, ii, jj, m, n, label, count, reach);
	}

	return 0;
}



int* hitBricks(int** grid, int gridRowSize, int *gridColSizes, int** hits, int hitsRowSize, int *hitsColSizes, int* returnSize) {

	int m = gridRowSize;
	int n = gridColSizes[0];
	int hm = hitsRowSize;
	int hn = hitsColSizes[0];
	int i, j;
	int* out = (int*)malloc(hm * sizeof(int));
	int **auxg = (int**)malloc(m * sizeof(int*));
	int label = 1;
	struct array_res *brkcnt = NULL;
	struct array_res *reaches = NULL;
	struct array_res *parents = NULL, *sz = NULL;

	array_res_alloc(&brkcnt, 100);
	array_res_alloc(&reaches, 100);
	*returnSize = hitsRowSize;

	for (i = 0; i < m; i++)
		auxg[i] = (int*)malloc(n * sizeof(int));

	// is this ok?
	//memcpy(auxg, grid, m * n * sizeof(int));
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			auxg[i][j] = (grid[i][j] == 0) ? 0 : -1;


	for (i = 0; i < hm; i++) {
		int ii = hits[i][0];
		int jj = hits[i][1];
		auxg[ii][jj] = 0;
	}

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (auxg[i][j] == -1) {
				int count = 0;
				int reach = 0;
				df(auxg, i, j, m, n, label, &count, &reach);
				array_res_add(brkcnt, count);
				array_res_add(reaches, reach);
				//we need a resizable array - brick counts - per component
				label++;
			}

	// we have label-1 components
	// brk cnt have label-1 elements inxeded from 0
	// time for UF
	if (label - 1 > 0) {
		array_res_alloc(&parents, label - 1);
		array_res_alloc(&sz, label - 1);
	}
	else {
		array_res_alloc(&parents, 1);
		array_res_alloc(&sz, 1);
	}

	for (i = 0; i < label - 1; i++) {
		array_res_add(parents, i);
		array_res_add(sz, 1);
	}

	for (i = hm - 1; i >= 0; i--) {
		int hi = hits[i][0];
		int hj = hits[i][1];
		int vi[] = { 0, 0, -1, 1 };
		int vj[] = { -1, 1, 0, 0 };
		int count = 0;
		int uf[4] = { 0 };
		int nc = 0;

		if (grid[hi][hj] == 0) {
			out[i] = 0;
			continue;
		}

		for (int k = 0; k < 4; k++) {
			int ii = hi + vi[k];
			int jj = hj + vj[k];
			if (ii < 0 || ii >= m || jj < 0 || jj >= n)
				continue;
			if (auxg[ii][jj] == 0)
				continue;
			uf[nc++] = auxg[ii][jj];
		}

		if (nc == 0) {
			array_res_add(parents, label - 1);
			//  label++;
			array_res_add(sz, 1);
			if (hi == 0)
				array_res_add(reaches, 1);
			else
				array_res_add(reaches, 0);
			array_res_add(brkcnt, 1);
			auxg[hi][hj] = label;
			label++;

			out[i] = 0;
			continue;
		}

		// uf now has our labels for union-find
		// loop treats cases where nc = 2, 3, 4
		for (int k = 0; k < nc - 1; k++) {
			// we need to UF here and update count appropriately
			int u = uf[k];
			int v = uf[k + 1];

			int pu = find(u - 1, parents, sz);
			int pv = find(v - 1, parents, sz);
			// if they already are in the same component skip it
			if (pu == pv)
				continue;

			// u and v different componets
			// this will fix parents and sz
			int sz1 = array_res_get(brkcnt, pu);
			int sz2 = array_res_get(brkcnt, pv);

			array_res_put(brkcnt, pu, sz1 + sz2);
			array_res_put(brkcnt, pv, sz1 + sz2);

			int ureaches = array_res_get(reaches, pu);
			int vreaches = array_res_get(reaches, pv);

			if (ureaches && !vreaches) {
				count += sz2;
				array_res_put(reaches, pv, 1);
			}
			else if (vreaches && !ureaches) {
				count += sz1;
				array_res_put(reaches, pu, 1);
			}

			unionf(u - 1, v - 1, parents, sz);
			// if one was reaching and the otehr was not

		}

		int pu = find(uf[0] - 1, parents, sz);
		int val = array_res_get(brkcnt, pu);
		int reach = array_res_get(reaches, pu);

		array_res_put(brkcnt, pu, val + 1);
		auxg[hi][hj] = pu + 1;
		if (!reach && hi == 0) {
			// that particular component now reaches
			// and it did not before
			array_res_put(reaches, pu, 1);
			count = val;
		}

		out[i] = count;
	}

	return out;
}


void Test_803_BricksFallingWhenHit() {

	vector<int> res1 = HitBricks().doit(vector<vector<int>>{ {1, 0, 0, 0}, { 1, 1, 1, 0 } }, vector<vector<int>> { {1, 0} });

	vector<int> res2 = HitBricks().doit(vector<vector<int>>{ {1, 0, 0, 0}, {1, 1, 0, 0}}, vector<vector<int>>{ {1, 1}, {1, 0} });
	//[1,0,1,0,0]
	vector<int> res3 = HitBricks().doit(vector<vector<int>>{ { 1 }, { 1 }, { 1 }, { 1 }, { 1 } }, vector<vector<int>>{ {3, 0}, { 4,0 }, {1, 0}, {0, 0}, {2, 0}});

	return;
}
