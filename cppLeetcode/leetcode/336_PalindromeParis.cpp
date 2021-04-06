

#include <vector>
#include <unordered_map>
#include <string>
#include <unordered_set>

using namespace std;

class PalindromePairs {

	/*
		336.Palindrome-Pairs
		最直观的想法是将数组里的字符串两两比较，o(n^2)的时间复杂度，每次比较需要遍历两个字符串拼接后的全部长度，所以会超时。

		AC的解法是构建一个集合，遍历字符串数组的过程中，将每个字符串与集合中已有的字符串进行考察，看是否有符合条件的配对。

		首先，将字符串数组按照字符串长度从小到大排列：

			static bool cmp(string a, string b)
			{
				return (a.size()<b.size());
			}

			sort(words.begin(),words.end(),cmp);
		在遍历的过程中，假设string t=words[i];
		遍历t的长度，将t拆分为两部分s1和s2. 注意这样的拆分，可以使s1从空字符串一直变化到t。

		考虑两种情况是符合要求的：
		1.s1的反序已经在集合中，并且s2本身就是回文，这样s1s2s1'构成回文；
		2.s2的反序已经在集合中，并且s1本身就是回文，这样s2's1s2构成回文。

		然后就可以把t添加到集合中，考察下一个t。  

				for (int i=0; i<words.size(); i++)
				{
					string t=words[i];

					for (int k=0; k<=t.size(); k++)
					{
						string s1=t.substr(0,k);
						reverse(s1.begin(),s1.end());
						string s2=t.substr(k,t.size()-k);
						if (Set.find(s1)!=Set.end() && palindrome(s2))
							result.push_back({Map[t],Map[s1]});
							
						s1=t.substr(0,k);
						s2=t.substr(k,t.size()-k);
						reverse(s2.begin(),s2.end());                
						if (Set.find(s2)!=Set.end() && palindrome(s1))
							result.push_back({Map[s2],Map[t]});
							
					}
					
					Set.insert(t);
				}
	*/

	static bool cmp(string a, string b)
    {
        return (a.size()<b.size());
    }
    
    vector<vector<int>> palindromePairs(vector<string>& words) 
    {
        vector<vector<int>>result;
        
        unordered_set<string>Set;
        unordered_map<string,int>Map;
        for (int i=0; i<words.size(); i++)
            Map[words[i]]=i;
            
        std::sort(words.begin(),words.end(),cmp);
        
        for (int i=0; i<words.size(); i++)
        {
            string t=words[i];

            for (int k=0; k<=t.size(); k++)
            {
                string s1=t.substr(0,k);
                reverse(s1.begin(),s1.end());
                string s2=t.substr(k,t.size()-k);
                if (Set.find(s1)!=Set.end() && palindrome(s2))
                    result.push_back({Map[t],Map[s1]});
                    
                s1=t.substr(0,k);
                s2=t.substr(k,t.size()-k);
                reverse(s2.begin(),s2.end());                
                if (Set.find(s2)!=Set.end() && palindrome(s1))
                    result.push_back({Map[s2],Map[t]});
                    
            }
            
            Set.insert(t);
        }
        
        return result;
    }
    
    bool palindrome(string s)
    {
        int i=0; 
        int j=s.size()-1;
        while (i<=j)
        {
            if (s[i]!=s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }

	static bool cmp(string a,string b)
    {
        return a.size()<b.size();
    }
public:
    vector<vector<int>> palindromePairs(vector<string>& words) 
    {
        unordered_set<string>Set;
        unordered_map<string,int>Map;
        for (int i=0; i<words.size(); i++)
            Map[words[i]]=i;

        sort(words.begin(),words.end(),cmp);
        
        vector<vector<int>>results;
        
        for (int i=0; i<words.size(); i++)
        {
            string w = words[i];
            for (int j=0; j<=w.size(); j++)
            {
                if (isPalindrome(w,0,j-1))
                {
                    string w2 = w.substr(j);
                    reverse(w2.begin(),w2.end());
                    if (Set.find(w2)!=Set.end())                    
                        results.push_back({Map[w2],Map[words[i]]});                    
                }                
                if (isPalindrome(w,j,w.size()-1))
                {
                    string w2 = w.substr(0,j);
                    reverse(w2.begin(),w2.end());
                    if (Set.find(w2)!=Set.end())                    
                        results.push_back({Map[words[i]],Map[w2]});                    
                }   
            }            
            Set.insert(words[i]);
        }        
        return results;
    }
    
    bool isPalindrome(string &w, int a, int b)
    {
        while (a<b)
        {
            if (w[a]!=w[b]) return false;
            a++;
            b--;
        }
        return true;
    }    

public:
	vector<vector<int>> doit_hashtable(vector<string>& words) {

		unordered_map<string, int> dict;
		for (auto i = 0; i < words.size(); i++) {
			dict[words[i]] = i;
		}

		vector<vector<int>> res;
		for (auto i = 0; i < words.size(); i++) {

			for (auto j = 0; j < words[i].length() + 1; j++) {

				if (isPalindrome(words[i], j, words[i].length() - 1)) {
					string suffix = words[i].substr(0, j);
					reverse(suffix.begin(), suffix.end());
					if (dict.find(suffix) != dict.end() && dict[suffix] != i) {
						res.push_back({ i, dict[suffix] });
					}
				}
				
				if (j > 0 && isPalindrome(words[i], 0, j-1)) {
					string prefix = words[i].substr(j);
					reverse(prefix.begin(), prefix.end());
					if (dict.find(prefix) != dict.end() && dict[prefix] != i) {
						res.push_back({dict[prefix], i});
					}
				}

			}
		}

		return res;
	}

	bool isPalindrome(string& word, int s, int e) {
		while (s <= e && word[s] == word[e])
			s++, e--;
		return s > e;
	}
};