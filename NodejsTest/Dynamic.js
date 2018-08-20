'use strict'



/***
 *  backpad { u1, u2, ..... Un}
 *  value {v1, v2, .... Vn}
 *  weight {S1, S2, ..... Sn}
 *  
 *  The Max value of all select backpad, also the Weight should be less then C
 * */
const ArrayGenerator = require('./ArrayGenetator.js');

function maxValue(a, b) {
    return a > b ? a : b;
}

function backpadIssueOrg(array, c) {
    
    const N = array.length;
    const C = c;
    
    let max = 0;
    let V = ArrayGenerator.generate2DArray(N + 1, C + 1);

    try {
        for (let i = 1; i < N + 1; i++) {
            for (let j = 1; j < C + 1; j++) {
                V[i][j] = V[i - 1][j];

                if (array[i - 1].C <= j) {
                    V[i][j] = maxValue(V[i -1][j], V[i - 1][j - array[i -1].C] + array[i - 1].val);
                }
            }
        }
    } catch (e) {
        console.log(e.message);
        return;
    }
    
    return V[N][C];
}


function backpadIssue(array, c) {

    const N = array.length;
    const C = c;
    
    let max = 0;
    let V = new Array(N + 1);

    for (let i = 0; i < N + 1; i++) {
        V[i] = new Array(N + 1);
        for (let j = 0; j < N + 1; j++) {
            V[i][j] = { C : 0, val : 0 };
        }
    }
    
    try {
        for (let i = 1; i < N + 1; i++) {
            for (let j = 1; j < i + 1; j++) {
                let value = 0;
                if (V[i - 1][j - 1].C + array[i - 1].C < C) {
                    V[i][j].val = maxValue(V[i - 1][j].val, V[i - 1][j - 1].val + array[i - 1].val);
                    
                    if (V[i - 1][j].val > V[i - 1][j - 1].val + array[i - 1].val) {
                        V[i][j].C = V[i - 1][j].C;
                    } else {
                        V[i][j].C = V[i - 1][j - 1].C + array[i - 1].C;
                    }
                } else {
                    V[i][j] = V[i - 1][j - 1];
                }
            }
        }
    } catch (e) {
        console.log(e.message);
        return;
    }

    return V[N][N];
}



function main() {

    let a = [
        { C : 2, val : 3 }, 
        { C : 5, val : 7 }, 
        { C : 4, val : 5 }, 
        { C : 3, val : 100 }
    ];

    let b = backpadIssue(a, 10);
    console.log(' the result is ' + (b.val, b.C));

    console.log("The biggest value is " + backpadIssueOrg(a, 10));
    
}

exports.main = main;