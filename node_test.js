let lNeo3 = require('./build/librarytest');
// c function needs wrapping... cpp don't!
var myteststr = lNeo3.cwrap('myteststr', 'string', ['string', 'number']);

// loading BigNum module
let lt_bn = require('./libs/lib/node_modules/bn.js/lib/bn.js');
let lt_csbn = require('./libs/lib/node_modules/csBigInteger.js/csBigInteger.js');
lNeo3['BN'] = lt_bn.BN; // "injecting" module
lNeo3['csBN'] = lt_csbn.csBigInteger;

let csBN = lt_csbn.csBigInteger;


function testMain() {
    console.log(" ======== testMain() ====== ");
    lNeo3._mytest(5);
    console.log("");
    console.log(" ------- will test string ---- ");
    var shello = 'hello';
    var str = myteststr(shello, shello.length);
    console.log(str);
    var str_cpp = lNeo3.my_cpp_teststr("Hello World!");
    console.log(str_cpp);
    console.log("");
    var str_cpp2 = lNeo3.cpp_Contract_cpp_teststr("Hello World!");
    console.log(str_cpp2);
    console.log("");
    console.log("");
    var pubKey = lNeo3.cpp_Util_GenerateVectorByte(8, 2);
    console.log(typeof(pubKey)); // console.log(
    //
    var vx = new lNeo3.vector$unsigned$char$();
    console.log(vx);
    vx.push_back(4);
    vx.push_back(5);
    
    pubKey.set(0, 50);

    console.log(" ----> testing cpp_Contract_CreateSignatureRedeemScript_Fake");
    var retVector = lNeo3.cpp_Contract_CreateSignatureRedeemScript_Fake(vx);
    console.log(retVector);
    for (var i = 0; i < retVector.size(); i++) {
        console.log("Vector Value: ", retVector.get(i));
    }

    console.log(" ----> testing cpp_gen_xy");
    var ret_point_xy = lNeo3.cpp_gen_xy();
    console.log(ret_point_xy);
    console.log(" ----> testing cpp_Contract_CreateSignatureRedeemScript_XY");
    var retVector = lNeo3.cpp_Contract_CreateSignatureRedeemScript_XY(ret_point_xy);
    console.log(retVector);
    for (var i = 0; i < retVector.size(); i++) {
        console.log("Vector Value: ", retVector.get(i));
    }

    console.log(" ----> testing cpp_gen_xy2");
    var ret_point_xy2 = lNeo3.cpp_gen_xy2();
    console.log(ret_point_xy2);
    console.log(" ----> testing cpp_Contract_CreateSignatureRedeemScript_XY2");
    var retVector2 = lNeo3.cpp_Contract_CreateSignatureRedeemScript_XY2(ret_point_xy2);
    console.log(retVector2);
    for (var i = 0; i < retVector2.size(); i++) {
        console.log("Vector2 Value: ", retVector2.get(i));
    }

    console.log(" ======= begin testing csBigInteger.js ======= ");
    var x = new csBN(1000);
    console.log(x.toByteArray());
    console.log(" ======= end testing csBigInteger.js ======= ");

    // =============
    console.log("");
    console.log("experimenting with ECPoint");
    console.log("");
    //
    var vx = new csBN("43563478194357645732161043749214420341576583724275881899443933055754116882936", 10);
    var vy = new csBN("6800198406926458502571476951697947402787919362010374841430910815761615021861", 10);

    var ecpoint = {
        "X" : vx.toHexString(),
        "Y" : vx.toHexString(),
        "curve" : "secp256r1"
    };
    var strJson = JSON.stringify(ecpoint);
    console.log("json str point: "+strJson);
    var vout = lNeo3.cpp_SmartContract_Contract_CreateSignatureRedeemScript("{}");
    console.log(vout);

}

// ----------- wait until loading ----------

setTimeout(function () {
    testMain()
}, 500);
