


# 332. Reconstruct Itinerary

# Given a list of airline tickets represented by pairs of departure and arrival airports [from, to],
# reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK.
# Thus, the itinerary must begin with JFK.

# Note:
# If there are multiple valid itineraries, you should return the itinerary
# that has the smallest lexical order when read as a single string.
# For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
# All airports are represented by three capital letters (IATA code).
# You may assume all tickets form at least one valid itinerary.

# Example 1:
# tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
# Return ["JFK", "MUC", "LHR", "SFO", "SJC"].

# Example 2:
# tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
# Return ["JFK","ATL","JFK","SFO","ATL","SFO"].

# Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order.

import collections

class findItinerary(object):

    def doit1(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        A = collections.defaultdict(list)
        for c, d in sorted(tickets, reverse= True):
            A[c].append(d)

        route = []
        buff = ['JFK']
        
        while buff:
        
            while A[buff[-1]]:
                buff.append(A[buff[-1]].pop()) 
           
            route.append(buff.pop())

        return route[::-1]


    def doit(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        A = collections.defaultdict(list)

        for c, b in sorted(tickets, reverse = True):
            A[c].append(b)

        
        route = []
        def search(city):

            while A[city]:
                search(A[city].pop())

            route.append(city)
        
        search('JFK')
        return route[::-1]

if __name__=="__main__":
    

    # ["JFK", "MUC", "LHR", "SFO", "SJC"].
    res = findItinerary().doit([["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]])

    # 
    res = findItinerary().doit([["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]])

    res = findItinerary().doit([["JFK","ATL"],["ATL","JFK"]])    

    pass