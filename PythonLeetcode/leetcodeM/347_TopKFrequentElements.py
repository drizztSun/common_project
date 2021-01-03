"""

347. Top K Frequent Elements

Given a non-empty array of integers, return the k most frequent elements.

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]
Example 2:

Input: nums = [1], k = 1
Output: [1]
Note:

You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
You can return the answer in any order.

"""

class TopKFrequent:



    def def doit_heap(self, nums: list, k: int) -> list:
        
        from heapq import heapify, heappop
        from collections import Counter
        
        cnt = Counter(nums)
        buf = [(-val, -key) for key, val in cnt.items()]

        res = []
        heapify(buf)
        for i in range(k):
            res.append(-heappop(buf)[1])
        return res
    
    """
    Approach 1: Heap
    Let's start from the simple heap approach with \mathcal{O}(N \log k)O(Nlogk) time complexity. To ensure that \mathcal{O}(N \log k)O(Nlogk) is always less than \mathcal{O}(N \log N)O(NlogN), the particular case k = Nk=N could be considered separately and solved in \mathcal{O}(N)O(N) time.

    Algorithm

    The first step is to build a hash map element -> its frequency. In Java, we use the data structure HashMap. Python provides dictionary subclass Counter to initialize the hash map we need directly from the input array.
    This step takes \mathcal{O}(N)O(N) time where N is a number of elements in the list.

    The second step is to build a heap of size k using N elements. To add the first k elements takes a linear time \mathcal{O}(k)O(k) in the average case, and \mathcal{O}(\log 1 + \log 2 + ... + \log k) = \mathcal{O}(log k!) = \mathcal{O}(k \log k)O(log1+log2+...+logk)=O(logk!)=O(klogk) in the worst case. It's equivalent to heapify implementation in Python. After the first k elements we start to push and pop at each step, N - k steps in total. The time complexity of heap push/pop is \mathcal{O}(\log k)O(logk) and we do it N - k times that means \mathcal{O}((N - k)\log k)O((N−k)logk) time complexity. Adding both parts up, we get \mathcal{O}(N \log k)O(Nlogk) time complexity for the second step.

    The third and the last step is to convert the heap into an output array. That could be done in \mathcal{O}(k \log k)O(klogk) time.
    """
    def doit_heap(self, nums: list, k: int) -> list:
        import heapq
        from collections import Counter
        # O(1) time 
        if k == len(nums):
            return nums
        
        # 1. build hash map : character and how often it appears
        # O(N) time
        count = Counter(nums)   
        # 2-3. build heap of top k frequent elements and
        # convert it into an output array
        # O(N log k) time
        return heapq.nlargest(k, count.keys(), key=count.get)


    """
    Approach 2: Quickselect
    Hoare's selection algorithm

    Quickselect is a textbook algorthm typically used to solve the problems "find kth something": kth smallest, kth largest, kth most frequent, kth less frequent, etc. Like quicksort, quickselect was developed by Tony Hoare, and also known as Hoare's selection algorithm.

    It has \mathcal{O}(N)O(N) average time complexity and widely used in practice. It worth to note that its worth case time complexity is \mathcal{O}(N^2)O(N 
    2
    ), although the probability of this worst-case is negligible.

    The approach is the same as for quicksort.
    """
    def doit_partition(self, nums: List[int], k: int) -> List[int]:
        count = Counter(nums)
        unique = list(count.keys())
        
        def partition(left, right, pivot_index) -> int:
            pivot_frequency = count[unique[pivot_index]]
            # 1. move pivot to end
            unique[pivot_index], unique[right] = unique[right], unique[pivot_index]  
            
            # 2. move all less frequent elements to the left
            store_index = left
            for i in range(left, right):
                if count[unique[i]] < pivot_frequency:
                    unique[store_index], unique[i] = unique[i], unique[store_index]
                    store_index += 1

            # 3. move pivot to its final place
            unique[right], unique[store_index] = unique[store_index], unique[right]  
            
            return store_index
        
        def quickselect(left, right, k_smallest) -> None:
            """
            Sort a list within left..right till kth less frequent element
            takes its place. 
            """
            # base case: the list contains only one element
            if left == right: 
                return
            
            # select a random pivot_index
            pivot_index = random.randint(left, right)     
                            
            # find the pivot position in a sorted list   
            pivot_index = partition(left, right, pivot_index)
            
            # if the pivot is in its final sorted position
            if k_smallest == pivot_index:
                 return 
            # go left
            elif k_smallest < pivot_index:
                quickselect(left, pivot_index - 1, k_smallest)
            # go right
            else:
                quickselect(pivot_index + 1, right, k_smallest)
         
        n = len(unique) 
        # kth top frequent element is (n - k)th less frequent.
        # Do a partial sort: from less frequent to the most frequent, till
        # (n - k)th less frequent element takes its place (n - k) in a sorted array. 
        # All element on the left are less frequent.
        # All the elements on the right are more frequent.  
        quickselect(0, n - 1, n - k)
        # Return top k frequent elements
        return unique[n - k:]