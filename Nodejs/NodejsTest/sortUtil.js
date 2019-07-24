"use strict"

console.log("load sort utility");


class SortKit{
    
    constructor(ar, length) {
        this._array = ar;
        this._len = length;  
    }

    static binary_search(arr, n) {
        let low = 0;
        let high = arr.length;
        while (low < high) {
            let mid = (low + high) >> 1;
            if (arr[mid] == n)
                return mid;

            if (arr[mid] < n) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return -1;
    }

    static binary_search_split(arr, n, s, e) {
        if (s > e)
            return -1;

        let mid = (s + e) >> 1;
        if (arr[mid] == n)
            return mid;
    
        let ret;
        if (arr[mid] < n) {
            ret = SortKit.binary_search_split(arr, n, mid + 1, e);
        } else {
            ret = SortKit.binary_search_split(arr, n, s, mid - 1);
        }
        return ret;
    }

    static merge(a, st, mid, end){
        let ar = [];
        let s1 = st;
        let s2 = mid;

        while (s1 < mid && s2 < end) {
            if (a[s1] < a[s2]) {
                ar.push(a[s1]);
                s1 += 1;
            } else {
                ar.push(a[s2]);
                s2 += 1;
            }
        }

        if (s1 < mid) {
            while (s1 < mid) {
                ar.push(a[s1]);
                s1 += 1;
            }
        } else {
            while (s2 < end) {
                ar.push(a[s2]);
                s2 += 1;
            }
        }

        for (let j = 0; j < ar.length; j++) {
            a[j + st] = ar[j];
        }
    }

    mergeSort() {

        

        return this._array;
    }

    bubbleUpSort() {
        let maxLen = this._len;
        let done = false;

        while (!done) {
            maxLen--;
            done = true;
            for (let i = 0; i < maxLen; i++) {
                if (this._array[i] > this._array[i + 1]) {
                    let x = this._array[i];
                    this._array[i] = this._array[i + 1];
                    this._array[i + 1] = x;
                    done = false;
                }
            }
        }
        return this._array;
    }

    bottomUpSort() {    
        let s = 1;
        let maxLen = this._len;
        while (s < maxLen) {
            let t = 2 * s;
            let j = 0;
            while ( j + t < maxLen) {
                SortKit.merge(this._array, j, j + s, j + t);
                j += t;
            }
            
            if (j + s < maxLen) {
                SortKit.merge(this._array, j, j + s, maxLen);
            }
            s = t;
        }
        return this._array;
    }

    insertSort() {
        for (let i = 1; i < this._len; i++) {
            let curVal = this._array[i];
            let j = i - 1;
        
            while (j >= 0 && this._array[j] > curVal) {
                this._array[j + 1] = this._array[j];
                j = j - 1;
            }

            this._array[j + 1] = curVal;
        }
        return this._array;
    }

    selectSort() {

        for (let i = 0; i < this._len; i++) 
        {
            let min = this._array[i];
            let minIndex = i;
        
            for (let j = i; j < this._len; j++) {
                if (min > this._array[j]) {
                    min = this._array[j];
                    minIndex = j;
                }
            }
        
            let curVal = this._array[minIndex];
            this._array[minIndex] = this._array[i];
            this._array[i] = curVal;
        }
    
        return this._array;
    }

    quickSort() {
        SortKit.QUICK_SORT(this._array, 0, this._array.length);
    }

    static Radix_sort(a) {

        let len = a.length;
        let n = 1;
        let done = false;
        let result = a;
    
        let posNumber = function (a, b) {
            let A1 = a % b;
            let A2 = a % (b / 10);
            let A3 = A1 - A2;
            return A3 / (b / 10); 
        }

        while ( !done) {
            let basic = Math.pow(10, n++);
        
            let L = [];
            for (let i = 0; i < 10; i++)
                L.push([]);
        
            done = true;
            for (let i = 0; i < len; i++) {
                let res = posNumber(result[i], basic);
                L[res].push(result[i]);
                if (res != 0) {
                    done = false;
                }
            }
        
            let pos = 0;
            for (let i = 0; i < 10; i++)
                for (let j = 0; j < L[i].length; j++) {
                    result[pos++] = L[i][j];
                }
        }

        return result;
    }

    static SPLIT(A, low, high) {
        if (low > high || low >= A.length || high > A.length)
            return -1;
    
        let i = low;
        let X = A[low];
        let j = low + 1;
        for (j = low + 1; j < high; j++) {
            if (A[j] <= X) {
                i++;
                if (i != j) {
                    let y = A[i];
                    A[i] = A[j];
                    A[j] = y;
                }
            }
        }

        let y = A[low];
        A[low] = A[i];
        A[i] = y;
        return i;
    }


    static QUICK_SORT(A, low, high) {
        if (low < high) {
            let w = SortKit.SPLIT(A, low, high);
            SortKit.QUICK_SORT(A, low, w);
            SortKit.QUICK_SORT(A, w + 1, high);
        }
    }
};


function main() {

    let a = [2, 3, 71, 96, 32, 1, 9];
    let b = new SortKit(a, a.length).selectSort();
    console.log('insert sort : ' + b);

    let c = [2, 3, 71, 96, 32, 1, 9];
    b = new SortKit(c, c.length).insertSort();
    console.log('insert sort : ' + b);
    
    let f = [2, 3, 71, 96, 32, 1, 9];
    b = new SortKit(f, f.length).bubbleUpSort();
    console.log('Bubble up sort is : ' + b);

    let d = [2, 3, 71, 96, 32, 1, 9];
    b = new SortKit(d, d.length).bottomUpSort();
    console.log('insert sort : ' + b);

    let e = [2, 3, 71, 96, 32, 1, 9];
    b = new SortKit(e, e.length).bottomUpSort();
    console.log('insert sort : ' + b);

    // Typical Stack Sort
    const heapUtil = require('./heap.js');
    c = new heapUtil.Heap(a);
    d = [];
    while (c._arr.length != 0) {
        d.push(c.deleteMax(0));
    }
    console.log("d Array sequence is : " + d);

    //Radix_sort
    let input = [7467, 1247, 3275, 6792, 9187, 9134, 4675, 1239];
    console.log("Input is " + input);
    console.log("Sorted input result is " + SortKit.Radix_sort(input));

    f = [21, 4, 71, 3, 96, 32, 11, 9];
    let pos = SortKit.SPLIT(f, 0, f.length);
    console.log("Sort pos is " + pos + " result is " + f);
    
    let g = [21, 71, 3, 96, 32, 11, 9, 23];
    SortKit.QUICK_SORT(g, 0, g.length);
    console.log("Sort sequence is " + g);
    
    console.log("9 pos is " +　 SortKit.binary_search(g, 9));
    console.log("96 pos is " +　 SortKit.binary_search(g, 96));
    console.log("21 pos is " +　 SortKit.binary_search(g, 21));
    console.log("22 pos is " +　 SortKit.binary_search(g, 22));

    
    console.log("9 pos is " +　 SortKit.binary_search_split(g, 9, 0, g.length));
    console.log("96 pos is " +　 SortKit.binary_search_split(g, 96, 0, g.length));
    console.log("21 pos is " +　 SortKit.binary_search_split(g, 21, 0, g.length));
    console.log("22 pos is " +　 SortKit.binary_search_split(g, 22, 0, g.length));
    console.log("100 pos is " +　 SortKit.binary_search_split(g, 100, 0, g.length));
}


exports.main = main;
exports.sortKit = SortKit;