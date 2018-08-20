'use strict'


class Heap {

    constructor(arr) {
        this._arr = [];
        //this.make_stack(arr);
        for (let i = 0; i < arr.length; i++) {
            this._arr.push(arr[i]);
        }
        this.make_heap();
    }

    /**
     *  n*log(n)
    **/
    make_stack(arr) {
        for (let i = 0; i < arr.length; i++) {
            this.insert(arr[i]);
        }
    }

    /**
     *  O(n)
    **/
    make_heap() {
        let len = this._arr.length >> 1;
        for (let i = len + 1; i >= 0; i--) {
            this.sift_down(i);
        }
    }

    sift_down(i) {

        let length = this._arr.length;
        if (2 * i + 1 > length - 1)
            return;
    
        let left_index = 2 * i + 1;
        let right_index = 2 * i + 2;
        let done = false;
        while (!done && left_index < length) {

            let pos = -1;
            if (right_index < length && this._arr[left_index] < this._arr[right_index]) {
                pos = right_index;
            } else {
                pos = left_index;
            }

            if (this._arr[i] > this._arr[pos]) {
                done = true;
                continue;
            }

            let x = this._arr[pos];
            this._arr[pos] = this._arr[i];
            this._arr[i] = x
        
            i = pos;
            left_index = 2 * i + 1;
            right_index = 2 * i + 2;
        }
     
    }

    sift_up(i) {
        let parentPos = i >> 1;
        let done = false;

        while (!done) {
            if (this._arr[parentPos] < this._arr[i]) {
                let x = this._arr[i];
                this._arr[i] = this._arr[parentPos];
                this._arr[parentPos] = x;
                
                i = parentPos;
                parentPos = i >> 1;
            } else {
                done = true;
            }
        }
    }

    insert(a) {
        let len = this._arr.length;
        this._arr.push(a);
        this.sift_up(len);
    }

    remove (i) {
        let length = this._arr.length;
        if (i < 0 || i > length - 1)
            return;

        let x = this._arr[i];
        this._arr[i] = this._arr[length - 1];
        this._arr[length - 1] = x;
        this._arr.pop();
    
        if (this._arr[i] > x) {
            this.sift_up(i);
        } else {
            this.sift_down(i);
        }
    }

    deleteMax() {
        let x = this._arr[0];
        this.remove(0);
        return x;
    }
}

function main() {

    let a = [8, 19, 6, 34, 25, 7, 13, 16];
    console.log("Array to Heap is " + a);
    let b = new Heap(a);
    console.log("Heap is " + b._arr);

    b.remove(0);
    console.log("Heap is " + b._arr);
    
    let len = b._arr.length;
    b._arr[len - 1] = 100;
    b.sift_up(len - 1);
    console.log("Last one is 100, then Heap becomes : " + b._arr);


    // Typical Stack Sort
    a = [8, 19, 6, 34, 25, 7, 13, 16];
    let c = new Heap(a);
    let d = [];
    while (c._arr.length != 0) {
        d.push(c.deleteMax(0));
    }
    console.log("d Array sequence is : " + d);
}


exports.main = main;
exports.Heap = Heap;