'use strict'

function main() {

    
    // Class instance
    class Complex {
        
        constructor(x, y) {
            this._x = x;
            this._y = y;
        }
        
        static distance(p1, p2) {
            let x = p1._x - p2._x;
            let y = p1._y - p2._y;
            return Math.sqrt(x * x + y * y);
        }
        
        get areaX() {
            return this._x;
        }
        
        get areaY() {
            return this._y;
        }
        
        calcMod() {
            return Math.sqrt(this._x * this._x + this._y * this._y);
        }
    }
    
    
    var num1 = new Complex(2, 3);
    var num2 = new Complex(3, 2);
    
    console.log('num1 mode X is ' + num1.areaX + " Y is " + num1.areaY + " _x is " + num1._x + " and _y is " + num1._y);
    console.log('num1 mode is ' + num1.calcMod());
    console.log('num1 distance is ' + Complex.distance(num1, num2));
    
    // Class extend instance
    class Point extends Complex {
        
        constructor(x, y) {
        super(x, y)
    }
        
        get geoArea() {
            var area = 1;
            if (super._x > 0) {
                return super._y > 0 ? 1 : 4;
            } else {
                return super._y > 0 ? 2 : 3;
            }
        }
    }
    
    var point1 = new Point(2, -3);
    console.log('point1 mode X is ' + point1.areaX + " Y is " + point1.areaY);
    console.log('point1 mode is ' + point1.calcMod());
    console.log('point1 getArea is ' + point1.geoArea);
    
    // Typed arrays
    var buffer = new ArrayBuffer(16)
    console.log("buffer length is " + buffer.length);
    
    var int32view = new Int32Array(buffer);
    for (var i = 0; i < int32view.length; i++) {
        int32view[i] = i * 2;
    }
    
    var int16view = new Int16Array(buffer);
    for (let i = 0; i < int16view.length; i++) {
        console.log("   " + int16view[i]);
    }
    
    var buffer1 = new ArrayBuffer(24)
    var idview = new Uint32Array(buffer1, 0, 1);
    var usernameview = new Uint8Array(buffer1, 4, 16);
    var amountview = new Float32Array(buffer1, 20, 1);
    
    
    
    // Generator
    function* idMaker(i) {
        var index = 0;
        while (index < i) {
            yield index++;
        }
    }
    
    var gen = idMaker(3);
    
    console.log("generator " + gen.next().value);
    console.log("generator " + gen.next().value);
    console.log("generator " + gen.next().value);
    console.log("generator " + gen.next().value);
    
    function* anotherIdMaker(i) {
        
        yield i + 3;
        yield* idMaker(3);
        yield i + 2;
        yield i + 1;
        yield i;
    }
    
    var anotherGen = anotherIdMaker(3);
    
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    console.log("another id Maker " + anotherGen.next().value);
    
    
    // Promise case
    
    function $Http(URL) {
        
        var core = {
            
            ajax : function (method, URL, arg) {
                
                var pro = new Promise(function (resolve, reject) {
                    var client = new XMLHttpRequest();
                    var uri = URL;
                    
                    if (arg && method == 'post' || method == 'put') {
                    
                    }
                    
                    client.open(method, uri);
                    client.send();
                    
                    client.onload = function () {
                        if (this.status >= 200 && this.status < 300) {
                            resolve(this.response);
                        } else {
                            reject(this.response);
                        }
                    };
                    
                    client.onerror = function () {
                        reject(this.response);
                    };
                });
                
                return pro;
            }
        }
        
        return {
            'get' : function (arg) {
                return core.ajax('GET', url, arg);
            },
            'post' : function (args) {
                return core.ajax('POST', url, arg);
            },
            'put' : function (args) {
                return core.ajax('PUT', url, arg);
            },
            'delete' : function (args) {
                return core.ajax('DELETE', url, arg)
            }
        };
    };
    
    var callback = {
        
        success : function (data) {
            console.log("callback success " + JSON.parse(data));
        },
        
        error : function (data) {
            console.log("call back error " + JSON.parse(data));
        }
    };
    
    
    var url = 'http://www.google.com';
    
    $Http(url).get().then(callback.success).catch(callback.error);
    
    $Http(url).get().then(callback.success, callback.error);
    
    $Http(url).get().then(callback.success).then(undefined, callback.error);
    
    
    
    // Symbol
    var sym1 = Symbol();
    var sym2 = Symbol("foo");
    var sym3 = Symbol("foo");
    
    console.log("Sym2 == Sym3 is " + (sym2 == sym3));
    
    var sym4 = Object(sym3);
    console.log(" sym3 type is " + typeof sym3);
    console.log(" sym4 type is " + typeof sym4);
    
    //template string
    
    console.log('Content will connect to the next line');
    
    var a = 5;
    var b = 10;
    
    console.log(' 5 + 10 = ${a + b}  and\nnot ${2* a + b}');
    
    
    // Arrow function
    var a = ["Hydrogen", "Helium", "Lithium", "Beryllium"];
    var a2 = a.map(function (s) {
        return s.length
    });
    
    var a3 = a.map(s=> s.length);

console.log('a2 is ' + a2);
console.log( 'a3 is ' + a3);

var addr = {

base : 1,

add: function(a) {
var f = v => v + this.base;
return f(a);
},

addThurCall : function (a) {
var f = v => v + this.base;
var obj = {
base : 3
}

return f.call(obj, a);
}
};

console.log(' a1 is ' + addr.add(1));
console.log(' a2 is ' + addr.add(1));


try {
// Object assignment
var obj = {i : 1}
var objNew = Object.assign({}, obj);
//console.log(objNew);

var obj1 = {a : 1};
var obj2 = {b : 1};
var obj3 = {c : 3};

var objNew1 = Object.assign(obj1, obj2, obj3);
//console.log(objNew1);
} catch (e) {
console.log(" error: " + e.message);
}



var v1 = 123;
var v2 = true;
var v3 = 10;
var v4 = Symbol("foo")

var objCom = Object.assign({}, v1, null, v2, undefined, v3, v4);
//console.log(objCom)

// new.target
// It has ref with 'new' calling, or it holds a 'undefined'

function foo() {
if (!new.target) throw "error";
console.log("Foo Initiated with new : " + new.target.name);
}

new foo();
try {
foo()
} catch(e) {
console.log(e.msg)
}

//Spread operator
function myFun(a, b, c) {
console.log(a);
console.log(b);
console.log(c);
}

var org = [1, 2, 3];
//myFun(org);
myFun.apply(null, org);
// With 'Spread'
myFun(...org);

function myFun2(x, y, z, j, m, n) {
console.log(x);
console.log(y);
console.log(z);
console.log(j);
console.log(m);
console.log(n);
}

var org1 = [1, 2]
myFun2(0, ...org1, 3, ...[4, 5]);


var org2 = [-2, -1];
var org3 = [...org2, 1, 2, ...[3, 4]]
console.log(org3);

// Map
var myMap = new Map();
var keyString = "a string",
keyObj = {},
keyfunc = function () {};

myMap.set(keyString, "first string");
myMap.set(keyObj, "send string");
myMap.set(keyfunc, "third string");

console.log("size is " + myMap.size);

console.log("1st is " + myMap.get(keyString));
console.log("2nd is " + myMap.get(keyObj));
console.log("3rd is " + myMap.get(keyfunc));

console.log("1st is " + myMap.get("a string"));  // keyString === 'a string'
console.log("2nd is " + myMap.get({}));  // undefined, because keyObj != {}
console.log("3rd is " + myMap.get(function(){})); //undefined

myMap.set(NaN, "not a number");
console.log("4th is " + myMap.get(NaN));
var otherNum = Number('foo');
console.log("4th is 'foo' " + myMap.get(otherNum));

// Map 2



// HTTP server
//var http = require('http');

//http.createServer(function (request, response) {
//    try {
//        response.writeHead(200, {'Content-Type': 'text/plain'});
//        response.end('Hello World \n');
//    } catch (e) {
//        console.log(e.msg);
//    }

//}).listen(8080);

console.log('Create HTTP server done!');
}

exports.main = main;