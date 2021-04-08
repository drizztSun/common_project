/*
 
 # 1044. Longest Duplicate Substring

 # Given a string S, consider all duplicated substrings: (contiguous) substrings of S that occur 2 or more times.
 # (The occurrences may overlap.)

 # Return any duplicated substring that has the longest possible length.
 # (If S does not have a duplicated substring, the answer is "".)


 # Example 1:

 # Input: "banana"
 # Output: "ana"

 # Example 2:

 # Input: "abcd"
 # Output: ""


 # Note:

 # 2 <= S.length <= 10^5
 # S consists of lowercase English letters.
 
 
 */
#include <string>
#include <vector>
#include <unordered_set>
#include <math.h>
#include <unordered_map>

using std::unordered_set;
using std::string;
using std::vector;
using std::unordered_map;


class longestDupSubstring {

    /*
        1044.Longest-Duplicate-Substring
        本题的high level的思想是二分搜索这样的substring最多能有多长。对于一个固定的len，如果能在S里找到两处相同的子串滑窗，那么我们就可以对len的搜索往上调整；反之，我们就必须将len的搜索往下调。

        于是本题转化为，如果快速在S里找到两处相同的、长度都是len的滑窗。比较直观的想法是对每一处滑窗组成的字符串都放入集合，如果看到集合中已经有一个相同的substring了，就意味着duplicate了。但是当len很大的时候，将字符串放入集合的内置hash化操作很耗时。于是rolling hash是比较常见的解决方案。

        Rolling hash的基本思想就是将abcd转化为26进制的0123.将一个数作为key放入集合很轻松。除此之外，对于abcdef这样的字符串，如果已经知道了[abcd]这个子串的hash key是0123，那么再求相邻的[bcde]的hash key 1234就非常高效，只需要将之前的key的最高位数字去掉(a对应的0)、左移一位、加上最低位数字(e对应的4）。用o(1)的时间就能完成。

        总结一下，rolling hash的思想，就是将两个字符串的比较，转化为hash化之后的两个26进制数的比较。但是当len很大时，这个数可能很大，我们通常不得不对一个大数取模再作为hash key。这样就会有两个不同的字符串，但是会对应同一个hash key（26进制数取模后的结果）。针对这种hash collision的情况，我们可以调整base和mod来规避。或者使用两套hash规则来生成两个key，那么不同字符串拥有两个相同key的概率就会大大降低。
    */
    unordered_map<int,int>len2start;

    string longestDupSubstring(string S) 
    {
        int left = 1, right = S.size()-1;
        while (left<right)
        {
            int mid = right - (right-left)/2;
            if (found(S,mid))
                left = mid;
            else
                right = mid - 1;
        }
        if (found(S, left))
            return S.substr(len2start[left],left);
        else
            return "";        
    }

    bool found(string&S, int len)
    {
        unordered_set<long long>Set;
        long long base = 26;
        long long mod = (1l<<32);
        long long hash = 0;

        long long pow_base_len = 1;
        for (int i=0; i<len; i++)        
            pow_base_len = (pow_base_len * base) % mod;                    
            
        for (int i=0; i<S.size(); i++)
        {
            hash = (hash * base + (S[i]-'a')) % mod;
            if (i>=len)            
                hash = (hash - pow_base_len*(S[i-len]-'a') ) % mod;                            

            if (i>=len-1)
            {                
                if (Set.find(hash)!=Set.end())
                {
                    len2start[len] = i-len+1;
                    return true;
                }                
                Set.insert(hash);
            }          
        }
        return false;
    }
public:

    int BASE = 26;
    int MOD = 10007;

    string longestDupSubstring_rollonghash_binary_search(const string& S) {

        // binary search the biggest length of duplicate substring
        int begin = 0, end = S.size(), pos = -1;
        vector<vector<long>> hashTable(MOD);    // self-implemented hash table
        
        while (begin + 1 < end) {
            int mid = (begin + end) / 2;
            pos = kDupSubstring(S, mid, hashTable);
            if (pos != -1) 
                begin = mid;
            else 
                end = mid;
        }
        
        return begin == 0 ? "" : S.substr(kDupSubstring(S, begin, hashTable), begin);
    }

    // check if S has duplicate substring of length K and return position
    int kDupSubstring(const string& S, int K, vector<vector<long>>& hashTable) {
        for (auto& item : hashTable) item.clear();

        // calculate the first hash value for S[0...K)
        long hash = Hash(S, 0, K);
        hashTable[hash].push_back(0);

        // calcluate the remainder of (BASE ^ K) % MOD
        long power = 1;
        for (int idx = 0; idx < K; ++idx) power = (power * BASE) % MOD;

        // rolling hash
        for (int idx = 0; idx + K < S.size();) {
            // calculate next hash of S[idx + 1, ..., idx + K + 1)
            hash = (hash * BASE + S[idx + K] - 'a' - power * (S[idx] - 'a')) % MOD;
            if (hash < 0) hash += MOD;
            ++idx;

            // resolve collision
            for (auto it = hashTable[hash].begin(); it != hashTable[hash].end(); ++it) {
                if (S.compare(idx, K, S, *it, K) == 0) return idx;
            }
            hashTable[hash].push_back(idx);
        }

        return -1;
    }

    long Hash(const string& str, int pos, int len) {
        long ret = 0;
        for (int idx = pos; idx < pos + len; ++idx) {
            ret = (ret * BASE + str[idx] - 'a') % MOD;
        }
        return ret;
    }

public:
    
    string doit_hashtable_binary_search(string S) {
        
        int N = S.length();
        vector<long> nums;
        int base = 26;
        int64_t mod = pow(2, 32);
        
        auto search = [N](int L, int base, int64_t mod, vector<short>& nums){
        
            long int hash = 0;
            for (int i = 0; i < L; i++)
                hash = (hash * base + nums[i]) % mod;
            
            unordered_set<int> seen;
            seen.insert(hash);
            int al = int64_t(pow(base, L)) % mod;
            
            for (int s = 1; s < N - L + 1; s++) {
                hash = (hash * base - nums[s-1] * al + nums[s+L-1]) % mod;
                if (seen.count(hash) != 0) {
                    return s;
                }
                seen.insert(hash);
            }
            return -1;
        };
        
        for (auto c : S) {
            nums.push_back(c - 'a');
        }
        
        int left = 1, right = nums.size();
        
        while (left <= right) {
            int mid = (left + right) / 2;
            
            if (search(mid, base, mod, nums) != -1) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        int s = search(left - 1, base, mod, nums);
        return S.substr(s, left - 1);
    }

    
    string doit_rollinghash_binary_search(string S) 
    {
        int left = 1, right = S.size()-1;
        unordered_map<int,int> len2start;

        auto found = [&](string&S, int len) {

            unordered_set<long long>Set;
            long long base = 26;
            long long mod = (1l<<32);
            long long hash = 0;

            long long pow_base_len = 1;
            for (int i=0; i<len; i++)        
                pow_base_len = (pow_base_len * base) % mod;                    
                
            for (int i = 0; i < S.size(); i++)
            {
                hash = (hash * base + (S[i]-'a')) % mod;
                if (i>=len)            
                    hash = (hash - pow_base_len*(S[i-len]-'a') % mod + mod) % mod;

                if (i>=len-1)
                {                
                    if (Set.find(hash)!=Set.end())
                    {
                        len2start[len] = i-len+1;
                        return true;
                    }                
                    Set.insert(hash);
                }          
            }
            return false;
        };

        while (left < right) {
            int mid = right - (right-left)/2;
            if (found(S,mid))
                left = mid;
            else
                right = mid - 1;
        }

        if (found(S, left)) // Maybe doesn't find target, so call found again.
            return S.substr(len2start[left],left);
        else
            return "";        
    }



public:

    string doit_rollinghash_binary_search(string S) {
        s = move(S);
        createPowr();

        int l = 1, r = s.size(), maxLen = 0, pos = 0;
        while (l < r) {
            int len = (l + r) / 2;
            if (auto [hasDup, i] = isDupExist(len); hasDup) {
                maxLen = len;
                pos = i;
                l = len + 1;
            }
            else r = len;
        }
        return s.substr(pos - maxLen + 1, maxLen);
    }

    std::pair<bool, int> isDupExist(int len) {
        unordered_map<long long, int> m;  //hash, index
        long long hash = 0;
        int i = 0;
        for (; i < len; i++) hash = rollhash(i, len, hash);
        m[hash] = i-1;
        for (; i < s.size(); i++) { 
            hash = rollhash(i, len, hash);
            if (m.count(hash)) {
                int j = m[hash];
                if (s.substr(j - len + 1, len) == s.substr(i - len + 1, len)) return { true, i };
            }
            m[hash] = i;
        }
        return { false, -1 };
    }

    long long rollhash(int i, int len, long long preHash) {
        auto res = preHash;
        if (i - len >= 0)
            res -= powr[len - 1] * (s[i - len] - 'a');
        res = res % mod + mod;
        res *= r; 
        res += (s[i] - 'a');
        return (res + mod) % mod;
    }

    void createPowr() {
        powr.reserve(s.size());
        long long pow = 1;
        for (int i = 0; i < s.size(); i++) {
            powr.push_back(pow);
            pow *= r;
            pow %= mod;
        }
    }

    const long long mod = 1e9 + 7;
    const long long r = 10007;
    vector<long long> powr;
    string s;
    
};