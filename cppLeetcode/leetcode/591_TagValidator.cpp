/*

# 591. Tag Validator


# Given a string representing a code snippet, you need to implement a tag validator to parse the code and return whether it is valid.
# A code snippet is valid if all the following rules hold :

# 1. The code must be wrapped in a valid closed tag.Otherwise, the code is invalid.
# 2. A closed tag(not necessarily valid) has exactly the following format : <TAG_NAME>TAG_CONTENT< / TAG_NAME>.
#    Among them, <TAG_NAME> is the start tag, and < / TAG_NAME> is the end tag.The TAG_NAME in start and end tags should be the same.
#    A closed tag is valid if and only if the TAG_NAME and TAG_CONTENT are valid.
# 3. A valid TAG_NAME only contain upper - case letters, and has length in range[1, 9].Otherwise, the TAG_NAME is invalid.

# 4. A valid TAG_CONTENT may contain other valid closed tags, cdata and any characters(see note1) EXCEPT unmatched <,
	#    unmatched start and end tag, and unmatched or closed tags with invalid TAG_NAME.Otherwise, the TAG_CONTENT is invalid.
	# 5. A start tag is unmatched if no end tag exists with the same TAG_NAME, and vice versa.
	#    However, you also need to consider the issue of unbalanced when tags are nested.
	# 6. A < is unmatched if you cannot find a subsequent >.And when you find a < or < / , all the subsequent characters until the next >
	#    should be parsed as TAG_NAME(not necessarily valid).
	# 7. The cdata has the following format : <![CDATA[CDATA_CONTENT]]>.
	#    The range of CDATA_CONTENT is defined as the characters between <![CDATA[and the first subsequent]]>.
	# 8. CDATA_CONTENT may contain any characters.The function of cdata is to forbid the validator to parse CDATA_CONTENT,
	#    so even it has some characters that can be parsed as tag(no matter valid or invalid), you should treat it as regular characters.


	# Valid Code Examples :

	# Input : "<DIV>This is the first line <![CDATA[<div>]]></DIV>"
	# Output : True

	# Explanation :

	# The code is wrapped in a closed tag : <DIV> and < / DIV>.
	# The TAG_NAME is valid, the TAG_CONTENT consists of some characters and cdata.
	# Although CDATA_CONTENT has unmatched start tag with invalid TAG_NAME, it should be considered as plain text, not parsed as tag.
	# So TAG_CONTENT is valid, and then the code is valid.Thus return true.


	# Input: "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"
	# Output : True

	# Explanation :
	# We first separate the code into : start_tag | tag_content | end_tag.
	# start_tag -> "<DIV>"
	# end_tag -> "</DIV>"

	# tag_content could also be separated into : text1 | cdata | text2.
	# text1 -> ">>  ![cdata[]] "
	# cdata -> "<![CDATA[<div>]>]]>", where the CDATA_CONTENT is "<div>]>"
	# text2 -> "]]>>]"

	# The reason why start_tag is NOT "<DIV>>>" is because of the rule 6.
	# The reason why cdata is NOT "<![CDATA[<div>]>]]>]]>" is because of the rule 7.

	# Invalid Code Examples :
# Input : "<A>  <B> </A>   </B>"
# Output : False
# Explanation : Unbalanced.If "<A>" is closed, then "<B>" must be unmatched, and vice versa.

# Input : "<DIV>  div tag is not closed  <DIV>"
# Output : False

# Input : "<DIV>  unmatched <  </DIV>"
# Output : False

# Input : "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"
# Output : False

# Input : "<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"
# Output : False

# Input : "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"
# Output : False

# Note :
	# For simplicity, you could assume the input code(including the any characters mentioned above)
	# only contain letters, digits, '<', '>', '/', '!', '[', ']' and ' '.

*/

/*
	A simple summary for all the elements in this syntax is like this:

	tag :
	<tagname> + content + </tagname>
	tagname :
	[A-Z]{1, 9}                 # 1 ~ 9 uppercase chars
	content :
	(tag|cdata|text)*           # 0 or more of : tag, cdata, text
	cdata :
	"<![CDATA[" + .* + "]]>"
	text :
	[^<]+                       # non '<' chars

	So we can just create parser for each elements, and dedicate the work to the right parsers.
*/
#include <string>
#include <stack>


using std::string;
using std::stack;

class TagValidator {

	/*
		591.Tag-Validator
		此题的表述非常复杂，需要逐条分析，各个击破。

		首先检测是否 cdata 的段首关键字<![CDATA[。有的话,在遇到cdata段尾关键字]]>之前，所有字符不用check。
		如果不满足条件1，则检测是否 end tag 的标记</。有的话就遍历直到找到>，分割这段TagName，检测TagName是否和栈顶的tag匹配，退栈。另外，如果退栈后为空，说明这是最后一个end tag，此时应该对应code的末尾。
		如果不满足条件2，则检测是否 start tag 的标记<。有的话就就遍历直到找到>，分割这段TagName，判断TagName是否合法，将TagName推入栈。注意，另外，如果这是栈第一次非空，说明这是第一个start tag，此时应该对应code的开头。
		在遍历完整个code字符串之后，还要保证栈空，且栈曾经非空过。这里可以用一个ever的变量来记录是否曾经有tag入栈过。
	*/

	bool isValid(string code) 
    {
        stack<string>TagStack;
        int i=0;
        bool cdata_flag=0;
        bool ever=0;

        while (i<code.size())
        {
            if (cdata_flag==0 && i+9<=code.size() && code.substr(i,9)=="<![CDATA[")
            {
                cdata_flag=1;
                i+=9;
                continue;
            }
            
            if (cdata_flag==1)
            {
                if (i+3<=code.size() && code.substr(i,3)=="]]>")
                {
                    cdata_flag=0;
                    i+=3;
                    continue;
                }
                else
                {
                    i++;
                    continue;
                }
                
            }
            
            if (code[i]=='<' && i+1<code.size() && code[i+1]!='/')
            {
                i++;
                int i0=i;
                while (i<code.size() && code[i]!='>') i++;
                if (i==code.size()) return false;
                string TagName=code.substr(i0,i-i0);
                
                if (validTagName(TagName)==false)
                    return false;
                else if (TagStack.empty() && i0-1!=0) // must start with a tag
                    return false;
                else
                {
                    TagStack.push(TagName);
                    ever=1; 
                }
                i++;
                continue;
            }
            
            if (code[i]=='<' && i+1<code.size() && code[i+1]=='/')
            {
                i+=2;
                int i0=i;
                while (i<code.size() && code[i]!='>') i++;
                if (i==code.size()) return false;
                string TagName=code.substr(i0,i-i0);
                
                if (TagStack.empty() || TagStack.top()!=TagName)
                    return false;
                else if (TagStack.size()==1 && i<code.size()-1)  // must end with a tag
                    return false;
                else
                    TagStack.pop();
                i++;
                continue;
            }
            
            i++;
        }
        
        if (TagStack.empty() && ever==1)
            return true;
        else
            return false;
        
    }
    
	bool validTagName(string t)
	{
		if (t=="") return false;
		if (t.size()>9) return false;
		for (int i=0; i<t.size(); i++)
		{
			if (t[i]<'A' || t[i]>'Z')
				return false;
		}
		return true;
	}

	bool isValid(string code) 
    {
        stack<string>Stack;
        
        int i=0;
        bool ever = 0;
        
        while (i<code.size())
        {
            if (i+8<code.size() && code.substr(i,9)=="<![CDATA[")
            {
                i+=9;
                int i0=i;
                while (i+2<code.size() && code.substr(i,3)!="]]>")
                    i++;
                if (i+2==code.size()) return false;
                i+=3;                
            }
            
            else if (i+1<code.size() && code.substr(i,2)=="</")
            {
                i+=2;
                int i0=i;
                while (i<code.size() && code[i]!='>')
                    i++;
                if (i==code.size()) return false;
                string tagname = code.substr(i0,i-i0);
                if (Stack.empty() || Stack.top()!=tagname)
                    return false;
                Stack.pop();
                i++; 
                if (Stack.empty() && i!=code.size()) return false;                             
            }
            
            else if (code[i]=='<')
            {
                i++;
                int i0=i;
                while (i<code.size() && code[i]!='>')
                    i++;
                if (i==code.size()) return false;
                string tagname = code.substr(i0,i-i0);
                if (!isValidTag(tagname)) return false;                
                if (ever==false && i0!=1) return false;
                ever = true;                
                Stack.push(tagname);
                i++;
            }
            
            else
                i++;
        }
        
        if (!Stack.empty()) return false;
        if (ever==0) return false;
        
        return true;
    }
    
    bool isValidTag(string tagname)
    {
        if (tagname.size()<1 || tagname.size()>9) return false;
        for (auto ch:tagname)
            if (ch<'A'|| ch>'Z') return false;
        return true;
    }

public:
	bool isValid(string&& code) {
		int i = 0;
		return validTag(code, i) && i == code.size();
	}

	bool validTag(string& s, int & i) {
		int j = i;
		string tag = parseTagName(s, j);

		if (tag.empty())
			return false;

		if (!validContent(s, j))
			return false;

		int k = j + tag.size() + 2;
		if (k >= s.size() || s.substr(j, k + 1 - j) != "</" + tag + ">")
			return false;

		i = k + 1;
		return true;
	}

	string parseTagName(string& s, int& i) {
		if (s[i] != '<')
			return "";

		int j = s.find('>', i);
		if (j == string::npos || j - i - 1 > 9 || j - i - 1 < 1)
			return "";

		string tag = s.substr(i + 1, j - 1 - i);
		for (auto c : tag) {
			if (c < 'A' || c > 'Z')
				return "";
		}
		i = j + 1;
		return tag;
	}

	bool validContent(string& s, int& i) {
		int j = i;
		while (j < s.size()) {
			if (!validText(s, j) && !validCDData(s, j) && !validTag(s, j))
				break;
		}
		i = j;
		return true;
	}

	bool validText(string&s, int&i) {
		int  j = i;
		while (i < s.size() && s[i] != '<')
			i++;

		return i != j;
	}

	bool validCDData(string& s, int& i) {
		if (s.find("<![CDATA[", i) != i)
			return false;
		
		int j = s.find("]]>", i);

		if (j == string::npos)
			return false;

		i = j + 3;
		return true;
	}

};

void Test_591_TagValidator() {

	bool res = false; 

	// True
	res = TagValidator().isValid(string("<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"));

	res = TagValidator().isValid(string("<DIV>This is the first line <![CDATA[<div>]]></DIV>"));

	// False
	res = TagValidator().isValid(string("<A>  <B> </A>   </B>"));

	res = TagValidator().isValid(string("<DIV>  div tag is <DIV> not closed  </DIV>"));

	res = TagValidator().isValid(string("<DIV>  div tag is not closed  <DIV>"));

	res = TagValidator().isValid(string("<DIV>  unmatched <  </DIV>"));

	res = TagValidator().isValid(string("<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"));

	res = TagValidator().isValid(string("<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"));

	res = TagValidator().isValid(string("<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>"));
}
