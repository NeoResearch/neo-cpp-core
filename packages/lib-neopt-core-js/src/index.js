//
import ourtest from '../build/neopt_raw_lib.js';
import ourtestWasm from '../build/neopt_raw_lib.wasm';

// advice from gist (fibonacci example)
export const mymodule = ourtest({
  locateFile(path) {
    if (path.endsWith('.wasm')) {
      return ourtestWasm;
    }
    return path;
  }
});

// =====================================================
// initialization callback (do we need this?)
// -----------------------------------------------------

let myFunc = function () { console.log("initialized wasm"); };

export function myOnInit(f) {
  myFunc = f;
};

mymodule.onRuntimeInitialized = () => {
  myFunc();
};

// =====================================================
//             exported dependencies
// -----------------------------------------------------

export const csbiginteger = require('csbiginteger');
export const CryptoJS = require('crypto-js');

// =====================================================
//                 exported functions 
// -----------------------------------------------------

export const Neo3_SmartContract_Contract_CreateSignatureRedeemScript =
  mymodule.cwrap('Neo3_SmartContract_Contract_CreateSignatureRedeemScript', 'string', ['string']);


// ------ finished