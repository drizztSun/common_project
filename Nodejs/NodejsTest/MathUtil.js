'use strict'

const arrayGenerator = require('./ArrayGenetator.js');
const sortUtil = require('./sortUtil.js');

class MathWithBitOps{

     static add(num1, num2) {
    
        if (num2 == 0)
            return num1;
    
        let a1 = num1 ^ num2;
        let b1 = (num1 & num2) << 1;
    
        return MathWithBitOps.add(a1, b1);
    }

    static minus(num1, num2) {
    
        if (num2 == 0)
            return num1;

        let a1 = num1 ^ num2;
        let b1 = (~num1 & num2) << 1;
        return MathWithBitOps.minus(a1, b1);
    }

    static multiply(num1, num2) {

    }

    static devide(num1, num2) {

    }


}

class Number_is_power_of_4{
    static way(num) {
        return ((num - 1) & num) == 0 && (num - 1) % 3 == 0;
    }

    static way2(num) {
        return ((num - 1) & num) == 0 && (num & 0x55555555) != 0; 
    }

}

/*** Important
 * 
 * */
class Math_power {
    // O(logn)
    static way(x, n) {
    
        if (n == 1) {
            return x;
        } else {
            let y = Math_power.way(x, n >> 1);
            y = y * y;
            if (n % 2 == 1)
                y = y * x;
            return y;
        }
    }

    // O(logn)
    static way_binary(x, n) {
        let y = 1;
        let times = n;
        let num = [];

        while (times) {
            let a = times & 1;
            num.push(a);
            times >>= 1;
        }

        for (let i = num.length - 1; i >= 0; i--) {
            y = y * y;
            if (num[i] == 1)
                y = y * x;
        }
        return y;
    }

    static way3(x, n) {
        let result = 1;
        let y = x
        while (n != 0) {
            if (n & 1) {
                result *= y;
            }
            y *= y;
            n = Math.floor(n / 2);
        }
        return result;
    }

    static way2(x, n) {
        let result = 1;
        for (; n; n >>= 1) {
            if (n & 1)
                result *= x;
            x *= x;
        }
        return result;
    }
}




/*** Important
 * Maximum value of a sub array in a given array
 * **/
class Array1DMaxValue {

    static MaxSumOfSubArray(array) {
        if (typeof array !== 'object')
            return { max : 0, startE : -1, endE : -1 };
    
        let k = 0;
        let start = 0;
        let end = 0;
        let maxSum = 0;
        let currentSum = 0;
    
        for (let i = 0; i < array.length; i++) {
        
            currentSum += array[i];
        
            if (currentSum < 0) {
                currentSum = 0;
                k = i + 1;
            }
        
            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = k;
                end = i;
            }
        }
    
        if (maxSum == 0) {
            maxSum = array[0];
            for (let i = 0; i < array.length; i++) {
                if (maxSum < array[i]) {
                    maxSum = array[i];
                    start = i;
                    end = i;
                }
            }
        }
    
        return { max : maxSum, startE : start, endE : end };
    }

    static MaxSumOfSubArray2(array) {
        let len = array.length;
        let dp = array[len - 1];
        let start = len - 1;
        let end = len - 1;
        let temp = n - 1;
        let maxVal = dp;
    
        for (let i = len - 2; i >= 0; --i) {
            if (dp > 0) {
                dp += array[i];
            } else {
                temp = i;
                dp = 0;
            }
        
            if (dp > maxVal) {
                maxVal = dp;
                start = i;
                end = temp;
            }
        }
    
        return { max: maxVal, startE : start, endE : end };
    }

    /***
     *  Max sum vaue of a rong array
     * */
    static MaxSumOfRongArray(array) {
        const len = array.length;
        let dp = 0;
        let start = 0;
        let end = 0;
        let temp = 0;
        let max1 = 0;
    
        for (let i = 0; i < len; ++i) {
        
            if (dp < 0) {
                dp = array[i];
                temp = i;
            } else {
                dp += array[i];
            }
        
            if (dp > max1) {
                max1 = dp;
                start = temp;
                end = i;
            }
        }
    
    
        dp = 0;
        temp = 0;
        let min = 0;
        let sum = 0;
        let max2 = 0;
        let start1 = 0;
        let end1 = 0;
    
        for (let i = 0; i < len; ++i) {
        
            if (dp > 0) {
                dp = array[i];
                temp = i;
            } else {
                dp += array[i]
            }
        
            if (min > dp) {
                min = dp;
                start1 = temp;
                end1 = i;
            }
            sum += array[i];
        }
        max2 = sum - min;
    
        //
        if (max2 > max1) {
            max1 = max2;
            start = end1 + 1;
            end = start1 - 1;
        }
    
    
        return { max : max1, startE : start, endE : end }
    }
}

/**
 * Lesson 10 Get Sum of two numbers are equal to n 
 * */
function getPairNumberEqualToN(array, N) {

    const sortUtil = require('./sortUtil.js');
    let sortedArray = new sortUtil.sortKit(array).bottomUpSort();
    
    let begin = 0;
    let end = sortedArray.length - 1;
    let sum = 0;

    while (end > begin && sum != N) {

        sum = sortedArray[begin] + sortedArray[end];

        if (sum == N)
            break; 

        if (sum > N) {
            end--;
        } else {
            begin++;
        }
    }

    return {a : begin, b : end};
}

/***
 * lesson 15 Array has 2N elements. Split it to two parts, which has closer sum of each N element
 * */
class SplitArray2TwoEqualPart {

    /*
     * It is only wokring when all elements is no less than 0. but if there is one or more less than 0. we have to minus the negative value for each amount.
     * then submit this abs value, after we get final.
    **/
    
    static solution1(array) {
    
        const length = array.length;
        const halfLen = length / 2;
        let SUM = 0;

        for (let i = 0; i < length; i++)
            SUM += array[i];
    
        const halfSUM = SUM / 2;
        let V = arrayGenerator.generate3DArray(length + 1, halfLen + 1, SUM / 2 + 2);
    
        for (let i = 1; i < length + 1; i++) {
            for (let j = 1; j < Math.min(i, halfLen + 1); j++) {
            //for (let z = array[i - 1]; z < SUM / 2 + 1; z++)
                for (let z = SUM / 2 + 1; z >= array[i - 1]; z--)
                    V[i][j][z] = Math.max(V[i - 1][j][z], V[i - 1][j - 1][z - array[i - 1]] + array[i - 1]);
            }

        }
    
        let i = length;
        let j = halfLen;
        let z = SUM / 2 + 1;
        let result = [];

        while (i > 0 && z > 0 && j > 0) {
            if (V[i][j][z] == V[i - 1][j - 1][z - array[i - 1]] + array[i - 1]) {
                result.push(array[i - 1]);
                j--;
                z -= array[i - 1];
            }
            i--;
        }
    
        return {max: V[length][halfLen][SUM/2 + 1], res : result};
    }

    static solution2(array) {
    
        const length = array.length;
        const halflength = length / 2;
        let SUM = 0;

        for (let i = 0; i < length; i++)
            SUM += array[i];
    
        const halfSUM = SUM / 2;
        let V = arrayGenerator.generate2DArray(halflength + 1, halfSUM + 2);

        for (let i = 0; i < length; i++) {
            for (let j = 1; j <= Math.min(halflength, array[i]); j++) {
                for (let z = halfSUM + 1; z >= array[i]; z--) {
                    V[j][z] = Math.max(V[j - 1][z - array[i]] + array[i], V[j][z]);
                }
            }
        }

        return V[halflength][halfSUM + 1];
    }

    static solution3(array) {

        const length = array.length;
        const halflength = length / 2;
        let SUM = 0;
    
        for (let i = 0; i < length; i++)
            SUM += array[i];
    
        const halfSUM = SUM / 2;
        let V = arrayGenerator.generate2DArray(halflength + 1, halfSUM + 2);
        V[0][0] = 1;
    
        for (let i = 0; i < length; i++) {
            for (let j = 1; j <= Math.min(i, halflength); j++) {
                for (let z = halfSUM + 1; z >= array[i]; z--) {
                    if (V[j - 1][z - array[i]] == 1)
                            V[j][z] = 1
                }
            }
        }
    
        let res = [];
        for (let i = halfSUM + 1; i >= 0; i--) {
            if (V[halflength][i] == 1)
                res.push(i);
        }

        return res;
    }
}



/****
 *  Get 2D Array maxmium value of sub array
 * */
class Array2DMaxVal {

    constructor() {

    }

    static get2DArray_sub_maximum_value_low(array, d1, d2) {
    
        let maxVal = 0;
        for (let i_min = 0; i_min < d1; i_min++) {

            for (let j_min = 0; j_min < d2; j_min++) {

                for (let i_max = i_min; i_max < d1; i_max++) {

                    for (let j_max = j_min; j_max < d2; j_max++) {

                        maxVal = arrayGenerator.maxValue(maxVal, Array2DMaxVal.ArraySum(array, i_min, i_max, j_min, j_max));
                    }
                }
            }
        }
        return maxVal;
    }

    static ArraySum(A, i_min, i_max, j_min, j_max) {

        let max = 0;
        for (let i = i_min; i < i_max; i++) {
            for (let j = j_min; j < j_max; j++) {
                max += A[i][j];
            }
        }
        return max;
    }

    static BC(array, i_min, i_max, j) {
        return array[i_max][j] - array[i_max][j - 1] - array[i_min - 1][j] + array[i_min - 1][j - 1];
    }


    static get2DArray_PS(array, d1, d2) {
    
        let V = arrayGenerator.generate2DArray(d1 + 1, d2 + 1);
        let max = 0;
        for (let i = 1; i < d1 + 1; i++) {
            for (let j = 1; j < d2 + 1; j++) {
                V[i][j] = V[i - 1][j] + V[i][j - 1] - V[i - 1][j - 1] + array[i - 1][j - 1];
            }
        }
    
        return V;
    }

    static get2DArray_MaxSubValue(array, d1, d2) {
    
        let maxVal = 0;
        let scope = { x : 0, y : 0, z : 0, j : 0};
        let V = Array2DMaxVal.get2DArray_PS(array, d1, d2);

        for (let i_min = 0; i_min < d1; i_min++) {
            for (let i_max = i_min; i_max < d2; i_max++) {
            
                let start = Array2DMaxVal.BC(V, i_min + 1, i_max + 1, d2);
                let temp = d2 - 1;

                for (let j = d2 - 2; j >= 0; j--) {
                    if (start < 0) {
                        start = 0;
                        temp = j;
                    }
                     
                    start += Array2DMaxVal.BC(V, i_min + 1, i_max + 1, j + 1);

                    if (start > maxVal) {
                        maxVal = start;
                        scope.x = i_min;
                        scope.y = i_max;
                        scope.z = j;
                        scope.j = temp;
                    }
                }
            }
        }
        return { maxValue : maxVal, dir : scope };
    }
}


/*
 * Get two number in array to make their SUM is eqaul to 9
 * */


class CalculateTwoNumEqualToTarget{

    static way1(array, target) {
    
        let util = new sortUtil.sortKit(array, array.length);
        let b = util.bottomUpSort();

        let i = 0;
        let j = b.length - 1;
        while (j > i) {
            if (b[j] + b[i] == target) {
                return [b[i], b[j]];
            }

            if (b[j] + b[i] > target)
                j--;
            else
                i++
        }
        return [0, 0];
    }
}


/*** Important
 * 
 * */
class Integer_Split_Max_Product {
    static way(n) {

        let MAX = [];
        for (let i = 0; i < n + 1; i++) {
            MAX[i] = 0;
        }

        for (let i = 3; i < n + 1; i++) {
            for (let j = 1; j < i; j++) {
            
                /*
                 * Try to write i as: i = j + S, where S=i-j corresponds to either one number or a sum of two or more numbers
                 * Assuming that j + S corresponds to the optimal solution for MAX[i]
                 * We have two cases:
                 * 1.    i is the sum of the two numbers. j and S=i-j, and MAX[j] = j * (i - j)
                 * 2.    i is the sum of three numbers or more,  j is one, S=i-j is a sum of at least 2 numbers,
                 *    so the product of the numbers in the sum for S is MAX[i-j]
                 *    MAX[j] = j * MAX[i - j]
                */

                MAX[i] = Math.max(MAX[i], Math.max(j * (i - j), j * MAX[i - j]));
            }
        }

        return MAX[n];
    }
}

/**** Important
 * 
 * **/

class Self_Crossing {

    static way(Line) {

        const len = Line.length;
        if (len <= 3)
            return false;

        let i = 3;
        for (; i < len && Line[i] > Line[i - 2]; i++);
    
        if (i > len)
            return false;

        if ((i >= 4 && Line[i] > Line[i - 2] - Line[i - 4]) ||
            (i == 3 && Line[i] == Line[i-2]) ) {
            Line[i - 1] -= Line[i - 3];
        }
    
        i++;
        while (i < len) {
            if (Line[i] >= Line[i - 2])
                return true;
            i++;
        }
        return false;
    }

}

/***
 * 
 * leetcode 12 13 Roman To Integer / Integer to Roman
 * 
 * */
class ConverRoman2Interger {

    /*
     * I,1   IV,4  V,5  IX,9  X,10  XX,20  
     * XL, 40   L,50
     * XC, 90   C,100
     * CD, 400  D,500
     * CM, 900  M,1000      
    **/


    static Int2Roman(number) {
    
        if (number > 3999)
            return null;
    
        let a = 10;
        let el = [];
        let RomaTable = [];
        RomaTable[0] = ['I', 'IV', 'V', 'IX'];
        RomaTable[1] = ['X', 'XL', 'L', 'XC'];
        RomaTable[2] = ['C', 'CD', 'D', 'CM'];
        RomaTable[3] = ['M'];
        let i = 0;

        while (number != 0) {
            let b = number % a;
            let num = b;
        
            let str = '';
            if (num < 4) {
                while (num--)
                    str += RomaTable[i][0];
            } else if (num == 4) {
                str += RomaTable[i][1];
            } else if (num == 5) {
                str += RomaTable[i][2];
            } else if (num > 5 && num < 9) {
                str += RomaTable[i][2];
                num -= 5;
                while (num--) {
                    str += RomaTable[i][0];
                }
            }
            else if (num == 9) {
                str += RomaTable[i][3]; 
            } 
        
            el.push(str);
            number = (number - b) / a;
            i++;
        }
    
        let result = '';
        for (let i = el.length - 1; i >= 0; i--) {
            result += el[i];
        }

        return result;
    }

    static Roman2Int(str) {
        let result = 0;
        let lastNum = 0;
        for (let i = 0; i < str.length; i++) {
            let b = 0;
            switch (str[i]) {
                case 'M':
                    b = 1000;
                    break;
                case 'C':
                    b = 100;
                    break;
                case 'D':
                    b = 500;
                    break;
                case 'L':
                    b = 50;
                    break;
                case 'X':
                    b = 10;
                    break;
                case 'V':
                    b = 5;
                    break;
                case 'I':
                    b = 1;
                    break;
                default :
            }
        
            result += b;
            if (lastNum < b) {
                if (lastNum == 1 && b == 5)
                    result -= 2;
                else if (lastNum == 1 && b == 10)
                    result -= 2;
                else if (lastNum == 10 && b == 50)
                    result -= 20;
                else if (lastNum == 10 && b == 100)
                    result -= 20;
                else if (lastNum == 100 && b == 500)
                    result -= 200
                else if (lastNum == 100 && b == 1000)
                    result -= 200;
            }
        
            lastNum = b;
        }
        return result;
    }
}

//class ThreeSum {

//    static way(arrNum, n) {

//        // sort the num
    
//        //
//        if (arrNumm[0] > n || arrNum[arrNum.length - 1] < n) {
//            return false;
//        }

//        // Binary search
//        let low = 0;
//        let high = arrNum.length;
//        let numNPos = (low + high) / 2;
//        while (low < high) {
//            if (arrNum[numNPos] == n) {
//                break;   
//            } else if (arrNum[numNPos] > n) {
//                high = numNPos;
//                numNPos = (low + high) / 2;
//            } else if (arrNum[numNPos] < n) {
//                low = numNPos + 1;
//                numNPos = (low + high) / 2;
//            }
//        }

//        while (low < numNPos) {
//            let a = arrNum[low];
//            for () {

//            }
//        }
//    }
//}


class Number_is_Palindrome{

    static way(number) {

        let str = [];
        while (number != 0) {
            let b = number % 10;
            str.push(b);
            number = (number - b) / 10;
        }


        let low = 0;
        let high = str.length - 1;
        while (low < high) {
            if (str[low] != str[high])
                return false;
            low++;
            high--
        }
        return true;
    }
}

class max_min {

    static way(arr) {
        return max_min.split_max_min_search(arr, 0, arr.length - 1);
    }

    static split_max_min_search(arr, s, e) {
        if (s == e) {
            return { max : arr[s], min: arr[s] };
        } else if (e - s == 1) {
            return { max : Math.max(arr[s], arr[e]), min : Math.min(arr[s], arr[e]) };
        }

        let min = Math.floor((s + e) / 2);
        let obj1 = max_min.split_max_min_search(arr, s, min);
        let obj2 = max_min.split_max_min_search(arr, min + 1, e);

        return { max: Math.max(obj1.max, obj2.max), min: Math.min(obj1.min, obj2.min) };
    }
}


/***
 * LeetCode 342 Power of Four
 * 
 * */
class is_Power_of_Two{
    static way(num) {
        return num > 0 && ((num - 1) & num) == 0;
    }
}

class is_Power_of_Three{

    static way(num) {
        let t = Math.floor(Math.log(Number.MAX_SAFE_INTEGER) / Math.log(3));
        let max3Power = Math.pow(3, t);
        return max3Power % num == 0;
    }
}

class is_Power_of_Four{
    
    static way(num) {
        // wrong for -2147483648
        let a = (((num - 1) & num) == 0);
        let b = (((num - 1) % 3) == 0);
        return (num - 1) & num == 0 && (num - 1) % 3 == 0;
    }

    static way2(num) {
        return ((num - 1) & num) == 0 && (num & 0x55555555) != 0;
    }
}


/**
 * Leetcode 8 String to Integer
 * 
 * **/
class convert_integer_to_string{

    static atoi(str) {
        let sum = 0;
        let based = 1;
        let negative = true;
        for (let i = str.length - 1; i >= 0; i--) {
            if (str[i] >= '0' &&　 str[i] <= '9') {
                sum += (str[i] - '0') * based;
                based *= 10;
            } else if (str[i] == '-'){
                negative = true;
            } else if (str[i] == '+') {
                negative = false;
            } else {
                return;
            }
        }
    
        if (negative) {
            sum = -sum; 
        }
        return sum;
    }

}

/*
 * 
 * Leetcode 2 Add Two Number
 * */

var addTwoNumbers = function (l1, l2) {
    
    let L1index = 0;
    let L2index = 0;
    let accum = 0;
    let result = [];
    let done = false;
    
    while (!done) {
        
        let num = 0;
        let a1 = accum;
        if (L1index < l1.length) {
            num += l1[L1index];
            L1index++;
        }
        if (L2index < l2.length) {
            num += l2[L2index];
            L2index++;
        }
        
        if (num >= 10) {
            num = num % 10;
            accum = 1;
        }
        
        result.push(num + a1);
        
        if (L1index >= l1.length && L2index >= l2.length)
            done = true;
        
    }
    
    return result;
};



/**
 * Leetcode 233 Number of Digit one
 * BOP 2.4
 * */
class NumberofDigit{

    /**
    * A > 2  (Ah + 1) * pow(10 * j)
    * A = 1  Ah * pow(10 * j) + A(rest)
    * A = 0  Ah * pow(10 * j)   
    */
    static numberOne(n) {
        let num = n;
        let lowNum = 0;
        let currentNum = 0;
        let highNum = 0;
        let Factor = 1;
        let result = 0;

        while (Math.floor(num / Factor) > 0) {

            lowNum = num - Math.floor(num / Factor) * Factor;
            currentNum = Math.floor(num / Factor) % 10;
            highNum = Math.floor(num / (Factor * 10));
    
            switch (currentNum) {

                case 0:
                    result += highNum * Factor;
                    break;
                case 1:
                    result += highNum * Factor + lowNum + 1;
                    break;
                default:
                    result += (highNum + 1) * Factor;
            }

            Factor *= 10;
        }

        return result;
    }
}

/**
 * 
 * BOP 2.2
 * 
 * **/
class Factorial_AmountOfZero {

    constructor(N) {
        this._number = N;
    }

    static way1(N) {
        let res = 0;
        for (let i = 1; i < N + 1; i++) {
            let j = i;
            while (j % 5 == 0) {
                res++;
                j = Math.floor(j / 5);
            }
        }
        return res;
    }

    static way2(N) {
        let res = 0;
        while (N) {
            res += Math.floor(N/5);
            N = Math.floor(N/5);
        }
        return res;
    }

}

/**
 * 
 * BOP 2.2
 * It is equal to how many 2, N! has 
 * **/
class Factorial_PosOfBinaryOne {

    constructor(N) {

    }

    static way1(N) {
        let res = 0;
        while (N) {
            res += Math.floor(N / 2)
            N = Math.floor(N / 2)
        }
        return res;
    }

}



// Main function of MathUtil
function main() {
    
    console.log("---------------------MathUtil.js Begin-----------------------")

    let a = 5;
    let b = 17;
    console.log('the result ' + a + ' + ' + b + ' = ' + MathWithBitOps.add(a, b));
    
    a = 2;
    b = 5
    console.log('the result ' + a + ' - ' + b + ' = ' + MathWithBitOps.minus(a, b));

    let arr = [1, 2, 3, 4, -7, -2, 2, 3];
    let c = Array1DMaxValue.MaxSumOfSubArray (arr);
    console.log("Array " + c + " has maxmuim sub array : " + [c.max, c.startE, c.endE]);

    c = Array1DMaxValue.MaxSumOfRongArray(arr);
    console.log("Array " + c + " has maxmuim sub array : " + [c.max, c.startE, c.endE]);


    let d = getPairNumberEqualToN([1, 3, 5, 7, 9, 2, 4, 6, 8, 11], 18);
    console.log("Num Pair has 19 request is " + [d.a, d.b]);
    
    
    
    // Verify 2D Array maximum value
    let A = arrayGenerator.generate2DArray(6, 6);
    for (let i = 0; i < 6; i++) {
        for (let j = 0; j < 6; j++) {
            A[i][j] = A[i][j] + i; 
        }
    }
    let B = Array2DMaxVal.get2DArray_MaxSubValue(A, 6, 6);
    console.log("Max sub value is " + B.maxValue + " Scope  " + [B.dir.x, B.dir.y, B.dir.z, B.dir.j]);


    //
    B = SplitArray2TwoEqualPart.solution1([2, 4, 6, 8, 1, 3, 5, 7]);
    console.log("Max value 1 : " + B.max + " group : " + B.res);

    B = SplitArray2TwoEqualPart.solution2([2, 4, 6, 8, 1, 3, 5, 7]);
    console.log("Max value 2 : " + B);

    B = SplitArray2TwoEqualPart.solution3([2, 4, 6, 8, 1, 3, 5, 7]);
    console.log("Max value 3 : " + B);

    
    B = CalculateTwoNumEqualToTarget.way1([2, 5, 17, 6, 7, 9, 1, 12], 9);
    console.log("Two number equal to 7 : " + B);

    let x = 2;
    let n = 5;
    console.log("2 ^ 5 is " + Math_power.way(2, 5));

    console.log("way2 2 ^ 5 is " + Math_power.way_binary(2, 5));

    console.log("way2 2 ^ 5 is " + Math_power.way2(2, 5));
        
    console.log("way2 2 ^ 5 is " + Math_power.way3(2, 5));

    console.log(" 4 is power of 4 is : " + Number_is_power_of_4.way(4));
    console.log(" 16 is power of 4 is : " + Number_is_power_of_4.way2(16));
    console.log(" 15 is power of 4 is : " + Number_is_power_of_4.way(15));


    console.log("Max value is " + Integer_Split_Max_Product.way(13));

    console.log(" 123321 equal Palodrome is " + Number_is_Palindrome.way(123321));


    console.log("Roman number is " + ConverRoman2Interger.Int2Roman(100));
    
    let obj = max_min.way([1, 2, 3, 4, 5, 6, 7, 8, 9]);
    console.log("Max is " + obj.max + " Min is " + obj.min);


    console.log("64 is power of 4 : " + is_Power_of_Four.way2(64));
    console.log("2147483648 is power of 4 " + is_Power_of_Four.way2(2147483648));
    console.log("-2147483648 is power of 4 " + is_Power_of_Four.way2(-2147483648));

    console.log("27 is a power of 3 : " + is_Power_of_Three.way(27));


    console.log("The number is " + convert_integer_to_string.atoi("123456789"));
    console.log("The number is " + convert_integer_to_string.atoi("-123456789"));


    console.log("addTwoNumber : " + addTwoNumbers([2, 4, 3], [5, 6, 4]));

    console.log("Factorial 25 is 15511210043330985984000000 Binary is ");
    console.log("Factorial_AmountOfZero 25 is : " + Factorial_AmountOfZero.way1(25));
    console.log("Factorial_AmountOfZero 25 is : " + Factorial_AmountOfZero.way2(25));

    console.log("Factorial_PosOfBinaryOne 25 is : " + Factorial_PosOfBinaryOne.way1(25));

    
    console.log("Factorial 6 is 720 Binary is 1011010000");
    console.log("Factorial_AmountOfZero 6 is : " + Factorial_AmountOfZero.way1(6));
    console.log("Factorial_AmountOfZero 6 is : " + Factorial_AmountOfZero.way2(6));
    console.log("Factorial_PosOfBinaryOne 6 is : " + Factorial_PosOfBinaryOne.way1(6));



    console.log("Amount of 1 is -------------");
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(8));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(10));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(16));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(20));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(21));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(100));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(101));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(121));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(165));
    console.log("the amount of number 1 is : " + NumberofDigit.numberOne(221));







    console.log("---------------------MathUtil.js End-----------------------")
}

exports.main = main;
