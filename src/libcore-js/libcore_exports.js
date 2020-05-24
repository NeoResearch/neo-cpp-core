mergeInto(
  LibraryManager.library, {
  mycrypto: function (vint) {
    //alert('mycrypto(value='+vint+')');
    console.log('mycrypto print: ' + vint);
    return vint + 1;
  },
  bignum_add: function (ptr_str1, ptr_str2, ptr_str_out) {
    // 'Pointer_stringify' is deprecated... now use 'UTF8ToString'
    vstr1 = Module.UTF8ToString(ptr_str1);
    vstr2 = Module.UTF8ToString(ptr_str2);
    // TODO: AsciiToString ??
    // https://emscripten.org/docs/api_reference/preamble.js.html

    console.log("js bignum_add: " + vstr1 + " " + vstr2);

    //console.log("printing Module['BN']:");
    //console.log(Module['BN']);
    let BN = Module['BN'];

    // exporting some other function... testing..
    Module['mytestf'] = function () {
      console.log("oi");
    };
    //console.log(BN);
    var b1 = new BN(vstr1);
    var b2 = new BN(vstr2);
    var b3 = b1.add(b2);
    var rstr = b3.toString(10);
    console.log("b3=" + rstr);

    console.log("requires some bytes: " + lengthBytesUTF8(rstr));
    console.log("out space is '" + Module.UTF8ToString(ptr_str_out) + "'");
    //ptr_str_out = rstr;
    stringToUTF8(rstr, ptr_str_out, rstr.length + 1);
    //Module.writeStringToMemory(rstr, ptr_str_out); // DEPRECATED!! But stringToUTF8 is not working...
    console.log("out space is '" + Module.UTF8ToString(ptr_str_out) + "'");
    //stringToUTF8(rstr, ptr_str_out);
    //////return ptr; // string
    // NO RETURN... pass by parameter 'ptr_str_out'
    return lengthBytesUTF8(rstr);
  },
  csbiginteger_gt: function (ptr1, sz1, ptr2, sz2) {
    // inputs are pre-allocated
    //console.log("csbiginteger_gt ptr1="+ptr1+ " sz1="+sz1+ " ptr2="+ptr2+ " sz2="+sz2);
    //
    let csBN = Module['csBN'];
    var v1 = Module.HEAPU8.subarray(ptr1, ptr1 + sz1);
    var v2 = Module.HEAPU8.subarray(ptr2, ptr2 + sz2);
    //
    var lst1 = [];
    for (var i = 0; i < sz1; i++)
      lst1.push(v1[i]);
    var big1 = new csBN(lst1);
    var big1bn = big1.asBN();
    //
    var lst2 = [];
    for (var i = 0; i < sz2; i++)
      lst2.push(v2[i]);
    var big2 = new csBN(lst2);
    var big2bn = big2.asBN();
    //
    return big1bn.gt(big2bn);
  },
  csbiginteger_lt: function (ptr1, sz1, ptr2, sz2) {
    // inputs are pre-allocated
    //console.log("csbiginteger_gt ptr1="+ptr1+ " sz1="+sz1+ " ptr2="+ptr2+ " sz2="+sz2);
    //
    let csBN = Module['csBN'];
    var v1 = Module.HEAPU8.subarray(ptr1, ptr1 + sz1);
    var v2 = Module.HEAPU8.subarray(ptr2, ptr2 + sz2);
    //
    var lst1 = [];
    for (var i = 0; i < sz1; i++)
      lst1.push(v1[i]);
    var big1 = new csBN(lst1);
    var big1bn = big1.asBN();
    //
    var lst2 = [];
    for (var i = 0; i < sz2; i++)
      lst2.push(v2[i]);
    var big2 = new csBN(lst2);
    var big2bn = big2.asBN();
    //
    return big1bn.lt(big2bn);
  },
  csbiginteger_init_s: function (str_val, int_base, ptr_out, sz_out) {
    // inputs are pre-allocated
    var vstr1 = Module.UTF8ToString(str_val);
    let csBN = Module['csBN'];
    var big1 = new csBN(vstr1, int_base);
    //console.log("csbiginteger_init_s str='"+vstr1+"' base="+int_base+ " ptr_out="+ptr_out+ " sz_out"+sz_out);
    //console.log(big1.toString());
    //
    var barray = big1.toByteArray();
    const myUint8Array = new Uint8Array(barray);
    //console.log(barray);
    //console.log(myUint8Array);
    //console.log("barray length = "+barray.length+ " myUint8Array length =" + myUint8Array.length);
    //console.log("will malloc");
    //const buffer = Module._malloc(myUint8Array.length);
    //console.log("will set");
    Module.HEAPU8.set(myUint8Array, ptr_out);
    //Module.HEAPU8.set(myUint8Array, buffer); // to test
    //console.log(Module.HEAPU8.subarray(ptr_out, ptr_out+myUint8Array.length));
    //console.log("will free");
    //Module._free(buffer);

    // returns 'real' size for out...
    return barray.length;
  },
  // perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
  // cs_int32 csbiginteger_mod(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);
  csbiginteger_mod: function (ptr1, sz1, ptr2, sz2, ptr_out, sz_out) {
    // inputs are pre-allocated
    let csBN = Module['csBN'];
    //
    var v1 = Module.HEAPU8.subarray(ptr1, ptr1 + sz1);
    var v2 = Module.HEAPU8.subarray(ptr2, ptr2 + sz2);
    //
    var lst1 = [];
    for (var i = 0; i < sz1; i++)
      lst1.push(v1[i]);
    var big1 = new csBN(lst1);
    var big1bn = big1.asBN();
    //
    var lst2 = [];
    for (var i = 0; i < sz2; i++)
      lst2.push(v2[i]);
    var big2 = new csBN(lst2);
    var big2bn = big2.asBN();
    //
    console.log("csbiginteger_mod big1='" + big1.toString(10) + "' big2='" + big1.toString(10) + "' -> ");
    // ====== perform operation ======
    var big3bn = big1bn.mod(big2bn);
    //
    var big3 = new csBN(big3bn);
    console.log("big3 ='" + big3.toString(10) + "'");
    var barray = big3.toByteArray();
    const myUint8Array = new Uint8Array(barray);
    Module.HEAPU8.set(myUint8Array, ptr_out);

    // returns 'real' size for out...
    return barray.length;
  },
  external_sha256: function (ptr1, sz1, ptr_out, sz_out) {
    let CryptoJS = Module['CryptoJS'];
    //
    var v1 = Module.HEAPU8.subarray(ptr1, ptr1 + sz1);
    //
    // helper function
    const toHexString = bytes =>
      bytes.reduce((str, byte) => str + byte.toString(16).padStart(2, '0'), '');
    //
    //console.log("SHA256 v1 = "+v1);
    //
    var hexv1 = toHexString(v1);
    //
    //console.log("SHA256 hexv1 = "+hexv1);
    //
    var hexEnc1 = CryptoJS.enc.Hex.parse(hexv1);
    //
    //console.log("SHA256 hexEnc1 = "+hexEnc1);
    //
    var outEnc1 = CryptoJS.SHA256(hexEnc1);
    //
    //console.log("SHA256 outEnc1 = "+outEnc1);
    //
    // MAYBE THIS IS USEFUL ON WEB PLATFORMS (NON-NODE)
    const fromHexString = hexString =>
      new Uint8Array(hexString.match(/.{1,2}/g).map(byte => parseInt(byte, 16)));
    //
    var hex_out = CryptoJS.enc.Hex.stringify(outEnc1);
    //
    var vout = Uint8Array.from(Buffer.from(hex_out, 'hex'));
    //var vout = fromHexString(outEnc1);
    //
    //console.log("SHA256 vout = "+vout);
    Module.HEAPU8.set(vout, ptr_out); // TODO: test 'sz_out' for size checks

    //var v2 = Module.HEAPU8.subarray(ptr2, ptr2+sz2);

    //console.log("WARNING: EMPTY FUNCTION 'external_sha256' on licore_exports.js");
    return vout.length;
  }
}
);
//
// ==================================================================================
// TODO: we may need to implement more of these BigInteger functions... wait to see!
// ==================================================================================
/*

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_init_empty(cs_byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_init_i(cs_int32 value, cs_byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_init_l(cs_int64 value, cs_byte* vr, int sz_vr);

// initialize big integer and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_init_s(char* value, cs_int32 base, cs_byte* vr, int sz_vr);

// ================
// auxiliar methods
// ================

// ToString(base). input vb and output sr must be pre-allocated (return indicates failure, 'true' is fine)
extern "C" bool
csbiginteger_to_string(cs_byte* vb, int sz_vb, int base, char* sr, int sz_sr);

// toInt(). input vb must be pre-allocated
extern "C" int
csbiginteger_to_int(cs_byte* vb, int sz_vb);

// toLong(). input vb must be pre-allocated
extern "C" long
csbiginteger_to_long(cs_byte* vb, int sz_vb);

// =======================
// csbiginteger operations
// =======================

// perform big1 == big2
extern "C" bool
csbiginteger_eq(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2);

// perform big1 > big2
extern "C" bool
csbiginteger_gt(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2);

// perform big1 < big2
extern "C" bool
csbiginteger_lt(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2);

// ------------------- arithmetic ---------------------

// perform big1 + big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_add(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 - big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_sub(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 * big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_mul(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 / big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_div(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 % big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_mod(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 >> big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_shr(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big1 << big2 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_shl(cs_byte* big1, int sz_big1, cs_byte* big2, int sz_big2, cs_byte* vr, int sz_vr);

// perform big ^ int32 and return its size (in bytes). output vr must be pre-allocated
extern "C" cs_int32
csbiginteger_pow(cs_byte* big, int sz_big, int exp, cs_byte* vr, int sz_vr);
*/