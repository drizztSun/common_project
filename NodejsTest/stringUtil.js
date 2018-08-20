'use strict'



class stringUtil {

    constructor(str1, str2) {    
        if (typeof str1 !== 'string' ||
            typeof str2 !== 'string') {
            throw Error("Invalid type")
        }
        this._str1 = str1;
        this._str2 = str2;
    }

    commonSubSequence() {
        let len1 = this._str1.length;
        let len2 = this._str2.length;
    
        // stepValue for each step 
        let stepValue = new Array(len1 + 1);
        for (let i = 0; i < stepValue.length; i++) {
            stepValue[i] = new Array(len2 + 1);
        }
    
        for (let i = 0; i < len1 + 1; i++) {
            stepValue[i][0] = 0;
        }
    
        for (let i = 0; i < len2 + 1; i++) {
            stepValue[0][i] = 0;
        }
    
        //
        let maxValue = -1;
        for (let i = 0; i < len1; i++) {
             for (let j = 0; j < len2; j++) {
                // make sure the character is same of not, i                
                if (this._str1[i] == this._str2[j]) {
                    stepValue[i + 1][j + 1] = stepValue[i][j] + 1;

                } else {
                    if (stepValue[i + 1][j] > stepValue[i ][j + 1]) {
                        stepValue[i + 1][j + 1] = stepValue[i + 1][j];
                    } else {
                        stepValue[i + 1][j + 1] = stepValue[i ][j + 1];
                    }
                }
                // make sure the max length of common sequence
                if (maxValue < stepValue[i + 1][j + 1]) {
                    maxValue = stepValue[i + 1][j + 1];
                }
            }
        }
    
        let commonSeq = '';
        let i = len1;
        let j = len2;
        let value = 0;
        while (i > 0 && j > 0) {
            //value = stepValue[i - 1][j - 1];
            if (this._str1[i - 1] == this._str2[j - 1]) {
                commonSeq = this._str1[i - 1] + commonSeq;
                i--;
                j--;
            } else {
                if (stepValue[i - 1][j] > stepValue[i ][j -1]) {
                    i--;
                } else {
                    j--;
                }
            }
        }

        return commonSeq;
    }

    commonSubString() {
        let len1 = this._str1.length;
        let len2 = this._str2.length;
    
        // stepValue for each step 
        let stepValue = new Array(len1 + 1);
        for (let i = 0; i < stepValue.length; i++) {
            stepValue[i] = new Array(len2 + 1);
        }
    
        for (let i = 0; i < len1 + 1; i++) {
            stepValue[i][0] = 0;
        }
    
        for (let i = 0; i < len2 + 1; i++) {
            stepValue[0][i] = 0;
        }

        let maxValue = -1;
        let maxX = -1;
        let maxY = -1;
        for (let i = 0; i < len1; i++) {
            for (let j = 0; j < len2; j++) {
                // make sure the character is same of not, i                
                if (this._str1[i] == this._str2[j]) {
                    stepValue[i + 1][j + 1] = stepValue[i][j] + 1;
                } else {
                    stepValue[i + 1][j + 1] = 0;
                }
                // make sure the max length of common sequence
                if (maxValue < stepValue[i + 1][j + 1]) {
                    maxValue = stepValue[i + 1][j + 1];
                    maxX = i + 1;
                    maxY = j + 1;
                }
            }
        }
    
        let commonSeq = '';
        let i = maxX;
        let j = maxY;
        let value = 0;
        while (i > 0 && j > 0 && stepValue[i][j] != 0) {
            value = stepValue[i - 1][j - 1];
            if (this._str1[i - 1] == this._str2[j - 1]) {
                commonSeq = this._str1[i - 1] + commonSeq;
                i--;
                j--;
            } else {
                break;
            }
        }

        return commonSeq;
    }
}



/***
 * Leetcode 5 
 * */
class longest_Palindromic_substring {

    static way(str) {
        if (typeof str !== 'string')
            return;
    
        const len = str.length;
        let maxLen = -1;
        let maxS = -1;
        let maxE = -1;
    
        for (let i = 0; i < len; i++) {
        
            let j = i;
            let start = j - 1;
            let end = j + 1;
            while (start >= 0 && end < len && str[start] == str[end]) {
                start--;
                end++;
            }
        
            let length = end - start - 1;
            if (maxLen < length) {
                maxLen = length;
                maxS = start + 1;
                maxE = end - 1;
            }
        
            start = j;
            end = j + 1;
            while (start >= 0 && end < len && str[start] == str[end]) {
                start--;
                end++;
            }
        
            length = end - start - 1;
            if (maxLen < length) {
                maxLen = length;
                maxS = start + 1;
                maxE = end - 1;
            }

        }
    
        return str.substr(maxS, maxLen);
    }

    static way2(str) {
        if (typeof str !== 'string')
            return;
    
        const len = str.length;
        let maxLen = -1;
        let maxS = -1;
        let maxE = -1;
    
        for (let i = 0; i < len;) {
        
            let j = i;
            // skip some substring like 'bbbb'
            while (j < str.length - 1 && str[j + 1] == str[j]) j++;

            let start = i - 1;
            let end = j + 1;
            while (start >= 0 && end < len && str[start] == str[end]) {
                start--;
                end++;
            }
        
            let length = end - start - 1;
            if (maxLen < length) {
                maxLen = length;
                maxS = start + 1;
                maxE = end - 1;
            }
        
            start = i;
            end = j + 1;
            while (start >= 0 && end < len && str[start] == str[end]) {
                start--;
                end++;
            }
        
            length = end - start - 1;
            if (maxLen < length) {
                maxLen = length;
                maxS = start + 1;
                maxE = end - 1;
            }

            i = j + 1;    
        }
    
        return str.substr(maxS, maxLen);
    }
}



class Reverse_Vowels_String{

    static way1(str) {
    
        const len = str.length;
        var start = 0;
        var end = len - 1;
        var vowel = 'aeiou';
        var array = str.split("");
        var isVowel = function (a) {
            return (a == 'a' || a == 'A' || 
                            a == 'e' || a == 'E' || 
                            a == 'i' || a == 'I' || 
                            a == 'o' || a == 'O' || 
                            a == 'u' || a == 'U');
        };
    
        while (true) {
        
            while (start < len && !isVowel(array[start]))
                start++;
        
            while (end >= 0 && !isVowel(array[end]))
                end--;
        
            if (end <= start)
                break;
        
            var x = array[start];
            array[start] = array[end];
            array[end] = x;
            start++;
            end--;
        }
    
        var result = '';
        for (var i = 0; i < array.length; i++) {
            result += array[i];
        }
    
        return result;
    }
}

class String_Reverse{

    static way(str) {
        let low = 0;
        let high = str.length - 1;

        while (low < high) {
            let a = str[low];
            str[low] = str[high];
            str[high] = a;
        
            low++;
            high--;
        }

        return str;
    }
}

class strHelper{

    static atoi(str) {
        const len = str.length;
        let a = 1;
        let result = 0;
        for (let i = len - 1; i >= 0; i--) {
            let b = str[i] - '0';
            b *= a;
            result += b;
            a *= 10;
        }
        return result;
    }

}


class LongestCommonPrefix {

    static way(strs) {
        if (strs.length === 0) {
            return "";
        }
    
        let j = 0;
        let commonPrefix = '';
        let done = false;
        while (!done) {
            let common = '';
            for (let i = 0; i < strs.length; i++) {
                if (j >= strs[i].length) {
                    done = true;
                    break;
                }
                if (common === '') {
                    common = strs[i][j];
                } else if (strs[i][j] === common) {
                    continue;
                } else {
                    done = true;
                    break;
                }
            }
            
            j++;
            if (!done) 
                commonPrefix += common;
        }
        return commonPrefix;
    }
};


/*
 *  '?' Matches any single character.
 *  '*' Matches any sequence of characters (including the empty sequence).
 *  
 * Some examples:
    isMatch("aa","a") → false
    isMatch("aa","aa") → true
    isMatch("aaa","aa") → false
    isMatch("aa", "*") → true
    isMatch("aa", "a*") → true
    isMatch("ab", "?*") → true
    isMatch("aab", "c*a*b") → false
 * */
class StringMatch {

    static matchSolution(str, match) {
        let star = false
        let s = 0;
        let p = 0;
        let start = 0;
        let ps = 0;

        for (; s < str.length && p < match.length; s++, p++) {
        
            switch (match[p]) {

                case '?':
                    break;
                case '*':
                    {
                        star = true;
                        start = s;
                        ps = p;
                    
                        while (ps < match.length && match[ps++] == '*');
                        
                        if (ps == match.length)
                            return true;
                    
                        s = start - 1;
                        p = ps - 1
                    }
                    break;
                default:
                    {
                        if (str[s] != match[p]) {
                            if (!star)
                                return false;

                            start++;
                            s = start - 1;
                            p = ps - 1;
                        }
                    }
            }
        }

        if (p == match.length) {
            return s == str.length;
        } else {
            while (p < match.length && match[p++] == '*')        ;
            return p == mathc.legnth;
        }
    }

    static matchSolutionLoop(str, match) {

    }
}


function main() {
    
    console.log("-------------------------Start StringUtil----------------------------------------")

    let str1 = 'xyxxzxyzxy';
    let str2 = 'zxzyyzxxyxxz';
    console.log('Str1 : ' + str1 + " str2 : " + str2 + " has common seq :  " 
        + new stringUtil(str1, str2).commonSubSequence());

    str1 = "2ushge93249"
    str2 = "tru111ghzzz3"
    console.log('Str1 : ' + str1 + " str2 : " + str2 + " has common seq :  " 
        + new stringUtil(str1, str2).commonSubSequence());


    str1 = "12345syx987676";
    str2 = "126798syx98098676";

    console.log('Str1 : ' + str1 + " str2 : " + str2 + " has common seq :  " 
        + new stringUtil(str1, str2).commonSubString());


    str1 = '12328473ABCDCBA3284737';
    console.log('Str 1 : ' + str1 + " has symmettic string : " + longest_Palindromic_substring.way(str1));
    console.log('Str 1 : ' + str1 + " has symmettic string : " + longest_Palindromic_substring.way2(str1));
    console.log(longest_Palindromic_substring.way('a'));
    console.log(longest_Palindromic_substring.way('bb'));

    //let a = new String("LeetCode");
    let a = new String("hello");
    console.log("the reverse string of LeetCode is : " + Reverse_Vowels_String.way1(a));

    
    console.log("12345 string becomes number : " + strHelper.atoi('12345'));
    
    console.log("The common string is " + LongestCommonPrefix.way(['12348', '123456', '1234567']));
    
    console.log("check string match is : " + StringMatch.matchSolution("a", "a"));    
    console.log("check string match is : " + StringMatch.matchSolution("aaa", "a"));
    console.log("check string match is : " + StringMatch.matchSolution("adddbc", "ad*dbc"));
    console.log("check string match is : " + StringMatch.matchSolution("aaa", "a*"));
    console.log("check string match is : " + StringMatch.matchSolution("aaa", "*"));
    console.log("check string match is : " + StringMatch.matchSolution("aaa", "a?*"));
    console.log("check string match is : " + StringMatch.matchSolution("aab", "c*a*b"));

    console.log("-------------------------End StringUtil----------------------------------------")
}


exports.main = main;