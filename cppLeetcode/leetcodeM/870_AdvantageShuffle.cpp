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

public:

    vector<int> doit_sort(vector<int>& A, vector<int>& B) {
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

    vector<int> doit_(vector<int>& A, vector<int>& B) {

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