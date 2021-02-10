"""
1618. Maximum Font to Fit a Sentence in a Screen


You are given a string text. We want to display text on a screen of width w and height h. You can choose any font size from array fonts, which contains the available font sizes in ascending order.

You can use the FontInfo interface to get the width and height of any character at any available font size.

The FontInfo interface is defined as such:

interface FontInfo {
  // Returns the width of character ch on the screen using font size fontSize.
  // O(1) per call
  public int getWidth(int fontSize, char ch);

  // Returns the height of any character on the screen using font size fontSize.
  // O(1) per call
  public int getHeight(int fontSize);
}
The calculated width of text for some fontSize is the sum of every getWidth(fontSize, text[i]) call for each 0 <= i < text.length (0-indexed). The calculated height of text for some fontSize is getHeight(fontSize). Note that text is displayed on a single line.

It is guaranteed that FontInfo will return the same value if you call getHeight or getWidth with the same parameters.

It is also guaranteed that for any font size fontSize and any character ch:

getHeight(fontSize) <= getHeight(fontSize+1)
getWidth(fontSize, ch) <= getWidth(fontSize+1, ch)
Return the maximum font size you can use to display text on the screen. If text cannot fit on the display with any font size, return -1.

 

Example 1:

Input: text = "helloworld", w = 80, h = 20, fonts = [6,8,10,12,14,16,18,24,36]
Output: 6
Example 2:

Input: text = "leetcode", w = 1000, h = 50, fonts = [1,2,4]
Output: 4
Example 3:

Input: text = "easyquestion", w = 100, h = 100, fonts = [10,15,20,25]
Output: -1
 

Constraints:

1 <= text.length <= 50000
text contains only lowercase English letters.
1 <= w <= 107
1 <= h <= 104
1 <= fonts.length <= 105
1 <= fonts[i] <= 105
fonts is sorted in ascending order and does not contain duplicates.
"""



class MaximumFont:

    """
        Explaination

        We can use binary search to find the answer.

        Define function check(fs) that checks if text can fit on the display with font size fs. We use binary search to find the maximum fs such that check(fs) == True.


        Complexity

        Time complexity: O(NlogM), where N = len(text) and M = len(fonts)
        Space complexity: O(1)


        Similar Questions

        Many other questions can be solved using similar techniques. I listed some of them below:

        410. Split Array Largest Sum
        774. Minimize Max Distance to Gas Station
        875. Koko Eating Bananas
        1011. Capacity To Ship Packages Within D Days
        1231. Divide Chocolate
        1482. Minimum Number of Days to Make m Bouquets
        1552. Magnetic Force Between Two Balls


        Can anyone explain why we use m = r - (r - l) // 2 instead of m = (l + r) // 2 and why l = m, r = m -1 instead of l = m + 1, r = m? I guess it's something related to bisect_left & bisect_right?
        Btw I found this solution also works. I am really confused with the binary search template

        l, r = 0, len(fonts) - 1
        while l < r:
            mid = (l + r) // 2
            if check(fonts[mid + 1]): 
                l = mid + 1
            else:
                r = mid
        return fonts[l] if check(fonts[l]) else -1

    """
    def maxFont(self, text: str, w: int, h: int, fonts: list, fontInfo : 'FontInfo') -> int:
        
        def check(fs):
            if fontInfo.getHeight(fs) > h:
                return False
            if sum(fontInfo.getWidth(fs, c) for c in text) > w:
                return False
            return True
        
        l, r = -1, len(fonts) - 1
        while l < r:
            m = r - (r - l) // 2
            if check(fonts[m]):
                l = m
            else:
                r = m - 1
        return fonts[l] if l > -1 else -1




    def doit_binary_search(self, text: str, w: int, h: int, fonts: list, fontInfo : 'FontInfo') -> int:

        from collections import Counter

        l, r, cnt = -1, len(fonts) - 1, Counter(text)
        
        while l < r:

            m = max(l + 1, (l + r) // 2)

            if fontInfo.getHeight(fonts[m]) > h or sum(n * fontInfo.getWidth(fonts[m], ch) for ch, n in cnt.items()) > w:
                r = m - 1
            else:
                l = m

        return fonts[l] if l != -1 else -1

    def doit_(self, text, w, h, fonts, fontInfo) -> int:
        def search(font: int):
            
            if fontInfo.getHeight(font) > h: return False
            
            return sum(fontInfo.getWidth(font, c) for c in text) <= w
        
        left, right = 0, len(fonts) - 1
        
        while left < right:
            
            mid = (right + left) // 2
            
            if not search(fonts[mid]):
                right = mid-1
            else:
                left = mid
                
        return fonts[left]

    def doit_binary_search(self, text: str, w: int, h: int, fonts: list, fontInfo : 'FontInfo') -> int:
        from collections import Counter

        cnt = Counter(text) # O(n) time complexity
        
        def isFit(font):
		    # O(26) time complexity
            total_width = 0
            for k, times in cnt.items():
                total_width += fontInfo.getWidth(font, k) * times
            height = fontInfo.getHeight(font)
            return total_width <= w and height <= h
        
        leftright = len(fonts) - 1
        while left <= right:   # O(logk) time complexity, where k = len(fonts)
            mid = (left + right) >> 1
            if isFit(fonts[mid]):
                left = mid + 1
            else:
                right = mid - 1

        if 0 <= right <= len(fonts) - 1:
            return fonts[right]
        return -1

