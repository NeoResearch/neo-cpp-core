// https://github.com/indutny/bn.js/
//
let lt = require('./build/librarytest');
//
let lt_bn = require('./libs/lib/node_modules/bn.js/lib/bn.js');
let BN = lt_bn.BN;
//
let lt_csbn = require('./libs/lib/node_modules/csBigInteger.js/csBigInteger.js');
let csBN = lt_csbn.csBigInteger;
lt['csBN'] = lt_csbn.csBigInteger;



//
var b = new BN('101010', 2);
console.log(b.toString(10));

var big1 = new BN(1);

var big2 = new BN('123123123');
var big3 = big2.add(big1);
console.log(big3.toString(10));
