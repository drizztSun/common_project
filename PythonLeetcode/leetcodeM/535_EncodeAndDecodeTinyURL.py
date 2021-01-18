"""
535. Encode and Decode TinyURL

TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
"""

class Codec:

    def __init__(self):
        self.url2Code = {}
        self.code2Url = {}
    
    
    def encode(self, longUrl):
        """Encodes a URL to a shortened URL.
        
        :type longUrl: str
        :rtype: str
        """
        alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFQHIJKLMNOPQRSTUVWXYZ"
        
        while longUrl not in self.url2Code:
            
            code = ''.join(random.choice(alphabet) for _ in range(6))
            
            if code not in self.code2Url:
                self.code2Url[code] = longUrl
                self.url2Code[longUrl] = code
                
        return 'http://tinyurl.com/' + self.url2Code[longUrl]

    def decode(self, shortUrl):
        """Decodes a shortened URL to its original URL.
        
        :type shortUrl: str
        :rtype: str
        """
        return self.code2Url[shortUrl[-6:]]