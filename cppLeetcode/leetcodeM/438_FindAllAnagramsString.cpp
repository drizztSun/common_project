/*
438. Find All Anagrams in a String

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/
#include <vector>
#include <string>

using std::string;
using std::vector;


class FindAnagrams {

public:
    
    vector<int> doit_slidingwindow(string s, string p) {

        int n = s.size();
        int m = p.size();
        vector<int> Pcount(26,0),Scount(26,0),res; 
        if(s.size() < p.size()) return res; // base case for error cheaking. If s's length is samller than p's then there is not anagram possible
            // This loop is used to create the initial window which will be = p's length;
        // Loop through the strings and just increment the count;
            for(int i = 0;i<m;i++)
            {
                    Pcount[p[i] - 'a']++; 
                    Scount[s[i] - 'a']++;  
            }
        // For the initial window if both the arrays are same then stating index is 0;
        
        if(Pcount == Scount) res.push_back(0);
        
        // This loop is used to slide the window and keep cheaking for the rest of the string;
        for(int i = m;i<n;i++)
        {
            Scount[s[i] - 'a']++; // Once a new element enters the window we should increament it's count in the Scount array;
            Scount[s[i-m] - 'a']--; // Since we include one element in the window we should decrement the count of the element that goes out of the window
            if(Pcount == Scount){
                res.push_back(i - m + 1); // if both the count arrays are same then store the index;
                    }
        }
        return res;
    }
};
