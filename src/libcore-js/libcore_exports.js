mergeInto(
  LibraryManager.library, {
    mycrypto: function(vint) {
      //alert('mycrypto(value='+vint+')');
      console.log('mycrypto print: ' + vint);
      return vint+1;
    },
    bignum_add: function(ptr_str1, ptr_str2, ptr_str_out) {
      // 'Pointer_stringify' is deprecated... now use 'UTF8ToString'
      vstr1 = Module.UTF8ToString(ptr_str1);
      vstr2 = Module.UTF8ToString(ptr_str2);
      // TODO: AsciiToString ??
      // https://emscripten.org/docs/api_reference/preamble.js.html

      console.log("js bignum_add: "+vstr1+" "+vstr2);

      //console.log("printing Module['BN']:");
      //console.log(Module['BN']);
      let BN = Module['BN'];
      
      // exporting some other function... testing..
      Module['mytestf'] = function(){
        console.log("oi");
      };
      //console.log(BN);
      var b1 = new BN(vstr1);
      var b2 = new BN(vstr2);
      var b3 = b1.add(b2);
      var rstr = b3.toString(10);
      console.log("b3="+rstr);
      
      console.log("requires some bytes: "+ lengthBytesUTF8(rstr));
      console.log("out space is '"+Module.UTF8ToString(ptr_str_out)+"'");
      //ptr_str_out = rstr;
      stringToUTF8(rstr, ptr_str_out, rstr.length + 1);
      //Module.writeStringToMemory(rstr, ptr_str_out); // DEPRECATED!! But stringToUTF8 is not working...
      console.log("out space is '"+Module.UTF8ToString(ptr_str_out)+"'");
      //stringToUTF8(rstr, ptr_str_out);
      //////return ptr; // string
      // NO RETURN... pass by parameter 'ptr_str_out'
      return lengthBytesUTF8(rstr);
    }
  }
);


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