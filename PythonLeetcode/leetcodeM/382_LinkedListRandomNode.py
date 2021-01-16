"""
382. Linked List Random Node


Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.



Example 1:

Input
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
Output
[null, 1, 3, 2, 2, 3]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // return 1
solution.getRandom(); // return 3
solution.getRandom(); // return 2
solution.getRandom(); // return 2
solution.getRandom(); // return 3
// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.


Constraints:

The number of nodes in the linked list will be in the range [1, 104]
-104 <= Node.val <= 104
At most 104 calls will be made to getRandom.


Follow up:

What if the linked list is extremely large and its length is unknown to you?
Could you solve this efficiently without using extra space?


Solution
Overview
The solution for this problem could be as simple as it sounds, i.e. sampling from a linked list. However, with the constraint raised by the follow-up question, it becomes more interesting.

As a spoiler alert, in this article we will present an algorithm called Reservoir sampling which is a family of randomized algorithms for sampling from a population of unknown size.

"""
import random

"""
    Approach 1: Fixed-Range Sampling
    Intuition

    First of all, let us talk about the elephant in the room. Yes, the problem could be as simple as choosing a random sample from a list, which in our case happens to be a linked list.

    If we are given an array or a linked list with a known size, then it would be a no brainer to solve the problem.

    One of the most intuitive ideas would be that we convert the linked list into an array. With the array, we would know its size and moreover we could have an instant access to its elements.

    Algorithm

    We are asked to implement two interfaces in the object, namely the init(head) and getRandom() functions.

    The init(head) function would be invoked once when we construct the object. Within which, intuitively we could convert the given linked list into an array for later reuse.

    Concerning the getRandom() function, with the linked list converted into an array, we could simply sample from this array.


    The above solution is simple, which happens to be fast as well. But it comes with two caveats:

    It requires some space to keep the pool of elements for sampling, which does not meet the constraint asked in the follow-up question, i.e. a solution of constant space.

    It cannot cope with the scenario that we have a list with ever-growing elements, i.e. we don't have unlimited memory to hold all the elements. For example, we have a stream of numbers, and we would like to pick a random number at any given moment. With the above naive solution, we would have to keep all the numbers in the memory, which is not scalable.

    We will address the above caveats in the next approach.

    Complexity Analysis

    Time Complexity:

    For the init(head) function, its time complexity is O(N) where NN is the number of elements in the linked list.

    For the getRandom() function, its time complexity is O(1). The reason is two-fold: it takes a constant time to generate a random number and the access to any element in the array is of constant time as well.

    Space Complexity: \mathcal{O}(N)O(N)

    The overall solution requires \mathcal{O}(N)O(N) space complexity, since we make a copy of elements from the input list.

"""
class LinkedListRandomNode:

    def __init__(self, head: 'ListNode'):
        """
        @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node.
        """
        self.range = []
        while head:
            self.range.append(head.val)
            head = head.next

    def getRandom(self) -> int:
        """
        Returns a random node's value.
        """
        pick = int(random.random() * len(self.range))
        return self.range[pick]


"""
Approach 2: Reservoir Sampling
Intuition

In order to do random sampling over a population of unknown size with constant space, the answer is reservoir sampling. As one will see later, it is an elegant algorithm that can address the two caveats of the previous approach.

The reservoir sampling algorithm is intended to sample k elements from an population of unknown size. In our case, the k happens to be one.

Furthermore, the reservoir sampling is a family of algorithms which includes several variants over the time. Here we present a simple albeit slow one, also known as Algorithm R by Alan Waterman.

# S has items to sample, R will contain the result
def ReservoirSample(S[1..n], R[1..k])
  # fill the reservoir array
  for i := 1 to k
      R[i] := S[i]

  # replace elements with gradually decreasing probability
  for i := k+1 to n
    # randomInteger(a, b) generates a uniform integer
    #   from the inclusive range {a, ..., b} *)
    j := randomInteger(1, i)
    if j <= k
        R[j] := S[i]
reservoir sampling

We summarize the main idea of the algorithm as follows:

Initially, we fill up an array of reservoir R[] with the heading elements from the pool of samples S[]. At the end of the algorithm, the reservoir will contain the final elements we sample from the pool.

We then iterate through the rest of elements in the pool. For each element, we need to decide if we want to include it in the reservoir or not. If so, we will replace an existing element in reservoir with the current element.

One important question that one might have is that how we can ensure that each element has an equal probability to be chosen.

Given the above algorithm, it is guaranteed that at any moment, for each element scanned so far, it has an equal chance to be selected into the reservoir.

Here we provide a simple proof.

Suppose that we have an element at the index of i (and i > k), when we reach the element, the chance that it will be selected into the reservoir would be \frac{k}{i} 
i
k
​	
 , as we can see from the algorithm.

Later on, there is a chance that any chosen element in the reservoir might be replaced with the subsequent element. More specifically, when we reach the element j (j > i), there would be a chance of \frac{1}{j} 
j
1
​	
  for any specific element in the reservoir to be replaced. Because for any specific position in the reservoir, there is \frac{1}{j} 
j
1
​	
  chance that it might be chosen by the random number generator. On the other hand, there would be \frac{j-1}{j} 
j
j−1
​	
  probability for any specific element in the reservoir to stay in the reservoir at that particular moment of sampling.

To sum up, in order for any element in the pool to be chosen in the final reservoir, a series of independent events need to occur, namely:

Firstly, the element needs to be chosen in the reservoir when we reach the element.
Secondly, in the following sampling, the element should remain in the reservoir, i.e. not to be replaced.
Therefore, for a sequence of length n, the chance that any element ends up in the final reservoir could be represented in the following formula:

\frac{k}{i} \cdot \frac{i}{i+1} \cdot \frac{i+1}{i+2} ... \frac{n-1}{n} = \frac{k}{n} 
i
k
​	
 ⋅ 
i+1
i
​	
 ⋅ 
i+2
i+1
​	
 ... 
n
n−1
​	
 = 
n
k
​	
 

Algorithm

Given the intuition above, we can now put it into implementation as follows:

In the init() function, we simply keep the head of the linked list, rather than converting it into array.

In the getRandom() function, we then do a reservoir sampling starting from the head of the linked list. 
More specifically, we scan the element one by one and decide whether we should put it into the reservoir (which in our case case happens to be of size one).

"""

class Solution:
    def __init__(self, head: ListNode):
        """
        @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node.
        """
        self.head = head

    def getRandom(self) -> int:
        """
        Returns a random node's value.
        """
        scope = 1
        chosen_value = 0
        curr = self.head

        while curr:
            # decide whether to include the element in reservoir
            if random.random() < 1 / scope:
                chosen_value = curr.val
            # move on to the next node
            curr = curr.next
            scope += 1
        return chosen_value