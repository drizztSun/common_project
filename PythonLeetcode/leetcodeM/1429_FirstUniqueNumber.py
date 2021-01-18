"""
1429. First Unique Number

You have a queue of integers, you need to retrieve the first unique integer in the queue.

Implement the FirstUnique class:

FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
int showFirstUnique() returns the value of the first unique integer of the queue, and returns -1 if there is no such integer.
void add(int value) insert value to the queue.
 

Example 1:

Input: 
["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
[[[2,3,5]],[],[5],[],[2],[],[3],[]]
Output: 
[null,2,null,2,null,3,null,-1]
Explanation: 
FirstUnique firstUnique = new FirstUnique([2,3,5]);
firstUnique.showFirstUnique(); // return 2
firstUnique.add(5);            // the queue is now [2,3,5,5]
firstUnique.showFirstUnique(); // return 2
firstUnique.add(2);            // the queue is now [2,3,5,5,2]
firstUnique.showFirstUnique(); // return 3
firstUnique.add(3);            // the queue is now [2,3,5,5,2,3]
firstUnique.showFirstUnique(); // return -1
Example 2:

Input: 
["FirstUnique","showFirstUnique","add","add","add","add","add","showFirstUnique"]
[[[7,7,7,7,7,7]],[],[7],[3],[3],[7],[17],[]]
Output: 
[null,-1,null,null,null,null,null,17]
Explanation: 
FirstUnique firstUnique = new FirstUnique([7,7,7,7,7,7]);
firstUnique.showFirstUnique(); // return -1
firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7]
firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3]
firstUnique.add(3);            // the queue is now [7,7,7,7,7,7,7,3,3]
firstUnique.add(7);            // the queue is now [7,7,7,7,7,7,7,3,3,7]
firstUnique.add(17);           // the queue is now [7,7,7,7,7,7,7,3,3,7,17]
firstUnique.showFirstUnique(); // return 17
Example 3:

Input: 
["FirstUnique","showFirstUnique","add","showFirstUnique"]
[[[809]],[],[809],[]]
Output: 
[null,809,null,-1]
Explanation: 
FirstUnique firstUnique = new FirstUnique([809]);
firstUnique.showFirstUnique(); // return 809
firstUnique.add(809);          // the queue is now [809,809]
firstUnique.showFirstUnique(); // return -1
 

Constraints:

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^8
1 <= value <= 10^8
At most 50000 calls will be made to showFirstUnique and add.



"""
from collections import OrderedDict


class FirstUnique:

    def __init__(self, nums: list):
        self._duplicate = set()
        self._dict = OrderedDict()
        
        for c in nums:
            self.add(c)

    def showFirstUnique(self) -> int:
        return -1 if not self._dict else next(iter(self._dict))

    def add(self, value: int) -> None:
        
        if value in self._duplicate: return
            
        if value in self._dict:
            del self._dict[value]
            self._duplicate.add(value)
            return
                
        self._dict[value] = 0


"""
    Approach 2: Queue and HashMap of Unique-Status
    Intuition

    When given a data-structure-design question like this one, a good strategy is to start simple and identify where the inefficiencies are.

    In Approach 1, we performed numerous count operations; each call to showFirstUnique() performed, in the worst case, NN count operations. At a cost of O(N)O(N) per count, this was expensive! These count-ups are also repetitive, and so should be our focus for optimization.

    When deciding whether or not to return a particular number, all we need to know is whether or not that number is unique. In other words, we only want to know whether it has occurred "once", or "more than once". Seeing as numbers cannot be removed from the FirstUnique data structure, we know that once a particular number is added for the second time, that number will never again be unique.

    So, instead of counting how many times a number occurred in the queue, we could instead keep a HashMap of numbers to booleans, where for each number that has been added, we're storing the answer to the question is this number unique?. We'll call it isUnique. Then, when FirstUnique.add(number) is called, one of three cases will apply:

    This particular number has never been seen before now. Add it to isUnique with a value of true. Also, add it to the queue.

    This particular number has already been seen by isUnique, with a value of true. This means that the number was previously unique (and is currently in the queue), but with this new addition, it no longer is. Update its value to false. Do not add it to the queue.

    This particular number has already been seen by isUnique, with a value of false. This means that it has already been seen twice before. We don't need to do anything, and shouldn't add it to the queue.

    Then, instead of needing to perform "count" operations, the showFirstUnique() can simply look in isUnique for the information it needs.

    Here is an animation showing how this works so far.

    Current
    1 / 26
    This is a good start. However, you might have noticed another inefficiency while watching the animation: the 7 at the front needs to be stepped passed on every call to showFirstUnique(). As soon as the second 7 was added, though, this 7 was no longer unique, and so would never be the answer to a call to showFirstUnique() again (remember, this queue has no deletion operation). Therefore, there is no reason to leave it in the queue—we should remove it so that we don't keep looking at it.

    But, where should we actually do these removals from the queue? In showFirstUnique(), or in add()?

    If we do a removal in the add() method, we'll need to do an O(N)O(N) search of the queue to find the number, and then potentially another to remove it from the queue, (if you're chosen programming language even supports deletions from the middle of a queue!).

    If we do the removal in the showFirstUnique() method, we might sometimes need to do lots of removals before we find a unique number to return. However, it will be faster across all calls to the data structure, because we didn't need to do a search to find the non-unique number like we would have with add(). We'll talk more about this in the time complexity section.

    So, our best option is to do the removals in the showFirstUnique() method.

    We should leave the number's value as false in isUnique, though. Like we said above, a number can never "become" unique again.

    Here is an animation showing the full algorithm.

    Current
    1 / 19
    Algorithm


    Complexity Analysis

    Let KK be the length of the initial array passed into the constructor.

    Let NN be the total number of items added onto the queue so far (including those from the constructor).

    Time complexity :

    constructor: O(K)O(K).

    For each of the KK numbers passed into the constructor, we're making a call to add(). As we will determine below, each call to add() has a cost of O(1)O(1). Therefore, for the KK numbers added in the constructor, we get a total cost of K \cdot O(1) = O(K)K⋅O(1)=O(K).

    add(): O(1)O(1).

    We check the status of the number in a HashMap, which is an O(1)O(1) operation. We also optionally modify its status in the HashMap, which, again, is an O(1)O(1) operation.

    Depending on the status of the number, we add it to the queue, which is again, an O(1)O(1) operation.

    Therefore, we get an O(1)O(1) time complexity for the add() method.

    showFirstUnique(): O(1)O(1) (amortized).

    For this implementation, the showFirstUnique() method needs to iterate down the queue until it finds a unique number. For each unique number it encounters along the way, it removes it. Removing an item from a queue has a cost of O(1)O(1). The total number of these removals we need to carry out is proportional to the number of calls to add(), because each add() corresponds to at most one removal that will ultimately have to happen. Then when we find a unique number, it is an O(1)O(1) operation to return it.

    Because the number of O(1)O(1) removals is proportional to the number of calls to add(), we say that the time complexity amortizes across all calls to add() and showFirstUnique(), giving an overall time complexity of O(1)O(1) (amortized).

    If you're not familiar with amortized time complexity, check out the Wikipedia page.

    Space complexity : O(N)O(N).

    Each number is stored up to once in the queue, and up to once in the HashMap. Therefore, we get an overall space complexity of O(N)O(N).
"""
from collections import deque

class FirstUnique:

    def __init__(self, nums: list):
        self._queue = deque(nums)
        self._is_unique = {}
        for num in nums:
            # Notice that we're calling the "add" method of FirstUnique; not of the queue. 
            self.add(num)
        
    def showFirstUnique(self) -> int:
        # We need to start by "cleaning" the queue of any non-uniques at the start.
        # Note that we know that if a value is in the queue, then it is also in
        # is_unique, as the implementation of add() guarantees this.
        while self._queue and not self._is_unique[self._queue[0]]:
            self._queue.popleft()
        # Check if there is still a value left in the queue. There might be no uniques.
        if self._queue:
            return self._queue[0] # We don't want to actually *remove* the value.
        return -1
        
    def add(self, value: int) -> None:
        # Case 1: We need to add the number to the queue and mark it as unique. 
        if value not in self._is_unique:
            self._is_unique[value] = True
            self._queue.append(value)
        # Case 2 and 3: We need to mark the number as no longer unique.
        else:
            self._is_unique[value] = False


class FirstUnique:

    def __init__(self, nums: list):
        self.is_unique = {}
        self.q = deque()
        for n in nums:
            if n in self.is_unique:
                self.is_unique[n] = False
            else:
                self.is_unique[n] = True
                self.q.append(n)
        self.trim()
        
            
    def trim(self):
        while self.q and self.is_unique[self.q[0]] == False:
            self.q.popleft()

    def showFirstUnique(self) -> int:
        self.trim()
        if self.q:
            return self.q[0]
        return -1

    def add(self, value: int) -> None:
        if value not in self.is_unique:
            self.is_unique[value] = True
            self.q.append(value)
        else:
            self.is_unique[value] = False
            # self.trim()

"""
Approach 3: LinkedHashSet for Queue, and HashMap of Unique-Statuses
Intuition

While an amortized time of O(1)O(1) will always be better than a non-amortized time of a higher complexity class, say, O(N)O(N), non-amortized O(1)O(1) would be even better. The downside of amortized time complexities is that while the average time per method call is "good", some calls might be really slow. Imagine if every one-millionth Google search took 1,000,000 ms, and all the others took 1 ms. The amortized time would be 2 ms, which, in theory, sounds great! However, the one-in-a-million person waiting 16 minutes for their search results won't be very happy with Google! (There would probably be less bad press if every search operation just took 5 ms...).

Is there a way we could remove the amortization from the data structure we designed in Approach 2?

For this to happen, we'd need to have each "removal" happen with its corresponding add(); not during some arbitrary showFirstUnique() call in the future. This is the only way we could avoid having lots of "waiting" removal operations. How does this work, though? Didn't we already decide it was too difficult?

The trouble with doing the removal in the add() method was that it leads to a worst-case O(N)O(N) search of the queue, and potentially a worst-case O(N)O(N) removal from the middle of a queue—if it's even possible (Java doesn't allow removals from the middle of a queue).

Making the actual remove an O(1)O(1) operation isn't too difficult; we simply need to use a LinkedList-based rather than Array-based queue implementation.

Searching a LinkedList for a value is still O(N)O(N), though. The only data structures that supports search in O(1)O(1) time are hash-sets and hash-maps. But these don't maintain the input order; aren't we just going around in circles now?

There is another, not so well known, data structure we can use here: LinkedHashSet. Note that in Python, we can use an OrderedDict to achieve the same functionality. If you have never heard of it, have a look at its specs before reading any further. Can you see how it solves our problem?

A LinkedHashSet is a HashSet-LinkedList hybrid. Like a HashSet, items can be found, updated, added, and removed in O(1)O(1) time. In addition, it puts links between the entries to keep track of the order they were added. Whenever an item is removed from the LinkedHashSet, the links are updated to point to the previous and next, just like they are in an ordinary LinkedList.

In essence, a LinkedHashSet is a type of queue that supports O(1)O(1) removals from the middle! This is exactly what we need to solve the problem. We can now do the removal in the add() method, and know that it is O(1)O(1).

Algorithm


Complexity Analysis

Let KK be the length of the initial array passed into the constructor.

Let NN be the total number of items added onto the queue so far (including those from the constructor).

Time complexity :

constructor: O(K)O(K).

For each of the KK numbers passed into the constructor, we're making a call to add(). As we will determine below, each call to add() has a cost of O(1)O(1). Therefore, for the KK numbers added in the constructor, we get a total cost of K \cdot O(1) = O(K)K⋅O(1)=O(K).

add(): O(1)O(1).

Like before, we're performing a series of O(1)O(1) operations when add() is called. Additionally, we're also removing the number from the queue if it had been unique, but now no longer is. Seeing as the queue is implemented as a LinkedHashSet, the cost of this removal is O(1)O(1).

Therefore, we get an O(1)O(1) time complexity for add().

showFirstUnique(): O(1)O(1).

This time around, the implementation for showFirstUnique() is straightforward. It simply checks whether or not the queue contains any items, and if it does, it returns the first one (without removing it). This has a cost of O(1)O(1).

Space complexity : O(N)O(N).

Each number is stored up to once in the LinkedHashSet, and up to once in the HashMap. Therefore, we get an overall space complexity of O(N)O(N).
"""

# In Python, we have to make do with the OrderedDict class. We can use it as a Set by setting
# the values to None.

from collections import OrderedDict

class FirstUnique:

    def __init__(self, nums: list):
        self._queue = OrderedDict()
        self._is_unique = {}
        for num in nums:
            # Notice that we're calling the "add" method of FirstUnique; not of the queue. 
            self.add(num)
        
    def showFirstUnique(self) -> int:
        # Check if there is still a value left in the queue. There might be no uniques.
        if self._queue:
            # We don't want to actually *remove* the value.
            # Seeing as OrderedDict has no "get first" method, the way that we can get
            # the first value is to create an iterator, and then get the "next" value
            # from that. Note that this is O(1).
            return next(iter(self._queue))
        return -1
        
    def add(self, value: int) -> None:
        # Case 1: We need to add the number to the queue and mark it as unique. 
        if value not in self._is_unique:
            self._is_unique[value] = True
            self._queue[value] = None
        # Case 2: We need to mark the value as no longer unique and then 
        # remove it from the queue.
        elif self._is_unique[value]:
            self._is_unique[value] = False
            self._queue.pop(value)
        # Case 3: We don't need to do anything; the number was removed from the queue
        # the second time it occurred.