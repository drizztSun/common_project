"""
468. Validate IP Address

Given a string IP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.

A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot contain leading zeros. For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses but "192.168.01.1", while "192.168.1.00" and "192.168@1.1" are invalid IPv4 addresses.

A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:

1 <= xi.length <= 4
xi is a hexadecimal string which may contain digits, lower-case English letter ('a' to 'f') and upper-case English letters ('A' to 'F').
Leading zeros are allowed in xi.
For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while "2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.



Example 1:

Input: IP = "172.16.254.1"
Output: "IPv4"
Explanation: This is a valid IPv4 address, return "IPv4".
Example 2:

Input: IP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
Output: "IPv6"
Explanation: This is a valid IPv6 address, return "IPv6".
Example 3:

Input: IP = "256.256.256.256"
Output: "Neither"
Explanation: This is neither a IPv4 address nor a IPv6 address.
Example 4:

Input: IP = "2001:0db8:85a3:0:0:8A2E:0370:7334:"
Output: "Neither"
Example 5:

Input: IP = "1e1.4.5.6"
Output: "Neither"

"""
import re
from ipaddress import ip_address, IPv6Address


class ValidIPAddress:

    def doit_2(self, IP: str) -> str:
        try:
            return "IPv6" if type(ip_address(IP)) is IPv6Address else "IPv4"
        except ValueError:
            return "Neither"

    def doit_1(self, IP: str):

        chunk_IPv4 = r'([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])'
        patten_IPv4 = re.compile(r'^(' + chunk_IPv4 + r'\.){3}' + chunk_IPv4 + r'$')

        chunk_IPv6 = r'([0-9a-fA-F]{1,4})'
        patten_IPv6 = re.compile(r'^(' + chunk_IPv6 + r'\:){7}' + chunk_IPv6 + r'$')

        if self.patten_IPv4.match(IP):
            return "IPv4"
        return "IPv6" if self.patten_IPv6.match(IP) else "Neither"

    """
    Approach 2: Divide and Conquer
    Intuition

    Both IPv4 and IPv6 addresses are composed of several substrings separated by certain delimiter,
    and each of the substrings is of the same format.

    Therefore, intuitively, we could break down the address into chunks, and then verify them one by one.

    The address is valid if and only if each of the chunks is valid. We can call this methodology divide and conquer.

    Algorithm

    For the IPv4 address, we split IP into four chunks by the delimiter ., while for IPv6 address, we split IP into eight chunks by the delimiter :.

    For each substring of "IPv4" address, we check if it is an integer between 0 - 255, and there is no leading zeros.

    For each substring of "IPv6" address, we check if it's a hexadecimal number of length 1 - 4.

    Implementation

    Complexity Analysis

    Time complexity: O(N) because to count number of dots requires to parse the entire input string.

    Space complexity: O(1).

    """
    def doit(self, IP):

        def validate_IPv4(IP):
            nums = IP.split('.')
            for x in nums:
                # Validate integer in range (0, 255):
                # 1. length of chunk is between 1 and 3
                if len(x) == 0 or len(x) > 3:
                    return "Neither"
                # 2. no extra leading zeros
                # 3. only digits are allowed
                # 4. less than 255
                if x[0] == '0' and len(x) != 1 or not x.isdigit() or int(x) > 255:
                    return "Neither"
            return "IPv4"

        def validate_IPv6(IP):
            nums = IP.split(':')
            hexdigits = '0123456789abcdefABCDEF'
            for x in nums:
                # Validate hexadecimal in range (0, 2**16):
                # 1. at least one and not more than 4 hexdigits in one chunk
                # 2. only hexdigits are allowed: 0-9, a-f, A-F
                if len(x) == 0 or len(x) > 4 or not all(c in hexdigits for c in x):
                    return "Neither"
            return "IPv6"

        if IP.count('.') == 3:
            return validate_IPv4(IP)
        elif IP.count(':') == 7:
            return validate_IPv6(IP)
        else:
            return "Neither"

