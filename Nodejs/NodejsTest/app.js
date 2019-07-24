"use strict"
console.log('Hello world');


function main() {

    // Call Sort Util js module
    try {
        const sortUtil = require('./sortUtil.js');
        sortUtil.main();
   
        let a = new sortUtil.sortKit([2, 1], 2);
        console.log(a.selectSort());
    } catch (e) {
        console.log('get error : ' + e.message)
    }


    // test SyntaxTest.js
    try {
        const syntaxTest = require('./SyntaxTest.js');
        syntaxTest.main();
    } catch (e) {
        console.log('get error : ' + e.message);
    }
    
    // test stringUtil.js
    try {
        const stringUtil = require('./stringUtil.js');
        stringUtil.main();
    } catch (e) {
        console.log('get error ' + e.message);
    }
    
    
    try {
        const bitOps = require('./bitOps.js');
        bitOps.main();
    } catch (e) {
        console.log('get error' + e.message);
    }

    try {
        const back_tracking = require('./back_tracking.js');
        back_tracking.main();
    } catch (e) {
        console.log('get error' + e.message);
    }

    try {
        const mathUtil = require('./MathUtil.js');
        mathUtil.main();
    } catch (e) {
        console.log('get error ' + e.message);
    }

    try {
        const Dynamic = require('./Dynamic.js');
        Dynamic.main();
    } catch (e) {
        console.log('get error ' + e.message);
    }

    try {
        const Stack = require('./heap.js');
        Stack.main()
    } catch (e) {
        console.log('get error ' + e.message);
    }
    
    try {
        const Tree = require('./TreeUtil.js');
        Tree.main();
    } catch (e) {
        console.log('get error ' + e.message);
    }

    try {
        const backpack = require('./greedyAlgorithms.js');
        backpack.main();
    } catch (e) {
        console.log('get error ' + e.message);
    }
}

main();

