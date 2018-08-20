# 535. Encode and Decode TinyURL

# TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and 
# it returns a short URL such as http://tinyurl.com/4e9iAk.

# Design the encode and decode methods for the TinyURL service. 
# There is no restriction on how your encode/decode algorithm should work. 
# You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.

import randmon

class Codec:

    def __init__(self):
        self._url2code = {}
        self._code2url = {}
        

    def encode(self, longUrl):
        """Encodes a URL to a shortened URL.
        :type longUrl: str
        :rtype: str
        """
        alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFQHIJKLMNOPQRSTUVWXYZ"
        while longUrl not in self._url2code:
            code = "".join(random.choice(alphabet) for _ in range(6))
            if code not in self._code2url:
                self._url2code[longUrl] = code
                self._code2url[code] = longUrl
        
        return 'http://tinyurl/' + self._url2code[longUrl]
        

    def decode(self, shortUrl):
        """Decodes a shortened URL to its original URL.
        :type shortUrl: str
        :rtype: str
        """
        return slef._code2url[shortUrl[-6:]]
        




# 534. Design TinyURL


# How would you design a URL shortening service that is similar to TinyURL?

# Background:
# TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

# Requirements:
# For instance, "http://tinyurl.com/4e9iAk" is the tiny url for the page "https://leetcode.com/problems/design-tinyurl". The identifier (the highlighted part) can be any string with 6 alphanumeric characters containing 0-9, a-z, A-Z.
# Each shortened URL must be unique; that is, no two different URLs can be shortened to the same URL.
# Note about Questions:
# Below are just a small subset of questions to get you started. In real world, there could be many follow ups and questions possible and the discussion is open-ended (No one true or correct way to solve a problem). If you have more ideas or questions, please ask in Discuss and we may compile it here!

# Questions:
# How many unique identifiers possible? Will you run out of unique URLs?
# Should the identifier be increment or not? Which is easier to design? Pros and cons?
# Mapping an identifier to an URL and its reversal - Does this problem ring a bell to you?
# How do you store the URLs? Does a simple flat file database work?
# What is the bottleneck of the system? Is it read-heavy or write-heavy?
# Estimate the maximum number of URLs a single machine can store.
# Estimate the maximum number of queries per second (QPS) for decoding a shortened URL in a single machine.
# How would you scale the service? For example, a viral link which is shared in social media could result in a peak QPS at a moment's notice.
# How could you handle redundancy? i,e, if a server is down, how could you ensure the service is still operational?
# Keep URLs forever or prune, pros/cons? How we do pruning? (Contributed by @alex_svetkin)
# What API would you provide to a third-party developer? (Contributed by @alex_svetkin)
# If you can enable caching, what would you cache and what's the expiry time? (Contributed by @Humandroid)



class TinyURL:

    def __init__(self, url):
        """
        """
        self._url = url


    def shortURL(self) :

        return self._shortURL



if __name__=="__main__":

    
    


    pass