# 648. Replace Words

# In English, we have a concept called root, which can be followed by some other words to form another longer word
# - let's call this word successor. For example, the root an, followed by other, which can form another word another.

# Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor 
# in the sentence with the root forming it. If a successor has many roots can form it, 
# replace it with the root with the shortest length.

# You need to output the sentence after the replacement.

# Example 1:
# Input: dict = ["cat", "bat", "rat"]
# sentence = "the cattle was rattled by the battery"
# Output: "the cat was rat by the bat"

# Note:
# The input will only have lower-case letters.
# 1 <= dict words number <= 1000
# 1 <= sentence words number <= 1000
# 1 <= root length <= 100
# 1 <= sentence words length <= 1000
    
       
class Tie:

    def __init__(self):
        self.existed = False
        self.next = {}
                 

class ReplaceWords:


    def doit(self, dict, sentence):
        """
        :type dict: List[str]
        :type sentence: str
        :rtype: str
        """

        def buildTie(dict):

            root = Tie()
        
            for word in dict:
                node = root
                #for i in range(len(c)):
                for c in word:
                    if c not in node.next:
                        node.next[c] = Tie()
                    node = node.next[c]

                node.existed = True
           
            return root        

        def find(word, root):
    
            res = ''
            node = root
            for i, c in enumerate(word):
                if c in node.next:
                    node = node.next[c]
                    res += c
                    if node.existed:
                        break
                else:
                    break
    
            return res if node.existed else ''                       

        root = buildTie(dict)

        res = []
        for word in sentence.split():
                                 
            r = find(word, root) 

            res.append(word if not r else r)

        return ' '.join(res)


if __name__ == "__main__":

    res = ReplaceWords().doit(dict = ["cat", "bat", "rat"], sentence = "the cattle was rattled by the battery")

    res = ""