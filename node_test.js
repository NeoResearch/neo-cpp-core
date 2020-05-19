let lt = require('./build/librarytest');
// c function needs wrapping... cpp don't!
var myteststr = lt.cwrap('myteststr', 'string', ['string', 'number']);

// loading BigNum module
let lt_bn = require('./libs/lib/node_modules/bn.js/lib/bn.js');

lt['BN'] = lt_bn.BN; // "injecting" module

function testMain() {
    lt._mytest(5);
    var shello = 'hello';
    var str = myteststr(shello, shello.length);
    console.log(str);
    var str_cpp = lt.my_cpp_teststr("Hello World!");
    console.log(str_cpp);
}

// ----------- wait until loading ----------

setTimeout(function () {
    testMain()
}, 500);
