/*
 
 # 1023. Camelcase Matching

 # A query word matches a given pattern if we can insert lowercase letters to the pattern word so that it equals the query.
 # (We may insert each character at any position, and may insert 0 characters.)

 # Given a list of queries, and a pattern, return an answer list of booleans, where answer[i] is true if and only if queries[i] matches the pattern.


 # Example 1:

 # Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
 # Output: [true,false,true,true,false]
 # Explanation:
 # "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
 # "FootBall" can be generated like this "F" + "oot" + "B" + "all".
 # "FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".

 # Example 2:

 # Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
 # Output: [true,false,true,false,false]
 # Explanation:
 # "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
 # "FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".

 # Example 3:

 # Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
 # Output: [false,true,false,false,false]
 # Explanation:
 # "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".
 
 */
#include <algorithm>
#include <vector>
#include <string>
using std::string;
using std::vector;

class CamelMatch {

public:
    
    bool isMatch(const string& query, const string& pattern) {
        
        int i = 0, j = 0;
        
        while (i < query.length() && j < pattern.length()) {
            
            int e = j+1;
            while (e < pattern.length() && pattern[e] > 96)
                e++;

            if (i + e - j >= query.length() || pattern.substr(j, e - j) != query.substr(i, e - j))
                return false;
            
            do {
                i++;
            } while (i < query.length() && query[i] > 96);
            
            j = e;
        }
        
        return i == query.length() && j == pattern.length();
    }
    
    vector<bool> doit(vector<string>&& queries, string pattern) {
        
        vector<bool> res;
        
        std::transform(queries.begin(), queries.end(), std::back_inserter(res), [pattern](const string& query) -> bool{
            size_t j = 0;
            for (size_t i = 0; i < query.length(); i++) {
                if (j < pattern.length() && query[i] == pattern[j]) {
                    j++;
                } else if (query[i] <= 'Z') {
                    return false;
                }
            }
            return j == pattern.length();
        });
        
        return res;
    }
};


void test_1023_CamlcaseMatching() {
    
    auto res1 = CamelMatch().doit(vector<string>{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FB");
                                  
    auto res2 = CamelMatch().doit(vector<string>{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FoBa");
    
    auto res3 = CamelMatch().doit(vector<string>{"FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"}, "FoBaT");
    
    return;
}
