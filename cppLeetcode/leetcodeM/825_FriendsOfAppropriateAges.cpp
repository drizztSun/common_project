/*
825. Friends Of Appropriate Ages


Some people will make friend requests. The list of their ages is given and ages[i] is the age of the ith person. 

Person A will NOT friend request person B (B != A) if any of the following conditions are true:

age[B] <= 0.5 * age[A] + 7
age[B] > age[A]
age[B] > 100 && age[A] < 100
Otherwise, A will friend request B.

Note that if A requests B, B does not necessarily request A.  Also, people will not friend request themselves.

How many total friend requests are made?

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 3
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
 

Notes:

1 <= ages.length <= 20000.
1 <= ages[i] <= 120.

*/

#include <vector>
#include <unordered_map>
#include <algorithm>

using std::unordered_map;
using std::vector;


class FriendRequests {

public:

    int doit_hashtable(vector<int>& ages) {
        
        unordered_map<int, int> cnt;
        
        for (auto c: ages) cnt[c]++;
        
        
        int ans = 0;
        
        for (int ageA = 0; ageA <= 120; ageA++) {
            
            if (cnt.count(ageA) == 0) continue;
            
            for (int ageB = 0; ageB <= 120; ageB++) {
                
                if (cnt.count(ageB) == 0) continue;
                
                if (ageA*0.5 + 7 >= ageB) continue;
                
                if (ageA < ageB) break;
                
                if (ageA < 100 && ageB > 100) break;
                
                ans += cnt[ageA] * cnt[ageB];
                
                if (ageA == ageB) ans -= cnt[ageB];
            }
            
        }
        
        return ans;
    }

    int doit_slidingwindow(vector<int>& ages) {
        vector<int> arr(121);
        for (int i = 0; i < ages.size(); i++) arr[ages[i]]++;

        // int start = 15; // age[B] <= 0.5 * age[A] + 7, it must bigger then 15
        int count = 0, result = 0;

        for (int i = 15, start = 15; i <= 120; i++) {
            
            while (start <= (0.5 * i + 7))
                count -= arr[start++];
            
            count += arr[i];
            result += (count - 1) * arr[i];
        }

        return result;
    }
};