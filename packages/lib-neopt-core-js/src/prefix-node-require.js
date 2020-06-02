// Prefix-node.js for loading dependent libraries with backup
// this works for Node (CommonJS) versions (that have "require()")

let lt_csbn = require('csbiginteger');
let lt_cryptojs = require('crypto-js');

Module["csBN"] = lt_csbn.csBigInteger;
Module["CryptoJS"] = lt_cryptojs;

// helper modules

let csBN = Module['csBN'];


// ====================================
//         helper functions
// ------------------------------------
//
// ============ VANILLA JS =============
const toHexString = bytes =>
    bytes.reduce((str, byte) => str + byte.toString(16).padStart(2, '0'), '');


// ============ VANILLA JS =============
const fromHexString = hexString =>
    new Uint8Array(hexString.match(/.{1,2}/g).map(byte => parseInt(byte, 16)));

// ============ CommonJS (NodeJS) =============
//var vout = Uint8Array.from(Buffer.from(hex_out, 'hex'));
//

const fromUint8ArrayToList = function(uint8array)
{
    var lst1 = [];
    for (var i = 0; i < uint8array.length; i++)
      lst1.push(uint8array[i]);
    return lst1;
}

