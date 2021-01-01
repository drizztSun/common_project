"""
277. Find the Celebrity

Suppose you are at a party with n people (labeled from 0 to n - 1), and among them, there may exist one celebrity.

The definition of a celebrity is that all the other n - 1 people know him/her, but he/she does not know any of them.

Now you want to find out who the celebrity is or verify that there is not one. The only thing you are allowed to do is to ask questions like: "Hi, A. Do you know B?" to get information about whether A knows B.
You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).

You are given a helper function bool knows(a, b) which tells you whether A knows B. Implement a function int findCelebrity(n).
 There will be exactly one celebrity if he/she is in the party. Return the celebrity's label if there is a celebrity in the party. If there is no celebrity, return -1.



Example 1:


Input: graph = [[1,1,0],[0,1,0],[1,1,1]]
Output: 1
Explanation: There are three persons labeled with 0, 1 and 2. graph[i][j] = 1 means person i knows person j,
otherwise graph[i][j] = 0 means person i does not know person j. The celebrity is the person labeled as 1 because both 0 and 2 know him but 1 does not know anybody.
Example 2:


Input: graph = [[1,0,1],[1,1,0],[0,1,1]]
Output: -1
Explanation: There is no celebrity.


Constraints:

n == graph.length
n == graph[i].length
2 <= n <= 100
graph[i][j] is 0 or 1.
graph[i][i] == 1

"""


# The knows API is already defined for you.
# return a bool, whether a knows b
# def knows(a: int, b: int) -> bool:

class FindCelebrity:


    """
    Approach 2: Logical Deduction

    Complexity Analysis

    Time Complexity : O(n).

    Our code is split into 2 parts.

    The first part finds a celebrity candidate. This requires doing n - 1n−1 calls to knows(...) API, and so is O(n)O(n).

    The second part is the same as before—checking whether or not a given person is a celebrity. We determined that this is O(n)O(n).

    Therefore, we have a total time complexity of O(n + n) = O(n)O(n+n)=O(n).

    Space Complexity : O(1).

    Same as above. We are only using constant extra space.
    """
    def doit_(self, n: int) -> int:

        candidate = 0

        for i in range(1, n):
            if knows(candidate, i):
                candidate = i

        for j in range(n):
            if j == candidate: continue

            if knows(candidate, j) or not knows(j, candidate):
                return -1

        return candidate


    """
    Approach 1: Brute Force
    Intuition

    As per the problem statement, for a given person i, we can check whether or not i is a celebrity by using the knows(...) API to see if everybody knows i, and that i know nobody.

    Therefore, the simplest way of solving this problem is to go through each of the people in turn, and check whether or not they are a celebrity.

    Algorithm

    It's best to define a separate isCelebrity(...) function that takes the id number of a specific person and returns true if they are a celebrity and false if not. This avoids the need for complex loop-break conditions, thus keeping the code cleaner.

    One edge case we need to be cautious of is not asking person i if they know themselves. This can be handled by a check for i == j at the start of the main loop of isCelebrity(...) and then simply continue-ing when it is true.

    We don't know what time and space the knows(...) API uses. Because it's not our concern, we'll assume it's O(1)O(1) for the purpose of analysing our algorithm.
    
    Time Complexity : O(n^2) For each of the nn people, we need to check whether or not they are a celebrity.
    
    Checking whether or not somebody is a celebrity requires making 22 API calls for each of the n - 1n−1 other people, for a total of 2 \cdot (n - 1) = 2 \cdot n - 22⋅(n−1)=2⋅n−2 calls. In big-oh notation, we drop the constants, leaving O(n)O(n).
    
    So each of the nn celebrity checks will cost O(n)O(n), giving a total of O(n^2)O(n 
    2
     ).
    
    Space Complexity : O(1)O(1).
    
    Our code only uses constant extra space. The results of the API calls are not saved.
    """

    def doit_bruteforce(self, n: int) -> int:

        def is_celebrity(i: int):

            for j in range(n):
                if i == j: continue

                if konws(i, j) or not knows(j, i):
                    return False

            return True

        for i in range(n):

            if is_celebrity(i):
                return i

        return -1

    """
    
    """









