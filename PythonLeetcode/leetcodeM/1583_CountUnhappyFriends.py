"""
1583. Count Unhappy Friends


You are given a list of preferences for n friends, where n is always even.

For each person i, preferences[i] contains a list of friends sorted in the order of preference. 
In other words, a friend earlier in the list is more preferred than a friend later in the list. Friends in each list are denoted by integers from 0 to n-1.

All the friends are divided into pairs. The pairings are given in a list pairs, where pairs[i] = [xi, yi] denotes xi is paired with yi and yi is paired with xi.

However, this pairing may cause some of the friends to be unhappy. A friend x is unhappy if x is paired with y and there exists a friend u who is paired with v but:

x prefers u over y, and
u prefers x over v.
Return the number of unhappy friends.

 

Example 1:

Input: n = 4, preferences = [[1, 2, 3], [3, 2, 0], [3, 1, 0], [1, 2, 0]], pairs = [[0, 1], [2, 3]]
Output: 2
Explanation:
Friend 1 is unhappy because:
- 1 is paired with 0 but prefers 3 over 0, and
- 3 prefers 1 over 2.
Friend 3 is unhappy because:
- 3 is paired with 2 but prefers 1 over 2, and
- 1 prefers 3 over 0.
Friends 0 and 2 are happy.
Example 2:

Input: n = 2, preferences = [[1], [0]], pairs = [[1, 0]]
Output: 0
Explanation: Both friends 0 and 1 are happy.
Example 3:

Input: n = 4, preferences = [[1, 3, 2], [2, 3, 0], [1, 3, 0], [0, 2, 1]], pairs = [[1, 3], [0, 2]]
Output: 4
 

Constraints:

2 <= n <= 500
n is even.
preferences.length == n
preferences[i].length == n - 1
0 <= preferences[i][j] <= n - 1
preferences[i] does not contain i.
All values in preferences[i] are unique.
pairs.length == n/2
pairs[i].length == 2
xi != yi
0 <= xi, yi <= n - 1
Each person is contained in exactly one pair.

"""


class UnhappyFriends:

    def doit_hashtable(self, n: int, preferences: list, pairs: list) -> int:
        """
        72% faster O(n^2), 44% less mem O(n)
        """
        # keep track of people & their paired partner
        seen_pairs = {}
        for pair in pairs:
            seen_pairs[pair[0]] = pair[1]
            seen_pairs[pair[1]] = pair[0]
        
        # keep track of people that would rather prefer someone else over their current partner
        more_preferred = {}
        for i in range(len(preferences)):
            for preference in preferences[i]:
                if preference == seen_pairs[i]:
                    break
                if i not in more_preferred:
                    more_preferred[i] = []
                more_preferred[i].append(preference)
        
        # if both person in more_preferred feel same way abt each other, increment unhappy
        # [A, B] if A, B is in more prefered, 
        unhappy = 0
        for person, preferences in more_preferred.items():
            for friend in preferences:
                if friend in more_preferred and person in more_preferred[friend]:
                    unhappy += 1
                    # don't remove anything, just keep for next check
                    break
                    
        return unhappy

    """
        Explanation
        In the first step we create a list of size n which stores a dictionary for each person. Each dictionary contains the preferences of the other person for a given person. 
        In the second step we loop through the pairs and create a hashtable of size n which enables the access to a paired person for a given person in constant time. 
        In the final step we loop through the (x, y) pairs and for each pair, we loop through all persons u which are to the left of y in the list of preferences for x. 
        For all u we access the paired person v and check if x is to the left of v in the list of preferences for u. 
        This is accomplished by comparing the indices of x and v in terms of index(x) < index(v) which are accessable through the dictionary for person u. 
        If this condition is met, we have found an unhappy friend x. We also repeat this processing with x and y being swapped.

        Runtime Complexity
        O(n^2): Expected overall runtime complexity.

        O(n^2): Exptected runtime for assigning the position (index) to each remaining person in the list of preferences for each person.
        O(n): For looping through all pairs to create the hashtable which links each person to his/her partner (n / 2 pairs in total).
        O(n^2): Expected runtime for possibly looping through all (n - 2) persons for each person (if the partner is placed at the end of the preference list).

        Space Complexity
        O(n^2): Overall space complexity.

        O(n): For the hashtable which links each person to his partner.
        O(n^2): For the list which holds a dictionary of size (n - 1) for each person.
    """
    def doit_(self, n: int, preferences: list, pairs: list) -> int:
        person_to_preferences = [None] * n
        unhappy_friends = 0
        
        for i in range(n):
            friend_to_preference = {}
            
            for j in range(len(preferences[i])):
                friend_to_preference[preferences[i][j]] = j
                
            person_to_preferences[i] = friend_to_preference
            
        person_to_paired = [None] * n
        
        for pair in pairs:
            person_to_paired[pair[0]] = pair[1]
            person_to_paired[pair[1]] = pair[0]
            
        for pair in pairs:
            for j in range(2):
                x = pair[0]
                y = pair[1]
                i = 0

                while(preferences[x][i] != y):
                    u = preferences[x][i]
                    v = person_to_paired[u]

                    if person_to_preferences[u][x] < person_to_preferences[u][v]:
                        unhappy_friends += 1
                        break
                        
                    i += 1

                pair = (pair[1], pair[0],)
                
        return unhappy_friends

        