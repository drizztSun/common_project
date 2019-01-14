# 721. Accounts Merge

# Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, 
# and the rest of the elements are emails representing emails of the account.

# Now, we would like to merge these accounts. Two accounts definitely belong to the same person 
# if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

# After merging the accounts, return the accounts in the following format: the first element of each account is the name, 
# and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

# Example 1:
# Input: 
# accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
# Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
# Explanation: 
# The first and third John's are the same person as they have the common email "johnsmith@mail.com".
# The second John and Mary are different people as none of their email addresses are used by other accounts.
# We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
# ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.


#<union-find>
#class DSU:
#    def __init__(self):
#        self.tree = []

#    def make_set(self, x):
#        if len(self.tree) <= x:
#            self.tree += range(len(self.tree), x+1)
#        return x

#    def find(self, x):
#        while x != self.tree[x]:
#            self.tree[x] = self.tree[self.tree[x]]
#            x = self.tree[x]
#        return x

#    def union(self, x, y):
#        self.tree[self.find(x)] = self.find(y)


import collections

class AccountsMerge:
    def doit(self, accounts):
        """
        :type accounts: List[List[str]]
        :rtype: List[List[str]]
        """
        parents = [i for i in range(len(accounts))]
        
        def find(a):
            if parents[a] != a:
                parents[a] = find(parents[a])
            return parents[a]

        def union(a, b):
            a = find(a)
            b = find(b)

            if parents[a] != parents[b]:
                parents[parents[b]] = parents[a]            
          
        email2Accounts = collections.defaultdict(list) 
        for i, account in enumerate(accounts):
            for email in account[1:]:
                email2Accounts[email].append(i)

        for email, index in email2Accounts.items():
            if len(index) > 1:
                for i in range(1, len(index)):
                    union(index[i], index[0])
            else:
                find(index[0])
                    
        for i in range(len(parents)):
            find(i)

        accountres = {}
        for i in range(len(parents)):
            if (parents[i], accounts[i][0]) not in accountres:
                accountres[(parents[i], accounts[i][0])] = set()

            for email in accounts[i][1:]:
                    accountres[(parents[i], accounts[i][0])].add(email)

        return [[key[1]] + sorted(list(val)) for key, val in accountres.items()]


# <union-find>
class Solution:
    def accountsMerge(self, accounts):
        i, e_i, i_n, d, r = 0, {}, {}, DSU(), {}

        for name, *emails in accounts:
            for e in emails:
                if e not in e_i: 
                    e_i[e], i_n[i], i = i, name, i+1

                d.union(d.find(d.make_set(e_i[e])), d.find(e_i[emails[0]]))

        for e in e_i: 
            r.setdefault(d.find(e_i[e]), set()).add(e)

        return [[i_n[i], *sorted(r[i])] for i in r]

class DSU:
    def __init__(self):
        self.tree = []

    def make_set(self, x):
        if len(self.tree) <= x:
            self.tree += range(len(self.tree), x+1)
        return x

    def find(self, x):
        while x != self.tree[x]:
            self.tree[x] = self.tree[self.tree[x]]
            x = self.tree[x]
        return x

    def union(self, x, y):
        self.tree[self.find(x)] = self.find(y)

         
if __name__ == "__main__":

    res = AccountsMerge().doit([["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], 
                ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]])

    res = AccountsMerge().doit([["David","David0@m.co","David1@m.co"],["David","David3@m.co","David4@m.co"],["David","David4@m.co","David5@m.co"],
                ["David","David2@m.co","David3@m.co"],["David","David1@m.co","David2@m.co"]])

    Solution().accountsMerge(accounts = [["David","David0@m.co","David1@m.co"],["David","David3@m.co","David4@m.co"],["David","David4@m.co","David5@m.co"],
                ["David","David2@m.co","David3@m.co"],["David","David1@m.co","David2@m.co"]])
        
    res = 0        
        
