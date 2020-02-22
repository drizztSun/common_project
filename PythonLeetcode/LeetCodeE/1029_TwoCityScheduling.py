# 1029. Two City Scheduling

# There are 2N people a company is planning to interview.
# The cost of flying the i-th person to city A is costs[i][0],
# and the cost of flying the i-th person to city B is costs[i][1].

# Return the minimum cost to fly every person to a city such that exactly N people arrive in each city.


# Example 1:

# Input: [[10,20],[30,200],[400,50],[30,20]]
# Output: 110
# Explanation:
# The first person goes to city A for a cost of 10.
# The second person goes to city A for a cost of 30.
# The third person goes to city B for a cost of 50.
# The fourth person goes to city B for a cost of 20.

# The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.


# Note:

# 1 <= costs.length <= 100
# It is guaranteed that costs.length is even.
# 1 <= costs[i][0], costs[i][1] <= 1000

class TwoCitySchedCost:

    """
    Find out how cheap is landing to city A for each individual as compared to landing in city B.
    For minimum cost we should be sending people to city A if this difference is very huge and negative (more savings over choosing city B in stead).
    But due to the constraint of having N individuals in each city,
    we might have to send a few individuals to city A even when sending them to city B is cheaper - in this case,
    it would make sense to take those prices to A that are least different from the fare to city B to minimize cost.
    That's why we sort the costs w.r.t difference in cost_to_A - cost_to_B.
    """

    def doit(self, costs):
        costs.sort(key=lambda x: (x[0]-x[1]))
        return sum(costs[i][0] if i < len(costs)//2 else costs[i][1] for i in range(len(costs)))


if __name__ == '__main__':

    res = TwoCitySchedCost().doit(
        [[10, 20], [30, 200], [400, 50], [30, 20]])  # 110

    res = TwoCitySchedCost().doit(
        [[259, 770], [448, 54], [926, 667], [184, 139], [840, 118], [577, 469]])  # 1859

    pass
