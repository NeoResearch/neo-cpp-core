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
      //stringToUTF8(rstr, ptr_str_out);
      Module.writeStringToMemory(rstr, ptr_str_out);
      console.log("out space is '"+Module.UTF8ToString(ptr_str_out)+"'");
      //stringToUTF8(rstr, ptr_str_out);
      //////return ptr; // string
      // NO RETURN... pass by parameter 'ptr_str_out'
      return lengthBytesUTF8(rstr);
    }
  }
);