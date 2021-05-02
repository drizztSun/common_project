/*
1711. Count Good Meals


A good meal is a meal that contains exactly two different food items with a sum of deliciousness equal to a power of two.

You can pick any two different foods to make a good meal.

Given an array of integers deliciousness where deliciousness[i] is the deliciousness of the i​​​​​​th​​​​​​​​ item of food, 
return the number of different good meals you can make from this list modulo 109 + 7.

Note that items with different indices are considered different even if they have the same deliciousness value.

 

Example 1:

Input: deliciousness = [1,3,5,7,9]
Output: 4
Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
Example 2:

Input: deliciousness = [1,1,1,3,3,3,7]
Output: 15
Explanation: The good meals are (1,1) with 3 ways, (1,3) with 9 ways, and (1,7) with 3 ways.
 

Constraints:

1 <= deliciousness.length <= 105
0 <= deliciousness[i] <= 220

*/
#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using std::unordered_map;
using std::unordered_set;
using std::vector;
using std::map;

class CountPairs {

public:

    // because search scope is too big, but target sum is just 20 item
    int doit_search_TLE(vector<int>& deliciousness) {

        unordered_map<int, int> buff;
        unordered_set<int> nums;
        for (const auto c: deliciousness) {
            buff[c]++;
            nums.insert(c);
        }        

        vector<int> idx(begin(nums), end(nums));
        constexpr int hmod = 1e9+7;
        int ans = 0;
        
        for (int i = 0; i < idx.size(); i++) {
            
            int n1 = idx[i], v = buff[n1];

            if ((2*n1 & (2*n1-1)) == 0) ans = (ans + v*(v-1)/2) % hmod; 
            
            for (int j = i+1; j < idx.size(); j++) {
                int n2 = idx[j], v2 = buff[n2];
                if (((n1+n2) & (n1+n2-1)) == 0)
                    ans = (ans + v * v2) % hmod;
            }
        }
        
        return ans;
    }


    int doit_hashtable(vector<int>& deliciousness) {
        
        constexpr int hmod = 1e9 + 7;
        unordered_map<int, int> record;
        long long ans = 0;
        
        for (auto d : deliciousness)
        {
            for (int i = 1; i <= (1 << 21); i *= 2)
            {
                if (record.count(i - d))
                    ans += record[i - d];
            }
            
            record[d]++;
        }
        
        return ans % hmod;
    }

    int doit_(vector<int>& A) {
        using ll = long long;
        constexpr int mod = 1e9 + 7;

        unordered_map<int, int> buf;
        for (auto c: A) buf[c]++;

        vector<int> arr;
        for (auto it: buf) arr.push_back(it.first);

        std::sort(begin(arr), end(arr));


        int target = std::pow(2, 21);
        ll res = 0;

        while (target > 0) { 

            int i = 0;
            int j = arr.size() - 1;
            ll tmp = 0;

            while (i <= j)
            {
                if (arr[i] + arr[j] < target)
                {
                    i++;
                }
                else if (arr[i] + arr[j] > target)
                {
                    j--;
                }
                else
                {
                    if (i == j)
                    {
                        ll x = buf[arr[i]];
                        tmp += x * (x-1) / 2;
                        break;
                    }

                    tmp += buf[arr[i]] * buf[arr[j]];
                    if (buf[arr[i]] != 0)
                        i++;
                    j--;
                }
            }
            res += tmp;
            target /= 2;
        }

        return (int)(res % mod);
    }


public:

    int countPairs_best(vector<int> &deli)
    {
        using ll = long long;
        constexpr int mod = 1e9 + 7;

        std::sort(begin(deli), end(deli), [](int a, int b) { return a < b; });
        vector<std::pair<int, ll>> arr;
        ll i = 0;
        ll len = (ll)(deli.size());
        
        while (i < len)
        {
            ll j = i;
            while (j < len && deli[i] == deli[j])
                j++;
            arr.push_back({deli[i], j - i});
            i = j;
        }

        int target = std::pow(2, 21);
        ll res = 0;

        while (target > 0) { 

            i = 0;
            ll j = (ll)(arr.size() - 1);
            ll tmp = 0;

            while (i <= j)
            {
                if (arr[i].first + arr[j].first < target)
                {
                    i++;
                }
                else if (arr[i].first + arr[j].first > target)
                {
                    j--;
                }
                else
                {
                    if (i == j)
                    {
                        ll x = arr[i].second;
                        tmp += x * (x-1) / 2;
                        break;
                    }

                    tmp += arr[i].second * arr[j].second;
                    if (arr[i].first != 0)
                        i++;
                    j--;
                }
            }
            res += tmp;
            target /= 2;
        }

        return (int)(res % mod);
    }
};