/*

321. Create Maximum Number

You are given two integer arrays nums1 and nums2 of lengths m and n respectively. nums1 and nums2 represent the digits of two numbers. You are also given an integer k.

Create the maximum number of length k <= m + n from digits of the two numbers. The relative order of the digits from the same array must be preserved.

Return an array of the k digits representing the answer.

 

Example 1:

Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
Output: [9,8,6,5,3]
Example 2:

Input: nums1 = [6,7], nums2 = [6,0,4], k = 5
Output: [6,7,6,0,4]
Example 3:

Input: nums1 = [3,9], nums2 = [8,9], k = 3
Output: [9,8,9]
 

Constraints:

m == nums1.length
n == nums2.length
1 <= m, n <= 500
0 <= nums1[i], nums2[i] <= 9
1 <= k <= m + n
 

Follow up: Try to optimize your time and space complexity.
*/

#include <vector>
#include <algorithm>
#include <string>

using std::string;
using std::vector;


class CreateMaximumNumber {

	/*
		321.Create-Maximum-Number
		解法1：
		此题的形式比较像双序列DP。令dp[i][j][k]表示考虑第一个数组的前i个数、第二个数组的前j个数、并在其中总共取k个，所能够得到的字典序最大的“字符串”。这是利用了题目中每个数字只有单个digit的特点：字典序更大的字符串一定代表了更大的拼接的“数”。

		dp[i][j][k]有四种来源：

		dp[i-1][j][k-1]+nums1[i]，即第k个元素选为nums1[i]，拼接在dp[i-1][j][k-1]上.
		dp[i][j-1][k-1]+nums2[j]，即第k个元素选为nums2[j]，拼接在dp[i][j-1][k-1]上.
		dp[i-1][j][k]，即第k个元素不为nums1[i]，那么此时的解直接继承自 dp[i-1][j][k].
		dp[i][j-1][k]，即第k个元素不为nums2[j]，那么此时的解直接继承自 dp[i][j-1][k].
		这个解法的时间复杂度是o(M*N*K).

		解法2：
		另一个比较容易理解的算法是：考虑将k拆分成k1和k2，将取数的指标分配给nums1,nums2，遍历所有的可能取最优解。

		于是得到子问题就是：如何在一个给定顺序的数组nums1里取k1个数，使得连接起来的数最大。这个就和 402.Remove K Digits非常相似，贪心法+栈的典型应用（当然用数组也行）。总体的思想就是遍历nums1的过程中，用栈维护一个递减序列（因为递减序列说明是当前的字典序最大），一旦出现递增的元素，则考虑退栈之前的元素，直至栈恢复为递减序列、或者退栈元素数目达到了上限为止。

		然后将处理nums1、nums2得到的两个数组p1、p2进行"归并"。注意，这个归并要求保持p1,p2保持原来的顺序，但归并后得到的数字最大。这个和传统意义的归并排序是有区别的，因为p1,p2本身并不是有序的。这样的“归并”并不容易，不能只依次比较两个数组的首元素。一个比较简单的C++写法就是，利用C++默认的数组大小的比较方法。比如，若p1>p2，说明p1的整体字典序比p2大，我们就首选p1的首元素（这是正解），然后去除p1首元素p1.erase(p1.begin()). 然后比较剩下的p1和p2.

		最后将所有的k的拆分结果再进行比较，同样用到了C++默认的对数组大小比较的定义。不停更新result = max(result, temp)就可以了。

		这个解法的时间复杂度是o(K*K).
			
	*/
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        int K = k;
        int m = nums1.size();
        int n = nums2.size();
        nums1.insert(nums1.begin(), 0);
        nums2.insert(nums2.begin(), 0);

        string dp[m+1][n+1][K+1];        

        for (int i=0; i<=m; i++)
            for (int j=0; j<=n; j++)
                for (int k=1; k<=std::min(K,i+j); k++)
                {
                    dp[i][j][k] = "";
                    if (i-1>=0) dp[i][j][k] = std::max(dp[i][j][k], dp[i-1][j][k-1] + std::to_string(nums1[i]));
                    if (j-1>=0) dp[i][j][k] = std::max(dp[i][j][k], dp[i][j-1][k-1] + std::to_string(nums2[j]));
                    if (i-1>=0) dp[i][j][k] = std::max(dp[i][j][k], dp[i-1][j][k]);
                    if (j-1>=0) dp[i][j][k] = std::max(dp[i][j][k], dp[i][j-1][k]);                    
                }

        vector<int>ret;
        for (int i=0; i<dp[m][n][K].size(); i++)
            ret.push_back(dp[m][n][K][i]-'0');

        return ret;
    }

	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int K) 
    {
        vector<int> ret;
        for (int i=0; i<=K; i++)
        {
            if (i>nums1.size()) continue;
            if (K-i>nums2.size()) continue;
            vector<int>p1 = findMax(nums1, i);
            vector<int>p2 = findMax(nums2, K-i);
            vector<int>temp = merge(p1, p2);
            ret = max(ret, temp);            
        }
        return ret;
    }
    
    vector<int> findMax(vector<int>&nums, int k)
    {
        int drop = nums.size()-k;
        vector<int>ret;
        
        for (int i=0; i<nums.size(); i++)
        {
            while (drop>0 && ret.size()>0 && nums[i] > ret.back())
            {
                ret.pop_back();
                drop--;
            }
            ret.push_back(nums[i]);
        }
        ret.resize(k);
        return ret;
    }
    
    vector<int> merge(vector<int>&p1, vector<int>&p2)
    {
        vector<int>ret;
        int L = p1.size()+p2.size();
        for (int i=0; i<L; i++)
        {
            if (p1 > p2)
            {
                ret.push_back(p1[0]);
                p1.erase(p1.begin());
            }
            else
            {
                ret.push_back(p2[0]);
                p2.erase(p2.begin());
            }                
        }
        return ret;
    }

public:
    
    vector<int> doit_dp(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> ans;
        if(!nums1.size() && !nums2.size() || !k)
            return ans;
        ans.resize(k);
        int n = nums1.size(), m = nums2.size();
        vector<string> dp1(std::min(k, n)), dp2(std::min(k, m));
        vector<string> dpprev1(n), dpcur1(n), dpprev2(m), dpcur2(m);

        for(int i = 0; i < dp1.size(); ++ i){
            string tmpval(i + 1, 0);
            dp1[i] = tmpval;
            if(!i){
                for(int j = 0; j < n; ++ j){
                    dpprev1[j] = "";
                    dpprev1[j] += (char)(nums1[j] + '0');
                    dp1[i] = max(dp1[i], dpprev1[j]);
                    if(j)
                        dpprev1[j] = max(dpprev1[j], dpprev1[j - 1]);

                }
            }else{
                for(int j = i; j < n; ++ j){
                    dpcur1[j] = tmpval;

                    dpcur1[j] = max(dpcur1[j], dpprev1[j - 1] + (char)(nums1[j] + '0'));

                    dp1[i] = max(dp1[i], dpcur1[j]);
                    if(j >= i)
                        dpcur1[j] = max(dpcur1[j], dpcur1[j - 1]);
                }
                dpprev1 = dpcur1;
            }

        }



        for(int i = 0; i < dp2.size(); ++ i){
            string tmpval(i + 1, 0);
            dp2[i] = tmpval;
            if(!i){
                for(int j = 0; j < m; ++ j){
                    dpprev2[j] = "";
                    dpprev2[j] += (char)(nums2[j] + '0');
                    dp2[i] = max(dp2[i], dpprev2[j]);
                    if(j)
                        dpprev2[j] = max(dpprev2[j], dpprev2[j - 1]);
                }
            }else{
                for(int j = i; j < m; ++ j){
                    dpcur2[j] = tmpval;

                    dpcur2[j] = max(dpcur2[j], dpprev2[j - 1] + (char)(nums2[j] + '0'));

                    dp2[i] = max(dp2[i], dpcur2[j]);
                    if(j >= i)
                        dpcur2[j] = max(dpcur2[j], dpcur2[j - 1]);
                }
                dpprev2 = dpcur2;
            }

        }


        string tmpans(k, 0), v = "";

        if(!dp1.size()){
            getAns(v, dp2[k - 1], ans, tmpans);
        }else{
            for(int i = 0; i <= std::min(k, (int)dp1.size()); ++ i){
                if(i == 0){
                    if(dp2.size() >= k)
                        getAns(v, dp2[k - 1], ans, tmpans);
                }else if(i < k){
                    if(dp2.size() >= k - i)
                        getAns(dp1[i - 1], dp2[k - i - 1], ans, tmpans);
                }else{
                    if(dp1.size() >= k)
                        getAns(dp1[k - 1], v, ans, tmpans);
                }
            }

        }

        return ans;
    }

private:
    void getAns(string &s1, string &s2, vector<int> &ans, string &tmpans){
        string res;
        if(!s1.size())
            res = s2;
        else if(!s2.size())
            res = s1;
        else{
            int id1 = 0, id2 = 0;

            while(id1 < s1.size() && id2 < s2.size()){
                if(s1[id1] > s2[id2]){
                    res += s1[id1 ++];
                }else if(s1[id1] < s2[id2]){
                    res += s2[id2 ++];
                }else{
                    if(s1.substr(id1) >= s2.substr(id2))
                        res += s1[id1 ++];
                    else
                        res += s2[id2 ++];
                }
            }
            while(id1 < s1.size())
                res += s1[id1 ++];
            while(id2 < s2.size())
                res += s2[id2 ++];
        }

        if(res > tmpans){
            tmpans = res;
            for(int i = 0; i < res.size(); ++ i)
                ans[i] = (res[i] - '0');
        }
    }
    
    vector<int> getSubMaximumArray(vector<int>& nums, int k) {

        if (nums.size() < k) {
            return vector<int>();
        }

        size_t needRemoved = nums.size() - k;
        vector<int> result;
        
        for (size_t i = 0; i < nums.size(); i++) {

            while (!result.empty() && needRemoved != 0 && result[result.size()-1] < nums[i]) {
                needRemoved -= 1;
                result.pop_back();
            }

            result.push_back(nums[i]);
        }
            
        result.resize(k);
        return result;
    }
    
	vector<int> doit_bfs(vector<int>& nums1, vector<int>& nums2, int k) {

		vector<int> best(k);
		
		for (size_t i = 0; i < k + 1; i++) {
			vector<int> A = getSubMaximumArray(nums1, i);
			vector<int> B = getSubMaximumArray(nums2, k - i);
			
			if (A.size() != i || B.size() != k - i) {
				continue;
			}

			size_t offset1 = 0;
			size_t offset2 = 0;
			vector<int> result;

			while (offset1 < A.size() || offset2 < B.size()) {

				size_t s1 = 0;
				size_t s2 = 0;
				for (size_t s1 = s2 = 0;
					((s1 + offset1) < A.size() && (s2 + offset2) < B.size() && (A[s1 + offset1] == B[s2 + offset2]));
					s1++, s2++);

				//while ((s1 + offset1) < nums1.size() && (s2 + offset2) < nums2.size() && (nums1[s1 + offset1] == nums2[s2 + offset2])) {
				//	s1 += 1;
				//	s2 += 1;
				//}
				size_t item = 0;
				if ((s1 + offset1) < A.size() && (s2 + offset2) < B.size()) {
					if ( A[s1 + offset1] > B[s2 + offset2] ) {
						item = A[offset1];
						offset1 += 1;
					}
					else {
						item = B[offset2];
						offset2 += 1;
					}
				}
				else {
					if ((s1 + offset1) < A.size()) {
						item = A[offset1];
						offset1 += 1;
					} else {
						item = B[offset2];
						offset2 += 1;
					}
				}

				result.push_back(item);
			}

			
			// get Best result 
			best = std::max(best, result);
		}

		return best;
	}



};


// 
class CreateMaximumNumber1 {

public:
	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
		int n1 = nums1.size(), n2 = nums2.size();
		vector<int> best;

		// nums1 i starts from k- n2, because of n2 < k
		// ends up to k, or n1, because at most is n1 because of n1 < k
		for (int k1 = std::max(k - n2, 0); k1 <= std::min(k, n1); ++k1)
			best = max(best, maxNumber(maxNumber(nums1, k1), maxNumber(nums2, k - k1)));

		return best;
	}

	vector<int> maxNumber(vector<int> nums, int k) {
		int drop = nums.size() - k;
		vector<int> out;
		for (int num : nums) {
			while (drop && out.size() && out.back() < num) {
				out.pop_back();
				drop--;
			}
			out.push_back(num);
		}
		out.resize(k);
		return out;
	}

	vector<int> maxNumber(vector<int> nums1, vector<int> nums2) {
		vector<int> out;
		while (nums1.size() + nums2.size()) {
			vector<int>& now = nums1 > nums2 ? nums1 : nums2;
			out.push_back(now[0]);
			now.erase(now.begin());
		}
		return out;
	}
};


class Solution {
public:
#define MIN(a,b) (a<b?a:b)
#define MAX(a,b) (a>b?a:b)
	// create max number of length t from single non-empty vector
	void getMax(int* num, int& len, int* result, int& t, int& sortedLen)
	{
		int n, top = 0;
		result[0] = num[0];
		const int need2drop = len - t;
		for (int i = 1; i < len; ++i) {
			n = num[i];
			while (top >= 0 && result[top] < n && (i - top) <= need2drop) --top; // i - top means already dropped i - top numbers
			if (i - top > need2drop) {
				sortedLen = MAX(1, top);
				while (++top < t) result[top] = num[i++];
				return;
			}
			if (++top < t) result[top] = n;
			else top = t - 1;
		}
	}
	// create max number of different length from single vector
	void dp(int *num, int len, int&sortedLen, int& minL, int& maxL, int *res, int &k) {
		int  j, *head, *prevhead = res;
		const int soi = sizeof(int);
		getMax(num, len, res, maxL, sortedLen);
		for (int l = maxL; l > MAX(minL, 1); --l) {
			head = prevhead + k;
			memcpy(head, prevhead, l*soi);
			for (j = sortedLen; j < l; ++j) {
				if (head[j] > head[j - 1]) {
					sortedLen = MAX(1, j - 1);
					memcpy(head + j - 1, prevhead + j, soi*(l - j));
					break;
				}
			}
			if (j == l) sortedLen = l;
			prevhead = head;
		}
	}
	// merge max number created from single vector
	void merge(int* num1, int len1, int* num2, int len2, int* result, int& resSize) {
		int i = 0, j = 0, k = 0;
		while (i < resSize) {
			if (j < len1 && k < len2) {
				if (num1[j] > num2[k])
					result[i++] = num1[j++];
				else if (num1[j] < num2[k])
					result[i++] = num2[k++];
				else {
					int remaining1 = len1 - j, remaining2 = len2 - k, tmp = num1[j];
					int flag = memcmp(num1 + j, num2 + k, sizeof(int) * MIN(remaining1, remaining2));
					flag = (flag == 0 ? (remaining1>remaining2 ? 1 : -1) : flag);
					int * num = flag > 0 ? num1 : num2;
					int & cnt = flag > 0 ? j : k;
					int len = flag > 0 ? len1 : len2;
					while (num[cnt] == tmp && cnt < len && i<resSize) result[i++] = num[cnt++];
				}
			}
			else if (j < len1) result[i++] = num1[j++];
			else result[i++] = num2[k++];
		}
	}

	vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
		int soi = sizeof(int), len1 = nums1.size(), len2 = nums2.size(), step = k*soi;
		int minL1 = MAX(0, k - len2), maxL1 = MIN(k, len1), minL2 = k - maxL1, maxL2 = k - minL1, range = maxL1 - minL1 + 1;
		int * res = new int[range * k * 2 + 2 * k], *dp1 = res + k, *dp2 = res + range*k + k, *tmp = res + range * 2 * k + k;
		memset(res, 0, step);
		int sortedLen1 = 1, sortedLen2 = 1;
		if (len1 == 0 && len2 > 0) getMax(&nums2[0], len2, res, k, sortedLen2);
		else if (len1 > 0 && len2 == 0) getMax(&nums1[0], len1, res, k, sortedLen2);
		else if (len1 > 0 && len2 > 0) {
			dp(&nums1[0], len1, sortedLen1, minL1, maxL1, dp1, k);
			dp(&nums2[0], len2, sortedLen2, minL2, maxL2, dp2, k);
			if (sortedLen1 + sortedLen2 > k) {
				merge(dp1 + k*(maxL1 - sortedLen1), sortedLen1, dp2 + k*(maxL2 - sortedLen2), sortedLen2, tmp, k);
				vector<int> resv(tmp, tmp + k);
				delete[] res;
				return resv;
			}
			for (int i = minL1; i <= maxL1; ++i) {
				merge(dp1 + k*(maxL1 - i), i, dp2 + k*(maxL2 - k + i), (k - i), tmp, k);
				if (memcmp(res, tmp, step) < 0) memcpy(res, tmp, step);
			}
		}
		vector<int> resv(res, res + k);
		delete[] res;
		return resv;
	}
};

void Test_321_Create_Maximum_Number()
{
	// [3, 4, 6, 5], [9, 1, 2, 5, 8, 3], 5 
	vector<int> nums1 = { 3, 4, 6, 5 };
	vector<int> nums2 = { 9, 1, 2, 5, 8, 3 };

	// [9, 8, 6, 5, 3]
	vector<int> res = CreateMaximumNumber().doit_dp(nums1, nums2, 5);

	vector<int> a = { 6, 7 };
	vector<int> b = { 6, 0, 4 };
	// [6, 7, 6, 0, 4]
	vector<int> res1 = CreateMaximumNumber().doit_dp(a, b, 5);

	vector<int> c = { 3, 9 };
	vector<int> d = { 8, 9 };
	// # [9, 8, 9]
	vector<int> res2 = CreateMaximumNumber().doit_dp(c, d, 3);


	vector<int> e = { 1, 6, 5, 4, 7, 3, 9, 5, 3, 7, 8, 4, 1, 1, 4 };
	vector<int> f = { 4, 3, 1, 3, 5, 9 };
	vector<int> res4 = CreateMaximumNumber().doit_dp(e, f, 21);
	

	return;

}
