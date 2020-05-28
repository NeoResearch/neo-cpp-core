let libModuleNeo3 = require('./build/librarytest');
// c function needs wrapping... cpp don't!
var myteststr = libModuleNeo3.cwrap('myteststr', 'string', ['string', 'number']);

let c_API_CreateSignatureRedeemScript = libModuleNeo3.cwrap('c_API_CreateSignatureRedeemScript', 'string', ['string'])

/*
// loading BigNum module
let lt_bn = require('./libs/lib/node_modules/bn.js/lib/bn.js');
let lt_csbn = require('./libs/lib/node_modules/csBigInteger.js/csBigInteger.js');
let lt_cryptojs = require('./libs/lib/node_modules/crypto-js/crypto-js.js');

lNeo3['BN'] = lt_bn.BN; // "injecting" module
lNeo3['csBN'] = lt_csbn.csBigInteger;
lNeo3['CryptoJS'] = lt_cryptojs;

let csBN = lt_csbn.csBigInteger;
*/

function testMain() {
    console.log(" ======== testMain() ====== ");
    /*
    lNeo3._mytest(5);
    console.log("");
    console.log(" ------- will test string ---- ");
    var shello = 'hello';
    var str = myteststr(shello, shello.length);
    console.log(str);
    var str_cpp = lNeo3.my_cpp_teststr("Hello World!");
    console.log(str_cpp);
    console.log("");
    console.log("");
    console.log("");
    var pubKey = lNeo3.cpp_Util_GenerateVectorByte(8, 2);
    console.log(typeof(pubKey)); // console.log(
    //
    console.log(" ======= begin testing csBigInteger.js ======= ");
    var x = new csBN(1000);
    console.log(x.toByteArray());
    console.log(" ======= end testing csBigInteger.js ======= ");
    */
    // =============
    console.log("");
    console.log("experimenting with ECPoint");
    console.log("");
    //
 
    var vx = new libModuleNeo3.csBN("43563478194357645732161043749214420341576583724275881899443933055754116882936", 10);
    var vy = new libModuleNeo3.csBN("6800198406926458502571476951697947402787919362010374841430910815761615021861", 10);
    //console.log(vx);
    //console.log(vy);
    var ecpoint = {
        "X" : vx.toHexString(),
        "Y" : vy.toHexString(),
        "curve" : "secp256r1"
    };
    var strJson = JSON.stringify(ecpoint);
    console.log("json str point: "+strJson);
    var vout = c_API_CreateSignatureRedeemScript(strJson);
    console.log(vout);

}

// ----------- wait until loading ----------

setTimeout(function () {
    testMain()
}, 500);
