// Prefix-node.js for loading dependent libraries with backup
// this works for Node (CommonJS) versions (that have "require()")
/*
define(function() {
    return function(Module) {
        */

let lt_csbn = require('csbiginteger');
let lt_cryptojs = require('crypto-js');

Module["csBN"] = lt_csbn.csBigInteger;
Module["CryptoJS"] = lt_cryptojs;