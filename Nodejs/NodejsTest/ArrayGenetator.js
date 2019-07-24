'use strict'


function maxValue(a, b) {
    return a > b ? a : b;
}

function generate2DArray(d1, d2) {

    let a = new Array(d1);
    for (let i = 0; i < d1; i++) {
        a[i] = new Array(d2);
        for (let j = 0; j < d2; j++) {
            a[i][j] = 0;
        }
    }
    return a;
}

function generate3DArray(d1, d2, d3) {
    
    let a = new Array(d1);
    for (let i = 0; i < d1; i++) {
        a[i] = new Array(d2);
        for (let j = 0; j < d2; j++) {
            a[i][j] = new Array(d3);
            for (let z = 0; z < d3; z++) {
                a[i][j][z] = 0
            }
        }
    }
    return a;
}


function main() {

}

exports.generate3DArray = generate3DArray;
exports.generate2DArray = generate2DArray;
exports.main = main;