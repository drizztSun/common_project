


# 336. Palindrome Pairs


# Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, 
# so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

# Example 1:
# Given words = ["bat", "tab", "cat"]
# Return [[0, 1], [1, 0]]
# The palindromes are ["battab", "tabbat"]

# Example 2:
# Given words = ["abcd", "dcba", "lls", "s", "sssll"]
# Return [[0, 1], [1, 0], [3, 2], [2, 4]]
# The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]


class palindromePairs:




# The basic idea is to check each word for prefixes (and suffixes) that are themselves palindromes.
# If you find a prefix that is a valid palindrome, then the suffix reversed can be paired with the word
# in order to make a palindrome. It�s better explained with an example.

# words = ["bot", "t", "to"]
# Starting with the string �bot�. We start checking all prefixes. If "", "b", "bo", "bot" are themselves palindromes.
# The empty string and �b� are palindromes. We work with the corresponding suffixes (�bot�, �ot�) and check to see if their reverses (�tob�, �to�) are present in our initial word list. If so (like the word to"to"), we have found a valid pairing where the reversed suffix can be prepended to the current word in order to form �to� + �bot� = �tobot�.

# You can do the same thing by checking all suffixes to see if they are palindromes.
# If so, then finding all reversed prefixes will give you the words that can be appended to the current word to form a palindrome.

# The process is then repeated for every word in the list.
# Note that when considering suffixes, we explicitly leave out the empty string to avoid counting duplicates.
# That is, if a palindrome can be created by appending an entire other word to the current word,
# then we will already consider such a palindrome when considering the empty string as prefix for the other word.

    def doit(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        wordDict = {}
        for i in range(len(words)):
            wordDict[words[i]] = i

        ans = []
        for i in range(len(words)):
            for j in range(len(words[i]) + 1):

                front = words[i][:j]
                back = words[i][j:]

                if front[::-1] in wordDict and wordDict[front[::-1]] != i  and back == back[::-1]:
                    ans.append([ i, wordDict[front[::-1]] ])
    
                if j != 0 and back[::-1] in wordDict and wordDict[back[::-1]] != i and front == front[::-1]:
                    ans.append([ wordDict[back[::-1]], i ])

        return ans


    # O(n**2)
    def doit1(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        def isPalindrome(A, B):
            word = A + B
            i , j = 0 , len(word) - 1

            while j >= i and word[i] == word[j]:
                i += 1
                j -= 1

            return i > j

        wordIndex = []
        for i in range(len(words)):
            for j in range(i+1, len(words)):
                if isPalindrome(words[i], words[j]):
                    wordIndex.append([i, j])
        
                if isPalindrome(words[j], words[i]):
                    wordIndex.append([j, i])

        return wordIndex

             
    # best    
    def doit1(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """ 
        res = []
        d = {}

        for i, w in enumerate(words):
            d[w] = i
        
        for i, w in enumerate(words):
            if not w:
                continue
            
            if w[::-1] in d:
                if w[::-1] == w:
                    if '' in d:
                        res.append([d[''], i])
                        res.append([i, d['']])
                else:
                    res.append([d[w[::-1]], i])
            
            for j in range(1, len(w)):
                wl = w[:j]
                wr = w[j:]
                if wl == wl[::-1] and wr[::-1] in d:
                    res.append([d[wr[::-1]], i])
                
                if wr == wr[::-1] and wl[::-1] in d:
                    res.append([i, d[wl[::-1]]])
        
        return res



    # Another one
    def doit(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        def isPalindrome(s):
            start, end = 0, len(s) - 1
            while start < end:
                if s[start] != s[end]:
                    return False
                start += 1
                end -= 1
            return True


        i, length, reversedStrDict, result = 0, len(words), {}, []
        while i < length:
            reversedStrDict[words[i][::-1]] = i
            i += 1

        if reversedStrDict.has_key("") :
            i = 0
            while i < length:
                if i == reversedStrDict[""]:
                    i += 1
                    continue
                if isPalindrome(words[i]) :
                    result.append([reversedStrDict[""], i])
                i += 1


        i = 0
        while i < length:
            j = 0
            while j < len(words[i]):
                left, right = words[i][0:j], words[i][j:]
        
                if reversedStrDict.has_key(left) and isPalindrome(right) and reversedStrDict[left] != i:
                    result.append([i, reversedStrDict[left]])

                if reversedStrDict.has_key(right) and isPalindrome(left) and reversedStrDict[right] != i:
                    result.append([reversedStrDict[right], i])
                j += 1
            i += 1
        
        return result


if __name__=="__main__":


    res = palindromePairs().doit(['a', ''])


    res = palindromePairs().doit(["bat", "tab", "cat"])

    
    res = palindromePairs().doit(["abcd", "dcba", "lls", "s", "sssll"])
    

    res = palindromePairs().doit(["hijajcd","hjhgahbcegj","fjbjfecjgfjdbbgdadcb","did","cgjhfafgea","chdbicgcij","jiebc","aajaaed","afddjhg","hiabij","hfgidgegedeafc","ifedfcaahhbc","fci","jbadcfghehiecbgjcg","gihedfiabhdjicaea","ji","hgacdbeadahceag","hij","fhheadbjb","gieghcacfccfadijcdbg","dbeabaafia","je","ebieia","becjedbdadecfafi","acbchfigbiaafechfeii","fddfbb","jefdihii","cfcifihdfgcjadbeec","jbcfgdhifjgdgcccggfe","ibhj","iihihigj","jifbhdgffiaii","gdcgdabdhbdh","giaa","fgaidgcbgbagjjgcja","becgcgjbeegebb","jadgeej","h","fddgcbgahhh","gecajfjcheha","gaeejd","bc","fd","jh","jddecghbjaedgeadieej","ehi","cfijccggfeijfc","jbdaeaeigbedebaabdg","hjiijifigbhae","aeihbbfdgfhi","bibhjdgdejjfgd","b","dgfhcbgfifchhihg","faaefigafd","fijbabeifgjcefeffdgc","ahdaiejbhegaha","difcfcbcfg","abdffeifcb","ggeaej","hbcicchejbecidi","ijedjfcjahhajc","jfacgfijbdehg","dfbhhbdafcfhjffbcij","cddjdgefdjbhccgaeb","c","gajfibiaehichfhfh","cheegj","icjhhcigfeedg","dggf","ificjhaihgicbhagjjgc","ifbjbadgcccacjcaea","biaafggehahijagj","dghehgccj","ccigbcajbb","fgafdfhagi","jdifdcj","haagafjfa","cdjibbfgije","jgbgdcgaabeicfadedjg","iahehcjhjecbjdehd","acahgc","ejggbffeea","ebacgded","ci","igggjhfgcjfeagaed","jjifjgfefgjgafdc","ddiefahhfeifggj","jggjfacda","dig","bajbghfecjajdhfebi","bfjcbiceefafhbc","bi","cdaj","bfedf","affdcjd","ebjceefjji","cgedidfdaj","diagcdjgcidcaabdec","biajbeajggcaadb","gg","af","ddeibadahhhbcgbb","fbgjaedfgah","fhagi","dbggfjbhefcg","dfgdhjcecbhjffhhcc","gcg","ibejfeehbfhbcceagbf","beefhdiiaajbbid","fcbgeeaggcehjagfbec","cehgbhhdjdabjhgbdf","ibjchciabig","fjfhbdhbdchacfi","dgaiffdjjfhihheajda","afbdfijbaacechfeehai","bhccifjcigdge","ghdibjdih","fhjiaja","fadfaea","ghhdicafbdgbccahb","fhf","jhfg","jehedbbcidgahjhefj","jdigdea","acfiiaebjfeea","eibciijib","fghhghdhb","bf","jgdbcciehebec","cbef","ccdcegbejhcdhbjgd","dacefieigggddd","icjfbhabjjaehgic","dja","egidaegjegceied","eifggahef","d","gh","aabhihfhbjjgaaaaaaf","hhfjgcd","efcejjcgbhdicghbcbda","jeecggeaidcdfeae","i","ddibebgcibi","gcffcijafghehgffijbj","ieb","hhbfcdgeicihcbcgje","aegbdaeedadig","jjhfgeijciji","ecjijiahfcbcf","hibddjjgifbf","eccaajecechb","deaaj","ecgfaaigjce","jhhejciejdhh","cb","f","cjddcfdihddechegg","cgdfdbficba","jajh","hcfadbghjbicbachah","g","fhchedhbcigeci","ghbbcijcbgeccbebaa","chgdgjiac","adfgjbbhfbdbheebhgb","gbbebiaijhagcjfgjda","aadhgcfjhcjaa","fhdbhccfccajfheiaaj","ijgjfc","dcdcfaebjhgafh","egadegbjabjgjhdbhcfb","hhaeabfcfcjc","gfjcijhbbie","icgihfcgd","gfaihjbcb","hae","ciiaefdegffchagaccj","dbadejehhgjjfd","abfbfdaaebhgbadf","gfeijf","acidgfeccdaccc","chhicfj","aejjeejbjcebd","bcchhd","aajideccdfgfdee","fdd","idabig","bfgigiacibhibfc","ghjidfcjdbfagbgg","jdgefifgfg","figabdib","ieegjbjaaaheieccfifj","hhifigebihbec","abfdca","j","dfecghggj","fbdg","aghigddeagaj","hjghddg","biededhjegi","aed","jcgbbhiacef","hgbhaadhe","bjffahgjibfjijjcah","abjgacciihhigafe","bhighdhjgb","idjbedcbcghfhgdjgd","fdcge","jiefciajfacejcbhiijb","gghchaac","jdh","ccdabajaihbigbfbi","edcchgggdajibbafag","fiihgiebhhb","ggbhhfjfa","gechicejjgbebe","fdadccghiadhgeecfeb","fh","gbddbi","acjcafggc","chgbfjfdghjfgaje","fgdcfffcabdbih","ffggdfd","eeibfggddgbb","bcccgbihhhaa","ecegdgdaieicfffebd","heig","aeafdijcgffhaagajbc","cdfecjaabhajjcag","jgacggaabdidjgg","hfcdjddbchagfa","bgh","bbiefehhfc","dfhic","checjfabdceddfefa","bbiebgigjg","hdchejdjeecc","cieafdi","bjbebfjbb","jeeghjiaagdf","ibbjgh","jgfje","gddfb","iadhbabgjjci","faafifgeddfcaji","ijejbiidaefibga","gjhdgffcebfdbbhh","hfbccbbbhebgjihfbhad","jhjeffebgiaijecihcbh","bdacgdeeiajehjhd","cej","fbbhabbdhbeigag","dhb","cbgahbcjjcb","jfbgegddgbfij","bjhcaabhgcfcieai","dfbedgacb","bh","hbgjhchebdigfef","becbjjgbdgfg","jigbiecdcegcgdha","ddacfbgaibdag","afid","gijejaagbghjha","becaigcjdbeiba","gd","cbfffhbacc","jjbafcijeffacaej","ihihgcgjgefiehgdijb","afifbbhfbd","dhigif","chcfjjahbjjgjjheie","ggfaaeeca","afjiccee","dddeigfhbgjiiffgf","edbcfcbiibhcdbihahd","jfhf","cgeeefjhj","ehaaahjbf","dbdbfeabhhdfhedc","jagiegfhgeicd","cg","fjhbaj","djfejdacebedjjh","ejhdbjaagcih","hhifahefah","decabhgbhf","hjgfhdcfjghiehfbaccb","hc","cicefggjjhahhihh","ebghgcehfdbgjef","ihjfejiaidccj","feebgfadjjih","efdjbhbcdgfabia","ebjdhij","ccbjjbfgjifgibibhdi","ddhgfihdifiegfdcbg","jjhccchci","bjhffdchjgfdejbjcc","ghfhfadhadggbf","degiigae","ffefbjgfacjghchab","affcadjjedffagcija","hfaahajcijjigihjdbh","eccahdhacfaaechc","gaidhegbhdbg","gdacg","ajiafgjbi","dcecgfgjh","e","cj","iijjbfbciidi","hhabcihigiccc","hdje","ghgiagda","gcgii","jgccffabdd","eafd","jgajgdghgjihfj","hf","jfhhagebiaage","jcbgf","cehifbja","egidejh","jd","hhfgdcedjbafijia","jejiajdffhdg","ebdificebhah","djddifjeb","ibgfadfebjefjehed","fcbad","gfajh","eabhddjadabaadc","jfjdaibedicjfd","a","ahfiihcjceefjghjhi","hdbcfidadjaggacigg","bbfjhiegacbicihgbd","beddihjhhjhi","ahgideccga","eadhajdegaig","bccbgahhh","ihfieebjejfhfh","jddigigfhfegf","acdihgjab","hgcbfheehjafij","hagfebifdcah","ecfbiefefcgha","giifif","cfiadgbb","faiecgcbaidi","ffhcfc","dgcbabfchj","gchhhdhjjjjgfbeeaig","jiebceebjeeiadcjehia","ajbbhbighd","hgiidjeagfgeejb","gdehaffbfjc","dhfibjfdfedbe","hbeeedddgaaa","bj","fgdhidihjfbedbbhb","dcigfcd","jjgccccjfhjgagjbccbd","djggj","fdfbcaj","hhh","ebgddabghbje","ijaeaihjbjgeb","bcgf","geabfbf","ajdf","behefaeeb","icjecdbeejbg","dcfhcchjabbbe","ficggejecefjahagfc","cbjbaaig","cgghddihbibdahajjjj","febcdicdjhigigjf","jccfhaafj","hgagaghagejgdbhiaa","gdibfadcfjdchdcda","faice","jddahggg","ig","ajihabc","ifc","ddbdie","hgf","iicihahjicfbce","egfjiifaigfhafdcdi","gahbbfgebhajgajgf","gibegcbhhjhcgeg","gahahjjjid","beeghbgiaiffcbedhi","hb","dgfdhbajiej","ehjieabbfgjfabegijii","chdafjb","giejchjbifieeeigccah","dadgcgjddbc","cdiiea","icdjffie","iehihifddj","jfcgfbjghbgfd","edebbjiieahada","badbhciaf","icdffehcddgacgjcfji","fgiheieeeibdjhhjae","accebdijaedhhajaj","acdgcbaehgaiedfcddf","jiagjghcaihbf","ga","ggghd","gb","ehcjcd","aac","cdfghgfagbcjjc","cddadcdidegifbi","ddhhch","fe","eaageabiccfcdd","fbbbjfjffj","icjfacdcbdajecda","aegdcbbicebaffaifg","hedichggfajdbagh","fggjjg","bdbigbjbjadiabjbhch","cdddaajifjjjiigj","bhb","faa","bdfgebjf","hicgahicd","hcfghggjcibb","ieddefeccfeccajhcah","ghc","jdgcbjaeeijjgciae","bdeaif","ehfdc","jjjddhjd","jibaejfc","gddibbagdjbefaga","fhca","iaggggg","bgbhgei","gigfa","fbibghagehecbedidbf","igbfedebhcjbbcegaa","cdceiffdjech","fbdjdhhfgaija","jgjccccchjabdgejfcj","aca","jghb","ffeejefecheefdjh","aediabejhghedgdah","edfcbijbihjafedcc","jbeg","gfdeccbdgdgidabe","figbaajccj","dh","eeafbfcccbjidci","adfgdc","becaafdhg","cjfhajagc","fhfifchf","djdihjjdiibhaegfehc","cgecbjhdjh","acbfbccbiehjhjahjbic","hhgbjdcidhdhdcijfdg","jdcjaichdbiaefe","bbdgfafiehc","acdaajjfjcaeahcddage","edbbehfdiddc","ghabih","ba","dhjhdbieifabebajf","cccdhicdbdf","jfgdddh","chhjg","fgheacjabhiiihefbji","jhcfbgbbgfe","jgffhddba","jibffbeijfcif","dcghgfddfhj","gaggjcdcaaf","igjiaajgcjhbeeebdf","gejibddcbj","jcaaebfebjh","jeedhcejgbegide","jebfehdfdibg","hdefhaia","eb","fjchhceceijfi","egabjjcdbegfeabc","gbiagfgfg","gfajge","iii","dccjjeajd","aihegdchjef","gdaiegffaih","haacjdcfheheeejefg","bcde","agcbagagadfjfdghdbb","ejjiageabfh","gichcecbfd","iacajf","fdfeaajhccbhb","aecc","da","ecgcbdggffjg","biebjjhfidb","dadfcigjif","badafaheg","gddadiifadaa","echjgchihgadb","bhgaghbihef","cjihigiiibdc","bdheddceciaib","ggegccjahfbib","jfabidhcjefcfd","iiiadhfhaig","geedcbchc","bafhbicaeidjg","hfgiefdcgjjieejii","hgiiigfcididicgaijde","ihdbeahaehgd","difgjfagjfidcdbggce","ajdfddjbbdjjb","iccabdaahhgcdejf","gichhgejcgddcgbij","jjea","gcigbjhbaadjhi","jjeeefibachiddid","hjbehbeic","adibfgfdgfgghgbggaa","biggeedhffd","hffdaaeidhfjgj","ige","ichijijc","bhjh","bifeidf","hcgd","jfbdabjbcadjgahgjd","fhghdhfahibcbieiab","gcjijfbiigiegb","ibgabbhbijadhgib","djadidiihhdfhiabb","badefeccfjgca","edehccejiajcb","adjf","afcefdjajhjhddffbjb","biejjg","ffjfhieaebhbiag","gaegidbb","jaahhjfca","egg","jeeaaffch","bjaaafccjiii","gcghehg","egdibghgbhicdfdcicif","jidaafdbhggfea","daceegcdfbbbehejdgej","jdbjcaad","aihf","fhgahbafcd","bgcdcdejeiefdggfhha","ccafhij","hdahgjieaacabfa","hgjeajaacfce","jhejhibcbdacgjbjhbe","hajgigd","aaid","fbjhbd","eaddhgedigbffgbhcc","diiiabffdifheaaahe","cifigegjbibihd","ahhiffjfff","eebhji","cidjigijdaghhcjic"])


    pass