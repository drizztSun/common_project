/*
535. Encode and Decode TinyURL

Note: This is a companion problem to the System Design problem: Design TinyURL.
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.

Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. 
You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.

*/
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

/*
    535.Encode-and-Decode-TinyURL
    利用62位的dict随机生成一个6位的字符串来作为短链接

    dict=""abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"";
    for (int i=0; i<6; i++) 
    shortUrl+=dict[rand()%62];
    将longUrl和shortUrl的配对放入两个哈希表中，用于查验短链接的生成是否重复、以及解码。
*/
class Solution {

    string dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    unordered_map<string,string>Map1;
    unordered_map<string,string>Map2;

public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) 
    {
        string sr;
        do {
            sr="";
            for (int i=0; i<6; i++)
                sr += dict[rand()%62];
        } while(Map1.find(sr)!=Map1.end());
        
        Map1[longUrl]=sr;
        Map2[sr]=longUrl;
        return sr;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) 
    {
        return Map2[shortUrl];
    }
};