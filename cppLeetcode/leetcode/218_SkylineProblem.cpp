/*
# 218 The Skyline Problem


# A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. 
# Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo(Figure A),
# write a program to output the skyline formed by these buildings collectively(Figure B).


# The geometric information of each building is represented by a triplet of integers[Li, Ri, Hi],
# where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively,
# and Hi is its height.It is guaranteed that 0 ? Li, Ri ? INT_MAX, 0 < Hi ? INT_MAX, and Ri - Li > 0.
# You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.

# For instance, the dimensions of all buildings in Figure A are recorded as : [[2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8]] .
# The output is a list of "key points" (red dots in Figure B) in the format of[[x1, y1], [x2, y2], [x3, y3], ...] that uniquely defines a skyline.
# A key point is the left endpoint of a horizontal line segment.Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, 
and always has zero height.Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.

# For instance, the skyline in Figure B should be represented as : [[2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0]].

# Notes :

	# The number of buildings in any input list is guaranteed to be in the range[0, 10000].
	# The input list is already sorted in ascending order by the left x position Li.
	# The output list must be sorted by the x position.
	# There must be no consecutive horizontal lines of equal height in the output skyline.
	# For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three lines of height 5 should be merged into one in the final output as such :
# [...[2 3], [4 5], [12 7], ...]

	# This is a Python version of my modification of dong.wang.1694�s brilliant C++ solution.
	# It sweeps from left to right.But it doesn�t only keep heights of �alive buildings� in the priority queue
	# and it doesn�t remove them as soon as their building is left behind.
	# Instead, (height, right) pairs are kept in the priority queue and they stay in there as long as there�s a larger height in there,
	# not just until their building is left behind.

	# In each loop, we first check what has the smaller x - coordinate: adding the next building from the input,
	# or removing the next building from the queue.In case of a tie, adding buildings wins, as that guarantees correctness(think about it : -).
	# We then either add all input buildings starting at that x - coordinate or we remove all queued buildings ending at that x - coordinate or earlier
# (remember we keep buildings in the queue as long as they�re �under the roof� of a larger actually alive building).
	# And then, if the current maximum height in the queue differs from the last in the skyline, we add it to the skyline.


*/

#include <unordered_map>
#include <vector>
#include <queue>
#include <set>


using namespace std;

class SkylineProblem {

public:

    vector<vector<int>> doit_heap_best(vector<vector<int>>& buildings) {
        
        if (buildings.empty()) return {};
     
        vector<vector<int>> skyline;
        priority_queue<tuple<int, int, int, int>> heap;
        
        for (auto& c : buildings) {
            heap.push({-c[0], c[2], -c[1], c[2]});
        }
        
        auto c = heap.top();
        auto l = std::get<0>(c), h = std::get<1>(c), end = std::get<2>(c), cur = std::get<3>(c);
        heap.pop();
        l = -l, end = -end;
        skyline.push_back({l, cur});
        
        while (!heap.empty()) {
            
            auto c = heap.top();
            auto left = std::get<0>(c), right = std::get<2>(c), height = std::get<3>(c);
            heap.pop();
            left = -left, right = -right;
            
            if (left == end && height != cur) {
                skyline.push_back({end, height});
                
            } else if (left > end) {
                skyline.push_back({end, 0});
                skyline.push_back({left, height});
                
            } else if (left < end) {
                
                if (height > cur) {
                    
                    skyline.push_back({left, height});
                    
                    if (end > right)
                        heap.push({-right, cur, -end, cur});
                    
                } else {
                    if (right > end)
                        heap.push({-end, height, -right, height});
                    continue;
                }
            }
            cur = height;
            end = right;
        }
        
        
        skyline.push_back({end, 0});
        return skyline;
    }

	vector<vector<int>> doit_heap(vector<vector<int>>& buildings) {

        priority_queue<pair<int, int>> rightNd;
        vector<vector<int>> skyline;
        size_t i = 0, x = 0;
        
        std::sort(buildings.begin(), buildings.end(), [](auto& a, auto& b) {
            return a[0] < b[0];
        });

        while (i < buildings.size() || !rightNd.empty()) {

            if (rightNd.empty() || (i < buildings.size() && buildings[i][0] <= rightNd.top().second)) {
                // uphill, there is one or more cross the heightest one
                // if current item i crossed heighest one, we are gonna push it into heap.
                x = buildings[i][0];
                while (i < buildings.size() && buildings[i][0] <= x) {
                    rightNd.push(make_pair(buildings[i][2], buildings[i][1]));
                    i++;
                }
            }
            else {
                // downhill
                x = rightNd.top().second;
                // any item, which x-axis less than x will be drop. because it has less height and x-axis ahead 'x' and could be covered by current top() item.
                // Until there is one less height and greater than x. it is gonna croos with x axis line.
                // the point will be (x, rightNd.top().first)
                while (!rightNd.empty() && rightNd.top().second <= x)
                    rightNd.pop();
            }

            int height = rightNd.empty() ? 0 : rightNd.top().first;

            if (skyline.empty() || height != skyline.back()[1]) {
                skyline.push_back(vector<int>{int(x), height});
            }
        }

        return skyline;
	}


    /*
		The idea is to do line sweep and just process the buildings only at the start and end points.
		The key is to use a priority queue to save all the buildings that are still �alive�.
		The queue is sorted by its height and end time (the larger height first and if equal height,
		the one with a bigger end time first). For each iteration, we first find the current process time,
		which is either the next new building start time or the end time of the top entry of the live queue.
		If the new building start time is larger than the top one end time, then process the one in the queue first
		(pop them until it is empty or find the first one that ends after the new building); otherswise,
		if the new building starts before the top one ends, then process the new building (just put them in the queue).
		After processing, output it to the resulting vector if the height changes. Complexity is the worst case O(NlogN)

		Not sure why my algorithm is so slow considering others Python solution can achieve 160ms, any commments?
	*/
	vector<pair<int, int>> doit(vector<vector<int>>& buildings) {

		std::priority_queue<pair<int, int>> heightQ;
		std::vector<pair<int, int>> skyline;
		int i = 0;

		while (i < buildings.size() || !heightQ.empty()) {
			int x = -1;
			if (heightQ.empty() || (i < buildings.size() && buildings[i][0] <= heightQ.top().second)) {
				x = buildings[i][0];
				while (i < buildings.size() && buildings[i][0] <= x) {
					heightQ.push({buildings[i][2], buildings[i][1]});
					i++;
				}
			}
			else {
				x = heightQ.top().second;
				while (!heightQ.empty() && heightQ.top().second <= x) {
					heightQ.pop();
				}
			}

			int height = heightQ.empty() ? 0 : heightQ.top().first;

			if (skyline.empty() || height != skyline.back().second) {
				skyline.push_back({x, height});
			}
		}

		return skyline;
	}

    vector<vector<int>> doit_heap(vector<vector<int>>& buildings) {

		vector<vector<int>> res;
		int cur = 0, cur_X, cur_H = -1, len = buildings.size();
		priority_queue<pair<int, int>> liveBlg; // first: height, second, end time

		while (cur<len || !liveBlg.empty())
		{ // if either some new building is not processed or live building queue is not empty
			cur_X = liveBlg.empty() ? buildings[cur][0] : liveBlg.top().second; // next timing point to process

			if (cur >= len || buildings[cur][0] > cur_X)
			{ //first check if the current tallest building will end before the next timing point
			  // pop up the processed buildings, i.e. those  have height no larger than cur_H and end before the top one
				while (!liveBlg.empty() && (liveBlg.top().second <= cur_X)) 
					liveBlg.pop();
			}
			else
			{ // if the next new building starts before the top one ends, process the new building in the vector
				cur_X = buildings[cur][0];
				while (cur<len && buildings[cur][0] == cur_X)  // go through all the new buildings that starts at the same point
				{  // just push them in the queue
					liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
					cur++;
				}
			}
			cur_H = liveBlg.empty() ? 0 : liveBlg.top().first; // outut the top one
			if (res.empty() || (res.back()[1] != cur_H)) 
				res.push_back({cur_X, cur_H});
		}

		return res;
    }

    vector<pair<int, int>> doit(vector<vector<int>>& buildings) {

		priority_queue<pair<int, int>> rightNd;
		vector<pair<int, int>> skyline;
		size_t i = 0, x = 0;

		while (i < buildings.size() || !rightNd.empty()) {

			if (rightNd.empty() || (i < buildings.size() && buildings[i][0] <= rightNd.top().second)) {

				x = buildings[i][0];
				while (i < buildings.size() && buildings[i][0] <= x) {
					rightNd.push(make_pair(buildings[i][2], buildings[i][1]));
					i++;
				}
			}
			else {

				x = rightNd.top().second;
				while (!rightNd.empty() && rightNd.top().second <= x)
					rightNd.pop();
			}


			int height = rightNd.empty() ? 0 : rightNd.top().first;

			if (skyline.empty() || height != skyline.back().second) {
				skyline.push_back(make_pair(x, height));
			}
			
		}

		return skyline;
	}

    /*
        218.The-Skyline-Problem
        ---

        解法1:有序容器
        此题需要设置一个multiSet记录所有的当前下降沿的高度，则*prev(Set.end(),1)就是这个Set里的最大值。

        首先，将所有的edges放入一个数组，按时间顺序排序，然后顺次遍历考虑：如果是上升沿，则在Set里加入对应高度（即添加一个上升沿）；如果是下降沿，则需要在Set里删除对应的高度（即退出当前的下降沿）。

        那何时对results进行更新呢？我们在每次处理edge时，不管是加入上升边沿还是退出下降沿之后，都意味着天际线有可能变动。天际线会变成什么呢？答案是此时Set里的最大值！回想一下，Set里装的是所有当前仍未退出的下降沿，说明他们都在当前可以撑起对应的高度。那么Set里的最大值就是当前天际线的最高值。

        所以每次查看一个edges，我们都要比较当前的高度（用cur记录）和Set里的最大值进行比较：一旦不同，就用Set里的最大值去加入results，同时也要更新cur。

        有一个细节需要注意，在生成edges数组时，如果某一个位置同时有上升沿也有下降沿，注意要先考察上升沿，再考察下降沿。也就是要先加入一个上升沿，再退出可能的下降沿。否则类似[[0,2,3],[2,5,3]]的测试例子就会有问题。

        ---
        解法2:线段树
        此题类似 699. Falling Squares 的方法,采用改造的线段树模型.同样,这里每个区间的status表示该区间内的maxHeight.

        在设计setStatus(a,b,s)函数时,目标是对区间[a,b)内的高度进行更新（也就是小于s的部分拉高至s，大于s的部分不变）。我们在具体遍历到某个节点时，注意只是对[start,end)其中那些status<s的子区间进行更新。所以我们需要必要的分情况讨论。

                int setStatus(int a, int b, int s)
                {
                        // 边界条件1. [a,b]与该节点的线段区间[start,end)不相交，返回原先的状态
                    if (begin>=b || end<=a)                     
                        return status;                        
                        
                        // 边界条件2. [a,b]包括了该节点的整个线段区间[start,end)，并且该区间的status<s，说明整体都要被更新为更大的值s，所以其内部全部抹平。
                    if (a<=begin && end<=b && status<=s)        
                    {
                        remove(left);
                        remove(right);
                        return status = s;
                    }         
                    
                        // 边界条件3. [a,b]包括了该节点的整个线段区间[start,end)，但该区间的status>s 且无子树，这说明该节点的线段区域整体都比s还高，我们什么都不用做。
                    if (a<=begin && end<=b && status>s && !left)    
                    {
                        return status;
                    }         
                    
                        // 其他所有情况，我们需递归考虑其子树
                    if (!left)                         
                    {
                        int mid = (end-begin)/2+begin;
                        left = new SegTree(begin,mid,status);
                        right = new SegTree(mid,end,status);
                    }            
                    int leftStatus = left->setStatus(a,b,s);
                    int rightStatus = right->setStatus(a,b,s);
                    return status = max(leftStatus,rightStatus);
        }
        注意,因为本题不要求动态地查询区间，所以不需要设计getStatus(x,y)。当全部setStatus操作结束之后，用DFS将所有区间都抽取出来就行。

        另外，本题中setStatus并不会合并相邻的高度相同的区间，所以通过DFS抽取后的区间集合仍然要在做合并的处理。
    
    */
    class SegTree
    {
        public:
        int start,end,status;
        SegTree* left;
        SegTree* right;
        SegTree(int a, int b, int s):start(a),end(b),status(s),left(NULL),right(NULL){}
        
        void remove(SegTree* &node)
        {
            if (node==NULL) return;
            remove(node->left);
            remove(node->right);
            delete node;
            node = NULL;
            return;            
        }
        
        void setStatus(int a, int b, int s)
        {
            if (a>=end || b<=start)
                return;
            if (a<=start && b>=end && s>=status)
            {
                remove(left);
                remove(right);
                status = s;
                return;
            }
            if (a<=start && b>=end && s<status && left==NULL)
                return;
            if (left==NULL)
            {
                int mid = start+(end-start)/2;
                left = new SegTree(start,mid,status);
                right = new SegTree(mid,end,status);
            }
            left->setStatus(a,b,s);
            right->setStatus(a,b,s);
            status = max(left->status,right->status);            
        }
    };

public:
    vector<pair<int,int>>results;
    vector<pair<int, int>> doit_segmenttree(vector<vector<int>>& buildings) 
    {
        if (buildings.size()==0) return {};
        
        SegTree* root = new SegTree(0,INT_MAX,0);
        for (auto q:buildings)
            root->setStatus(q[0],q[1],q[2]);
        
        DFS(root);
        if (results.back().second!=0) results.push_back({INT_MAX,0});
        
        vector<pair<int,int>>filteredResults;
        for (auto p: results)
        {
            if (filteredResults.size()!=0 && p.second==filteredResults.back().second)
                continue;
            filteredResults.push_back({p.first,p.second});
        }
        if (filteredResults.size()!=0 && filteredResults[0].second==0) filteredResults.erase(filteredResults.begin());
        return filteredResults;
    }
    
    void DFS(SegTree* node)
    {        
        if (node->left==NULL)
            results.push_back({node->start,node->status});
        else
        {
            DFS(node->left);
            DFS(node->right);
        }
    }

    vector<pair<int, int>> doit_heap_1(vector<vector<int>>& buildings) 
    {
        vector<vector<int>>edges;
        for (int i=0;i<buildings.size(); i++)
        {
            edges.push_back({buildings[i][0],-buildings[i][2]});
            edges.push_back({buildings[i][1],buildings[i][2]});
        }
        
        sort(edges.begin(),edges.end());
        
        multiset<int>Set={0};        
        vector<pair<int, int>>results;
        int cur=0;
        
        for (int i=0; i<edges.size(); i++)
        {
            if (edges[i][1]<0) 
                Set.insert(-edges[i][1]);
            else
                Set.erase(Set.lower_bound(edges[i][1]));
            
            int H=*Set.rbegin();
            if (cur!=H)
                results.push_back({edges[i][0],H});
            cur=H;
        }
        
        return results;
    }

// _lazy_segmenttree

    class SegTreeNode
    {
        public:
        SegTreeNode* left;
        SegTreeNode* right;
        int start, end;
        int info;       
        int tag;
        SegTreeNode(int a, int b):start(a),end(b),info(0),tag(0),left(NULL),right(NULL){}
    };
    
    void init(SegTreeNode* node, int a, int b)  // init for range [a,b]
    {                        
        if (a==b)
        {
            node->info = 0;
            return;
        }
        int mid = (a+b)/2;
        if (node->left==NULL)
        {
            node->left = new SegTreeNode(a, mid);
            node->right = new SegTreeNode(mid+1, b);
        }
        init(node->left, a, mid);
        init(node->right, mid+1, b);
                
        node->info = 0;  // write your own logic
    }
    
    void updateRange(SegTreeNode* node, int a, int b, int val)
    {        
        if (b < node->start || a > node->end ) 
            return;
        if (node->start == node->end)
        {
            node->info = max(node->info, val);
            return;
        }        
        if (a <= node->start && node->end <=b && val >= node->info)
        {
            // write your own logic            
            node->info = val;    
            node->tag = 1;   
            return;
        }
        
        pushDown(node);        
        node->info = max(node->info, val);
        
        updateRange(node->left, a, b, val);
        updateRange(node->right, a, b, val);                
    }
    
   
    void pushDown(SegTreeNode* node)
    {
        if (node->tag!=0)
        {
            node->left->info = node->info;
            node->right->info = node->info;
            node->left->tag = 1;
            node->right->tag = 1;
            node->tag = 0;
        }        
    }    
    
    vector<pair<int,int>>height; // {idx, h}
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) 
    {
        set<int>Set;
        for (auto & building: buildings)
        {
            Set.insert(building[0]);
            Set.insert(building[1]);
        }
        int id = 0;
        unordered_map<int,int>pos2idx;
        unordered_map<int,int>idx2pos;
        for (auto x:Set)
        {
            pos2idx[x] = id;
            idx2pos[id] = x;
            id++;
        }
        
        int n = pos2idx.size();
        SegTreeNode* root = new SegTreeNode(0, n-1);
        init(root, 0, n-1);
        
        sort(buildings.begin(), buildings.end(), [](vector<int>&a, vector<int>&b){return a[2]<b[2];});
        
        for (auto & building: buildings)
        {
            updateRange(root, pos2idx[building[0]], pos2idx[building[1]]-1, building[2]); 
        }
        
        DFS(root);
                
        vector<vector<int>>rets;
        for (int i=0; i<height.size(); i++)
        {
            auto [idx, h] = height[i];
            rets.push_back({idx2pos[idx], h});
            while (i+1 < height.size() && height[i+1].second == height[i].second)
                i++;
        }
        return rets;
    }
    
    void DFS(SegTreeNode* node)
    {
        if (node->start==node->end || node->tag==1)
        {
            height.push_back({node->start, node->info});
            return;
        }
        DFS(node->left);
        DFS(node->right);
    }
};