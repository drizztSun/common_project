"""
1052. Grumpy Bookstore Owner

Today, the bookstore owner has a store open for customers.length minutes.  Every minute, some number of customers
(customers[i]) enter the store, and all those customers leave after the end of that minute.

On some minutes, the bookstore owner is grumpy.  If the bookstore owner is grumpy on the i-th minute, grumpy[i] = 1,
otherwise grumpy[i] = 0.  When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise they are satisfied.

The bookstore owner knows a secret technique to keep themselves not grumpy for X minutes straight, but can only use it once.

Return the maximum number of customers that can be satisfied throughout the day.



Example 1:

Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], X = 3
Output: 16
Explanation: The bookstore owner keeps themselves not grumpy for the last 3 minutes.
The maximum number of customers that can be satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.


Note:

1 <= X <= customers.length == grumpy.length <= 20000
0 <= customers[i] <= 1000
0 <= grumpy[i] <= 1

"""


class GrumpyBookstoreOwner:

    def doit_search(self, customers: list, grumpy: list, X: int) -> int:

        total = sum([customers[i] for i in range(len(customers)) if grumpy[i] == 0])

        maxfixed, res = 0, 0
        for i in range(len(customers)):
            if grumpy[i] == 1:
                maxfixed += customers[i]

            if i - X >= 0 and grumpy[i - X] == 1:
                maxfixed -= customers[i - X]

            res = max(res, maxfixed)

        return total + res


if __name__ == '__main__':

    GrumpyBookstoreOwner().doit_search([1,0,1,2,1,1,7,5], [0,1,0,1,0,1,0,1], 3)










