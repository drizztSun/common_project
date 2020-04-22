/*
 
 
 936. Stamping The Sequence
 
 
 You want to form a target string of lowercase letters.

 At the beginning, your sequence is target.length '?' marks.  You also have a stamp of lowercase letters.

 On each turn, you may place the stamp over the sequence, and replace every letter in the sequence with the corresponding letter from the stamp.  You can make up to 10 * target.length turns.

 For example, if the initial sequence is "?????", and your stamp is "abc",  then you may make "abc??", "?abc?", "??abc" in the first turn.  (Note that the stamp must be fully contained in the boundaries of the sequence in order to stamp.)

 If the sequence is possible to stamp, then return an array of the index of the left-most letter being stamped at each turn.  If the sequence is not possible to stamp, return an empty array.

 For example, if the sequence is "ababc", and the stamp is "abc", then we could return the answer [0, 2], corresponding to the moves "?????" -> "abc??" -> "ababc".

 Also, if the sequence is possible to stamp, it is guaranteed it is possible to stamp within 10 * target.length moves.  Any answers specifying more than this number of moves will not be accepted.

  

 Example 1:

 Input: stamp = "abc", target = "ababc"
 Output: [0,2]
 ([1,0,2] would also be accepted as an answer, as well as some other answers.)
 Example 2:

 Input: stamp = "abca", target = "aabcaca"
 Output: [3,0,1]
 
 
 
 
 
 Approach 1: Work Backwards
 Intuition
 Imagine we stamped the sequence with moves m_1, m_2, Now, from the final position target, we will make those moves in reverse order.

 Let's call the ith window, a subarray of target of length stamp.length that starts at i.
 Each move at position i is possible if the ith window matches the stamp.
 After, every character in the window becomes a wildcard that can match any character in the stamp.

 For example, say we have stamp = "abca" and target = "aabcaca". Working backwards, we will reverse stamp at window 1 to get "a????ca",
 then reverse stamp at window 3 to get "a??????", and finally reverse stamp at position 0 to get "???????".

 Algorithm

 Let's keep track of every window. We want to know how many cells initially match the stamp (our "made" list), and which ones don't (our "todo" list).
 Any windows that are ready (ie. have no todo list), get enqueued.

 Specifically, we enqueue the positions of each character. (To save time, we enqueue by character, not by window.)
 This represents that the character is ready to turn into a "?" in our working target string.

 Now, how to process characters in our queue? For each character, let's look at all the windows that intersect it, and update their todo lists.
 If any todo lists become empty in this manner (window.todo is empty), then we enqueue the characters in window.made that we haven't processed yet.

 Complexity Analysis

 Time Complexity: O(N(N-M)) where M, NM,N are the lengths of stamp, target.

 Space Complexity: O(N(N-M)).
 
 
 */
#include <vector>
using std::vector;

#include <string>
using std::string;

#include <deque>
using std::deque;

#include <unordered_set>
using std::unordered_set;

#include <algorithm>


class MovesToStamp {
    
    int match(string s, string t) {
        int count = 0;
        for (int i = 0; i < s.size(); i++) {
            if (t[i] != '?') count++;
            if (t[i] != '?' && s[i] != t[i]) return 0;
        }
        return count;
    }
    
public:
    
    vector<int> doit1(string stamp, string target) {
        int m = stamp.size(), n = target.size();
        vector<int> res;
        int count = 0;
        while(count < n) {
            int onePass = 0;
            for (int i = 0; i <= n - m; i++) {
                string t = target.substr(i, m);
                int matched = match(stamp, t);
                if (matched) {
                    for (int j = i; j < i+m; j++)
                        target[j] = '?';
                    res.push_back(i);
                }
                onePass += matched;
            }
            if (onePass == 0) break;
            count += onePass;
        }
        if (count < n) return {};
        reverse(res.begin(), res.end());
        return res;
    }
    
    vector<int> doit(string stamp, string target) {
        
        vector<int> ans;
        deque<int> queue;
        int M = stamp.length(), N = target.length();
        vector<bool> done(N, false);
        vector<vector<unordered_set<int>>> A(N, vector<unordered_set<int>>(2));
        
        for (int i = 0; i < N - M + 1; i++) {
            
            for (int j = 0; j < M; j++){
                
                if (stamp[j] == target[i+j])
                    A[i][0].insert(i+j);
                else
                    A[i][1].insert(i+j);
            }
                
                
            if (A[i][1].empty()) {
                ans.push_back(i);
                for (int j = 0; j < M; j++) {
                    if (!done[i+j]) {
                        done[i+j] = true;
                        queue.push_back(i+j);
                    }
                }
            }
        }
            
        
        
        while (!queue.empty()) {
            
            int i = queue.front();
            
            for (int j = std::max(0, i - M + 1); j < std::min(i, N - M) + 1; j++) {
                
                if (A[j][1].count(i) != 0) {
                    
                    A[j][1].erase(i);
                    
                    if (A[j][1].empty()) {
                        ans.push_back(j);
                        for (auto s : A[j][0]) {
                            if (!done[s]) {
                                done[s] = true;
                                queue.push_back(s);
                            }
                        }
                    }
                }
                
            }
            queue.pop_front();
        }
        
        if (std::all_of(done.begin(), done.end(), [](bool r){
            return r == true;}) ) {
            std::reverse(ans.begin(), ans.end());
        } else {
            ans.clear();
        }
        
        return ans;
    }
    
    
    
    // best
    // Idea is to greedily match stamp with target with offset, ignoring already matched characters. Reverse the process idea from
    std::vector<int> doit2(std::string stamp, std::string target) {
        int const ns = stamp.size();
        int const nt = target.size();

        // result cache
        auto res = std::vector<int>();

        // check if we have stamped at certain positions already, if
        // so, no need to check if we should stamp here
        bool stamped[nt-ns+1];
        std::fill(stamped, stamped + (nt-ns+1), false);

        
        while (true) {

            bool keepGoing = false;
            auto vec = std::vector<int>();
            
            for (int i = 0; i<= nt-ns; ++i) {
                if (stamped[i]) {
                    continue;
                }
                
                int currentMatch = 0;
                for (int j = 0; j < ns; ++j) {
                    
                    if (target[i+j] == '*') {
                        if (currentMatch) {
                            break;
                        }
                    } else if (target[i+j] != stamp[j]) {
                        currentMatch = 0;
                        break;
                    } else {
                        ++currentMatch;
                    }
                }
                
                if (currentMatch ) {
                    res.push_back(i);
                    stamped[i] = true;
                    
                    for (int j = i; j < ns + i; ++j) {
                        target[j] = '*';
                    }
                    keepGoing = true;
                }
            }
            
            if (!keepGoing) {
                break;
            }
        }

        for (auto const& ch : target) {
            if (ch != '*') {
                return std::vector<int>();
            }
        }

        std::reverse(res.begin(), res.end());
        return res;
    }
};


void test_936_stamping_the_sequence() {
    
    auto res1 = MovesToStamp().doit2("abc", "ababc");
    
    auto res2 = MovesToStamp().doit2("abca", "aabcaca");
}
