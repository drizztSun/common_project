# 860. Lemonade Change


# At a lemonade stand, each lemonade costs $5.

# Customers are standing in a queue to buy from you, and order one at a time (in the order specified by bills).

# Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill.
# You must provide the correct change to each customer, so that the net transaction is that the customer pays $5.

# Note that you don't have any change in hand at first.

# Return true if and only if you can provide every customer with correct change.


# Example 1:

# Input: [5,5,5,10,20]
# Output: true
# Explanation:
# From the first 3 customers, we collect three $5 bills in order.
# From the fourth customer, we collect a $10 bill and give back a $5.
# From the fifth customer, we give a $10 bill and a $5 bill.
# Since all customers got correct change, we output true.

# Example 2:

# Input: [5,5,10]
# Output: true

# Example 3:

# Input: [10,10]
# Output: false

# Example 4:

# Input: [5,5,10,10,20]
# Output: false

# Explanation:
# From the first two customers in order, we collect two $5 bills.
# For the next two customers in order, we collect a $10 bill and give back a $5 bill.
# For the last customer, we can't give change of $15 back because we only have two $10 bills.
# Since not every customer received correct change, the answer is false.

class LemonadeChange:

    def doit(self, bills):

        five_dollars, ten_dollars = 0, 0

        for c in bills:

            if c == 5:
                five_dollars += 1
                continue

            if c == 10:
                ten_dollars += 1

            if c - 5 == 5 and five_dollars > 0:
                five_dollars -= 1
            elif c - 5 == 15:
                if ten_dollars > 0 and five_dollars > 0:
                    ten_dollars -= 1
                    five_dollars -= 1
                elif five_dollars > 2:
                    five_dollars -= 3
                else:
                    return False
            else:
                return False

        return True

    def doit(self, bills):

        n5 = 0
        n10 = 0
        for b in bills:
            if b == 5:
                n5 += 1
            if b == 10:
                if n5 >= 1:
                    n5 -= 1
                    n10 += 1
                else:
                    return False
            if b == 20:
                if n5 >= 1 and n10 >= 1:
                    n5 -= 1
                    n10 -= 1
                elif n5 >= 3:
                    n5 -= 3
                else:
                    return False
        return True


if __name__ == '__main__':

    res = LemonadeChange().doit([5, 5, 5, 10, 20])  # true

    res = LemonadeChange().doit([5, 5, 10])  # true

    res = LemonadeChange().doit([10, 10])  # false

    res = LemonadeChange().doit([5, 5, 10])  # true

    res = LemonadeChange().doit([5, 5, 10, 10, 20])  # false

    pass
