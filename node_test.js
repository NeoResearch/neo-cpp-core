let lNeo3 = require('./build/librarytest');
// c function needs wrapping... cpp don't!
var myteststr = lNeo3.cwrap('myteststr', 'string', ['string', 'number']);

// loading BigNum module
let lt_bn = require('./libs/lib/node_modules/bn.js/lib/bn.js');

lNeo3['BN'] = lt_bn.BN; // "injecting" module

function testMain() {
    lNeo3._mytest(5);
    var shello = 'hello';
    var str = myteststr(shello, shello.length);
    console.log(str);
    var str_cpp = lNeo3.my_cpp_teststr("Hello World!");
    console.log(str_cpp);

    var pubKey = lNeo3.cpp_Util_GenerateVectorByte(8, 2);
    console.log(typeof(pubKey)); // console.log(
    //
    var vx = new lNeo3.vector$unsigned$char$();
    console.log(vx);
    vx.push_back(4);
    vx.push_back(5);
    
    pubKey.set(0, 50);

    var retVector = lNeo3.cpp_Contract_CreateSignatureRedeemScript(vx);
    console.log(retVector);
    for (var i = 0; i < retVector.size(); i++) {
        console.log("Vector Value: ", retVector.get(i));
    }
}

// ----------- wait until loading ----------

setTimeout(function () {
    testMain()
}, 500);
