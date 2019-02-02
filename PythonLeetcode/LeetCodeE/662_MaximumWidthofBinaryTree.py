# 662. Maximum Width of Binary Tree



class WidthOfBinaryTree:


    def doit(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        queue = [(root, 0, 0)]
        currentdepth = ans = left = 0
        
        for node, depth, pos in queue:
            
            if node:
                queue.append([node.left, depth+1, 2*pos])
                queue.append([node.right, depth+1, 2*pos+1])
                
                if currentdepth != depth:
                    currentdepth = depth
                    left = pos
                    
                ans = max(ans, pos - left + 1)
                
        return ans
        

    def doit1(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        buff = [root]
        res = 0
        
        while buff:
            
            temp = []
            
            res = max(res, len(buff))
            
            for c in buff:
                if not c :
                    temp.extend([None, None])
                else :
                    temp.extend([c.left, c.right])
                
            for i in range(len(temp)):
                if temp[i] != None:
                    break
            for j in reversed(range(len(temp))):
                if temp[j] != None:
                    break
                    
            temp = temp[i:j+1]
                
            buff = temp
            
        return res