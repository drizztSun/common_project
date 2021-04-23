/*
870. Advantage Shuffle

Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].

Return any permutation of A that maximizes its advantage with respect to B.

 

Example 1:

Input: A = [2,7,11,15], B = [1,10,4,11]
Output: [2,11,7,15]
Example 2:

Input: A = [12,24,8,32], B = [13,25,32,11]
Output: [24,32,8,12]
 

Note:

1 <= A.length = B.length <= 10000
0 <= A[i] <= 10^9
0 <= B[i] <= 10^9

*/

#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>

using std::sort;
using std::unordered_map;
using std::multiset;
using std::vector;


class AdvantageShuffleCount {


    vector<int> advantageCount(vector<int>& A, vector<int>& B) 
    {
        int n = A.size();
        vector<std::pair<int,int>> BB;

        for (int i=0; i<n; i++) BB.push_back({B[i],i});
        sort(BB.begin(), BB.end());
        sort(A.begin(), A.end());
        
        int j=0;
        vector<int>rets(n,-1);
        for (int i=0; i<n; i++)
        {
            while (j<n && A[j]<=BB[i].first)
                j++;
            if (j<n)
            {
                rets[BB[i].second] = A[j];
                A[j] = -1;
            }                
        }
        
        j = 0;
        for (int i=0; i<n; i++)
        {
            if (rets[i]!=-1) continue;
            while (j<n && A[j]==-1) j++;
            rets[i] = A[j];
            j++;
        }
        return rets;
    }

public:

    vector<int> doit_sort_treemap(vector<int>& A, vector<int>& B) {
        int n=A.size();
        multiset<int> mst;
        for(int i = 0; i < n; i++)
        	mst.insert(A[i]);

        vector<int> ans(n);
        for(int i = 0; i < n; i++){
        	auto it=mst.upper_bound(B[i]);
        	if(it == mst.end())
        		it = mst.begin();
        	ans[i] = *it;
        	mst.erase(it);
        }
        return ans;
    }

    /*
        Approach 1: Greedy
        Intuition

        If the smallest card a in A beats the smallest card b in B, we should pair them. Otherwise, a is useless for our score, as it can't beat any cards.

        Why should we pair a and b if a > b? Because every card in A is larger than b, any card we place in front of b will score a point. 
        We might as well use the weakest card to pair with b as it makes the rest of the cards in A strictly larger, and thus have more potential to score points.

        Algorithm

        We can use the above intuition to create a greedy approach. The current smallest card to beat in B will always be b = sortedB[j]. 
        For each card a in sortedA, we will either have a beat that card b (put a into assigned[b]), or throw a out (put a into remaining).

        Afterwards, we can use our annotations assigned and remaining to reconstruct the answer. Please see the comments for more details.


        Complexity Analysis
        Time Complexity: O(NlogN), where NN is the length of A and B.
        Space Complexity: O(N).
    */

    vector<int> doit_greedy(vector<int>& A, vector<int>& B) {

        std::sort(begin(A), end(A));
        auto sortedB = B;
        std::sort(begin(sortedB), end(sortedB));
        
        unordered_map<int, vector<int>> buff;
        vector<int> useless;
        int j = 0;
        
        for (auto a : A) {
            
            if (a > sortedB[j]) {
                buff[sortedB[j]].push_back(a);
                j++;
            } else {
                useless.push_back(a);
            }
        }
        
        vector<int> res;
        for (auto b: B) {

			auto it = buff.find(b);

			if (it == buff.end() || it->second.empty()) {
				res.push_back(useless.back());
				useless.pop_back();
			}
			else {
				res.push_back(buff[b].back());
				buff[b].pop_back();
			}
        }
        
        return res;
    }
};