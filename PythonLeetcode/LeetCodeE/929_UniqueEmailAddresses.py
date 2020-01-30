# 929. Unique Email Addresses

# Every email consists of a local name and a domain name, separated by the @ sign.

# For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.

# Besides lowercase letters, these emails may contain '.'s or '+'s.

# If you add periods ('.') between some characters in the local name part of an email address,
# mail sent there will be forwarded to the same address without dots in the local name.
#
# For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.
# (Note that this rule does not apply for domain names.)

# If you add a plus ('+') in the local name, everything after the first plus sign will be ignored.
# This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.
# (Again, this rule does not apply for domain names.)

# It is possible to use both of these rules at the same time.

# Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails?

# Example 1:

# Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
# Output: 2
# Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails


# Note:

# 1 <= emails[i].length <= 100
# 1 <= emails.length <= 100
# Each emails[i] contains exactly one '@' character.
# All local and domain names are non-empty.
# Local names do not start with a '+' character.

class NumUniqueEmails:

    """
    Approach 1: Canonical Form
    Intuition and Algorithm

    For each email address, convert it to the canonical address that actually receives the mail. This involves a few steps:

    Separate the email address into a local part and the rest of the address.

    If the local part has a '+' character, remove it and everything beyond it from the local part.

    Remove all the zeros from the local part.

    The canonical address is local + rest.

    After, we can count the number of unique canonical addresses with a Set structure.


    """

    def doit(self, emails):
        seen = set()
        for email in emails:
            local, domain = email.split('@')
            if '+' in local:
                local = local[:local.index('+')]
            seen.add(local.replace('.', '') + '@' + domain)
        return len(seen)

    def doit(self, emails):

        def generate_email(email):
            local_name, domain_name = email.split('@')
            local_name = local_name.replace('.', '')
            local_name = local_name.split('+')[0]
            return "@".join([local_name, domain_name])

        return len(set([generate_email(c) for c in emails]))

    def doit(self, emails):

        ans = set()

        for email in emails:

            name, domain = email.split('@')

            plus = name.find('+')
            if plus != -1:
                name = name[:plus]

            name = ''.join(name.split('.'))

            ans.add(name + '@' + domain)

        return len(ans)


if __name__ == '__main__':

    res = NumUniqueEmails().doit(["test.email+alex@leetcode.com",
                                  "test.e.mail+bob.cathy@leetcode.com", "testemail+david@lee.tcode.com"])

    pass
