//
import ourtest from '../build/neopt_raw_lib.js';
import ourtestWasm from '../build/neopt_raw_lib.wasm';

//
export const mymodule = ourtest({
  locateFile(path) {
    if(path.endsWith('.wasm')) {
      return ourtestWasm;
    }
    return path;
  }
});

export const myfib = mymodule._fib;

export const myoutro = mymodule._myoutro;

export const myoutro_denovo = mymodule._myoutro_denovo;

export const cpp_myoutro_denovo2 = mymodule.cpp_myoutro_denovo2;

export const c_API_CreateSignatureRedeemScript = mymodule.cwrap('c_API_CreateSignatureRedeemScript', 'string', ['string']);

export const cpp_SmartContract_Contract_CreateSignatureRedeemScript = mymodule.cpp_SmartContract_Contract_CreateSignatureRedeemScript;


//export let hasInit = false;

let myFunc = function(){console.log("initialized wasm");};

export function myOnInit(f){
  myFunc = f;
};

mymodule.onRuntimeInitialized = () => {
  console.log(mymodule._fib(20));
  myFunc();
};



//export const Neo3 = require('../src/neopt-sdk/Neo3').Neo3; // THIS CRASHES!!
export const csbig = require('csbiginteger');
export const CryptoJS = require('crypto-js');
//const CppModule = require('../../build/neopt-lib-cpp-node/neopt-lib-cpp-node');
// Can't resolve 'env' in '/home/imcoelho/git-reps/neopt-sdk-js/build/neopt-lib-cpp-node'
//const cppFunc = require('../build/neopt-lib-cpp-node/neopt-lib-cpp-node').cpp_SmartContract_Contract_CreateSignatureRedeemScript;
//const cppFunc2 = require('../build/neopt-lib-cpp-node/neopt-lib-cpp-node').cpp_SmartContract_Contract_CreateSignatureRedeemScript2;


//module.exports = {
  //Neo3,
  //CppModule, // emscripten Module

  //CryptoJS,
  //myfib,
  
  //cppFunc, // function
  //cppFunc2, // function

  //csbig
//}


// THIS IS A ES6 MODULE... NO MORE 'module.exports' HERE!!!
// ONLY USE: 'export bla bla bla...'